#include "DatabaseManager.h"
#include "LevelManager.h"

DatabaseManager::DatabaseManager(){
	open(_path_to_db);
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

void DatabaseManager::hydrate(){
	int return_value(0), i(0);
	bool clickable = false;
	std::vector<Entity> entities;
	std::string query="SELECT id, name, left, top, width, height, clickable, clicked  FROM ENTITY WHERE map_id="+std::to_string(_level_manager->_current_map+1);
	std::cout<<query<<std::endl;
	return_value = sqlite3_prepare_v2(_db, query.c_str(), -1, &_stmt, 0);
	if(return_value){
		std::cout<<"Error while preparing query!"<<std::endl;
	} else{
		bool loop = true;
		int return_value_anim(1);
		sqlite3_stmt* stmt_anim;
		while(loop){
			return_value = sqlite3_step(_stmt);
			if(return_value==SQLITE_ROW){
				clickable=sqlite3_column_int(_stmt,6);
				int id=sqlite3_column_int(_stmt,0);
				if(clickable){
					std::vector<std::string> replies=selectReplies(id);
					_level_manager->_text_map[id]=replies;
				}
				std::vector<Animation> anim=selectAnimations(id);
				Entity entity(_level_manager->_texture,sqlite3_column_int(_stmt, 2),sqlite3_column_int(_stmt, 3),sqlite3_column_int(_stmt, 4),sqlite3_column_int(_stmt, 5),sqlite3_column_int(_stmt, 6),sqlite3_column_int(_stmt, 7),reinterpret_cast<const char*>(sqlite3_column_text(_stmt,1)),sqlite3_column_int(_stmt, 0),anim);
				if(sqlite3_column_int(_stmt, 7))
					entity.changeState(false);
				entities.push_back(entity);
			}else {
				loop=false;
			}

		}
		_level_manager->_map = entities;
		for(int i=0; i<entities.size(); i++){
			entities.at(i).display();
		}
		sqlite3_finalize(_stmt);
	}
}

std::vector<std::string> DatabaseManager::selectReplies(int entity_id){
	sqlite3_stmt* stmt;
	int return_value(0), i(0);
	std::vector<std::string> replies;
	std::string query="SELECT content  FROM REPLY WHERE entity_id="+std::to_string(entity_id);
	return_value = sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, 0);
	if(return_value){
		std::cout<<"Error while preparing query!"<<std::endl;
	} else{
		bool loop = true;
		while(loop){
			return_value = sqlite3_step(stmt);
			if(return_value==SQLITE_ROW){
				std::string str=reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
				replies.push_back(str);
			} else {
				loop=false;
			}
		}
	}
	sqlite3_finalize(stmt);
	return replies;
}

std::vector<Animation> DatabaseManager::selectAnimations(int entity_id){
	std::vector<Animation> anim;
	sqlite3_stmt* stmt_anim;
	int return_value_anim(0);
	std::string query_anim = "SELECT * FROM ANIMATION A WHERE A.entity_id="+std::to_string(entity_id);
	return_value_anim=sqlite3_prepare_v2(_db, query_anim.c_str(), -1, &stmt_anim, 0);
	if(return_value_anim){
		std::cout<<"Could not fetch animations!"<<std::endl;
	} else {
		std::cout<<"Animation loading!"<<std::endl;
		bool loop_anim=true;
		while (loop_anim){
			return_value_anim=sqlite3_step(stmt_anim);
			if(return_value_anim==SQLITE_ROW){
				anim.push_back(Animation(150, reinterpret_cast<const char*>(sqlite3_column_text(stmt_anim, 2)),sqlite3_column_int(stmt_anim, 3),sqlite3_column_int(stmt_anim, 4),sqlite3_column_int(stmt_anim, 5),sqlite3_column_int(stmt_anim, 6),sqlite3_column_int(stmt_anim, 7),sf::seconds(sqlite3_column_double(stmt_anim, 8))));
			} else{
				loop_anim=false;
			}
		}

	}
	sqlite3_finalize(stmt_anim);
	return anim;
}

void DatabaseManager::save(){
	for(int i=0;i<_level_manager->_map.size();i++){
		updateClicked(_level_manager->_map.at(i).getId());	
	}
}

void DatabaseManager::updateClicked(int id){
	sqlite3_stmt* stmt;
	int return_code(0);
	for(int i=0; i<_level_manager->_map.size(); i++){
		std::string query="UPDATE ENTITY SET clicked="+std::to_string(_level_manager->_map.at(i)._clicked)+" WHERE id="+std::to_string(_level_manager->_map.at(i)._id);
		std::cout<<query<<std::endl;
		return_code = sqlite3_exec(_db, query.c_str(), NULL, NULL, NULL);
		if(return_code)
			std::cout<<"Failed to update clicked item in database!"<<std::endl;
		else
			std::cout<<"Updated clicked item in database!"<<std::endl;
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

void DatabaseManager::setLevelManager(LevelManager* level_manager){
	_level_manager = level_manager;
}
