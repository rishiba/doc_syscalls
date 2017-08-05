all:
	gcc -o elf.slow_write slow_write.c -Wall
	gcc -o elf.fast_write fast_write.c -Wall

run: setup all
	time -p ./elf.slow_write
	time -p ./elf.fast_write

clean:
	rm src_file elf.slow_write elf.fast_write copied_file.txt

setup:
	for i in `seq 1 10000`; do cat /etc/passwd >> src_file; done 
