GrizzlyManager
============

Authors: Vladimir Bartosik, Martin Kuzma, Marek Moravcik.

GrizzlyManager is lightweight utility for remote web administration of Linux server based on MonGoose.
It is written in C++ under GNU GPLv3 license. The core program runs as
service and can load modules (compiled as shared libraries) and use their functionalities.

Features:
- fast and modular administration tool
- module implementation as shared libraries in C++ (fast with limitless possibilities!)
- simple module API
- ajax support (see examples for more)
- jQuery and jQueryUI
- free and open source :)

Planned features:
- set of basic tools available for modules to ease things up
- authentification with strict connection policy
- example modules
- session handling
- init.d and systemd integration
- .configure script
- debian packages (x86, x64, armhf, armel)


License: GNU GPLv3

Repository: https://github.com/emem123/GrizzlyManager.git


Installation
===========

configure
***

This script checks if you have permissions to install GrizzlyManager,
if another instance of GrizzlyManager is running, if TCP port 80
is not used by another application. It also checks if you hane init.d
or Systemd script system on your computer.

make
****

Compiles core program and modules.

make install
***********

Creates service that runs GrizzlyManager during boot and copies necessary
files to filesystem.

make clean
***

This removes all compiled files, binaries, shared objects and so on.
It leaves only source code files. Make clean ends with error, but it is OK,
because it erases itself.

adding new modules
******************

If you want to add new modules, add all source files into src/modules/YourDirectory.
If your module need some additional files which do not have to be compiled, create
subdirectory with name libYourDirectory. This subdirectory will be copied into modules
folder with your compiled module.
