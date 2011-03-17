#!/bin/sh
#
# Depends on libpg-java	- Java database (JDBC) driver for PostgreSQL
#

killall -9 java

svn checkout http://freasy.googlecode.com/svn/trunk/server .

make

java -jar Server.jar
