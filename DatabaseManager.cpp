#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(){

}

DatabaseManager::DatabaseManager(LevelManager* lm){
	_level_manager = lm;
}

void DatabaseManager::open(std::string file){
	_return_code = sqlite3_open_v2(file.c_str(), &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if(_return_code){
		std::cout<<"Database not opened! Error code: "<<_return_code<<std::endl;
	} else{
		std::cout<<"Database created/opened!"<<std::endl;
		std::cout<<"Enabling foreign keys!"<<std::endl;
		int return_code = sqlite3_exec(_db, "PRAGMA foreign_keys = ON", NULL, NULL, NULL);
		if(return_code){
			std::cout<<"Failed to enable foreign keys!"<<std::endl;
		} else{
			std::cout<<"Enabled foreign keys successfully!"<<std::endl;
		}
	}
}

void DatabaseManager::close(){
	sqlite3_close(_db);
}

void DatabaseManager::selectEntities(){
	int return_value(0), i(0);
	std::vector<std::string> rows;
	std::string query="SELECT id, name, left, top, width, height, clickable  FROM ENTITY WHERE map_id="+std::to_string(_level_manager->_current_map);
	return_value = sqlite3_prepare_v2(_db, query.c_str(), -1, &_stmt, 0);
	if(return_value){
		std::cout<<"Error while preparing query!"<<std::endl;
	} else{
		bool loop = true;
		while(loop){
			return_value = sqlite3_step(_stmt);
			if(return_value==SQLITE_ROW){
				rows.push_back(sqlite3_column_int(_stmt, 0)+sqlite3);
			} else {
				loop=false;
			}
		}
	}
	sqlite3_finalize(_stmt);
}

void insertEntities(){
	
}

std::vector<std::string> DatabaseManager::explode(const std::string & s, char delim) const{
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim); )
	{
		result.push_back(std::move(token));
	}

	return result;
}

void DatabaseManager::saveEntities(){
	
}
