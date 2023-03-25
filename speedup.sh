LOWER=-1
UPPER=1
POINTS=1000000000
THREADS=1
make
while [[ $THREADS -le 8 ]]
    do
        echo ./integrate $LOWER $UPPER $POINTS $THREADS
        time ./integrate $LOWER $UPPER $POINTS $THREADS
        (( THREADS++ ))
done