#include "Player.h"

Player::Player(){
}

Player::Player(const sf::Texture& texture, int left, int top, int width, int height, bool clickable, bool clicked,  std::string name, int id, std::vector<Animation>& animations) : Entity(texture, left, top, width, height, clickable, clicked,  name, id, animations){ 
	std::cout<<"Player initialized!"<<std::endl;
}

void Player::setPositionLeft(){
	std::cout<<"Putting player left!"<<std::endl;
	_sprite.getSprite().setPosition(_init_pos.x+GAP, _init_pos.y);
}

void Player::setPositionRight(){
	std::cout<<"Putting player right!"<<std::endl;
	_sprite.getSprite().setPosition(WINDOWS_WIDTH-_init_pos.x-_sprite.getSprite().getGlobalBounds().width-GAP, _init_pos.y);
}

void Player::display() const{
	display();
}
