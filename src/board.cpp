#include "board.hpp"

void Board::initializeTextures(sf::Texture *textBoard, sf::Texture *textPieces)
{
	if(!textBoard->create(800, 800))
	{
		throw "Failed to create texture.";
	}

	//Create board
	sf::Uint8 *boardPixels = new sf::Uint8[800 * 800 * 4];

	for(int j = 0; j < 800; j++)
	{
		for(int i = 0; i < 800; i++)
		{
			int index = ( i + ( j * 800 ) ) * 4;

			bool isLight = ( i + ( j / 100 % 2 ) * 100 ) / 100 % 2 == 0;

			boardPixels[index] = isLight ? 240 : 168;
			boardPixels[index + 1] = isLight ? 216 : 121;
			boardPixels[index + 2] = isLight ? 192 : 101;
			boardPixels[index + 3] = 255;
		}
	}

	textBoard->update(boardPixels);
	
	if(!textPieces->loadFromFile("assets/chess_pieces.png"))
	{
		throw "Unable to load pieces texture";
	}
	textPieces->setSmooth(true);
	
	this->textBoard = textBoard;
	this->textPieces = textPieces;
}

sf::IntRect Board::getPieceTexPos(Board::Index index)
{
	int row = (index & Board::Index::White) == Board::Index::White ? 0 : 200;
	
	int col = 0;
	
	// int a = ~5;
	
	switch(index & ~Board::Index::White & ~Board::Index::Black)
	{
		case Board::Index::Queen:
			col = 200;
			break;
		case Board::Index::Bishop:
			col = 400;
			break;
		case Board::Index::Knight:
			col = 600;
			break;
		case Board::Index::Rook:
			col = 800;
			break;
		case Board::Index::Pawn:
			col = 1000;
			break;
	}
	
	return sf::IntRect(col, row, 200, 200);
}

Board::Board(sf::Texture *textBoard, sf::Texture *textPieces)
{
	this->initializeTextures(textBoard, textPieces);
	
	this->boardSprite = sf::Sprite();
	this->boardSprite.setTexture(*textBoard);
	
	//Initialize Board at none
	for(int i = 0; i < 64; i++)
	{
		this->board[i] = Board::Index::None;
	}
	
	this->update();
}

Board::Index Board::operator()(int x, int y)
{
	if(x < 0 || x >= 8 || y < 0 || y >= 8) throw std::invalid_argument("Index out of bounds");

	return board[y * 8 + x];
}

void Board::setPiece(int x, int y, Board::Index value)
{
	if(x < 0 || x >= 8 || y < 0 || y >= 8) throw std::invalid_argument("Index out of bounds");

	board[y * 8 + x] = value;
	
	update();
}

void Board::update()
{
	pieces.clear();
	
	for(int i = 0; i < 64; i++)
	{
		if(board[i] != Board::Index::None)
		{
			sf::Sprite sprite;
			sprite.setTexture(*textPieces);
			sprite.setTextureRect(getPieceTexPos(board[i]));
			sprite.setPosition( i%8 * 100, i/8 * 100 );
			sprite.setScale(0.5f, 0.5f);
			
			pieces.push_back(sprite);
		}
	}
}

void Board::draw(sf::RenderWindow &window)
{
	window.draw(boardSprite);
	
	for(auto &piece : pieces)
	{
		window.draw(piece);
	}
}