#include "Entity.h"

Entity::Entity(){

}

Entity::Entity(const sf::Texture& texture, int left, int top, int width, int height, bool clickable, bool clicked, std::string name, int id, std::vector<Animation>& animations){
	sf::IntRect int_rect(left,top,width,height);
	std::cout<<"Animations in entity: "<<animations.size()<<std::endl;
	_sprite = AnimatedSprite(texture, int_rect, animations);
	_sprite.getSprite().scale(SCALE, SCALE);
	_sprite.getSprite().setPosition(int_rect.left*SCALE, int_rect.top*SCALE);
	_init_pos = sf::Vector2f(int_rect.left*SCALE, int_rect.top*SCALE);
	_clickable = clickable;
	_name = name;
	_id=id;
	_clicked = clicked;
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

bool Entity::isClickable() const{
	return _clickable;
}

void Entity::setClicked(){
	_clicked=true;
}
