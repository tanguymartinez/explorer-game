#ifndef LevelManager_h
#define LevelManager_h
#include <sstream>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "IntelligentText.h"
#include <map>
#include "Clickable.h"

class LevelManager : public sf::Drawable {
	private:
		//MAP OF ENTITIES
		std::vector<std::vector<Entity> > _map;
		int _current_map=0;
		const std::string _spritesheet_path="res/image/spritesheet.png";
		const std::string _path_to_map="res/map";
		sf::Texture _texture;
		sf::RectangleShape _selected_shape;
		Player _player;
		void loadMap(std::vector<std::vector<Entity> >& map, const std::string); //loads map into _map
		std::map<int, bool> _clicked_map;
		const std::string _clicked_map_path="res/clicked";
		void loadClickedMap(std::map<int, bool>& clicked_map, std::string path);
		void addClickedEntry(int id, bool state, std::string path) const;
		sf::Window* _window=0;
		bool _has_selected=false;
		bool _can_unselect=false;
		Entity* _selected;
		const std::string _path_to_font_regular="res/font/OpenSans-Regular.ttf";

		//TEXT
		sf::Font _font_regular;
		IntelligentText _text;
		const std::string _path_to_text="res/text/";
		std::map<int, std::vector<std::string> > _text_map; //loads texts into a vector of vector (1st dimension = number of entities in level, 2nd dimension = number of replies
		int _reply_cursor=0;
		std::string relativePath(int a, int b) const; //get the path
		void loadText(std::map<int, std::vector<std::string> >& text_map, std::string path);

		//GENERAL
		std::vector<std::string> explode(const std::string & s, char delim) const;
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen

		//CLICK MANAGER
		bool _was_pressed=false;
		bool _pressed=false;
		bool _registered=false;
		sf::Vector2f _mouse_pos;
	public:
		LevelManager(sf::Window* w);
		bool clickDetected();
		void detectLevelChange();
		void animate();
		void interact(); 
		bool getEntityUnderCursor(Entity*& e);
		bool getTextUnderCursor(IntelligentText& t);
		bool unselected(const Entity& e);
		void loadLevel(int map);
};
#endif
