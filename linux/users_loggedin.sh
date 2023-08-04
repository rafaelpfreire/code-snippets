#!/bin/bash

# Show users not Idle within the last 10 minutes (600s)
#ls -lu /dev/pts | awk -v now="$(date +"%s")" '{"date +%s -d \""$7" "$8" "$9"\"" | getline login; if((now-login)<600)print $3;}' | uniq
#ls -lu --time-style=+%s /dev/pts/* | awk '{if((systime()-$7)<600) print $3}' | sort -u
#w -h | awk '{ "stat -c%X /dev/" $2 | getline t; d=systime()-t; if(d<600) print $1}' | sort -u
#find /dev/pts/ -amin -10 -exec stat --format=%U {} + | sort -u
find /dev/pts/ -amin -10 -printf '%u\n' | sort -u
