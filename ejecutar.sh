
#! /bin/bash

for j in {1..5}
do
	for i in 1000 100000 10000000 100000000 1000000000
	do
		./e $i 8
	done
done
