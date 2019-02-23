#!/bin/bash
make -s

RM='/bin/rm'
FTP='/usr/bin/ftp'
DATE='/bin/date'

var1=0
var2=0
arg="-gen"
if [ $# = 1 ] && [ $1 = "-g" ]; then
	./gen
fi
for i in `seq 0 99`;
do
	BEFORE=$(date +%s%N)
	var=/usr/bin/time var850=$(( $var850 + $(./FirstFit in$i 850)))
	time850=$(($time850+$(date +%s%N)-$BEFORE))
	BEFORE=$(date +%s%N)
	var900=$(( $var900 + $(./FirstFit in$i 900)))
	time900=$(($time900+$(date +%s%N)-$BEFORE))
	BEFORE=$(date +%s%N)
	var950=$(( $var950 + $(./FirstFit in$i 950)))
	time950=$(($time950+$(date +%s%N)-$BEFORE))
	BEFORE=$(date +%s%N)
	var1000=$(( $var1000 + $(./FirstFit in$i 1000)))
	time1000=$(($time1000+$(date +%s%N)-$BEFORE))
	#var2=$var2+$(./ReverseFirstFit in$i 950)
done
echo "FirstFit 850 $var850/100 en $(($time850/100000000)) ms"
echo "FirstFit 900 $var900/100 en $(($time900/100000000)) ms"
echo "FirstFit 950 $var950/100 en $(($time950/100000000)) ms"
echo "FirstFit 1000 $var1000/100 en $(($time1000/100000000)) ms"