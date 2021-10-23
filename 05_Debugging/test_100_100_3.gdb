set $counter = 0
break range.c:31 if (28 <= $counter++ && $counter <= 35)
command 1
	echo @@@
	printf "%d %d %d %d\n", start, stop, step, i
	continue
end

run -100 100 3 > /dev/null

quit