#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Entity.h"
#include "LevelManager.h"
#include "constants.h"
#include "DatabaseManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOWS_WIDTH,WINDOWS_HEIGHT), "Explorer Game");
    window.setFramerateLimit(FRAMERATE_LIMIT);
    LevelManager level_manager(&window);
    DatabaseManager dbm;
    level_manager.setDatabaseManager(&dbm);
    dbm.setLevelManager(&level_manager);
    dbm.hydrate();
    sf::Clock clock;
    while (window.isOpen())
    {
	    sf::Event event;
	    while (window.pollEvent(event))
	    {
		    if (event.type == sf::Event::Closed)
			    window.close();
	    }
	    if(clock.getElapsedTime().asSeconds() > 1.0f/60){
		    clock.restart();
		    window.clear();
		    level_manager.interact();
		    level_manager.animate();
		    window.draw(level_manager);
		    window.display();
	    }
    }
    return 0;
}
