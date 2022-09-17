TESTFILE=prio-q.c #edit this to your source file name

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

    if [[ "$exe" == "public11.x" || "$exe" == "public12.x" ]]; then
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
        $exe | diff -U 0 - $out >dif
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
     rm $exe
done
echo -e $str"\n"
tput sgr0
exit 0
