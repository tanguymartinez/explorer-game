#!/bin/bash

#Script to load data from text to database
#Argument 1: path to database file
#ARgument 2: path to maps' raw file
#Argument 2: path to entities' raw file
#Argument 3: path to animations' raw file
#Argument 4: path to replies' map raw file

#Argument 1: path to database file
#Argument 3: array to process (containes every lines)
parseInsert(){
	declare -a qp=($3)
	declare -a sub=("${!2}")
	declare string
	for((j=0; j<${#sub_arr[@]}; j++)); do
		if [ "$j" -eq 0 ] && [[ "${qp[@]}" =~ $j ]]; then
			string="NULL,'${sub_arr[$j]}'"
		elif [ "$j" -eq 0 ]; then
			string="NULL,${sub_arr[$j]}"
		elif [[ "${qp[@]}" =~ $j ]]; then
			string="${string},'${sub_arr[$j]}'"
		else
			string="${string},${sub_arr[$j]}"
		fi
	done
	echo $string
	sqlite3 $1 "INSERT INTO $4 VALUES ($string);"
}

readLoop(){
	declare -a qrl=($3)
	declare -a arr
	mapfile arr < $2
	declare -a sub_arr
	for((i=0; i<${#arr[@]}; i++)); do
		if [ "${arr[$i]}" != "" ]; then
			sub_arr=(${arr[$i]})
			parseInsert $1 $sub_arr "${qrl[*]}" $4
		fi			
	done

}

echo "Running script $0"
if [ "$#" -eq 3 ]; then
	if [ -f "$1" ] && [ -f "$2" ] && [ -f "$3" ]; then
		declare -a q=(1)
		readLoop $1 $2 "${q[*]}" ENTITY
		q=(0)
		readLoop $1 $3 "${q[*]}" MAP
	else
		echo 'This script takes files as arguments!'
	fi
else
	echo 'Wrong number of arguments!'
fi
