#pragma once

#include <chrono>
#include <condition_variable>
#include <logger.hh>
#include <mutex>
#include <queue>

template <typename DataType>
class SharedQueue {
public:
    explicit SharedQueue(size_t max_size) : m_max_size(max_size){};
    ~SharedQueue() = default;

    bool Enqueue(const DataType &data) {
        bool ret = true;
        std::lock_guard lock(m_mutex);

        if (m_queue.size() < m_max_size) {
            m_queue.push(data);
            m_cond_var.notify_one();
            ret = true;
        } else {
            ret = false;
            LOG_DEBUG("Trying to write new data but queue is full");
        }

        return ret;
    }

    std::optional<DataType> Dequeue(uint32_t timeout_ms = 0) {
        std::unique_lock ulock(m_mutex);
        std::optional<DataType> result;
        std::cv_status status = std::cv_status::no_timeout;

        if (m_queue.size() == 0) {
            // Wait for a single timeout if timeout_ms argument is different from zero
            // else wait until there is some data in the queue
            if (timeout_ms != 0) {
                status = m_cond_var.wait_for(ulock, std::chrono::milliseconds(timeout_ms));
            } else {
                do {
                    status = m_cond_var.wait_for(ulock, std::chrono::milliseconds(100));
                } while (m_queue.size() == 0);
            }
        }

        if (status != std::cv_status::timeout) {
            result = std::optional<DataType>(m_queue.front());
            m_queue.pop();
        }

        return result;
    }

    bool Full() const {
        std::lock_guard lock(m_mutex);
        return m_queue.size() == m_max_size;
    }

    bool Empty() const {
        std::lock_guard lock(m_mutex);
        return m_queue.size() == 0;
    }

    size_t UnoccupiedSize() const {
        std::lock_guard lock(m_mutex);
        return m_max_size - m_queue.size();
    }

    size_t OccupiedSize() const {
        std::lock_guard lock(m_mutex);
        return m_queue.size();
    }

private:
    const size_t m_max_size;
    std::queue<DataType> m_queue{};
    mutable std::mutex m_mutex{};
    std::condition_variable m_cond_var{};
};
