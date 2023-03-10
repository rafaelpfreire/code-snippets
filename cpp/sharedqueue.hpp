#include <queue>
#include <mutex>
#include <utility>
#include <optional>

template<typename T>
class SharedQueue {
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    
public:
    SharedQueue() = default;
    SharedQueue(const SharedQueue<T> &) = delete ;
    SharedQueue& operator=(const SharedQueue<T> &) = delete ;

    SharedQueue(SharedQueue<T>&& other) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue = std::move(other.m_queue);
    }

    virtual ~SharedQueue() { }

    unsigned long size() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty()) {
            return {};
        }
        T tmp = m_queue.front();
        m_queue.pop();
        return tmp;
    }

    void push(const T &item) {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_queue.push(item);
    }
};
