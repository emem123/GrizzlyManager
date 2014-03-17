GrizzlyManager
============

Authors of this document: Vladimir Bartosik, Martin Kuzma, Marek Moravcik.

GrizzlyManager is utility for remote administration of Linux server.
It is written in C++ under GNU GPLv3 license. The core program runs as
service and can load modules (compiled as shared libraries) and use their functionalities.

License: GNU GPLv3

Repository: https://github.com/emem123/GrizzlyManager.git


Installation
===========

configure
***

This script checks if you have permissions to install GrizzlyManager,
if another instance of GrizzlyManager is running and if TCP port 80
is not used by another application.

make clean
***

This removes all compiled files, binaries, shared objects and so on.
It leaves only source code files and readme files.

make
****

Compiles core program and modules.

make install
***********

Creates service that runs GrizzlyManager during boot and copies necessary
files to filesystem.

make uninstall
*************

Removes installed files from filesystem and disable start GrizzlyManager
during boot.
