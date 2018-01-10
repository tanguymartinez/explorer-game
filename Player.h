#ifndef Player_h
#define Player_h
#include "Entity.h"
#include "constants.h"

class Player : public Entity{
	private:

	public:
		Player();
		Player(const sf::Texture& texture, int left, int top, int width, int height, bool clickable, bool clicked,  std::string name, int id, std::vector<Animation>& animations);
		void setPositionLeft();
		void setPositionRight();
		void display()const;
};

#endif
