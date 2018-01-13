#ifndef Animation_h
#define Animation_h
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class Animation{
	private:
		std::vector<sf::IntRect> _entities_rect;
		int _position=0;
		sf::Time _duration;
		sf::Clock _clock;
		bool _play=true;
		int _nb_frames=1;
		std::string _name;
	public:
		Animation();
		Animation(int spritesheet_width, std::string name, int left, int top, int width, int height, int nb_frames, sf::Time duration);
		sf::IntRect getFrame() const;
		void animate();
		void play();
		void pause();
		void stop();
		void display() const;
};

#endif
