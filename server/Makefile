#  Makefile for the Java server part of Freasy.
#  Made by Johan Öhlin 2010. <johanohl@kth.se>
#
#  `make all' or just `make' will create a JAR-file
#  `make compile' will compile to class-files.
#  `make compile' will compile to class-files.
#  `make clean' will remove _every_ class object in the subdirectories.
#  `make help' will display this.
#
#  A Java compiler, javac, is required.

all: compile manifest
	jar -cfm Server.jar manifest */*class

jar: manifest
	jar -cfm Server.jar manifest */*class

compile: snor/snor.java Database/PADSQL.java				\
     Files/RequestFile.java Static/ParserConstants.java
	javac snor/snor.java
	javac Database/PADSQL.java
	javac Files/RequestFile.java
	javac Static/ParserConstants.java

clean :
	rm -v */*class

help :
	grep make\  Makefile
