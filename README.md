# c-compiler-antlr4-cpp-llvm

Writting a C compiler in c++ has been in my TODO list for a long time. It is time to make it real.

The idea is to use antlr4 (4.7 version) which let us to create a cpp backend from grammar and to use awesome llvm for code generation.

= Installing antlr =

1. First of all install java and other dependencies:

$ apt-get install java default-jre-headless java-common libtreelayout-java openjdk-8-jre-headless

2. Download antlr4 and put in a proper path, for example /usr/local/lib

$ wget -c http://www.antlr.org/download/antlr-4.7.1-complete.jar
$ cp antlr-4.7.1-complete.jar /usr/local/lib/

3. Create some aliases and environment stuff in your ~/.bashrc:

$ vi ~/.bashrc

```
...

# antlr 4 stuff
export CLASSPATH=".:/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH"
alias antlr4='java -Xmx500M -cp "/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool'
alias grun='java org.antlr.v4.gui.TestRig'
```



