## File: test.sh
## Author: Peter Currie (yeah) 
## Modified by: Anthony
# for CMSC216 spring 2021
TESTFILE=prio-q.c #edit this to your source file name
## INSTRUCTIONS
# 1. Make a new file in your project folder named "test.sh"
# 2. Copy and paste this entire thing (Ctrl+A-Ctrl+C) into the file and save it
# 3. Edit the TESTFILE variable above to the name of your source file (e.g. student.c)
# 4. Done! You can now run all public tests at once with the command: "bash test.sh"
## OPTIONS (feel free to leave these as the default if you want)
# FLAGS - These GCC flags will be used when compiling your code with the public tests.
# By default this is the flags used by the submit server, so I recommend leaving them.
FLAGS="-g -ansi -pedantic-errors -Wall -Werror -fstack-protector -fmax-errors=3 -lm"
# DELETE_X_FILES - This deletes the temporary executable files compiled from each test.
# For example: public01.x, public02.x, public03.x, etc.  You usually don't need these.
# By default this is TRUE so that you don't get a hundred *.x files in your project dir.
# Change this to FALSE if you want to keep these files so you can debug them using GDB.
# For example, if you failed test 4, you might use: "gdb public04.x" after doing this.
DELETE_X_FILES=true
## SCRIPT
# Go ahead and mess around with the code, I'm not the best at shell scripting so you
# might be able to improve it :) just don't complain to me if you break something :)
ERR=false
if [ ! -e $TESTFILE ]; then
    echo -e "\E[31mDid not find \E[36m$TESTFILE \E[31min this directory!"
    tput sgr0
    ERR=true
fi
if !(ls public*.c 1> /dev/null 2>&1); then
    echo -e "\E[31mNo public tests found in this directory!"
    tput sgr0
    ERR=true
fi
if $ERR; then
    exit 1
fi
str="\n\E[34;1mSummary:\E[0m\n"
for i in $(ls | grep "public[0-9][0-9].c"); do
    echo -e "\E[33mRunning test $i..."
    tput sgr0
    exe=${i%.c}.x
    out=${i%.c}.output
 
    if [[ "$exe" == "public03.x" || "$exe" == "public04.x" || "$exe" == "public05.x" || "$exe" == "public06.x" || "$exe" == "public07.x" || "$exe" == "public09.x" || "$exe" == "public11.x" ]]; then
        gcc $i $TESTFILE memory-checking.o -o $exe &>cmp
    elif [[ "$exe" == "public08.x" || "$exe" == "public10.x" || "$exe" == "public12.x" ]]; then
        gcc $i $TESTFILE memory-checking.o compare-name-lists.o -o $exe &>cmp
    elif [[ "$exe" == "public14.x" ]]; then
        gcc $i $TESTFILE compare-name-lists.o -o $exe &>cmp
    else 
        gcc $i $TESTFILE -o $exe &>cmp
fi    
	      if [ -s cmp ]; then
        echo -e "\E[31mTest did not compile!"
        tput sgr0
        str=${str}"\E[31mC"
        cat cmp
        echo ""
    else
        ./$exe | diff -U 0 -b - $out >dif
        if [ -s dif ]; then
            echo -e "\E[31mTest failed!"
            tput sgr0
            str=${str}"\E[31mX"
            cat dif
            echo ""
        else
            echo -e "\E[32mTest passed!"
            tput sgr0
            str=${str}"\E[32mP"
            echo ""
        fi
        rm dif
    fi
    rm cmp
    if $DELETE_X_FILES; then
        rm $exe
    fi
done
echo -e $str"\n"
tput sgr0
exit 0