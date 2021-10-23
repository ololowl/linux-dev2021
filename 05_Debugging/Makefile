main: range.c
	gcc -O0 -g range.c -o range

test:
	gdb -x test_1_12.gdb --batch ./range | grep @@@ | cut -c 4- | cmp expected_1_12.txt
	gdb -x test_100_100_3.gdb --batch ./range | grep @@@ | cut -c 4- | cmp expected_100_100_3.txt

clean:
	rm range