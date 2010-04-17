#!/bin/sh

createdb $USER 2> /dev/null

psql -c "copy Product from stdin  delimiter '|';" < ~/Databas/Product

psql -c "copy Customer from stdin  delimiter '|';" < ~/Databas/Customer

psql -c "copy Membership from stdin  delimiter '|';" < ~/Databas/Membership

psql -c "copy Buys from stdin  delimiter '|';" < ~/Databas/Buys

psql -c "copy Rents from stdin  delimiter '|';" < ~/Databas/Rents

psql -c "copy Rent from stdin  delimiter '|';" < ~/Databas/Rent

psql -c "copy Sale from stdin  delimiter '|';" < ~/Databas/Sale
