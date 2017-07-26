==================================================================
System Calls On x86_64 from User Space
==================================================================

There are three parts to calling a system call like any function call.

*  Setting up the arguments to be passed to the kernel space. Here we gather the right arguments to pass to the function. Based on these argument the kernel will do the required work for you.

*  Call the system call using the ``syscall`` assembly instruction. This is exact place where the programs ``hand-over`` the work to the kernel. The process then waits for the system call to return. In asynchronous system calls the process will get a return value to indicate that the task has been submitted correctly and kernel is doing the job.

*  Get back the return value. This is the return status of the work done by the kernel. Using this the kernel notifies the process about the task done. There is also a global error number variable which stores the error (if any) encountered by the kernel.

In the sections below we will see each of them in detail.

.. _system_calls: 

Setting Up Arguements
=====================

.. note:: The following text is copied verbatim from the document **System V
   Application Binary Interface AMD64 Architecture Processor 57 Supplement
   Draft Version 0.99.6**, Section **AMD64 Linux Kernel Conventions**. The
   copyright belongs to the original owners of the document.

::

    Calling Conventions

    The Linux AMD64 kernel uses internally the same calling conventions as user-
    level applications (see section 3.2.3 for details). User-level applications that like
    to call system calls should use the functions from the C library. The interface
    between the C library and the Linux kernel is the same as for the user-level appli-
    cations with the following differences:
    
    1. User-level applications use as integer registers for passing the sequence
    %rdi, %rsi, %rdx, %rcx, %r8 and %r9. The kernel interface uses %rdi,
    %rsi, %rdx, %r10, %r8 and %r9.
    2. A system-call is done via the syscall instruction. The kernel destroys
    registers %rcx and %r11.
    3. The number of the syscall has to be passed in register %rax.
    4. System-calls are limited to six arguments, no argument is passed directly on
    the stack.
    5. Returning from the syscall, register %rax contains the result of the
    system-call. A value in the range between -4095 and -1 indicates an error,
    it is -errno.
    6. Only values of class INTEGER or class MEMORY are passed to the kernel.

See the ``System V Application Binary Interface AMD64 Architecture Processor
Supplement Draft Version 0.99.6``. Section ``AMD64 Linux Kernel Conventions``
for the details.

.. _system_calls_args: 

Reiterating The Above Again
---------------------------

Hence when we have called any function in user space we will have the following
state of the registers when we are in the called function.

.. csv-table:: "Arguments Passing In Linux"
    :header: "Register", "Argument User Space", "Argument Kernel Space"
    :widths: 15, 10, 30

    "%rax", "Not Used",     "System Call Number"
    "%rdi", "Arguement 1",  "Arguement 1"
    "%rsi", "Arguement 2",  "Arguement 2"
    "%rdx", "Arguement 3",  "Arguement 3"
    "%r10", "Not Used",     "Arguement 4"
    "%r8",  "Arguement 5",  "Arguement 5"
    "%r9",  "Arguement 6",  "Arguement 6"
    "%rcx", "Arguement 4",  "Destroyed"
    "%r11", "Not Used",     "Destroyed"

.. note:: This table summarizes the differences when a function call is made in the user space, and when a system call is made.
   This will be more clear in coming texts. Right now make a note of it

Passing arguements
------------------

*   Arguments are passed in the registers. The called function then uses the register to get the arguments.
*   The arguments are passed in the following sequence ``%rdi, %rsi, %rdx, %r10, %r8 and %r9.``
*   Number of arguments are limited to ``six``, no arguments will be passed on the stack.
*   Only values of class ``INTEGER`` or class ``MEMORY`` are passed to the kernel.
*   Class ``INTEGER`` This class consists of integral types that fit into one of the general purpose registers.
*   Class ``MEMORY`` This class consists of types that will be passed and returned in memory via the stack. These will mostly be strings or memory buffer. For example in ``write()`` system call, the first parameter is ``fd`` which is of class ``INTEGER`` while the second argument is the ``buffer`` which has the data to be written in the file, the class will be ``MEMORY`` over here. The third parameter which is the count - again has the class as ``INTEGER``.

.. note:: The above information is sourced from AMD64 Architecture Processor Supplement Draft Version 0.99.6

Calling the System Call
=======================

*   A system-call is done via the ``syscall`` assembly instruction. The kernel destroys registers ``%rcx`` and ``%r11``.
*   The number of the system call has to be passed in register ``%rax``.

Retrieving the Return Value
===========================

*   Returning from the ``syscall``, register ``%rax`` contains the result of the
    system-call. A value in the range between ``-4095`` and ``-1`` indicates an error, it
    is ``-errno``.
