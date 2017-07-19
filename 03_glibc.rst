======================
Working with ``glibc``
======================

Introduction
============

This chapter deals with ``glibc`` library. We have earlier seen how to make our
own static library, and a dynamic library.

In this chapter we will see how to work with ``glibc`` library.

We will Download a fresh glibc and will compile it on ou systems. We will make
some changes to the code and then link our code with this library.

Why this chapter
================

This chapter will help you understand the basic concepts related to using glibc
and making changes to it. Generally you will never need to modify the code to
the glibc, but incase you need to make some modifications or if you need to
debug a function - this section will be quite useful.

What is ``glibc``
=================

``glibc`` is a library which has a lot of functions pre-written for you so that
you do not have to write the code again and again. Also it standardizes the
way you should be writing your code. It wraps a lot of system specific details
and all you need to know is to how to call the particular function, and what to
be expected from the function and what are the return values the function will
give you.

``glibc`` is the ``GNU Version of Standard C Library``. All the functions
supported in ``Standard C Library`` can be found in the ``glibc``.

**For example:** Let us say that we have to find the length of a string. Now
this is quite a small code to write and we can write the whole thing ourself,
but it is a function which will be used a lot of time accross a lot of
products. So the library gives you an implementation of this. As the function
is present in the library you can safely assume that the function will work
fine because of millions of people have used it and tested it.

For the sake of understanding it better we will now go into the code of the
library function and see if its similar to our code.

Also we will make some changes to the code so that it stops working incorrectly
and then use it in our programs. This exercise is just a demostration of the
following.

-   We can read the code of glibc.
-   We can compile the code of glibc ourselves and use the newly compiled library.
-   We can change the code of glibc.
-   We can use the changed code of glibc.

Download and extract ``glibc``
==============================

The source code of glibc is available at ``https://ftp.gnu.org/gnu/libc/``. You
can sort the list using ``Last Modified`` to get the latest tar package.

From the page I got the link as ``https://ftp.gnu.org/gnu/libc/glibc-2.24.tar.xz``.

*   Let us download this source, see the following snippet for the exact commands.

::

    $ wget https://ftp.gnu.org/gnu/libc/glibc-2.24.tar.xz
    --2017-01-29 07:50:02--  https://ftp.gnu.org/gnu/libc/glibc-2.24.tar.xz
    Resolving ftp.gnu.org (ftp.gnu.org)... 208.118.235.20, 2001:4830:134:3::b
    Connecting to ftp.gnu.org (ftp.gnu.org)|208.118.235.20|:443... connected.
    HTTP request sent, awaiting response... 200 OK
    Length: 13554048 (13M) [application/x-tar]
    Saving to: ‘glibc-2.24.tar.xz’

    glibc-2.24.tar.xz                     100%[==>]  12.93M   709KB/s    in 21s

    2017-01-29 07:50:26 (622 KB/s) - ‘glibc-2.24.tar.xz’ saved [13554048/13554048]

Extract the code
-----------------

*   The downloaded code is a compressed tar file. We need to extract it.

::

    rishi@rishi-VirtualBox:~$ tar -xf glibc-2.24.tar.xz

*   This creates a directory names ``glibc-2.24`` in the folder.

Walkthrough ``glibc``
=====================

*   Here is a listing of all the directories inside the extracted ``glibc``
    directory. You can see the diectories where the code related to ``math``
    ``strings`` ``stdlib`` are present.

::

    rishi@rishi-VirtualBox:~$ cd glibc-2.24/
    rishi@rishi-VirtualBox:~/glibc-2.24$ ls
    abi-tags          ChangeLog.3                        ChangeLog.old-ports-mips
    aclocal.m4        ChangeLog.4                        ChangeLog.old-ports-powerpc
    argp              ChangeLog.5                        ChangeLog.old-ports-tile
    assert            ChangeLog.6                        config.h.in
    benchtests        ChangeLog.7                        config.make.in
    bits              ChangeLog.8                        configure
    BUGS              ChangeLog.9                        configure.ac
    catgets           ChangeLog.old-ports                conform
    ChangeLog         ChangeLog.old-ports-aarch64        CONFORMANCE
    ChangeLog.1       ChangeLog.old-ports-aix            COPYING
    ChangeLog.10      ChangeLog.old-ports-alpha          COPYING.LIB
    ChangeLog.11      ChangeLog.old-ports-am33           cppflags-iterator.mk
    ChangeLog.12      ChangeLog.old-ports-arm            crypt
    ChangeLog.13      ChangeLog.old-ports-cris           csu
    ChangeLog.14      ChangeLog.old-ports-hppa           ctype
    ChangeLog.15      ChangeLog.old-ports-ia64           debug
    ChangeLog.16      ChangeLog.old-ports-linux-generic  dirent
    ChangeLog.17      ChangeLog.old-ports-m68k           dlfcn
    ChangeLog.2       ChangeLog.old-ports-microblaze     elf
    extra-lib.mk      LICENSES     nscd                  stdio-common
    extra-modules.mk  locale       nss                   stdlib
    gen-locales.mk    localedata   o-iterator.mk         streams
    gmon              login        po                    string
    gnulib            mach         posix                 sunrpc
    grp               Makeconfig   PROJECTS              sysdeps
    gshadow           Makefile     pwd                   sysvipc
    hesiod            Makefile.in  README                termios
    hurd              Makerules    resolv          test-skeleton
    iconv             malloc       resource        time
    iconvdata         manual       rt              timezone
    include           math         Rules           version.h
    inet              mathvec      scripts         wcsmbs
    INSTALL           misc         setjmp          wctype
    intl              NAMESPACE    shadow          WUR-REPORT
    io                NEWS         shlib-versions
    libc-abis         nis          signal
    libidn            nptl         socket
    libio             nptl_db      soft-fp


*   Some string related code is here

::

    rishi@rishi-VirtualBox:~/glibc-2.24$ ls string/str*
    string/stratcliff.c    string/strcmp.c     string/strerror_l.c      
    string/strcasecmp.c    string/strcoll.c    string/strfry.c          
    string/strcasecmp_l.c  string/strcoll_l.c  string/string.h          
    string/strcasestr.c    string/strcpy.c     string/string-inlines.c  
    string/strcat.c        string/strcspn.c    string/strings.h         
    string/strchr.c        string/strdup.c     string/strlen.c          
    string/strchrnul.c     string/strerror.c   string/strncase.c        
    string/strncase_l.c  string/strrchr.c    string/str-two-way.h
    string/strncat.c     string/strsep.c     string/strverscmp.c
    string/strncmp.c     string/strsignal.c  string/strxfrm.c
    string/strncpy.c     string/strspn.c     string/strxfrm_l.c
    string/strndup.c     string/strstr.c
    string/strnlen.c     string/strtok.c
    string/strpbrk.c     string/strtok_r.c



*   Some math related code is here

::

    $ ls math/w_*

    math/w_acos.c    math/w_hypotl.c          math/w_log1pl.c
    math/w_acosf.c   math/w_ilogb.c           math/w_log2.c
    math/w_acosh.c   math/w_ilogbf.c          math/w_log2f.c
    math/w_acoshf.c  math/w_ilogbl.c          math/w_log2l.c
    math/w_acoshl.c  math/w_j0.c              math/w_log.c
    math/w_acosl.c   math/w_j0f.c             math/w_logf.c
    math/w_asin.c    math/w_j0l.c             math/w_logl.c
    math/w_asinf.c   math/w_j1.c              math/w_pow.c
    math/w_asinl.c   math/w_j1f.c             math/w_powf.c
    math/w_atan2.c   math/w_j1l.c             math/w_powl.c
    math/w_atan2f.c  math/w_jn.c              math/w_remainder.c
    math/w_atan2l.c  math/w_jnf.c             math/w_remainderf.c
    math/w_atanh.c   math/w_jnl.c             math/w_remainderl.c
    math/w_atanhf.c  math/w_lgamma.c          math/w_scalb.c
    math/w_atanhl.c  math/w_lgamma_compat.c   math/w_scalbf.c
    math/w_cosh.c    math/w_lgamma_compatf.c  math/w_scalbl.c
    math/w_coshf.c   math/w_lgamma_compatl.c  math/w_scalbln.c
    math/w_coshl.c   math/w_lgammaf.c         math/w_scalblnf.c
    math/w_exp10.c   math/w_lgammaf_main.c    math/w_scalblnl.c
    math/w_exp10f.c  math/w_lgammaf_r.c       math/w_sinh.c
    math/w_exp10l.c  math/w_lgammal.c         math/w_sinhf.c
    math/w_exp2.c    math/w_lgammal_main.c    math/w_sinhl.c
    math/w_exp2f.c   math/w_lgammal_r.c       math/w_sqrt.c
    math/w_exp2l.c   math/w_lgamma_main.c     math/w_sqrtf.c
    math/w_expl.c    math/w_lgamma_r.c        math/w_sqrtl.c
    math/w_fmod.c    math/w_log10.c           math/w_tgamma.c
    math/w_fmodf.c   math/w_log10f.c          math/w_tgammaf.c
    math/w_fmodl.c   math/w_log10l.c          math/w_tgammal.c
    math/w_hypot.c   math/w_log1p.c
    math/w_hypotf.c  math/w_log1pf.c



*   The header files for the library is here.

::

    $ ls include/
    aio.h          gconv.h            net               stackinfo.h
    aliases.h      getopt.h           netdb.h           stap-probe.h
    alloca.h       getopt_int.h       netgroup.h        stdc-predef.h
    argp.h         glob.h             netinet           stdio_ext.h
    argz.h         gmp.h              nl_types.h        stdio.h
    arpa           gnu                nss.h             stdlib.h
    assert.h       gnu-versions.h     nsswitch.h        string.h
    atomic.h       grp.h              obstack.h         strings.h
    bits           grp-merge.h        poll.h            stropts.h
    byteswap.h     gshadow.h          printf.h          stubs-prologue.h
    caller.h       iconv.h            programs          sys
    complex.h      ifaddrs.h          protocols         syscall.h
    cpio.h         ifunc-impl-list.h  pthread.h         sysexits.h
    ctype.h        inline-hashtab.h   pty.h             syslog.h
    des.h          langinfo.h         pwd.h             tar.h
    dirent.h       libc-internal.h    regex.h           termios.h
    dlfcn.h        libc-symbols.h     resolv.h          tgmath.h
    elf.h          libgen.h           rounding-mode.h   time.h
    endian.h       libintl.h          rpc               ttyent.h
    envz.h         libio.h            rpcsvc            uchar.h
    err.h          limits.h           sched.h           ucontext.h
    errno.h        link.h             scratch_buffer.h  ulimit.h
    error.h        list.h             search.h          unistd.h
    execinfo.h     locale.h           set-hooks.h       utime.h
    fcntl.h        malloc.h           setjmp.h          utmp.h
    features.h     math.h             sgtty.h           values.h
    fenv.h         mcheck.h           shadow.h          wchar.h
    fmtmsg.h       memory.h           shlib-compat.h    wctype.h
    fnmatch.h      mntent.h           signal.h          wordexp.h
    fpu_control.h  monetary.h         spawn.h           xlocale.h
    ftw.h          mqueue.h           stab.h


Reading some functions of ``glibc``
===================================

Reading ``strlen``
------------------

*   Let us see the code of ``strcmp.c``. The file is present in the extracted glibc directory.

::

	#include <string.h>

	#undef strcmp

	#ifndef STRCMP
	# define STRCMP strcmp
	#endif

	/* Compare S1 and S2, returning less than, equal to or
	   greater than zero if S1 is lexicographically less than,
	   equal to or greater than S2.  */
	int
	STRCMP (const char *p1, const char *p2)
	{
	  const unsigned char *s1 = (const unsigned char *) p1;
	  const unsigned char *s2 = (const unsigned char *) p2;
	  unsigned char c1, c2;

	  do
		{
		  c1 = (unsigned char) *s1++;
		  c2 = (unsigned char) *s2++;
		  if (c1 == '\0')
		return c1 - c2;
		}
	  while (c1 == c2);

	  return c1 - c2;
	}
	libc_hidden_builtin_def (strcmp)

*   The code is pretty simple to understand. It iterates through the string till
    the time it finds both the characters equal.

    What I want to emphasize is that the glibc is just a collect of c functions,
    written in c files, packaged and compiled, and we can also make similar
    functions and libraries and publish.

Walkthrough ``div``
-------------------

*   Let us now see the code of ``stdlib/div.c``. I have again picked a very simple
    function which will enable you to understand that the functions and
    functionality provided by the glibc is just a simple function which we write
    almost daily in our code.

::

	#include <stdlib.h>

	/* Return the `div_t' representation of NUMER over DENOM.  */
	div_t
	div (int numer, int denom)
	{
	  div_t result;

	  result.quot = numer / denom;
	  result.rem = numer % denom;

	  return result;
	}

Compiling and installing ``glibc``
==================================

Generally compiling and installing code on Linux system involves the following stages

1.  Configuring -   running ``configure`` with right options.
2.  Compiling   -   running ``make`` with right options.
3.  Install     -   running ``make install``.

We will also go through the same steps and complete compilation and installation of the new library.

Configuring ``glibc``
---------------------

We will get into the glibc-2.24 source directory and run the ``configure``
script. I have intentionally shown the mistakes which happened so that you also
understand the small things which needs to be taken care while configuring and
compiling.

::

    rishi@rishi-VirtualBox:~/glibc-2.24$ ./configure
    checking build system type... x86_64-pc-linux-gnu
    checking host system type... x86_64-pc-linux-gnu
    checking for gcc... gcc
    checking for suffix of object files... o
    checking whether we are using the GNU C compiler... yes
    checking whether gcc accepts -g... yes
    checking for readelf... readelf
    checking for g++... g++
    checking whether we are using the GNU C++ compiler... yes
    checking whether g++ accepts -g... yes
    checking whether g++ can link programs... yes
    configure: error: you must configure in a separate build directory


*   We got an error that we should use a separate directory for running ``configure``

::

    rishi@rishi-VirtualBox:~/glibc-2.24$ mkdir ../build_glibc

    rishi@rishi-VirtualBox:~/glibc-2.24$ cd ../build_glibc/

*   Let us now run the configure command.


::

    rishi@rishi-VirtualBox:~/build_glibc$ ../glibc-2.24/configure
    checking build system type... x86_64-pc-linux-gnu
    checking host system type... x86_64-pc-linux-gnu
    checking for gcc... gcc
    checking for suffix of object files... o
    checking version of sed... 4.2.2, ok
    checking for gawk... no

    >>>>>>>>>>>>>>>>>SNIP<<<<<<<<<<<<<<<<<<<<<<

    checking if gcc is sufficient to build libc... yes
    checking for nm... nm
    configure: error:
    *** These critical programs are missing or too old: gawk
    *** Check the INSTALL file for required versions.

*   The configure step gave errors - let us install ``gawk`` now.

::

    rishi@rishi-VirtualBox:~/build_glibc$ sudo apt-get install gawk
    [sudo] password for rishi:
    Reading package lists... Done
    Building dependency tree
    Reading state information... Done
    The following additional packages will be installed:
    libsigsegv2
    Suggested packages:
    gawk-doc
    The following NEW packages will be installed:
    gawk libsigsegv2

    >>>>>>>>>>>>>SNIP<<<<<<<<<<<<<<

    Setting up gawk (1:4.1.3+dfsg-0.1) ...

*   Check if the command is present.

::

    rishi@rishi-office:~/mydev/publications/system_calls$ which gawk
    /usr/bin/gawk


*   Let us run configure again

::

    rishi@rishi-VirtualBox:~/build_glibc$ ../glibc-2.24/configure
    checking build system type... x86_64-pc-linux-gnu
    checking host system type... x86_64-pc-linux-gnu
    checking for gcc... gcc
    checking for suffix of object files... o
    checking whether we are using the GNU C compiler... yes

    >>>>>>>>>>SNIP<<<<<<<<<<<<<<<<<<<<<<

    running configure fragment for sysdeps/unix/sysv/linux/x86_64
    running configure fragment for sysdeps/unix/sysv/linux
    checking installed Linux kernel header files... 3.2.0 or later
    checking for kernel header at least 2.6.32... ok
    *** On GNU/Linux systems the GNU C Library should not be installed into
    *** /usr/local since this might make your system totally unusable.
    *** We strongly advise to use a different prefix.  For details read the FAQ.
    *** If you really mean to do this, run configure again using the extra
    *** parameter `--disable-sanity-checks`.


*   Configure does not want to overwrite the default library and hence we need to give another directory to install the library.


*   Let us make a directory and run the configure script.

::

    rishi@rishi-VirtualBox:~/build_glibc$ mkdir ../install_glibc
    rishi@rishi-VirtualBox:~/build_glibc$ ../glibc-2.24/configure --prefix=/home/rishi/install_glibc/
    checking build system type... x86_64-pc-linux-gnu
    checking host system type... x86_64-pc-linux-gnu
    checking for gcc... gcc
    checking for suffix of object files... o
    configure: creating ./config.status

    >>>>>>>SNIP<<<<<<<<<<<<

    config.status: creating config.make
    config.status: creating Makefile
    config.status: creating config.h
    config.status: executing default commands


*   Configure completed

::

    rishi@rishi-VirtualBox:~/build_glibc$ ls
    bits  config.h  config.log  config.make  config.status  Makefile

Compiling ``glibc``
-------------------

*   Let us run the ``make`` command now. Go to the ``build_glibc`` directory and run the ``make`` command.

::

    rishi@rishi-VirtualBox:~/build_glibc$ make -j 16
    make -r PARALLELMFLAGS="" -C ../glibc-2.24 objdir=`pwd` all
    make[1]: Entering directory '/home/rishi/glibc-2.24'
    LC_ALL=C gawk -f scripts/sysd-rules.awk > /home/rishi/build_glibc/sysd-rulesT \


    rishi@rishi-VirtualBox:~/build_glibc$ ls
    bits  config.h  config.log  config.make  config.status  Makefile
    rishi@rishi-VirtualBox:~/build_glibc$
    rishi@rishi-VirtualBox:~/build_glibc$
    rishi@rishi-VirtualBox:~/build_glibc$


    rishi@rishi-VirtualBox:~/build_glibc$ make -j 16
    make -r PARALLELMFLAGS="" -C ../glibc-2.24 objdir=`pwd` all
    make[1]: Entering directory '/home/rishi/glibc-2.24'
    LC_ALL=C gawk -f scripts/sysd-rules.awk > /home/rishi/build_glibc/sysd-rulesT \

        >>>>>>>>>>>>>>>>>>>>>SNIP<<<<<<<<<<<<<<<<<<<
    gcc -nostdlib -nostartfiles -o /home/rishi/build_glibc/elf/pldd    -Wl,-z,combreloc -Wl,-z,relro -Wl,--hash-style=both /home/rishi/build_glibc/csu/crt1.o /home/rishi/build_glibc/csu/crti.o `gcc  --print-file-name=crtbegin.o` /home/rishi/build_glibc/elf/pldd.o /home/rishi/build_glibc/elf/xmalloc.o  -Wl,-dynamic-linker=/home/rishi/install_glibc/lib/ld-linux-x86-64.so.2 -Wl,-rpath-link=/home/rishi/build_glibc:/home/rishi/build_glibc/math:/home/rishi/build_glibc/elf:/home/rishi/build_glibc/dlfcn:/home/rishi/build_glibc/nss:/home/rishi/build_glibc/nis:/home/rishi/build_glibc/rt:/home/rishi/build_glibc/resolv:/home/rishi/build_glibc/crypt:/home/rishi/build_glibc/mathvec:/home/rishi/build_glibc/nptl /home/rishi/build_glibc/libc.so.6 /home/rishi/build_glibc/libc_nonshared.a -Wl,--as-needed /home/rishi/build_glibc/elf/ld.so -Wl,--no-as-needed -lgcc  `gcc  --print-file-name=crtend.o` /home/rishi/build_glibc/csu/crtn.o
    make[2]: Leaving directory '/home/rishi/glibc-2.24/elf'
    make[1]: Leaving directory '/home/rishi/glibc-2.24'

*   Make runs successfully.

*   Let us check the ``install_glibc`` directory. It has nothing in it.

::

    $ ls ../install_glibc/

*   Let us run the ``make install`` command. This needs to be done in the ``build_glibc`` directory.

::

    $ make install
    LC_ALL=C; export LC_ALL; \
    make -r PARALLELMFLAGS="" -C ../glibc-2.24 objdir=`pwd` install
    make[1]: Entering directory '/home/rishi/glibc-2.24'
    make  subdir=csu -C csu ..=../ subdir_lib
    make[2]: Entering directory '/home/rishi/glibc-2.24/csu'
    make[2]: Leaving directory '/home/rishi/glibc-

    >>>>>>>>>>>SNIP<<<<<<<<<<<<<<<

    -f /home/rishi/build_glibc/elf/symlink.list
    test ! -x /home/rishi/build_glibc/elf/ldconfig || LC_ALL=C \
    /home/rishi/build_glibc/elf/ldconfig  \
    /home/rishi/install_glibc/lib /home/rishi/install_glibc/lib
    /home/rishi/build_glibc/elf/ldconfig: Warning: ignoring configuration file that cannot be opened: /home/rishi/install_glibc/etc/ld.so.conf: No such file or directory
    make[1]: Leaving directory '/home/rishi/glibc-2.24'

Installing ``glibc``
--------------------

*   Let us now check the ``install_glibc`` directory. It has the required files of the new compiled library.

::

    rishi@rishi-VirtualBox:~/build_glibc$ ls ../install_glibc/
    bin  etc  include  lib  libexec  sbin

Using new ``glibc``
===================

Let us now use the above library to link and run our code. We will add a new
function to the ``glibc``, change the behaviour of a function in glibc and use the
new function and call the changed function.

This will give us a good understanding of how to compile and link with the new
library.

Here is the code for adding some changes to the glibc code. See the file
``glibc-2.24/stdlib/div.c`` and ``glibc-2.24/include/stdlib.h``.

Here is the diff

``glibc-2.24/stdlib/div.c``
---------------------------

*   Here we have added a function ``my_div`` which just returns -1 on invokation
    and have changed the way the function div behaves. Now when we will pass 99 and
    99 to div it will return 100 and 100. Read the default behaviour in the man
    pages.

::

    $ diff glibc-2.24/stdlib/div.c temp/glibc-2.24/stdlib/div.c
    51d50
    < #include <stdio.h>
    59,64d57
    <   if (numer == 99 && denom == 99) {
    <   printf ("\nValues are 99 and 99");
    <   result.quot = 100;
    <   result.rem = 100;
    <   return result;
    <   }
    69,74d61
    < }
    <
    <
    < int my_div(void) {
    <   printf("\n\nCalling my_div() function.");
    <   return -1;

*   Here is the declaration of the new function.

``glibc-2.24/stdlib/stdlib.h``
------------------------------

::

    $ diff glibc-2.24/stdlib/stdlib.h temp/glibc-2.24/stdlib/stdlib.h
    753,754d752
    <
    < extern int my_div(void);

*   Here is the code which calls the functions.

.. literalinclude:: code_system_calls/05/div.c
    :linenos:
    :language: c

*   Here is the ``Makefile`` which will be used to compile the program.

.. literalinclude:: code_system_calls/05/Makefile
    :linenos:
    :language: make

*   Run the ``make`` command.

::

    $ make
    gcc -g -c div.c -I `gcc --print-file-name=include` -I /home/rishi/install_glibc/include
    gcc -nostdlib -nostartfiles -static -o div /home/rishi/install_glibc/lib//crt1.o /home/rishi/install_glibc/lib//crti.o `gcc --print-file-name=crtbegin.o` div.o -Wl,--start-group /home/rishi/install_glibc/lib//libc.a -lgcc -lgcc_eh -Wl,--end-group `gcc --print-file-name=crtend.o` /home/rishi/install_glibc/lib//crtn.o

*   Run the statically linked code

::

    $ ./div

    Values are 99 and 99

    Calling my_div() function.

    Quotient 100 Remainder 100

*   See the size of the staticically linked code. The huge size is due to static linking. In case of dynamically linked code the size will be very less.

::

    $ ls -lh div
    -rwxrwxr-x 1 rishi rishi 3.3M Jan 29 20:00 div
                            ^^^^^^^

*   Check the file type of the executable.

::

    rishi@rishi-VirtualBox:~/test_code$ file static-test
    static-test: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), statically linked, for GNU/Linux 2.6.32, BuildID[sha1]=866f4fe367915159ae62cc80a0ae614059d67153, not stripped

Conclusion
==========

In this chapter we have see pretty important things with respect to using
glibc. We have see where to find glibc, how to download, extract, make changes
and compile the glibc library in your system.

Doing all the steps hands-on will enable you understand the whole workflow more
clearly and will thus improve your understanding of systems.
