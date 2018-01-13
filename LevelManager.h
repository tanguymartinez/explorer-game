#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

class DatabaseManager;

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
#include "Animation.h"

class LevelManager : public sf::Drawable {
	friend class DatabaseManager;
	private:
		//DB MANAGER
		DatabaseManager* _dbm;
		//MAP OF ENTITIES
		std::vector<Entity> _map;
		int _current_map=0;
		int _last_map=2;
		int _nb_maps=3;
		const std::string _spritesheet_path="res/image/spritesheet.png";
		const std::string _path_to_map="res/map";
		sf::Texture _texture;
		sf::RectangleShape _selected_shape;
		Player _player;
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

		//GENERAL
		std::vector<std::string> explode(const std::string & s, char delim) const;
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen

		//CLICK MANAGER
		bool _was_pressed=false;
		bool _pressed=false;
		bool _registered=false;
		sf::Vector2f _mouse_pos;
	public:
		LevelManager();
		LevelManager(sf::Window* w);
		~LevelManager();
		bool clickDetected();
		void detectLevelChange();
		void animate();
		void interact(); 
		Entity* getEntityUnderCursor();
		bool getTextUnderCursor(IntelligentText& t);
		bool unselected(const Entity& e);
		void loadLevel(int map);
		void setDatabaseManager(DatabaseManager* dbm);
};
#endif
