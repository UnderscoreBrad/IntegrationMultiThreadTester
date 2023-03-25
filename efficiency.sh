LOWER=-1
UPPER=1
POINTS=100000000
THREADS=1
MAX_THREADS=$1
make
while [[ $THREADS -le $MAX_THREADS ]]
    do
        echo ./integrate $LOWER $UPPER $POINTS $THREADS
        time ./integrate $LOWER $UPPER $POINTS $THREADS
        (( POINTS += 100000000 ))
        (( THREADS++ ))
done
