#! /bin/bash
#Tomer Hadar 207651027

Recursion() {
    countElements=$(ls -1 $1 2>/dev/null | /usr/bin/wc -l)
    if [ "$countElements" -gt 0 ]; then
        Elements=$(ls $1)
        for element in $Elements; do
            if [ -d "$1/$element" ]; then
                $0 $1/$element $2 -r
            fi
        done
        DeleteCompiledFiles "$1"    
        CompileAllFiles "$1" "$2"
    fi
}

DeleteCompiledFiles() {
    count=$(ls -1 $1/*.out 2>/dev/null | /usr/bin/wc -l)
    if [ "$count" -ne 0 ]; then
        FILES=$(ls $1/*.out)
        for FILE in $FILES; do
            rm "$FILE"
        done
    fi
}

CompileAllFiles() {
    ccount=$(ls -1 $1/*.c 2>/dev/null | /usr/bin/wc -l)
    if [ "$ccount" -ne 0 ]; then
        CFILES=$(ls $1/*.c)
        PREFIX="$1/"
        SUFFIX=".c"
        for CFILE in $CFILES; do
            if grep -iwq "$2" "$CFILE"; then
                CFILE=${CFILE#$PREFIX}
                str=${CFILE%$SUFFIX}
                gcc -w "$1/$CFILE" -o "$1/$str.out" 
            fi
        done
    fi
}

if [ $# -ge 3 ] && [ $3 == "-r" ]; then
    Recursion "$1" "$2"
elif [ $# -ge 2 ]; then
    DeleteCompiledFiles "$1"
    CompileAllFiles "$1" "$2"
else
   echo 'Not enough parameters'
fi
