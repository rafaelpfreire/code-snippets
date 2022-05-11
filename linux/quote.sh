#!/bin/bash

# Inside the single quotes, you can include almost all meta-characters:
echo 'What the *heck* is a $ doing here???'

# Sometimes you want a weaker type of quoting: one that doesn't expand meta-characters like "*" or "?," but does expand variables and does command substitution
echo "Is your home directory $HOME?"
echo "Your current directory is $(pwd)"
