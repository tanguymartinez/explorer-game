#include "LevelManager.h"
#include "DatabaseManager.h"

LevelManager::LevelManager(){

}

LevelManager::LevelManager(sf::Window* window){
	_window = window;
	_current_map=0;
	if(_texture.loadFromFile(_spritesheet_path))
		std::cout<<"Spritesheet loaded!"<<std::endl;
	else
		std::cout<<"Error while loading spritesheet!"<<std::endl;
	loadClickedMap(_clicked_map, _clicked_map_path);
	std::cout<<"Clicked map loaded!"<<std::endl;
	std::cout<<"Map loaded!"<<std::endl;
	sf::IntRect int_rect(0, 150, 20, 70);
	Animation player_anim(150, int_rect.left, int_rect.top, int_rect.width, int_rect.height, 7, sf::seconds(.1f));
	std::vector<Animation> vect;
	vect.push_back(player_anim);
	_player=Player(_texture, int_rect.left, 75-70, int_rect.width, int_rect.height, 0, 0, "Player", 7, vect);
	_selected = 0; 
	_selected_shape.setFillColor(sf::Color::Transparent);
	_selected_shape.setOutlineThickness(5);
	_selected_shape.setOutlineColor(sf::Color::Black);
	if(_font_regular.loadFromFile(_path_to_font_regular)){	
		std::cout<<"Font loaded!"<<std::endl;
		std::cout<<"Text map loaded!"<<std::endl;
	} else{
		std::cout<<"Error while loading the font!"<<std::endl;
	}
}

LevelManager::~LevelManager(){
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
		for(int i=0; i<_map.size(); i++){
			target.draw(_map.at(i), states);
		}
		target.draw(_text, states);
		target.draw(_selected_shape, states);
		target.draw(_player, states);
	}
}

void LevelManager::animate(){
	for(int i=0; i<_map.size(); i++){
		_map.at(i).animate();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if(!(_player.getGlobalBounds().left<0 && _current_map==0)){
			_player.move(DIRECTION::LEFT);
			_player.changeState(true);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(!(_player.getGlobalBounds().left>WINDOWS_WIDTH-_player.getGlobalBounds().width && _current_map == _last_map)){
			_player.move(DIRECTION::RIGHT);
			_player.changeState(true);
		}
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		_player.changeState(false);
	}
	_player.animate();
}

void LevelManager::interact(){
	if(clickDetected()){
		Entity* e = getEntityUnderCursor();
		if(e!=nullptr && !_has_selected){
			_selected_shape.setSize(sf::Vector2f(e->getGlobalBounds().width, e->getGlobalBounds().height));
			_selected_shape.setPosition(e->getGlobalBounds().left, e->getGlobalBounds().top);
			_selected = e;
			_has_selected = true;
			for(int i=0; i<_text_map[e->getId()].size(); i++)
				std::cout<<"Text in text map @ "<<e->getId()<<": "<<_text_map[e->getId()].at(i)<<std::endl;
			_text = IntelligentText(*e, _font_regular, _text_map[e->getId()].at(_reply_cursor));
			std::cout<<"Text relating to the entity clicked: "<<_text.getText()<<std::endl;
			_reply_cursor++;
		} else if(_has_selected){
			if(_text_map[_selected->getId()].size()>_reply_cursor){
				_text = IntelligentText(*_selected, _font_regular, _text_map[_selected->getId()].at(_reply_cursor));
				_reply_cursor++;
			} else{
				addClickedEntry(_selected->getId(), 1, _clicked_map_path);
				_clicked_map[_selected->getId()]=1;
				std::cout<<"Stopping "<<_selected->getName()<<"'s animation!"<<std::endl;
				_selected->changeState(false);
				_can_unselect = true;
				_has_selected=false;
				_selected_shape.setSize(sf::Vector2f(0,0));
				_text = IntelligentText();
				_reply_cursor=0;
			}
		}	
	}
	detectLevelChange();
}

bool LevelManager::unselected(const Entity& e){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !e.hovered(_window)){
		return true;
	} else{
		return false;
	}
}

Entity* LevelManager::getEntityUnderCursor(){
	for(int i=0; i<_map.size(); i++){
		if(_map.at(i).hovered(_window)){
			std::cout<<"Sprite "<<_map.at(i).getName()<<" clicked!"<<std::endl;
			_map.at(i).display();
			return &(_map.at(i));
		}
	}
	return nullptr;
}

bool LevelManager::getTextUnderCursor(IntelligentText& t){
	if(_text.hovered(_window)){
		std::cout<<t.getText()<<" clicked!"<<std::endl;
		t = _text;
		return true;
	}
	return false;
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

void LevelManager::loadLevel(int map){
	_current_map=map;
}

void LevelManager::detectLevelChange(){
	if(_player.getGlobalBounds().left+_player.getGlobalBounds().width>WINDOWS_WIDTH-THRESHOLD){
		if(_current_map+1<_nb_maps){
			_text_map.clear();
			_map.clear();
			_current_map++;
			_player.setPositionLeft();
			std::cout<<"Going to hydrate in LevelManager!"<<std::endl;
			_dbm->hydrate();	
		}
	} else if(_player.getGlobalBounds().left<THRESHOLD){
		if(_current_map-1>=0){
			_text_map.clear();
			_map.clear();
			_current_map--;
			_player.setPositionRight();
			_dbm->hydrate();
		}
	}
}

void LevelManager::loadClickedMap(std::map<int, bool>& clicked_map, std::string path){
	std::ifstream stream(path.c_str());
	if(stream){
		std::vector<std::string> vect;
		std::string line;
		int i=0;
		while(getline(stream, line)){
			if(line!=""){
				vect=explode(line, ' ');
				if(vect.size()==2){
					clicked_map[std::stoi(vect.at(0))]=std::stoi(vect.at(1));
					std::cout<<"Clicked map, added a line: "<<clicked_map[std::stoi(vect.at(0))]<<std::endl;
				} else{
					std::cout<<"Line "<<i<<" got the wrong number of arguments!"<<std::endl;
				}
			}else{
				std::cout<<"Empty line!"<<std::endl;
			}
		} 
	} else{
		std::cout<<"Cannot open "<<path<<" file!"<<std::endl;
	}
}


void LevelManager::addClickedEntry(int id, bool state, std::string path) const{
	std::cout<<"Clicked map @ id "<<id<<": "<<_clicked_map.count(id)<<std::endl;
	if(_clicked_map.count(id)==0){
		std::ofstream stream(path.c_str(), std::ios::app);
		if(stream){
			stream<<std::to_string(id)<<" "<<std::to_string(state)<<std::endl;
			std::cout<<"Entry added to the clicked map!"<<std::endl;
		} else{
			std::cout<<"Failed to open stream "<<path<<std::endl;
		}
	}
}

void LevelManager::setDatabaseManager(DatabaseManager* dbm){
	_dbm = dbm;
}
