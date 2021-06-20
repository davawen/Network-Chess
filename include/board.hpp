#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdexcept>

#include <SFML/Graphics.hpp>

class Board
{
	private:
		sf::Texture boardTexture;
		sf::Sprite boardSprite;
		
		
		int time = 0;
		
		
		
	public:
		Board();
		
		/** Returns the piece at that given position */
		sf::RectangleShape *operator()(int x, int y)
		{
			
		}
		
		void draw(sf::RenderWindow &window);
};

#endif