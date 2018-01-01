#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(){

}

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, sf::IntRect base_rect, int nb_frames, sf::Time duration){
	_clock = sf::Clock();
	std::cout<<nb_frames<<std::endl;
	_nb_frames = nb_frames;
	_entities_rect.reserve(nb_frames);
	int y=base_rect.top;
	int x=base_rect.left;
	std::cout<<"Baserect: "<<base_rect.left<<"/"<<base_rect.top<<std::endl;
	for(int i=0; i<nb_frames; i++){
		sf::IntRect int_rect;
		if(x+base_rect.width>texture.getSize().x){
			y+=base_rect.height;
			x=0;
		} else if(i>0){
			x+=base_rect.width;
		}
		int_rect=sf::IntRect(x, y, base_rect.width, base_rect.height);
		_entities_rect.push_back(int_rect);
	}
	_sprite.setTexture(texture);
	_sprite.setTextureRect(base_rect);
	_duration = duration;
}

const sf::Sprite& AnimatedSprite::getSprite() const{
	return _sprite;
}

sf::Sprite& AnimatedSprite::getSprite(){
	return _sprite;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// You can draw other high-level objects
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

void AnimatedSprite::animate(){
	if(_play && _clock.getElapsedTime()>_duration && _nb_frames>1){
		_clock.restart();
		if(_position >= _nb_frames-1){
			_position=0;
		} else{
			_position++;
		}
		_sprite.setTextureRect(_entities_rect.at(_position));
	}
}

void AnimatedSprite::play(){
	_play=true;
}

void AnimatedSprite::pause(){
	_play=false;
}

void AnimatedSprite::stop(){
	_position=0;
	_play=false;
	_sprite.setTextureRect(_entities_rect.at(0));
}
