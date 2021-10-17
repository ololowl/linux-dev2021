#!/bin/bash

# tput clear ; tput cup 10 10; echo a; cat

sleeptime='0.5'
if [ $# -gt '0' ]; then
	sleeptime=$1
fi

text=""
lens=()
total_count=0
while IFS= read -r line; do
	text="$text $line"

	lens+=($((${#line} + 1)))
	total_count=$((total_count + ${#line} + 1))
done < 'calendar.txt'

shuf -i 0-$(($total_count - 1)) > "permutation.txt"

#tput clear
while IFS= read -r index; do
	sleep $sleeptime

	row=0
	col=0
	cumsum=0
	for elem in "${lens[@]}"; do
		if [ $(($cumsum + $elem)) -lt $index ]; then
			cumsum=$((cumsum + elem))
			row=$((row + 1))
		else
			col=$((index - cumsum))
			break
		fi
	done

	tput cup $row $col
	
	echo ${text:$index:1}

done < "permutation.txt"


sleep 15
