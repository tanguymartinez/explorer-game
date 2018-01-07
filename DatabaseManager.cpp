#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(){
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

bool DatabaseManager::createTables(){
	bool success_q1=false;
	bool success_q2=false;
	bool success_q3=false;
	bool success_q4=false;
	int return_code=0;
	std::string query_map = 
		"CREATE TABLE IF NOT EXISTS MAP("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"name VARCHAR NOT NULL,"
			"created_at DATETIME DEFAULT CURRENT_TIME,"
			"updated_at DATETIME DEFAULT CURRENT_TIME);";
	return_code = sqlite3_exec(_db, query_map.c_str(), NULL, NULL, NULL);
	if(return_code){
		std::cout<<"Failed to create MAP table!"<<std::endl;
	} else{
		std::cout<<"Created/opened MAP table!"<<std::endl;
		success_q1=true;
	}
	
	std::string query_entity = 
		"CREATE TABLE IF NOT EXISTS ENTITY("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"map_id INTEGER NOT NULL,"
			"name VARCHAR NOT NULL,"
			"left INT NOT NULL,"
			"top INT NOT NULL,"
			"width INT NOT NULL,"
			"height INT NOT NULL,"
			"pos_x INT NOT NULL,"
			"pos_y INT NOT NULL,"
			"clickable BOOLEAN NOT NULL,"
			"FOREIGN KEY (map_id) REFERENCES MAP(id));";
	int return_value = sqlite3_exec(_db, query_entity.c_str(), NULL, NULL, NULL);
	if(return_value){
		std::cout<<"Error while creating ENTITY table! Error code: "<<return_value<<std::endl;
	} else{
		std::cout<<"Created/opened ENTITY table!"<<std::endl;
		success_q2=true;
	}
	std::string query_animation = 
		"CREATE TABLE IF NOT EXISTS ANIMATION("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"entity_id INTEGER NOT NULL,"
			"name VARCHAR NOT NULL,"
			"left INT NOT NULL,"
			"top INT NOT NULL,"
			"width INT NOT NULL,"
			"height INT NOT NULL,"
			"nb_frames INT NOT NULL,"
			"duration FLOAT NOT NULL,"
			"FOREIGN KEY (entity_id) REFERENCES ENTITY(id));";
	return_value = sqlite3_exec(_db, query_animation.c_str(), NULL, NULL, NULL);
	if(return_value){
		std::cout<<"Error while creating ANIMATION table! Error code: "<<return_value<<std::endl;
	} else{
		std::cout<<"Created/opened ANIMATION table!"<<std::endl;
		success_q3=true;
	}

	std::string query_reply = 
		"CREATE TABLE IF NOT EXISTS REPLY("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"entity_id INTEGER NOT NULL,"
			"at INT NOT NULL,"
			"content TEXT NOT NULL,"
			"FOREIGN KEY (entity_id) REFERENCES ENTITY(id));";
	return_value = sqlite3_exec(_db, query_animation.c_str(), NULL, NULL, NULL);
	if(return_value){
		std::cout<<"Error while creating ANIMATION table! Error code: "<<return_value<<std::endl;
	} else{
		std::cout<<"Created/opened ANIMATION table!"<<std::endl;
		success_q4=true;
	}
	if(success_q1 && success_q2 && success_q3 && success_q4){
		return true;
	} else{
		return false;
	}

}

void DatabaseManager::select(){
	int return_value(0), i(0);
	std::string query="SELECT * FROM contact";
	return_value = sqlite3_prepare_v2(_db, query.c_str(), -1, &_stmt, 0);
	if(return_value){
		std::cout<<"Error while preparing query!"<<std::endl;
	} else{
		bool loop = true;
		while(loop){
			return_value = sqlite3_step(_stmt);
			if(return_value==SQLITE_ROW){
				std::cout<<sqlite3_column_int(_stmt, 0)<<std::endl;
			} else {
				loop=false;
			}
		}
	}
	sqlite3_finalize(_stmt);
}

void insertEntities(){
	
}

void DatabaseManager::loadMapFile(std::vector<std::vector<EntityData> >& map, const std::string& path){
	std::ifstream stream(path.c_str());
	std::string line;
	std::vector<std::string> vect;
	std::vector<EntityData> tmp_entities;
	int i=0;
	if(stream){
		while(getline(stream, line)){
			vect = explode(line, ' ');
			if(vect.size()==6){
				std::cout<<"Hydrating EntityData!"<<std::endl;
				tmp_entities.push_back(EntityData());
				i++;
			} else if(vect.size()==0){
				std::cout<<"Hydrating next map!"<<std::endl;
				map.push_back(tmp_entities);
				tmp_entities.clear();
			} else{
				std::cout<<"Wrong number of arguments in map file at line "<<i<<"!"<<std::endl;
			}
			i++;
		}
	} else{
		std::cout<<path<<" error!"<<std::endl;
	}
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
