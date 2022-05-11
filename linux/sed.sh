#!/bin/bash

# Basic substitution
echo day | sed s/day/night/ # Result night

# Slash as a delimiter
sed 's/\/usr\/local\/bin/\/common\/bin/' <old >new
sed 's_/usr/local/bin_/common/bin_' <old >new
sed 's:/usr/local/bin:/common/bin:' <old >new
sed 's|/usr/local/bin|/common/bin|' <old >new

# Using the '&' to use the string found
echo rafael | sed 's/[a-z]*/(&)/' # Result (rafael)
echo 123 abc | sed 's/[0-9]*/& &/' # Result 123 123 abc

# Using -r to enable extended regular expressions (i.e. '+' meta character)
echo "123 abc" | sed -r 's/[0-9]+/& &/' # Result 123 123 abc

# Backreference - remembering found patterns
echo "peres rafael" | sed 's/\([a-z][a-z]*\) \([a-z][a-z]*\)/\2 \1/' # Result rafael peres

# Backreference extended regex -r
echo "peres rafael" | sed -r 's/([a-z]+) ([a-z]+)/\2 \1/' # Result rafael peres
echo "rafael rafael" | sed -r 's/([a-z]+) \1/\1/' # Eliminate duplicate words. Result rafael

# Sed pattern flags
# /g - Global replacement.With no flags, the first matched substitution is changed. With the "g" option, all matches are changed.
echo "rafael rafael" | sed -r 's/rafael/peres/' # Result peres rafael
echo "rafael rafael" | sed -r 's/rafael/peres/g' # Result peres peres
# /1, /2, etc - add a number after the substitution command to indicate you only want to match that particular pattern
echo "rafael rafael rafael" | sed -r 's/rafael/DELETED/2' # Result rafael DELETED rafael
echo "rafael rafael rafael" | sed -r 's/rafael/DELETED/2g' # Result rafael DELETED DELETED
# /p - print
# /w - write to a file
# /I - ignore case
echo "rafael Rafael RAFAEL" | sed -r 's/rafael/matched/I2' # Result rafael matched RAFAEL

# Sed command flags
# -n - No printing
# -e - Combine multiple commands
sed -e 's/a/A/' -e 's/b/B/' <old >new
# -f - Put several sed expressions in a file called sed script

# Sed script
# If you place the '#!/bin/sed -f' on the file header, you can
# run the sed script as a command line script like this
# ./CapVowel <old >new
