#ifndef Entity_h
#define Entity_h
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Clickable.h"
#include "AnimatedSprite.h"

const float SCALE = 10;

enum DIRECTION{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Entity : public sf::Drawable, public sf::Transformable, public Clickable{
	private: //private member variables
		AnimatedSprite _sprite; //Sprite representing the player
		std::string _name="Entity";
		int _speed=5; //its speed
		int _id;
		bool _clickable = true;

	private: //private member functions
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen
	public:
		Entity();
		//Entity(const std::string path, const sf::IntRect rect, const sf::Vector2f pos);
		Entity(const sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos, bool clickable, std::string name, int id, int nb_frames, sf::Time time);
		~Entity();
		void move(DIRECTION d); //moves in the DIRECTION direction
		void display() const;
		std::string getName() const {return _name;}
		int getId() const {return _id;}
		void animate(bool state);

		//Inherited from Clickable
		virtual bool clicked(sf::Window* w) const;
		virtual sf::FloatRect getGlobalBounds() const; 
		virtual bool hovered(sf::Window* w) const;
};
#endif
