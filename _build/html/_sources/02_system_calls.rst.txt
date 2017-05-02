===================
System Architecture
===================

.. todo:: Write about System archtecture - little bit about how a process links with the libraries etc.

Shared Library
==============

.. todo:: Write about Shared library.

Static Library
==============

.. todo:: Write about Static Library.


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

Let us see a small demostration of this.

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

References
==========
