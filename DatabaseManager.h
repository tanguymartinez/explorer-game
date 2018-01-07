#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_
#include "sqlite3.h"
#include <string>
#include <iostream>
#include "EntityData.h"
#include <vector>
#include <sstream>
#include <utility>
#include <iostream>
#include <fstream>

class DatabaseManager{
	private:
		sqlite3* _db;
		sqlite3_stmt* _stmt;
		int _return_code;
		const std::string _path_to_map="res/map_data";
		std::vector<std::vector<EntityData> > _entities_map;
		std::vector<std::string> explode(const std::string & s, char delim) const;
	public:
		DatabaseManager();
		void open(std::string file);
		void close();
		void select();
		void insertEntities(std::vector<Entity> entities);
};

#endif
