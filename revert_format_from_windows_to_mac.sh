#!/bin/bash
find . -type f -print0 | xargs -0 dos2unix
find . -name "* *" -type d | rename 's/ /_/g'
find . -name "* *" -type f | rename 's/ /_/g'
python3 utf8.py 
