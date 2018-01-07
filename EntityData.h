#ifndef ENTITYDATA_H_
#define ENTITYDATA_H_
#include <string>

class EntityData{
	public:
		std::string _name;
		int _id=-1;
		bool _clickable;
		int _x;
		int _y;
		int _width;
		int _height;
		EntityData();
		EntityData(const std::string& name, int id, bool clickable, int x, int y, int width, int height);
};

#endif
