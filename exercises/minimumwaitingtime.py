# Dificulty: Easy
# Category: Greedy Algorithms
#
# You're given a non-empty array of positive integers representing the amounts
# of time that specific queries take to execute. Only one query can be executed
# at a time, but the queries can be executed in any order.
#
# A query's waiting time is defined as the amount of time that it must wait
# before its execution starts. In other words, if a query is executed second,
# then its waiting time is the duration of the firt query; if a query is
# executed third, then its waiting time is the sum of the durations of the 
# first two queries.
#
# Write a function that returns the minimum amount of total waiting time for
# all the queries. For example, if wou're given the queries of durations
# [1, 4, 5], then the total waiting time if the queries were executed in the
# order of [5, 1, 4] would be (0) + (5) + (5+1) = 11. The first queriy of
# duration 5 would be executed immediatly, so its waiting time would be 0,
# the second query of duration 1 would have to wait 5 seconds (the duration
# of the first query) to be executed, and the last query would have to wait
# the duration of the first two queries before being executed.
#
# Note: you're not allowed to mutate the input array.
#
#
# Sample Input:
# queries = [3, 2, 1, 2, 6]
#
# Sample Output:
# 17
#

#
# O(n.log) time | O(n) space
# n.log because the first step is to sort the array and we're copying
# the entire array to the waitTime representing the total time to wait
# for each query
#
def minimumWaitingTime(queries):
    waitTime = queries[:]
    waitTime.sort()

    for i in range(1,len(queries)):
        waitTime[i] += waitTime[i-1]

    return sum(waitTime[:-1])


#
# O(n.log) time | O(1) space
# n.log because the first step is to sort the array
#
def minimumWaitingTime(queries):
    queries.sort()

    totalWaitTime = 0
    length = len(queries)
    for i, time in enumerate(queries):
        queriesLeft = length - 1 - i
        # We need to sum the query exec time as many times
        # as the number of queries left to exec after the current one
        totalWaitTime += time * queriesLeft

    return totalWaitTime
