# explorer-game
A simple exploration game using SFML.

Hey there, find below the pieces of information you need to understand my little project.

## Motivation
This project is:
- for fun
- to improve myself
- to try this thingy called Github

## SFML-based game (C++)
See [SFML's Website](http://sfml-dev.org/) for installation and documentation.

The game is very basic at the moment, you "spawn" in a disgusting level (which was made for debugging and testing really), you can walk and click entities. When you click an entity, one reply show at a time.

## About the stucture of the project
Every resource file is located somewhere in the _res_ folder.
See the help file for guidelines on how to edit maps (very basic at the moment).

This is is the first project I push to Github, happy reviewing!
(and by the way, help is always welcome)

## A note on the bash scripts
There are 2 scripts that I have made (very simple ones):
- _cr\_sfml.sh_: Checks in the _files\_list_ file for files to compile, and then compiles them
- _animation\_to_sprite.sh_ : this one uses ImageMagick, and is handy to create a small spritesheet only containing the animation frames (from separate .png files)

__NOTE__: I am developping on Debian! The executable is called sfml-app for now (subject to change).
