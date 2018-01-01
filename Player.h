#ifndef Player_h
#define Player_h
#include "Entity.h"
#include "constants.h"

class Player : public Entity{
	private:

	public:
		Player();
		Player(const sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos, bool clickable, std::string name, int id, int nb_frames, sf::Time time);
		void setPositionLeft();
		void setPositionRight();
};

#endif
