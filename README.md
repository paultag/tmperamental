libtmperamental
===============

tmperamental is a library that intercepts filesystem writes, and causes loud
failures when writes are attempted on /tmp/\*.

The idea here is by setting TMPDIR and friends, you are able to use
libtmperamental to catch programs in the act of not respecting such
env-vars.

Basic Usage:
------------

    TMPDIR=~/.tmp LD_PRELOAD=/usr/lib/tmperamental/libtmperamental.so app arguments

In the event the app causes problems, you should see some stderr and a
nonzero exit status.

Things to keep in mind:
-----------------------

This library is *not* to be linked against, just preloaded.

![](http://static.guim.co.uk/sys-images/Society/Pix/pictures/2010/4/21/1271861774568/Crying-Baby-001.jpg)
