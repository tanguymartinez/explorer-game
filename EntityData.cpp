#include "EntityData.h"

EntityData::EntityData(){

}

EntityData::EntityData(const std::string& name, int id, bool clickable, int x, int y, int width, int height){
	_name=name;
	_id=id;
	_clickable=clickable;
	_x=x;
	_y=y;
}
	
