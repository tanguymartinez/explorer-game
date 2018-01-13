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
	friend class DatabaseManager;
	protected: //private member variables
		AnimatedSprite _sprite; //Sprite representing the player
		sf::Vector2f _init_pos;
		
	private: //private member functions
		virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const; //redefine the draw function to allow a nice syntax when drawing to the screen
		std::string _name="Entity";
		int _speed=5; //its speed
		int _id;
		bool _clickable = true;
		bool _clicked = false;

	public:
		Entity();
		Entity(const sf::Texture& texture, int left, int top, int width, int height, bool clickable, bool clicked, std::string name, int id, std::vector<Animation>& animations);
		void move(DIRECTION d); //moves in the DIRECTION direction
		void display() const;
		std::string getName() const {return _name;}
		int getId() const {return _id;}
		void animate();
		void changeState(bool state);
		bool isClickable() const;
		void setClicked();

		//Inherited from Clickable
		virtual bool clicked(sf::Window* w) const;
		virtual sf::FloatRect getGlobalBounds() const; 
		virtual bool hovered(sf::Window* w) const;
};
#endif
