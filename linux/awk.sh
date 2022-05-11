#!/bin/bash

# Prints the filename and fileowner given a ls command
echo
ls -l | awk 'BEGIN{}{print $8, "\t", $3}END{}'

# You also can do that in a script, which in this case is called fileowner.awk
echo
ls -l | ./fileowner.awk

# To use a command line variable, dont forget to break quotes. The backslash doesnt work in awk script.
echo
col=8
ls -l | awk '{print $'"$col"'}'

#There are only a few commands in AWK. The list and syntax follows:
#
#    if ( conditional ) statement [ else statement ]
#    while ( conditional ) statement
#    for ( expression ; conditional ; expression ) statement
#    for ( variable in array ) statement
#    break
#    continue
#    { [ statement ] ...}
#    variable=expression
#    print [ expression-list ] [ > expression ]
#    printf format [ , expression-list ] [ > expression ]
#    next
#    exit

# Example
echo
awk \
    'BEGIN{
        # How many lines
        lines = 0;
        # Sum of the first column
        total = 0;
    }
    {
        lines++
        total+=$1;
    }
    END{
        print lines " lines read";
        print "total is ", total;
        if (lines > 0) {
            print "average is ", total/lines;
        } else {
            print "average is 0"
        }
    }' << EndOfMyFile
"10
10
8
5
7
8"
EndOfMyFile
