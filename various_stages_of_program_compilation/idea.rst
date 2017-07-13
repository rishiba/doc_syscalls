=====================================
Various Stages Of Program Compilation
=====================================


Introduction
============

- ``gcc`` has to undergo a lot of stages while compiling your code.


- The sequence is ``PREPROCESSING -> ASSEMBLING -> COMPILATION - LINKING``

Preprocessing
=============

- 
Compilation
===========

- 

Assembling
==========


Linking
=======



Hands-On
========

- Write the code

::
    
    #include <stdio.h>
    int main() {
        printf("\nHello World");
        return 0;
    }


- Preprocess the file

    ``gcc -E hello_world.c > temp.c``

- Read the ``temp.c`` file to understand what has been done in the preprocessing stage.

- Assemble the ``temp.c`` file 

    ``gcc -S temp.c`` - you will get a file ``temp.s`` - Read the file to see the assmbled code


- Compile the ``temp.s`` file

    ``gcc -c temp.s`` - you will get a file ``temp.o`` - Read the file with ``objdump -D temp.o`` - You will get to see the full contents of the file

Link the file

- Now this is a bit tricky as calling ``ld`` with the right option will be required. We will see how ``gcc`` does it.

Run ``gcc hello_world.c -v`` to see what ``gcc`` does



- ``/usr/lib/gcc/x86_64-linux-gnu/4.7/collect2 --sysroot=/ --build-id --no-add-needed --as-needed --eh-frame-hdr -m elf_x86_64 --hash-style=gnu -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/4.7/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/4.7 -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../.. /tmp/ccJtDOL4.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/4.7/crtend.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crtn.o``

- You will get something like above, this is the exact step done during the linking step. ``gcc`` internally call it for linking. Read more about it http://gcc.gnu.org/onlinedocs/gccint/Collect2.html


- The difference is marked with ``>>>>> <<<<<`

- ``/usr/lib/gcc/x86_64-linux-gnu/4.7/collect2 --sysroot=/ --build-id --no-add-needed --as-needed --eh-frame-hdr -m elf_x86_64 --hash-style=gnu -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/4.7/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/4.7 -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib >>>>>>>>> -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../.. /tmp/ccJtDOL4.o <<<<<<<<<<<<<<< -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/4.7/crtend.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crtn.o``
- ``/usr/lib/gcc/x86_64-linux-gnu/4.7/collect2 --sysroot=/ --build-id --no-add-needed --as-needed --eh-frame-hdr -m elf_x86_64 --hash-style=gnu -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/4.7/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/4.7 -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu >>>>>>>>>>>>>temp.o<<<<<<<<<<<<<< -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/4.7/crtend.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crtn.o``

- Run the command with the  replaced the object file in the above

- ``/usr/lib/gcc/x86_64-linux-gnu/4.7/collect2 --sysroot=/ --build-id --no-add-needed --as-needed --eh-frame-hdr -m elf_x86_64 --hash-style=gnu -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/4.7/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/4.7 -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/4.7/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu temp.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/4.7/crtend.o /usr/lib/gcc/x86_64-linux-gnu/4.7/../../../x86_64-linux-gnu/crtn.o``

- You will get your ``a.out`` file

- Run it ``./a.out``

::

    Hello World
