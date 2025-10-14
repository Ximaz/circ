# CIRC - Client for IRC

This project provides C source code to build both an IRC client and server. As
it is new, it's not ready yet for use.

## Build & Run everywhere

This project uses Makefiles to build the sources. It uses special C compiler
flags to make sure the project is as stable as possible when it comes to memory
management.

The `-ansi` and `-pendantic` flags are used to make sure older compilers can
build the project, and it also makes thing easier when it comes to coding style
and formatting.
