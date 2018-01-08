#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_
#include "sqlite3.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iostream>
#include <fstream>
#include "Entity.h"
#include "LevelManager.h"

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
		DatabaseManager(LevelManager* lm);
		void open(std::string file);
		void close();
		void saveEntities();
		void selectEntities();
};

#endif
