########################
Basics of a Linux System
########################

============
Introduction
============

In this chapter we will see some of the very basic concepts of the operating systems and programs which run on it.

*   What is a computer program, how to convert the ``.c`` file to an ``executable`` and what are the steps involved.
*   What are libraries? What are shared libraries and static libraries?
*   What are system calls?
*   What is a kernel?
*   How the block diagram of the system looks like?

========================
Programs and Compilation
========================

Your program is a set of instructions to the computer which your computer needs to follow in order to get some work done for you.

For running a program on a Linux System these are the steps involved.

*   Write the program.
*   Pre-process the program. Run ``gcc -E hello_world.c > pre.c``.
*   Assemble the pre-processed code. Run ``gcc -S pre.c``. You will get a file ``pre.s``
*   Compile the assembled code. Run ``gcc -c pre.s``. You will get a file ``pre.s``.
*   Run the linker on the compiled code. ``gcc pre.o``. You will get a file with name as ``a.out``.

These steps are pretty simple and straight forward but there is a lot of things which go under the hood and is hidden under the ``gcc`` command.

What is ``gcc``
===============

*   ``gcc`` is a computer program which takes another program as an input and converts it into ``ELF`` file format. ``ELF`` file format is the file format of the executable files which can be run on ``Linux`` machines.

Stages of compilation
=====================

*   ``gcc`` has to undergo a lot of stages while compiling your code. The sequence is ``PREPROCESSING -> COMPILATION -> ASSEMBLING -> LINKING``

Preprocessing
-------------

*   This stage converts the macros in the c file to c code which can be compiled. See the file ``pre.e``. Here the macro ``#include`` has been expanded and the whole file ``stdio.h`` has been copied in the c file.

Compilation
-----------

*   Here the assembled code will be converted into the opcode of the assembly instruction.

Assembling
----------

*   This stage will convert the C programming language into the instruction set of the CPU. See the file ``pre.s``. Here you will only see assembly instructions.

Linking
-------

#.  Here the code will be linked with the libraries present on the system. Note that ``printf`` function is not defined in your code, neither it is defined in the file ``stdio.h``. It is just declared in the header file and it is stored in the compiled and executable format in a shared library on the system.

Hands-On
========

*   Write the code

.. literalinclude:: code_system_calls/00/01_hello_world/hello_world.c
    :language: c
    :linenos:

*   Pre-process the file

    ``gcc -E hello_world.c > pre.c``

*   Read the ``pre.c`` file to understand what has been done in the pre-processing stage.

*   Assemble the ``pre.c`` file

    ``gcc -S pre.c`` - you will get a file ``pre.s`` - Read the file to see the assembled code

*   Compile the ``pre.s`` file

    ``gcc -c pre.s`` - you will get a file ``pre.o`` - Read the file with ``objdump -D pre.o`` - You will get to see the full contents of the file

*   Link the file

*   Now this is a bit tricky as calling ``ld`` with the right option will be required. We will see how ``gcc`` does it.


*   Run ``gcc hello_world.c -v`` to see what ``gcc`` does. This is very specific to the flavor of Linux because of the folder paths it has. The same command may not run on your machine. My flavor is

::

    $ uname -a
    Linux rishi-office 4.4.0-83-generic #106-Ubuntu SMP Mon Jun 26 17:54:43 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
    
    rishi@rishi-office:~/publications/doc_syscalls/code_system_calls/00$ cat /etc/lsb-release 
    DISTRIB_ID=Ubuntu
    DISTRIB_RELEASE=16.04
    DISTRIB_CODENAME=xenial
    DISTRIB_DESCRIPTION="Ubuntu 16.04.2 LTS"

*   Here is the output of the command ``gcc hello_world.c -v``. We are focusing only on the last few lines.

*/usr/lib/gcc/x86_64-linux-gnu/5/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/5/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper -plugin-opt=-fresolution=/tmp/cc8bF6fB.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/5 -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/5/../../.. /tmp/cchjP9PO.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o*

*   You will get something like above, this is the exact step done during the linking step. ``gcc`` internally calls it for linking. Read more about it http://gcc.gnu.org/onlinedocs/gccint/Collect2.html


*   We will replace the object file name in the above string and then run the command. New command is

*ld -plugin /usr/lib/gcc/x86_64-linux-gnu/5/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper -plugin-opt=-fresolution=/tmp/cc1PIEfF.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/5 -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib   -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o pre.o -o pre.elf*

*   The difference is marked with ``>>>>> <<<<<``

*/usr/lib/gcc/x86_64-linux-gnu/5/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/5/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper -plugin-opt=-fresolution=/tmp/cc8bF6fB.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/5 -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib >>>>>>!!!-L/usr/lib/gcc/x86_64-linux-gnu/5/../../.. /tmp/cchjP9PO.o <<<<<!!! -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o*

*   Run the command after replacing the object file in the above command.

*   You will get your ``pre.elf`` file

*   Run it ``./pre.elf``

::

    $ ./pre.elf 


    Hello World

*   Using the following ``Makefile`` you can do the above steps one by one and see the results for yourself.

.. literalinclude:: code_system_calls/00/01_hello_world/Makefile
    :language: make
    :linenos:

=========
Libraries
=========

A library is a zipped file of compiled code. The code is compiled and kept in a
format that any other program can use the code by just linking to it. For this
the program should just have the function declared in the code so that the
compilation stage knows that the function's code will be linked to at a ``later
stage.``

In the linking phase the linker links the code by ``attaching`` the function
call's code present in the library to the function place where function is
called in the compiled code.

There are two words which I have ``formatted differntly`` in the above paragraph
``attaching`` and ``later stage``.

An executable is said to be **statically linked** if the ``later stage`` is
the last stage of the compilation and ``attaching`` is done in the last stage
of installation.

An executable is said to be **dynamically linked** if the ``later stage`` is at
the time of program execution and attaching is also done at the time of program
execution. This is the role of ``loader``.

Static Library
==============

In the above section we have understood that we can compile some code and keep
it as a library on the system, then use the code to ``link`` (read as
``attaching``) to some new programs. When we ``link``  the code at the compile
time we call it a statically compiled executable. This increases the size of
the executable program as the whole library gets copied to the executable. This
has the benefit that the executable becomes self sufficient and can execute on
any other Linux machine.

Shared Library
==============

If the compiled library is linked but not attached to the executable at the
time of execution then it is called a dynamically linked executable. This in
achieved by just storing the location of the function's address in the library.
The executable expects the library to be present on the system where it will be
executed. This is one downside of dynamic linking, where as the advantage is
that the new executable will have a smaller size.

This is very useful for the libraries which are used by a lot of executable
like ``glibc``.

See this 

::

    bin/ls: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=eca98eeadafddff44caf37ae3d4b227132861218, stripped

============
System Calls
============

System calls are API's which the Kernel provides to the user space
applications. The system calls pass some arguments to the kernel space and the
kernel acts accordingly on the arguments

For example: ``open()`` system call - opens a file so that further read and
write operations can be done on the file. The return value of the ``open``
system call is a ``file descriptor`` or an ``error status``. Successful return value
allows the user space applications to use the ``file descriptor`` for further reads
and writes.

System calls get executed in the kernel space. Kernel space runs in an elevated
privileged mode. There is a shift of the privileged modes whenever a system call
is called and hence its a bad idea to call system calls without considering the
time taken to switch to the elevated privileged mode.

For example - lets say that you want to copy a file. One way of copying the file
is to read each character of the file and for every character read you write the
character to another file. This will call two system calls for every
character you read and write. As this is expensive in terms of time its a bad
design.

Let us see a small demonstration of this.

.. literalinclude:: code_system_calls/00/02_slow_fast_write/slow_write.c
    :language: c
    :linenos:

What should instead be done here is that you read a block (set of characters)
and then write that block into another file. This will reduce the number of the
system calls and thus increase the overall performance of the file copy
program.

.. literalinclude:: code_system_calls/00/02_slow_fast_write/fast_write.c
    :language: c
    :linenos:

.. literalinclude:: code_system_calls/00/02_slow_fast_write/Makefile
    :language: make
    :linenos:

======
Kernel
======

Kernel is an important component of any Operating System. This is the only
layer which interacts directly with the hardware. So in order to get any work
done from your hardware you need to ``ask`` the kernel to do this.

This ``asking`` is done by ``system calls``. In assembly level language this is
the ``syscall`` instruction. When you call any system call a function in
the kernel is invoked and it gets the work done. The arguments we passed are
passed to the kernel and a particular function call is invoked.

For the functions any hardware interaction is needed the kernel interacts with
the hardware through the device driver of the hardware.

==========
Conclusion
==========

In this chapter we have seen some of the important concepts and steps required to take a program from a ``.c`` file to an executable format on a ``Linux`` machine. This chapter also introduced us to the concepts of system calls and libraries.

==========
References
==========

*   https://stackoverflow.com/questions/14163208/how-to-link-c-object-files-with-ld

*   For further reading refer 1st Chapter ``Getting Started`` of ``Beginning Linux Programming`` by ``Neil Matthew and Richard Stones``.
