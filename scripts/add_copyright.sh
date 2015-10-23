#!/bin/sh 

find .. \( -name '*.cpp' -o -name '*.h' -o -name '*.c' \) -exec sh -c "cat LICENSE > _tmp; cat {} >> _tmp; mv _tmp {}" \;
