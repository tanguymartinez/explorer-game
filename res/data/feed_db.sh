#!/bin/bash

#Script to load data from text to database
#Argument 1: path to database file
#ARgument 2: path to maps' raw file
#Argument 2: path to entities' raw file
#Argument 3: path to animations' raw file
#Argument 4: path to replies' map raw file

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
	echo "Inserted values into $4!"
}

#Usefull for reading and inserting raw map files
readLoopInsert(){
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

#Useful for reading and inserting replies
readLinesInsert(){
	declare -a entities=($(sqlite3 $1 "SELECT * FROM $3"))
	declare field
	for((i=0; i<${#entities[@]}; i++)); do
		fields=($(echo "${entities[$i]}" | awk -F"|" '{printf("%d %d %s %d",$NF,$2,$3, $1);}'))
		if [ "${fields[0]}" -ne 0 ]; then
			echo "Please enter path to ${fields[2]} in map ${fields[1]}"
			read input
			if [ -f "$input" ]; then
				declare -a lines
				mapfile lines < $input
				for((j=0; j<${#lines[@]}; j++)); do
					string="'${lines[$j]}'"
					sqlite3 $1 "INSERT INTO $4 VALUES (NULL, ${fields[3]}, $j, $string);"
					echo "Inserted values into $4!"
				done
			else
				echo 'Please enter a valid file, continuing!'
			fi
		fi
	done
}

echo "Running script $0"
if [ "$#" -eq 4 ]; then
	if [ -f "$1" ] && [ -f "$2" ] && [ -f "$3" ]; then
		declare -a q=(0)
		readLoop $1 $2 "${q[*]}" MAP
		q=(1)
		readLoopInsert $1 $3 "${q[*]}" ENTITY
		readLinesInsert $1 $4 ENTITY REPLY
	else
		echo 'This script takes files as arguments!'
	fi
else
	echo 'Wrong number of arguments!'
fi
