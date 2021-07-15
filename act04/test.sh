#!/bin/bash

cal=0

echo "Compiling..."
gcc $1 -o app > /dev/null 2>&1
if [[ $? -ne 0 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done"
cal=$((cal+10))

echo "Checking parameters..."
./app > /dev/null 2>&1
if [[ $? -ne 255 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."
cal=$((cal+10))
 
echo "Verifying that file 1 exists..." #-2
./app noexiste1 file2.txt file3.txt
if [[ $? -ne 254 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."

echo "Verifying that file 2 exists..." #-3
./app file1.txt noexiste2 file3.txt
if [[ $? -ne 253 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."

echo "Verifying that file 3 exists..." #-4
./app file1.txt file2.txt noexiste3 
if [[ $? -ne 252 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."
cal=$((cal+10))

echo "Verifying that input file 1 is not empty..." #-5
./app empty.txt file2.txt file3.txt
if [[ $? -ne 251 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."

echo "Verifying that input file 2 is not empty..." #-6
./app file1.txt empty.txt file3.txt
if [[ $? -ne 250 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."

echo "Verifying that input file 3 is not empty..." #-7
./app file1.txt file2.txt empty.txt 
if [[ $? -ne 249 ]] ; then 
	echo "grade: $cal"
	exit 1
fi
echo " done."
cal=$((cal+10))

echo "Running the program..."
./app file1.txt file2.txt file3.txt &
pid=$!
sleep 2

echo "Sending signal SIGUSR1..."
kill -s SIGUSR1 $pid
ps aux | grep $pid >/dev/null && cal=$((cal+15)) || echo "Not running"

echo "Sending signal SIGUSR2..."
kill -s SIGUSR2 $pid
ps aux | grep $pid >/dev/null && cal=$((cal+15)) || echo "Not running"

echo "Sending signal SIGUPWR..."
kill -s SIGPWR $pid
ps aux | grep $pid >/dev/null && cal=$((cal+15)) || echo "Not running"

echo "End with SIGINT..."
kill -s SIGINT $pid
sleep 5
echo "proc $pid"
ps -f
ps aux | grep $pid >/dev/null && cal=$((cal+15)) || echo "Not running"

echo "final grade: $cal"

rm app

