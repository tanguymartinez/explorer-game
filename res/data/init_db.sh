#!/bin/bash
#Argument 1: path to the sql init file
#Argument 2: path to database file
echo "Running $0 script!"
if [ "$#" -eq 2 ]; then
	if [ -f "$2" ]; then
		sqlite3 $1 < $2
		echo 'Successfully initialized database!'
	else
		echo "Argument 2 is not a file!"
	fi
fi
