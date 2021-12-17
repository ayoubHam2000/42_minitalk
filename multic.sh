#!/bin/bash
for i in $(seq 1 $1)
do
   ./client.out `echo $i + 555 | bc` &
done
