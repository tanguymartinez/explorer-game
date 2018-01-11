#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

class LevelManager;

#include "sqlite3.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iostream>
#include <fstream>
#include "Entity.h"
#include "Animation.h"

class DatabaseManager{
	private:
		sqlite3* _db;
		sqlite3_stmt* _stmt;
		int _return_code;
		LevelManager* _level_manager;
		const std::string _path_to_db="res/data/explorer.sqlite3";
		const std::string _path_to_map="res/map_data";
		std::vector<std::string> explode(const std::string & s, char delim) const;
	public:
		DatabaseManager();
		void open(std::string file);
		void close();
		void saveEntities();
		void hydrate();
		void setLevelManager(LevelManager* level_manager);
		std::vector<std::string> selectReplies(int entity_id);
};

#endif
