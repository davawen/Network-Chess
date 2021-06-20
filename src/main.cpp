#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <future>
#include <filesystem>

#include <sys/ioctl.h>

#include <SFML/Graphics.hpp>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "board.hpp"

namespace fs = std::filesystem;

namespace Date
{
	enum Unit
	{
		/**Nanosecond*/
		NS = 1,
		/**Microsecond*/
		US = 1000,
		/**Milisecond*/
		MS = 1000000
	};
	
	/**
	 * Returns the amount of time since the processor was started in the given unit
	 */
	long now(Unit unit = Unit::MS)
	{
		return std::chrono::high_resolution_clock::now().time_since_epoch().count() / unit;
	}
}

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");

	sf::Texture textureBoard, texturePieces;
	
	Board board{&textureBoard, &texturePieces};
	
	board.setPiece(7, 2, Board::Index::Bishop | Board::Index::White);
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		
		board.draw(window);
		
        window.display();
    }
	
	return 0;
}