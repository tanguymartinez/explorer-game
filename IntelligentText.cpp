#include "IntelligentText.h"

IntelligentText::IntelligentText(){
	_text.setString("");
	_text.setFillColor(sf::Color::Transparent);
	_rect.setSize(sf::Vector2f(0,0));
}

IntelligentText::IntelligentText(const Entity& relative_to, const sf::Font& font,  const std::string str){
	_relative_to = relative_to;
	_text.setFont(font);
	_text.setFillColor(sf::Color::Black);
	_text.setCharacterSize(FONT_SIZE);
	setText(str);
	resetPosition();
	_rect.setPosition(sf::Vector2f(_text.getGlobalBounds().left, _text.getGlobalBounds().top));
	_rect.setSize(sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height));
	_rect.setFillColor(sf::Color::White);
	_rect.setOutlineColor(sf::Color::Black);
}

void IntelligentText::setPosition(sf::Vector2f pos){
	_text.setPosition(pos.x, pos.y);
}

sf::Vector2f IntelligentText::calculatePosition() const{
	sf::FloatRect float_rect_self = _text.getGlobalBounds();
	sf::FloatRect float_rect_rel = _relative_to.getGlobalBounds();
	_relative_to.display();
	sf::Vector2f final_pos;
	if(WINDOWS_HEIGHT-(float_rect_rel.top+float_rect_rel.height)>=float_rect_self.height){
		//Put bottom
		final_pos.x = float_rect_rel.left;
		final_pos.y = (float_rect_rel.top+float_rect_rel.height);
	} else{ 
		//Put top
		final_pos.x = float_rect_rel.left;
		final_pos.y = (float_rect_rel.top-float_rect_self.height);
	}
	if(WINDOWS_WIDTH-(float_rect_rel.left+float_rect_rel.width)){
		//Put right
		final_pos.x = (float_rect_rel.left+float_rect_rel.width);
		//final_pos.y already calculated
	} else{
		//Put left
		final_pos.x = (float_rect_rel.left-float_rect_self.width);
		//final_pos.y already calculated
	}
	std::cout<<"Calculated text @ "<<final_pos.x<<"/"<<final_pos.y<<std::endl;
	return final_pos;
}

void IntelligentText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// You can draw other high-level objects
	target.draw(_rect, states);
	target.draw(_text, states);
}

bool IntelligentText::isEmpty() const{
	return _text.getString()=="";
}

void IntelligentText::resetPosition(){
	setPosition(calculatePosition());
}

void IntelligentText::setText(std::string str){
	_text.setString(str);
	for(int i=0; i<_text.getString().getSize(); i++){
		std::cout<<_text.findCharacterPos(i).x<<std::endl;
		if(_text.findCharacterPos(i).x>_MAX_WIDTH){
			std::cout<<"Breaking a line!"<<std::endl;
			std::string str = _text.getString();
			str.insert(i, "\n");
			_text.setString(str);
		}
	}
}

bool IntelligentText::clicked(sf::Window* w) const{
	std::cout<<"Checking text!"<<std::endl;
	std::cout<<"Clickable: "<<_clickable<<std::endl;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hovered(w)){
		return true;
	} else{
		return false;
	}
}

bool IntelligentText::hovered(sf::Window* w) const{
	if(_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*w).x, sf::Mouse::getPosition(*w).y)) && _clickable){
		return true;
	} else{
		return false;
	}

}

sf::FloatRect IntelligentText::getGlobalBounds() const{
	return _text.getGlobalBounds();
}
