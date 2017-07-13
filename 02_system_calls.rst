===================
System Architecture
===================

Introduction
============

In this chapter we will see some of the very basic concepts of the an operating systems. We will not deep dive anything, and will only skim the surface of every important component.

#.  What is a computer program, how to convert the ``.c`` file to an ``executable`` and what are the steps involved. 
#.  What are libraryies and see learn shared libraries as well as static libraries. 
#.  What are system calls.
#.  What is a kernel.
#.  How the block diagram looks like?

What is a program?
==================

For running a program on a Linux System these are the steps involved.

#.  Write the program.
#.  Compile and make an executable of that program using a compiler. For C programs we use ``gcc``.
#.  Run the program on the system.

These steps are pretty simple and straight foraward but there is a lot of things which go under the hood and is hidden under the following tools.

#.  Compiler
#.  Linker
#.  Loader.

Let me elaborate the above steps with respect to a C program. Following is the C program which we will take for consideration, ``prog1.c``.

::
    
    #include <stdio.h>

    int main() {
        printf("%s", "Hello World");
        return 0;
    }
    

#.  Write the program.
#.  Preprocess the program. Run ``gcc -E hello.c > hello.e``.
#.  Assemble the preprocessed code. Run ``gcc -S pprog1.e``. You will get a file ``pprog1.s``
#.  Compile the assembled code. Run ``gcc -c pprog1.s``. You will get a file ``pprog1.s``.
#.  Run the linker on the compiled code. ``gcc pprog1.o``. You will get a file with name as ``a.out``.

Now let us see the above stages in a bit detail.

Preprocessing
-------------

#.  This stage converts the macros in the c file to c code which can be compiled. See the file ``hello.e``. Here the macro ``#include`` has been exapnded and the whole file ``stdio.h`` has been copied in the c file.

Assembling
----------

#.  This stage will convert the C programming language into the instruction set of the CPU. See the file ``hello.s``. Here you will only see assemly instructions.

Compilation
-----------

#.  Here the assembled code will be converted into the opcode of the assembly instruction.

Linking
-------

#.  Here the code will be linked with the libraries present on the system. Note that ``printf`` function is not defined in your code, niether it is defined in the file ``stdio.h``. It is just declared in the header file and it is stored in the compiled and executable format in a shared libray on the system.

Libraries
=========

A library is a zipped file of compiled code. The code is compiled and kept in a
format that any other program can use the code by just linking to it. For the
this the program should just have the function declared in the code so that the
copliation stage knows that the function's code will be linked to at a ``later
stage.``

In the linking phase the linker links the code by ``attaching`` the function
call's code present in the library to the function place where function is
called in the compiled code.

There are two words which I have ``italicized`` in the above paragraph
``attaching`` and ``later stage``.

An executable is said to be **staticically linked** if the ``later stage`` is
the last stage of the compilation and ``attaching`` is done in the last stage
of installation.

An executable is said to be **dynamically linked** if the ``later stage`` is at
the time of program execution and attaching is also done at the time of program
execution. This is the role of ``loader``.

Static Library
==============

In the above section we have understood that we can compile some code and keep
it as a library on the syste, then use the code to ``link`` (read as
``attaching``) to some new programs. When we ``link``  the code at the compile
time we call it a statically compiled executable. This increases the size of
the executable program as the whole library gets copied to the executable. This
has the benefit that the executable becomes self sufficient and can execute on
any other linux machine.

Shared Library
==============

If the compiled library is not linked but not attached to the executable at the
time of execution then it is called a dynamically linked exeuctable. This is
achived by just storing the location of the function's address in the library.
The executable expects the library to be present on the system where it will be
executed. This is one downside of dynamic linking, where as the advantage is
that the new exectable will have a smaller size. 

This is very usefule for the libraries which are used by a lot of execuatbel
like ``glibc``.

See this 

::

    bin/ls: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=eca98eeadafddff44caf37ae3d4b227132861218, stripped


System Calls
============

System calls are API's which the Kernel Provides to the user space
applications. The system calls pass some arguements to the kernel space and the
kernel acts accordingly on the arguements.

For example: ``open()`` system call - opens a file so that further read and
write operations can be done on the file. The return value of the ``open``
system call is a ``file descriptor`` or an ``error status``. Sucessful return value
allows the user space applications to use the ``file descriptor`` for further reads
and writes.

System calls get executed in the kernel space. Kernel space runs in an elevated
prviledge mode. There is a shift of the priviledge modes whenever a system call
is called and hence its a bad idea to call system calls without considering the 
time taken to switch to the elevated priviledge mode.

For example - lets say that you want to copy a file. One way of copying the file
is to read each character of the file and for every character read you write the
character to another file. This will call two system calls for every
character you read and write. As this is expensive in terms of time its a bad
design.

Let us see a small demonstration of this.

.. literalinclude:: code_system_calls/00/slow_write.c
    :language: c
    :linenos:

What should instead be done here is that you read a block (set of characters)
and then write that block into another file. This will reduce the number of the
system calls and thus increase the overall performance of the file copy
program.

.. literalinclude:: code_system_calls/00/fast_write.c
    :language: c
    :linenos:

.. literalinclude:: code_system_calls/00/Makefile
    :language: make
    :linenos:

Kernel
======

Kernel is an important component of any Operating System. This is the only layer which interacts directly with the hardware. So in order to get any work done from your hardware you need to ``ask`` the kernel to do this.

This ``asking`` is done by ``system calls``. When you call any system call a function in the kernel is invoked and it gets the work done. The arguements we passed are passed to the kernel and a particular function call is invoked.

For the functions any hardware interaction is needed the kernel interacts with the hardware through the device driver of the hardware.

System Architecture
===================

With the above context about important components of the system we can now draw 


References
==========
