#!/bin/sh 

grep -r -l --include \*.h --include \*.cpp --include \*.c 'MIT License' .. | xargs sed -i '1,/\*\//d'
