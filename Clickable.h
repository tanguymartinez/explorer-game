#ifndef Clickable_h
#define Clickable_h
#include <SFML/Graphics.hpp>

class  Clickable{
	public:
		virtual bool clicked(sf::Window* w) const = 0;
		virtual sf::FloatRect getGlobalBounds() const = 0; 
		virtual bool hovered(sf::Window* w) const = 0;
};

#endif
