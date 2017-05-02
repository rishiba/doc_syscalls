====================
Setting Up Arguments
====================

Introduction
============

In the above section we have see the theory part related to passing arguements
to the system call interface of the kernel.  Now we will see some assignements
related to it.

We will see if how the above concepts being implemented in actual code. By this
time we know that the we need to link the code to the ``glibc`` in order to use
the system calls. In the following sections we will see this

We will do it in three different ways. 

#.  Walk through ``open`` system call in ``glibc`` library.
#.  See it using debugger.
#.  Use ``ptrace`` system call and see the state of the registers. Code related to this can be found in the appendix.

Walk through ``open`` system call in ``glibc``
==============================================

In this assignment we will download the source code of ``glibc`` and then walk through the code
to find out where exactly the code is calling the ``syscall`` assembly instruction and where is 
it moving the arguements to the registers.

We will do this with ``open`` system call and ``write`` system calls.


.. note:: If you have not understood above concepts. Do not worry, keep reading
   on and then re-read the whole thing once more.


How ``open()`` system call is called using ``glibc``
----------------------------------------------------

#.  All the above theory should match with the code which is written in ``glibc``.

#.  We will now read the code in the ``glibc`` to find out if the theory matches
    what is written in the code.

#.  We will also do some assignments to get a better understanding of the above theory.

#.  Now the question is ``open`` system call - how will it turn to a ``syscall``
    instruction.

#.  Now we need to find out what happens to the ``open`` system call when compiled.

#.  File where sys call numbers are mentioned
    ``/usr/include/x86_64-linux-gnu/asm/unistd_64.h``

#.  File where ``SYS_write`` maps to ``NR_Write``
    ``/usr/include/x86_64-linux-gnu/bits/syscall.h``

#.  From the objdump we saw that ``__libc_open`` was called. This called
    ``__open_nocancel`` and it had a ``syscall`` instruction. It means that the
    path to the kernel is in this function.

#.  See the ``object dump``, offset ``433e0e``. This dump is taken from a code where we had a
    ``open`` system call and was compiled.

::

    0000000000433e09 <_open_nocancel>:
    433e09:   b8 02 00 00 00          mov    $0x2,%eax

    433e0e:   0f 05                   syscall        <<<<<<<<<<<<<<<<<<
    
    433e10:   48 3d 01 f0 ff ff       cmp    $0xfffffffffffff001,%rax
    433e16:   0f 83 f4 46 00 00       jae    438510 <__syscall_error>
    433e1c:   c3                      retq
    433e1d:   48 83 ec 08             sub    $0x8,%rsp
    433e21:   e8 ca 2f 00 00          callq  436df0 <__libc_enable_asynccancel>
    433e26:   48 89 04 24             mov    %rax,(%rsp)
    433e2a:   b8 02 00 00 00          mov    $0x2,%eax
    433e2f:   0f 05                   syscall 
    433e31:   48 8b 3c 24             mov    (%rsp),%rdi
    433e35:   48 89 c2                mov    %rax,%rdx
    433e38:   e8 13 30 00 00          callq  436e50 <__libc_disable_asynccancel>
    433e3d:   48 89 d0                mov    %rdx,%rax
    433e40:   48 83 c4 08             add    $0x8,%rsp
    433e44:   48 3d 01 f0 ff ff       cmp    $0xfffffffffffff001,%rax
    433e4a:   0f 83 c0 46 00 00       jae    438510 <__syscall_error>
    433e50:   c3                      retq
    433e51:   66 2e 0f 1f 84 00 00    nopw   %cs:0x0(%rax,%rax,1)
    433e58:   00 00 00
    433e5b:   0f 1f 44 00 00          nopl   0x0(%rax,%rax,1)

#.  Now, when in glibc-2.3 dir I started finding the code for the function
    ``__open_nocancel`` I found this


#.  File is ``sysdeps/unix/sysv/linux/generic/open.c``

::

    int __open_nocancel (const char *file, int oflag, ...)
    {
        int mode = 0;
    
        if (__OPEN_NEEDS_MODE (oflag))
        {   
            va_list arg;
            va_start (arg, oflag);
            mode = va_arg (arg, int);
            va_end (arg);
        }   
    
        return INLINE_SYSCALL (openat, 4, AT_FDCWD, file, oflag, mode);
    }
    
#.  So INLINE_SYSCALL is being called by this function. This is defined in the
    file ``glibc-2.3/sysdeps/unix/sysv/linux/x86_64/sysdep.h`` 

::

    # define INLINE_SYSCALL(name, nr, args...) \
        ({                                          \
         unsigned long int resultvar = INTERNAL_SYSCALL (name, , nr, args);        \
         if (__glibc_unlikely (INTERNAL_SYSCALL_ERROR_P (resultvar, )))        \
         {                                       \
         __set_errno (INTERNAL_SYSCALL_ERRNO (resultvar, ));           \
         resultvar = (unsigned long int) -1;                   \
         }                                       \
         (long int) resultvar; })
    

#.  Thus it calls ``INTERNAL_SYSCALL`` which is defined as 

::

    # define INTERNAL_SYSCALL(name, err, nr, args...) \
      INTERNAL_SYSCALL_NCS (__NR_##name, err, nr, ##args)

#.  Now let us see the ``INTERNAL_SYSCALL_NCS`` in the file
    ``./sysdeps/unix/sysv/linux/x86_64/sysdep.h`` here see the macro
    ``INTERNAL_SYSCALL_NCS``. This is the exact macro which is calling the
    ``syscall`` assembly instruction. You can see the ``asm`` instructions in the code.

::

        # define INTERNAL_SYSCALL_NCS(name, err, nr, args...) \
            ({                                          \
             unsigned long int resultvar;                          \
             LOAD_ARGS_##nr (args)                             \
             LOAD_REGS_##nr                                \
             asm volatile (                                \
                 "syscall\n\t"                                 \
                 : "=a" (resultvar)                                \
                 : "0" (name) ASM_ARGS_##nr : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);   \
             (long int) resultvar; })


#.  Thus here we enter the kernel using the ``syscall`` assembly instruction.

#.  Also, we need to figure out how - ``open()`` call went to be called as ``__open_nocancel``

.. todo:: ``open`` call called ``__open_nocancel``, How.

.. todo:: The above section is not very well written, do it.

#.  We have redone the whole thing with the ``write`` system call in the
appendix. You can see that as well to get more clarity.

How is ``write`` system call implemented in ``glibc``
-----------------------------------------------------

.. todo:: Write this part - do it in the appendix. This will make the paper better organized. 

Check Arguements Using A Debugger
=================================

In the above example we saw how the code calls the ``syscall`` instruction to
enter the kernel and call the required functionality.  Write the following code
and compile it with ``gcc -g filename.c``

``-g`` flag adds the debugging information to the execuatable.

.. literalinclude:: code_system_calls/01/02.c
    :language: c
    :linenos:

*   Once done, run the code in the debugger ``gdb ./a.out``
*   Set the breakpoint in the call on write ``break write``
*   According to the calling conventions the register ``$rdi`` should have the
    file descriptor. ``$rdi`` should have the string's address and the ``$rdx``
    should have the length of the string.
*   Using ``print`` command will confirm these values.

::

    (gdb) b write
    Breakpoint 1 at 0x400560
    (gdb) r
    Starting program: /home/rishi/mydev/books/crash_book/code_system_calls/01/aaa/a.out 
    
    Breakpoint 1, write () at ../sysdeps/unix/syscall-template.S:81
    81  ../sysdeps/unix/syscall-template.S: No such file or directory.
    (gdb) print $rdi
    $1 = 3
    (gdb) print (char *) $rsi
    $2 = 0x7fffffffdeb0 "non_existent_file"
    (gdb) print $rdx
    $3 = 17
    (gdb) 

Using ``ptrace`` to see the variables passed
============================================

.. todo:: add code for this. Better to add it as a appendix.

