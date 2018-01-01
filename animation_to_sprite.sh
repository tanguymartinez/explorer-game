#!/bin/bash
#1st argument: path to images to convert
#1nd argument: path to spritesheet
#3rd argument: name of new file
if [ "$#" -eq 3 ]; then
	if [ -d "$1" ] && [ -f "$2" ]; then
		declare -a arr
		i=0
		echo 'Processing files!'
		for file in ${1}*; do
			if [ `identify -format %e $file` = 'png' ]; then
				arr[$i]=$file
				let "i = i + 1" 
			fi
	done
		dest_width=`identify -format %w $2`
		echo "Destination width: ${dest_width}px"
		source_width=`identify -format %w ${arr[0]}`
		echo "Source width: ${source_width}px"
		source_height=`identify -format %h ${arr[0]}`
		echo "Source height: ${source_height}px"
		let "tiles_per_line =  dest_width / source_width"
		echo "$tiles_per_line"
		echo "Tiles per line: $tiles_per_line"
		if [ ${#arr[@]} -ge "$tiles_per_line" ]; then
			let "nb_lines = ${#arr[@]} / tiles_per_line"
		else
			nb_lines=1
		fi
		echo "Number of lines: $nb_lines"
		montage ${arr[*]} -tile ${tiles_per_line}x${nb_lines} -geometry ${source_width}x${source_height} -background transparent $1$3
	else
		echo "Please specify a directory and a file in that specific order!"
	fi
else
	echo "Wrong number of arguments!"
fi
