#include "LevelManager.h"

LevelManager::LevelManager(sf::Window* window){
	_window = window;
	_current_map=0;
	loadMap(_map, _path_to_map);
	std::cout<<"Map loaded!"<<std::endl;
	_player = Entity(_texture, sf::IntRect(0, 150, 20, 70), sf::Vector2f(0,10), false, "Player", 0, 7, sf::seconds(.1f));
	_selected_shape.setFillColor(sf::Color::Transparent);
	_selected_shape.setOutlineThickness(5);
	_selected_shape.setOutlineColor(sf::Color::Black);
	if(_font_regular.loadFromFile(_path_to_font_regular)){	
		loadText(_text_map, _path_to_text);
		std::cout<<"Text map loaded!"<<std::endl;
	} else{
		std::cout<<"Error while loading the font!"<<std::endl;
	}
}

void LevelManager::loadMap(std::vector<std::vector<Entity> >& map, const std::string path){
	std::ifstream stream(path.c_str());
	std::string line;
	sf::Vector2f pos;		
	sf::Vector2f from;
	std::vector<std::string> vect;
	std::vector<Entity> tmp_entities;
	int i=0;
	if(_texture.loadFromFile(_spritesheet_path)){
		if(stream){
			while(getline(stream, line)){
				vect = explode(line, ' ');
				if(vect.size()==11){
					std::cout<<"Adding a tile in the map!"<<std::endl;
					tmp_entities.push_back(Entity(_texture, sf::IntRect(std::stof(vect.at(0)), std::stof(vect.at(1)), std::stof(vect.at(2)), std::stof(vect.at(3))), sf::Vector2f(std::stof(vect.at(4)), std::stof(vect.at(5))), std::stoi(vect.at(6)), vect.at(7), std::stoi(vect.at(8)), std::stoi(vect.at(9)), sf::seconds(std::stof(vect.at(10)))));
				} else if(vect.size()==0){
					std::cout<<"Adding a level to the map!"<<std::endl;
					map.push_back(tmp_entities);
					tmp_entities.clear();
				} else{
					std::cout<<"Wrong number of arguments in map file at line "<<i<<"!"<<std::endl;
				}
				i++;
			}
		} else{
			std::cout<<path<<" error!"<<std::endl;
		}
	} else{
		std::cout<<"Cannot load map texture!"<<std::endl;
	}
	for(int i=0; i<map.size(); i++){
		std::cout<<"Level "<<i<<" contains "<<map.at(i).size()<<" tiles!"<<std::endl;
	}
}

std::vector<std::string> LevelManager::explode(const std::string & s, char delim) const{
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim); )
	{
		result.push_back(std::move(token));
	}

	return result;
}

void LevelManager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	// You can draw other high-level objects
	if(_map.size()>0){
		for(int i=0; i<_map.at(_current_map).size(); i++){
			target.draw(_map.at(_current_map).at(i), states);
		}
		target.draw(_text, states);
		target.draw(_selected_shape, states);
		target.draw(_player, states);
	}
}

void LevelManager::animate(){
	for(int i=0; i<_map.at(_current_map).size(); i++){
		_map.at(_current_map).at(i).animate(true);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		_player.move(DIRECTION::LEFT);
		_player.animate(true);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		_player.move(DIRECTION::RIGHT);
		_player.animate(true);
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		_player.animate(false);
	}
}

void LevelManager::interact(){
	if(clickDetected()){
		Entity e;
		if(getEntityUnderCursor(e) && !_has_selected){
			e.display();
			_selected_shape.setSize(sf::Vector2f(e.getGlobalBounds().width, e.getGlobalBounds().height));
			_selected_shape.setPosition(e.getGlobalBounds().left, e.getGlobalBounds().top);
			_selected = e;
			_has_selected = true;
			for(int i=0; i<_text_map[e.getId()].size(); i++)
				std::cout<<"Text in text map @ "<<e.getId()<<": "<<_text_map[e.getId()].at(i)<<std::endl;
			_text = IntelligentText(e, _font_regular, _text_map[e.getId()].at(_reply_cursor));
			std::cout<<"Text relating to the entity clicked: "<<_text.getText()<<std::endl;
			_reply_cursor++;
		} else if(_has_selected){
			if(_text_map[_selected.getId()].size()>_reply_cursor){
				_text = IntelligentText(_selected, _font_regular, _text_map[_selected.getId()].at(_reply_cursor));
				_reply_cursor++;
			} else{
				_can_unselect = true;
				_has_selected=false;
				_selected_shape.setSize(sf::Vector2f(0,0));
				_text = IntelligentText();
				_reply_cursor=0;
			}
		}
	}
}

bool LevelManager::unselected(const Entity& e){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !e.hovered(_window)){
		return true;
	} else{
		return false;
	}
}

bool LevelManager::getEntityUnderCursor(Entity& e){
	for(int i=0; i<_map.at(_current_map).size(); i++){
		if(_map.at(_current_map).at(i).hovered(_window)){
			std::cout<<"Sprite "<<_map.at(_current_map).at(i).getName()<<" clicked!"<<std::endl;
			e = _map.at(_current_map).at(i);
			e.display();
			return true;
		}
	}
	return false;
}

bool LevelManager::getTextUnderCursor(IntelligentText& t){
	if(_text.hovered(_window)){
		std::cout<<t.getText()<<" clicked!"<<std::endl;
		t = _text;
		return true;
	}
	return false;
}

void LevelManager::loadText(std::map<int, std::vector<std::string> >& text_map, std::string path){
	std::string line;
	std::string str="";
	int cursor=0;
	std::vector<std::string> str_vect;
	std::cout<<"Map size:"<<_map.size()<<std::endl;
	std::cout<<"Map size @ "<<_map.at(_current_map).size()<<std::endl;
	for(int i=0; i<_map.at(_current_map).size(); i++){
		int id=_map.at(_current_map).at(i).getId();
		std::ifstream stream((path+relativePath(_current_map, id)).c_str());
		if(stream){
			std::cout<<"Now reading the text map file!"<<std::endl;
			while(getline(stream, line)){
				if(line==""){
					cursor++;
					std::cout<<"Reply added to the text map!"<<std::endl;
					str_vect.push_back(str);
					str="";
				} else{
					str+=line;
				}
			}
			str="";
		} else{
			std::cout<<"Cannot open text file @ "<<_current_map<<"/"<<i<<"!"<<std::endl;
		}
		_text_map[id]=str_vect;
		str="";
		str_vect.clear();
	}
}

std::string LevelManager::relativePath(int a, int b) const{
	return std::to_string(a)+"/"+std::to_string(b);
}



bool LevelManager::clickDetected(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		_pressed=true;
		_mouse_pos=sf::Vector2f(sf::Mouse::getPosition());
	} else if(_pressed){
		_pressed=false;
		_was_pressed=true;
		_registered=false;
	}
	if(!_registered && !_pressed && _was_pressed){
		_registered=true;
		std::cout<<"Click detected!"<<std::endl;
		return true;
	} else{
		return false;
	}
}
