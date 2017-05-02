============================================
System Call Implementation In the User Space
============================================

There are two ways system calls are being called in the user space. Both of
them will eventually call the ``syscall`` instruction but ``glibc`` provides a
wrapper around that instruction using a function call.

*  ``glibc`` library call which does the work which needs to be done before
    calling the ``syscall`` instruction.

*   ``syscall`` assembly instruction to enter the priviledged mode. This allows
    the process to move to the priviledge mode.





