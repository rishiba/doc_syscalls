=============
Return Values
=============

Introduction
=============

A system call is called to get some work done by the kernel. How does the kernel notify the caller about the work done?

The process of notifying about the work done is same as that of any other function call. Through return values and ``call-by-reference`` arguments. A list of error numbers and its definitions can be found in the file ``/usr/include/asm-generic/errno-base.h``.

Return Values
--------------

The return value, arguments and possible errors related to a system call are well documented in the ``man`` pages of the system call.

For converting the ``errno`` to relevant string error (for example ``errno`` 2 is "No such file or directory") we have the function ``strerror()``.

call-by-reference
-----------------

Some system call return the values using the ``call-by-reference`` method. For example ``read()`` system call. The second argument is the buffer where we want the data to be read. The kernel reads the data from the file and copies the data to the passed buffer.

Error Macros
------------

There are predefined macros in the form of ``#define``. These codes help us to write a more readable code. In the following text I have listed the error codes from the file ``/usr/include/asm-generic/errno-base.h``

::

    $ cat /usr/include/asm-generic/errno-base.h
    #ifndef _ASM_GENERIC_ERRNO_BASE_H
    #define _ASM_GENERIC_ERRNO_BASE_H

    #define EPERM        1  /* Operation not permitted */
    #define ENOENT       2  /* No such file or directory */
    #define ESRCH        3  /* No such process */
    #define EINTR        4  /* Interrupted system call */
    #define EIO      5  /* I/O error */
    #define ENXIO        6  /* No such device or address */
    #define E2BIG        7  /* Argument list too long */
    #define ENOEXEC      8  /* Exec format error */
    #define EBADF        9  /* Bad file number */
    #define ECHILD      10  /* No child processes */
    #define EAGAIN      11  /* Try again */

Error Explanation
-----------------

The man page of ``errno`` explains the above mentioned error codes in detail. Run the command ``man 2 errno``.

::

	
	>>>>>>>>>>>> SNIPPED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	E2BIG           Argument list too long (POSIX.1)

	EACCES          Permission denied (POSIX.1)

	EADDRINUSE      Address already in use (POSIX.1)

	EADDRNOTAVAIL   Address not available (POSIX.1)

	EAFNOSUPPORT    Address family not supported (POSIX.1)

	>>>>>>>>>>>> SNIPPED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Return Values
-------------

See the man page of open system call by the command ``man 2 open``. You will see a section like the following explaining the return value of the ``open`` system call.

::

	RETURN VALUE

		   open(),  openat(),  and creat() return the new file
		   descriptor, or -1 if an error  occurred  (in  which
		   case, errno is set appropriately).

Error Example
--------------

See the man page of open system call using ``man 2 open``. There will be section which will have the list of possible errors which this system call can throw.

::

	ERRORS
		   open(),  openat(),  and  creat()  can fail with the
		   following errors:

		   EACCES The requested access  to  the  file  is  not
				  allowed,  or search permission is denied for
				  one of the directories in the path prefix of
				  pathname,  or the file did not exist yet and
				  write access to the parent directory is  not
				  allowed.  (See also path_resolution(7).)

		   EDQUOT Where  O_CREAT  is  specified, the file does
				  not exist, and  the  user's  quota  of  disk
				  blocks  or inodes on the filesystem has been
				  exhausted.

		   EEXIST pathname  already  exists  and  O_CREAT  and
				  O_EXCL were used.

			>>>>>>>>>>>> SNIPPED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<

How system calls return value?
==============================

The return value is returned in the ``rax`` register. We can see this using a debugger. Let us read 50 bytes of a small file and see what is the status of the return value.


.. literalinclude:: code_system_calls/08/read/read.c
    :language: c
    :linenos:

We will now add a breakpoint at the ``read()`` system call line and see the register's value changing after the system call. See the snippet below. Here we are compiling the code using ``make`` and then running the code first.

Then we start the ``gdb`` and set up ``displays`` to list the registers ``rax`` and ``rsi``. These registers have the return values. ``rax`` has the number of bytes read and ``rsi`` has the pointer to the buffer which we are passing for the bytes to be copied.

We setup a breakpoint at ``read`` call and then we see the state of the registers before and after the read system calls are called.

.. note:: For linking we are using our own compiled ``glibc``. This helps us when we run the debugger. 

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

Printing Error Value
====================

Now let us see how do system call show the error encountered in the system calls. In this code we will try to open a file which does not exist and then we will print the global variable ``errno`` to get the status of the system call. We will also use the above mentioned function ``strerror()`` to print a more user friendly message.

::

    $ make

    $ ./elf.open 

    Error number is 2
    File does not exist. Check if the file is there.
    Error is: No such file or directory

Conclusion
==========

In this section we learnt in detail about

*   How system calls return values to the caller.
*   How system calls notify errors to the caller.
*   How to see the return values in the register.
*   How to convert a error code to a error string.

