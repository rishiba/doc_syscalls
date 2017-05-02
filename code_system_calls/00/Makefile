all:
	gcc -o slow_write slow_write.c -Wall
	gcc -o fast_write fast_write.c -Wall

run:
	time slow_write
	time fast_write

clean:
	rm src_file slow_write fast_write copied_file.txt

setup:
	for i in `seq 1 1000`; do cat /etc/passwd >> src_file; done 
