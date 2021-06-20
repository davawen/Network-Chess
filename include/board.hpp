#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdexcept>
#include <vector>

#include <SFML/Graphics.hpp>


class Board
{
	public:
		enum struct Index
		{
			None = 0,
			King = 1,
			Pawn = 2,
			Knight = 3,
			Bishop = 4,
			Rook = 5,
			Queen = 6,

			White = 8,
			Black = 16
		};
		
	
	private:
		sf::Texture *textBoard;
		sf::Texture *textPieces;
	
		sf::Sprite boardSprite;
		std::vector<sf::Sprite> pieces;
		
		Board::Index board[64];
		
		void initializeTextures(sf::Texture *textBoard, sf::Texture *textPieces);
		
		/**
		 * @return The texture coordinate of a given piece
		*/
		sf::IntRect getPieceTexPos(Board::Index index);
		
	public:
		Board(sf::Texture *textBoard, sf::Texture *textPieces);
		

		/**
		 * @return The piece at that given position
		 */
		Board::Index operator()(int x, int y);
		
		/**
		 * Set the piece at the given position
		*/
		void setPiece(int x, int y, Board::Index value);
		
		/** Redraws the board based on its current state */
		void update();
		
		void draw(sf::RenderWindow &window);
};

inline Board::Index operator|(Board::Index a, Board::Index b) { return static_cast<Board::Index>( static_cast<int>( a ) | static_cast<int>( b ) ); }
inline Board::Index operator&(Board::Index a, Board::Index b) { return static_cast<Board::Index>( static_cast<int>( a ) & static_cast<int>( b ) ); }
inline Board::Index operator^(Board::Index a, Board::Index b) { return static_cast<Board::Index>( static_cast<int>( a ) ^ static_cast<int>( b ) ); }
inline Board::Index operator~(Board::Index a){ return static_cast<Board::Index>( ~static_cast<int>( a ) ); }

#endif