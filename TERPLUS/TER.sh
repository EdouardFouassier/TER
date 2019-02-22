#!/bin/bash
make
var1=0
var2=0
#./gen
for i in `seq 0 9`;
do
	echo "try"$i
	var=$(./FirstFit in$i 950)
	var1=$(( $var1 + $var ))
	#var2=$var2+$(./ReverseFirstFit in$i 950)
done
echo "FirstFit $var1/10"
#echo "ReverseFirstFit $var1/10"