#ifndef AnimatedSprite_h
#define AnimatedSprite_h
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Animation.h"

class AnimatedSprite : public sf::Drawable, public sf::Transformable{
	private:
		std::vector<Animation> _animations;
		sf::Sprite _sprite;
		int _current_animation=0;
		bool _play=true;
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen
	public:
		AnimatedSprite();
		AnimatedSprite(const sf::Texture& texture, sf::IntRect base_rect, std::vector<Animation>& animations);
		const sf::Sprite& getSprite() const;
		sf::Sprite& getSprite();
		void animate();
		void play();
		void pause();
		void stop();
};

#endif
