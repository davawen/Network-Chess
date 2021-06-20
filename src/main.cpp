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
	
	sf::Sprite *selectedPiece = nullptr;
	sf::Vector2i selectedOffset;
	sf::Vector2i startIndex;
	
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
				{
					auto mousePos = sf::Mouse::getPosition(window);
					startIndex = { mousePos.x / 100, mousePos.y / 100 };
				
					selectedPiece = board.getPieceSprite( startIndex.x, startIndex.y );
					
					selectedOffset = sf::Vector2i(selectedPiece->getPosition()) - mousePos;
				}
					break;
				case sf::Event::MouseButtonReleased:
				{
					auto mousePos = sf::Mouse::getPosition(window); 
					
					if(mousePos.x > 0 && mousePos.x < 800 && mousePos.y > 0 && mousePos.y < 800)
					{
						board.movePiece(startIndex.x, startIndex.y, mousePos.x / 100, mousePos.y / 100);
					}
					
					board.update();
					
					selectedPiece = nullptr;
				}
					break;
				default:
					break;
			}
		}
		
		if(selectedPiece != nullptr)
		{
			selectedPiece->setPosition(sf::Vector2f(sf::Mouse::getPosition(window) + selectedOffset));
		}

        window.clear();
		
		board.draw(window);
		
        window.display();
    }
	
	return 0;
}