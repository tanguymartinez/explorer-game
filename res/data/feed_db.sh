#!/bin/bash

#Script to load data from text to database
#Argument 1: path to database file
#Argument 2: path to maps' raw file
#Argument 2: path to entities' raw file
#Argument 3: path to animations' raw file
#Argument 4: path to replies' map raw file

parseInsert(){
	declare -a qp=($3)
	declare string
	declare -a disp_parent_ids
	if [ "$#" -ge 5 ]; then
		columns=$(sqlite3 $1 "PRAGMA table_info($4)")
		case $5 in
			[12])
				echo $(sqlite3 $1 "SELECT id, name FROM $6")
				echo "Type in the desired $6 id for the $4 ${sub_arr[0]}:"
				read string
				for((j=0; j<${#sub_arr[@]}; j++)); do
					if [[ "${qp[@]}" =~ $j ]]; then
						string="${string},'${sub_arr[$j]}'"
					else
						string="${string},${sub_arr[$j]}"
					fi
				done
				declare -a columns_arr=($(gawk -F"|" '
				BEGIN{i=0; sub_str=1;}
				{arr[i]=$2; i++;}
				END{for(j=0;j<length(arr)-sub_str;j++){
					if(j==(NR-sub_str-1))
						printf("%s", arr[j]);
					else
						printf("%s%s", arr[j], ",");
				}}' < <(echo "$columns")))
				declare nb_defaults=($(gawk -F"|" '
				BEGIN{i=0;}
				{if($5!=""){
					i++;
				}
				}
				END{printf("%d", i);}' < <(echo "$columns")))
				declare string_null
				if (( $nb_defaults > 1 )); then
					for((k=0;k<$nb_defaults;k++));do
						if (( $k == 0 )); then
							string_null="NULL,$string_null"
						else
							string_null="${string_null},NULL"
						fi
					done
				else
					string_null=NULL
				fi
				if (( $5 == 1)); then 
					sqlite3 $1 "INSERT INTO $4 VALUES (NULL,$string, $string_null);"
				else
					sqlite3 $1 "INSERT INTO $4 VALUES (NULL,$string)"
				fi
				;;
			*)
				for((j=0; j<${#sub_arr[@]}; j++)); do
					if [ "$j" -eq 0 ] && [[ "${qp[@]}" =~  $j ]]; then
						string="NULL,'${sub_arr[$j]}'"
					elif [ "$j" -eq 0 ]; then
						string="NULL, ${sub_arr[$j]}"
					elif [[ "${qp[@]}" =~ $j ]]; then
						string="${string},'${sub_arr[$j]}'"
					else
						string="${string},${sub_arr[$j]}"
					fi
				done
				declare -a columns_arr=($(gawk -F"|" '
				BEGIN{i=0; sub_str=2;}
				{arr[i]=$2; i++;}
				END{for(j=0;j<length(arr)-sub_str;j++){
				if(j==(NR-sub_str-1))
					printf("%s", arr[j]);
				else
					printf("%s%s", arr[j], ",");
				}}' < <(echo "$columns")))
				sqlite3 $1 "INSERT INTO $4(${columns_arr[@]}) VALUES ($string);"
				;;
		esac
	fi
	echo "Inserted values into $4!"
}

#Usefull for reading and inserting raw map files
readLoop(){
	declare -a qrl=($3)
	declare -a arr
	mapfile arr < $2
	declare -a sub_arr
	for((i=0; i<${#arr[@]}; i++)); do
		if [ "${arr[$i]}" != "" ]; then
			sub_arr=(${arr[$i]})
			parseInsert $1 $sub_arr "${qrl[*]}" $4 $5 $6
		fi			
	done

}

#Useful for reading and inserting replies
readLinesInsert(){
	declare -a entities=($(sqlite3 $1 "SELECT * FROM $3"))
	declare -a field
	echo "${entities[@]}"
	for((i=0; i<${#entities[@]}; i++)); do
		fields=($(echo "${entities[$i]}" | gawk -F"|" '{printf("%d %d %s %d",$(NF-1),$2,$3, $1);}'))
		echo ${fields[0]}
		if [ "${fields[0]}" -ne 0 ]; then
			echo "Please enter path to ${fields[2]} in map ${fields[1]}"
			read input
			if [ -f "$input" ]; then
				declare -a lines
				mapfile lines < $input
				for((j=0; j<${#lines[@]}; j++)); do
					string="'${lines[$j]}'"
					string=$(echo -n $string)
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
if [ "$#" -eq 5 ]; then
	if [ -f "$1" ] && [ -f "$2" ] && [ -f "$3" ] && [ -f "$4" ]  && [ -f "$5" ]; then
		declare -a q=(0)
		readLoop $1 $2 "${q[*]}" MAP 0
		readLoop $1 $3 "${q[*]}" ENTITY 1 MAP
		readLoop $1 $4 "${q[*]}" ANIMATION 2 ENTITY
		readLinesInsert $1 $5 ENTITY REPLY
	else
		echo 'This script takes files as arguments!'
	fi
else
	echo 'Wrong number of arguments!'
fi
