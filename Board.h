#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


namespace Chess
{
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();

		//copy constructor
		Board(const Board& copy_board);

		// Returns a const pointer to the piece at a prescribed location if it exists,
		// or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator);

		// Displays the board by printing it to stdout
		void display() const;

		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;

		bool is_valid_position(const Position& position) const;

		void remove_piece(const Position& position);



		class iterator {
			Position position;

		public:
			// make a default constructor -> need to define pointer to position
			//iterator() { 
			//	*position = std::make_pair('A', '8');
			//}
			iterator(Position p) : position(p) { }
			// initial is passed as address vs a pair, try to pass as a pair instead			

			bool operator!=(const iterator& a) {
				return position.first != a.position.first || position.second != a.position.second;
			}

			Position& operator*() {
        		return position;
      		}

			iterator& operator++() { 
				if (position.first < 'H') {(position.first)++;} 
				else { position.first = 'A'; (position.second)--; } 
				return *this;
			}
      	};

		iterator begin() const {
			Position i = std::make_pair('A', '8'); return iterator(i);
		}

		iterator end() const {
			Position e = std::make_pair('A', '0'); return iterator(e);
		}
		
	private:
		// The sparse map storing the pieces, keyed off locations
		std::map<Position, Piece*> occ;

        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
	};
}
#endif // BOARD_H
