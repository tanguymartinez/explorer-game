#ifndef IntelligentText_h
#define IntelligentText_h
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "constants.h"
#include "Clickable.h"
#include "Entity.h"

enum POSITION{
	POS_LEFT,
	POS_RIGHT,
	POS_TOP,
	POS_BOTTOM
};

class IntelligentText : public sf::Drawable, public sf::Transformable, public Clickable{
	private:
		sf::Text _text;
		Entity _relative_to;
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen
		sf::Vector2f calculatePosition() const;
		sf::RectangleShape _rect;
		void setPosition(sf::Vector2f pos);
		bool _clickable=true;
		int _MAX_WIDTH=300;
	public:
		IntelligentText();
		IntelligentText(const Entity& relative_to, const sf::Font& font, const std::string str);
		bool isEmpty() const;
		void resetPosition();
		std::string getText() const {return _text.getString();}
		void setText(const std::string);

		//Inherited from clickable
		virtual bool clicked(sf::Window* w) const;
		virtual sf::FloatRect getGlobalBounds() const; 
		virtual bool hovered(sf::Window* w) const;
};

#endif
