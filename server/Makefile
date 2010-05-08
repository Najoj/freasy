#  Makefile for the Java server part of Freasy.
#  Made by Johan Öhlin on his birthday, 2010. <johanohl@kth.se>
#
#  `make all' or just `make' will compile and create a jar file.
#  `make compile' will compile class-files.
#  `make jar' will create to jar file.
#  `make clean' will remove _every_ jar file and class object.
#  `make help' will display this help description.
#
#  A Java compiler, javac, is required.

all: compile jar

compile: snor/SNOR.java Database/PADSQL.java		\
         Files/RequestFile.java Static/ParserConstants.java
	javac snor/SNOR.java
	javac Database/PADSQL.java
	javac Files/RequestFile.java
	javac Static/ParserConstants.java

jar: manifest
	jar -cfm Server.jar manifest */*class

clean :
	rm -fv */*class
	rm -fv *jar

help :
	grep make\  Makefile
