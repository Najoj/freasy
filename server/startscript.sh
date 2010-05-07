#!/bin/sh
#
# Depends on libpg-java	- Java database (JDBC) driver for PostgreSQL
#

CWD=`pwd`

cd $CWD

killall -9 java

svn checkout http://freasy.googlecode.com/svn/trunk/server .

javac */*.java

make

java -jar Server.jar
