=============
Return Values
=============

Introduction
=============

A system call is called to get some work done by the kernel. How does the kernel notify the caller about the work done.

The process of notifying about the work done is same as that of any other function call. Through return values. The return codes are well documented in the man pages. For example ``open`` system call will return a positive number if the file is opened. The positive number is the file handle and should be used to do any other operation on the opened file. A negative return value means error.

The error values are also well documented in the header files and functions like ``perror()`` are there to help you convert the error number to relevant strings.

Also - some system call return the values using the ``call-by-reference`` method. For example ``read()`` system call. The second argument is the buffer where we want the data to be read. The kernel reads the data from the file and copies the data to the passed buffer.

Return Value Status in the register
===================================

The return value is returned in the ``rax`` register. We can see this using a debugger. Let us read 50 bytes of a small file and see what is the status of the return value.

.. literalinclude:: code_system_calls/08/read/read.c
    :language: c
    :linenos:

We will now add a breakpoint at the read system call line and see the register's value changing after the system call. See the snippet below. Here we are compiling the code using ``make`` and then running the code first.

Then we start the ``gdb`` and set up ``displays`` to list the registers ``rax`` and ``rsi``. These registers have the return values. ``rax`` has the number of bytes read and rsi has the pointer to the buffer which we are passing for the bytes to be copied.

We setup a breakpoint at ``read`` call and then we see the state of the registers before and after the read system calls are called.

*	Compile and run the command.

::

	$ make
	gcc -g -c read.c -I `gcc --print-file-name=include` -I /home/rishi/glibc/install_glibc/include
	gcc -nostdlib -nostartfiles -static -o read /home/rishi/glibc/install_glibc/lib//crt1.o /home/rishi/glibc/install_glibc/lib//crti.o `gcc --print-file-name=crtbegin.o` read.o -Wl,--start-group /home/rishi/glibc/install_glibc/lib//libc.a -lgcc -lgcc_eh -Wl,--end-group `gcc --print-file-name=crtend.o` /home/rishi/glibc/install_glibc/lib//crtn.o 
	$ ./read

	Successfully opened the destination file..
	Bytes Read 20

	root:x:0:0$ 
	
*	 Start ``gdb``.

:: 
	$ gdb ./read
	GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.04) 7.11.1
	Copyright (C) 2016 Free Software Foundation, Inc.
	License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
	This is free software: you are free to change and redistribute it.
	There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
	and "show warranty" for details.
	This GDB was configured as "x86_64-linux-gnu".
	Type "show configuration" for configuration details.
	For bug reporting instructions, please see:
	<http://www.gnu.org/software/gdb/bugs/>.
	Find the GDB manual and other documentation resources online at:
	<http://www.gnu.org/software/gdb/documentation/>.
	For help, type "help".
	Type "apropos word" to search for commands related to "word"...
	Reading symbols from ./read...done.

*	Setup the displays and breaks ini gdb.

::

	(gdb) display $rax
	1: $rax = <error: No registers.>
	(gdb) display (char *) $rsi
	2: (char *) $rsi = <error: No registers.>
	(gdb) break read
	Breakpoint 1 at 0x433680: file ../sysdeps/unix/syscall-template.S, line 84.

*	Run the program. It will stop just before read is called. See the state of the registers.

::

	(gdb) r
	Starting program: /home/rishi/publications/doc_syscalls/doc/code_system_calls/08/read/read 

	Successfully opened the destination file..
	Breakpoint 1, read () at ../sysdeps/unix/syscall-template.S:84
	84	T_PSEUDO (SYSCALL_SYMBOL, SYSCALL_NAME, SYSCALL_NARGS)
	1: $rax = 3
	2: (char *) $rsi = 0x7fffffffcd10 "BUFFER"

*	Call the ``read()``. See the state of the registers. The ``rax`` register has the number of bytes read ``20`` and the ``rsi`` register has the pointer to the filled buffer.


::

	(gdb) n
	main () at read.c:41
	41	    printf ("\nBytes Read %d", bytes_read);
	1: $rax = 20
	2: (char *) $rsi = 0x7fffffffcd10 "root:x:0:0:root:/roo"

	(gdb) 


.. todo:: add content to show the return values as well and the error codes.

Printing Error Value
====================

Now let us see how do system call show the error encountered in the system calls. In this code we will try to open a file which does not exist and then check the value of the register ``rax``. Also we will print the global variable ``errno`` to get the status of the system call.



::

	$ gcc error_open.c 
	$ ./a.out 
	Got error as : No such file or directory
	Error is No such file or directory
	Error number is 2$ 



Conclusion
==========

Hence we now know the following stuff

.. todo:: Write the conclusion.
