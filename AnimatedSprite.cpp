#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(){

}

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, sf::IntRect base_rect, std::vector<Animation>& animations){
	_animations = animations;
	std::cout<<"Animation size in AnimatedSprite constructor: "<<_animations.size()<<std::endl;
	int y=base_rect.top;
	int x=base_rect.left;
	_sprite.setTexture(texture);
	_sprite.setTextureRect(base_rect);
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
	_animations.at(_current_animation).animate();
	_sprite.setTextureRect(_animations.at(_current_animation).getFrame());
}

void AnimatedSprite::play(){
	_animations.at(_current_animation).play();
}

void AnimatedSprite::pause(){
	_animations.at(_current_animation).pause();
}

void AnimatedSprite::stop(){
	_animations.at(_current_animation).stop();
}
