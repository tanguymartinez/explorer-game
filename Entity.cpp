#include "Entity.h"

Entity::Entity(){

}

Entity::Entity(const sf::Texture& texture, sf::IntRect int_rect, sf::Vector2f pos, bool clickable, std::string name, int id, int nb_frames, sf::Time time){
	_sprite = AnimatedSprite(texture, int_rect, nb_frames, time);
	_sprite.getSprite().scale(SCALE, SCALE);
	_sprite.getSprite().setPosition(pos.x*SCALE, pos.y*SCALE);
	_init_pos = sf::Vector2f(pos.x*SCALE, pos.y*SCALE);
	_clickable = clickable;
	_name = name;
	_id=id;
}

Entity::~Entity(){

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// You can draw other high-level objects
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

void Entity::move(DIRECTION d){
	switch(d){
		case DIRECTION::UP:
			_sprite.getSprite().move(0, -_speed);
			break;
		case DIRECTION::DOWN:
			_sprite.getSprite().move(0, _speed);
			break;
		case DIRECTION::LEFT:
			_sprite.getSprite().move(-_speed, 0);
			break;
		case DIRECTION::RIGHT:
			_sprite.getSprite().move(_speed, 0);
			break;
		default:
			break;
	}
}

void Entity::display()const{
	std::cout<<"Name: "<<_name<<" @ "<<_sprite.getSprite().getGlobalBounds().left<<"/"<<_sprite.getSprite().getGlobalBounds().top<<"; width: "<<_sprite.getSprite().getGlobalBounds().width<<", height: "<<_sprite.getSprite().getGlobalBounds().height<<std::endl;
}

bool Entity::clicked(sf::Window* w) const{
	std::cout<<"Checking "<<_name<<"!"<<std::endl;
	display();
	std::cout<<"Clickable: "<<_clickable<<std::endl;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hovered(w)){
		return true;
	} else{
		return false;
	}
}

bool Entity::hovered(sf::Window* w) const{
	if(getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*w).x, sf::Mouse::getPosition(*w).y)) && _clickable){
		return true;
	} else{
		return false;
	}

}

sf::FloatRect Entity::getGlobalBounds() const{
	return _sprite.getSprite().getGlobalBounds();
}

void Entity::animate(){
	_sprite.animate();
}

void Entity::changeState(bool state){
	if(state){
		_sprite.play();
	} else{
		_sprite.stop();
	}
}
