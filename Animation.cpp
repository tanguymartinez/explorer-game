#include "Animation.h"
Animation::Animation(){

}

Animation::Animation(int spritesheet_width, std::string name, int left, int top, int width, int height, int nb_frames, sf::Time duration){
	_clock = sf::Clock();
	_name=name;
	sf::IntRect base_rect(left,top,width,height);
	_nb_frames = nb_frames;
	_entities_rect.reserve(nb_frames);
	int y=base_rect.top;
	int x=base_rect.left;
	for(int i=0; i<nb_frames; i++){
		sf::IntRect int_rect;
		if(x+base_rect.width>spritesheet_width){
			y+=base_rect.height;
			x=0;
		} else if(i>0){
			x+=base_rect.width;
		}
		int_rect=sf::IntRect(x, y, base_rect.width, base_rect.height);
		_entities_rect.push_back(int_rect);
	}
	_duration = duration;
}

void Animation::animate(){
	if(_play && _clock.getElapsedTime()>_duration && _nb_frames>1){
		_clock.restart();
		if(_position >= _nb_frames-1){
			_position=0;
		} else{
			_position++;
		}
	}
}

void Animation::play(){
	_play=true;
}

void Animation::pause(){
	_play=false;
}

void Animation::stop(){
	_position=0;
	_play=false;
}

sf::IntRect Animation::getFrame() const{
	return _entities_rect.at(_position);
}

void Animation::display() const{
	std::cout<<"Nb frames of animation: "<<_nb_frames<<std::endl;
}
