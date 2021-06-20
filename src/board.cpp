#include "board.hpp"

Board::Board()
{
	if(!this->boardTexture.create(800, 800))
	{
		throw "Texture failed to create.";
	}
	
	//Create board
	sf::Uint8 *boardPixels = new sf::Uint8[800 * 800 * 4];
	
	for(int j = 0; j < 800; j++)	
	{
		for(int i = 0; i < 800; i++)
		{
			int index = (i + (j*800)) * 4;
			
			int value = (i + (j / 100 % 2)*100) / 100 % 2 == 0 ? 255 : 0;
			
			boardPixels[index  ] = value;	
			boardPixels[index+1] = value;
			boardPixels[index+2] = value;
			boardPixels[index+3] = 255;
			
			// this->shape[i] = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
			
			// this->shape[i].setPosition((i % 8)*50.f, (i / 8)*50.f);
			// this->shape[i].setFillColor(i % 2 == 0 ? sf::Color::White : sf::Color::Black);
		}
	}
	
	this->boardTexture.update(boardPixels);
	
	this->boardSprite = sf::Sprite();
	this->boardSprite.setTexture(boardTexture);
}

void Board::draw(sf::RenderWindow &window)
{
	window.draw(boardSprite);
}