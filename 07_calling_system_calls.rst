====================
Calling System Calls
====================

Glibc ``syscall()`` interface
=============================

*   There is a library function in ``glibc`` named as ``syscall``, you can read
    about it in the man pages by the command ``man 2 syscall``.

*   We already have the code of ``glibc`` with us.

*   See the function in the file
    ``glibc-2.23/sysdeps/unix/sysv/linux/x86_64/syscall.S``

*   On reading the code you will see that the function is moving the argument
    values to the registers and then calling the assembly instruction ``syscall``.

*   As ``syscall`` here is a user space ``glibc`` library function, first the
    arguments will be in the registers used for calling user space functions. Once
    this is done, as the system call is being called, the arguments will be used
    into the registers where the kernel wishes to find the arguments.

*   Code for ``syscall(2)`` library function.

.. note:: Remember the note above. As ``syscall`` is a function which we called
   in user space, the registers are different. We now need to pick and place
   the registers in a way that the system call understands it. THis is shown in
   the code below.

::

    .text

        ENTRY (syscall)
            movq %rdi, %rax             /* Syscall number -> rax.  */
            movq %rsi, %rdi             /* Shift the arg2 to arg1 for syscalls */
            movq %rdx, %rsi             /* Shift the arg3 to arg2 for syscalls */
            movq %rcx, %rdx             /* Shift the arg4 to arg3 for syscalls */
            movq %r8, %r10              /* Shift the arg5 to arg4 for syscalls */
            movq %r9, %r8               /* Shift the arg6 ro arg5 for syscalls */
            movq 8(%rsp),%r9            /* Shift the arg7 from the stack to arg6 for syscalls */
            syscall                     /* Do the system call.  */
            cmpq $-4095, %rax           /* Check %rax for error. %rax has the return value  */
            jae SYSCALL_ERROR_LABEL     /* Jump to error handler if error.  */
            ret                         /* Return to caller.  */
        PSEUDO_END (syscall)

.. todo::  The above code is not getting highlighted, maybe due to the use of
   incorrect lexer. See this page http://pygments.org/docs/lexers/ and
   hightlight the above code. use code block for this.

Assembly Instruction for calling system call.
=============================================

We know now that for calling a system call we just need to set the right
arguments in the register and then call the ``syscall`` instruction.

Register ``%rax`` needs the ``system call number``. So where are the ``system
call numbers`` defined. Here we can see the ``glibc`` code to see the mapping
of the number and the system call. Or you can see this in a header file in the
system's include directory.

System call numbers will never change, if they do there will be a lot of
porting efforts which will need to be done else a lot of applications will
break.

Let us see a excerpt from the file ``/usr/include/x86_64-linux-gnu/asm/unistd_64.h``

::

    #define __NR_read 0
    #define __NR_write 1
    #define __NR_open 2
    #define __NR_close 3
    #define __NR_stat 4

Here you can see that the system calls have numbers associated with them.

Now armed with the knowledge of how to call system calls let us write some
assembly code where we call a system call.

Before doing this exercise let us see the ``write`` system call a bit. In the
following code we will write ``hello world`` on the screen. We will not use
``printf`` for this, rather we will use ``2`` (the standard descriptor for
writing to the terminal) and ``write`` system call for it.

We need to do this so that we understand our assembly level program a bit better.

.. literalinclude:: code_system_calls/07/write.c
   :linenos:
   :language: c

You should go through the assembly code of the C file. Use command ``gcc -S
filename.c`` This will generate the assembly file with ``.s`` extension. If you
go through the assembly code you will see a call to ``write`` function. This
function is defined in the ``glibc``. We will see the source of ``write``
system call in sometime. At that time you can refer this and understand it
better.

.. note:: When I am compiling the code I can see the assembly code only using the eax register and not rax, why?

.. todo:: We should explain the assembly code generated above.

Now we will do the same using the ``syscall`` interface which the ``glibc`` provides.

.. literalinclude:: code_system_calls/07/syscall_write.c
   :linenos:
   :language: c

You should go through the assembly code of the C file. Use command ``gcc -S
filename.c`` This will generate the assembly file with ``.s`` extension. If you
go through the assembly code you will see a call to ``syscall`` function. This
function is defined in the ``glibc``. We will see the source of ``syscall``
system call in sometime. At that time you can refer this and understand it
better.

.. note:: When I am compiling the code I can see the assembly code only using the eax register and not rax, why?

.. todo:: We should explain the assembly code generated above.

Now we will do the same in our assembly code.

.. literalinclude:: code_system_calls/07/hello.asm
   :linenos:
   :language: nasm

Makefile for assembling the code.

.. literalinclude:: code_system_calls/07/Makefile
   :linenos:
   :language: make
