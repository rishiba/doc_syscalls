============
Introduction
============


In this white paper we will see how your code interacts with the glibc library and 
then the system calls in order to get some work done from the computer.

We will go deep into the code and see how it is all organized. How system calls
are called from the user space programs.  How arguements are passed and how is
return value accessed.

We will see the code, we will see the same thing using debugger and then we
will write our own small ``strace`` to see what the ``strace``  actually does when
it lists the paramters to you.


Acknowledgements
================

Most of the contents in the paper is inspired from the contents in the internet
and various blogs.

I wanted to understand the whole process of the glibc and system calls and
while doing that - I just documented the whole thing.

Wherever possilble I have given links of the reference point.


