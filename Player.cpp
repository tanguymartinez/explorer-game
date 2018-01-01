#include "Player.h"

Player::Player(){

}

Player::Player(const sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos, bool clickable, std::string name, int id, int nb_frames, sf::Time time) : Entity(texture, rect, pos, clickable, name, id, nb_frames, time){

}

void Player::setPositionLeft(){
	std::cout<<"Putting player left!"<<std::endl;
	_sprite.getSprite().setPosition(_init_pos.x+GAP, _init_pos.y);
}

void Player::setPositionRight(){
	std::cout<<"Putting player right!"<<std::endl;
	_sprite.getSprite().setPosition(WINDOWS_WIDTH-_init_pos.x-_sprite.getSprite().getGlobalBounds().width-GAP, _init_pos.y);
}
