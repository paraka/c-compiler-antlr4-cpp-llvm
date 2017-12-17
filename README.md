# c-compiler-antlr4-cpp-llvm

Writting a C compiler in c++ has been in my TODO list for a long time. It is time to make it real.

The idea is to use antlr4 (4.7 version) which let us to create a cpp backend from grammar and to use awesome llvm for code generation.

= Compile project =

$ mkdir build
$ cd build
$ cmake ..
$ make -j 8
