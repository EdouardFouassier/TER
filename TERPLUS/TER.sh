#!/bin/bash
make -s
#clear
RM='/bin/rm'
FTP='/usr/bin/ftp'
DATE='/bin/date'

var1=0
var2=0
arg="-gen"
if [ $# = 3 ] ; then
#if [ $# = 1 ] && [ $1 = "-g" ]; then
#print=$(echo -e  "Suppression des données \n ")
#clear
#echo $print
	rm -f data/in* 
#print=$(echo -e "$print Génération des nouvelles données \n ")
#clear
#echo $print
	./gen $1 $2 100
#fi
#pourcent=0
	var850=0
	for i in `seq 0 99`;
	do

	#clear
	#echo "$print$i%"
	
		BEFORE=$(date +%s%N)
		var850=$(($var850+$(./FirstFit data/in$i $3)))
		time850=$(($time850+$(date +%s%N)-$BEFORE))
#	BEFORE=$(date +%s%N)
#	var900=$(( $var900 + $(./FirstFit data/in$i 900)))
#	time900=$(($time900+$(date +%s%N)-$BEFORE))

#	BEFORE=$(date +%s%N)
#	var950=$(( $var950 + $(./FirstFit data/in$i 950)))
#	time950=$(($time950+$(date +%s%N)-$BEFORE))

#	BEFORE=$(date +%s%N)
#	var1000=$(( $var1000 + $(./FirstFit data/in$i 1000)))
#	time1000=$(($time1000+$(date +%s%N)-$BEFORE))
	done
	echo "FirstFit $4 $var850/100 en $(($time850/100000000)) ms"
#echo "FirstFit 900 $var900/100 en $(($time900/100000000)) ms"
#echo "FirstFit 950 $var950/100 en $(($time950/100000000)) ms"
#echo "FirstFit 1000 $var1000/100 en $(($time1000/100000000)) ms"
fi