break range.c:31 if i % 5 == 0
	command 1
	echo @@@
	printf "%d %d %d %d\n", start, stop, step, i
	continue
end

run 1 12 > /dev/null

quit