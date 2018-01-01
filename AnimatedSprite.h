#ifndef AnimatedSprite_h
#define AnimatedSprite_h
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class AnimatedSprite : public sf::Drawable, public sf::Transformable{
	private:
		std::vector<sf::IntRect> _entities_rect;
		sf::Sprite _sprite;
		int _position=0;
		sf::Time _duration;
		sf::Clock _clock;
		bool _play=false;
		int _nb_frames=1;
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen
	public:
		AnimatedSprite();
		AnimatedSprite(const sf::Texture& texture, sf::IntRect base_rect, int nb_frames, sf::Time duration);
		const sf::Sprite& getSprite() const;
		sf::Sprite& getSprite();
		void animate();
		void play();
		void pause();
		void stop();
};

#endif
