# Difficulty: Easy
# Category: Strings

# Write a function that takes a non-empty string and that returns a boolean whether
# the string is a palindrome.
# Sample Input:
#    string = "abcdcba"
# Sample Output:
#    true

def isPalindrome(string):
    return string == string[::-1]
