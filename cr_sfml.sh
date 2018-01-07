#!/bin/bash
name=sfml-app
echo  "Running $0 script!"
if [ "$#" -eq  1 ]; then
	if [ -f "$1" ]; then
		declare -a arr
		mapfile arr < $1
		declare string
		for ((i=0; i<${#arr[@]}; i++)); do
			string="$string${arr[$i]} "
		done
		echo "Content of the file: $string"
		echo "Now attempting to compile ${string}!"
		$(gcc $string -o $name -lpthread -ldl -lstdc++ -lsfml-window -lsfml-graphics -lsfml-system)
#		if [ "$?" -eq 0 ]; then
#			echo "Attempting to execute $name"
#			$(./$name)
#		else
#			echo "Failed to execute!"
#		fi
	else
		echo "Not a file, try again!"
	fi
else
	echo "Please specify one path and only one path!"
fi
