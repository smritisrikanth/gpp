#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::Board(const Board& copy_board){
      for (std::map<Position, Piece*>::const_iterator it = copy_board.occ.cbegin(); it != copy_board.occ.cend(); ++it){
        this->occ.insert({{it->first}, it->second});
      }
  }

  const Piece* Board::operator()(const Position& position) const {
    /////////////////////////
    if(Board::occ.find(position) != Board::occ.end()){
      return Board::occ.at(position);
    }
    /////////////////////////
    return NULL;
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {
    Chess::Piece *piece = create_piece(piece_designator);
    if (piece == NULL) {
      throw Exception("invalid designator");
    }
    else if (!is_valid_position(position)) {
      throw Exception("invalid position");
    }
    else if (operator()(position) != NULL) {
      throw Exception("position is occupied");
    }
    occ[position] = piece;
  }

  void Board::display() const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
  }

  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();
	 it != occ.end();
	 it++) {
      if (it->second) {
	switch (it->second->to_ascii()) {
	case 'K':
	  white_king_count++;
	  break;
	case 'k':
	  black_king_count++;
	  break;
	}
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  bool is_valid_position(const Position& position) {
    return (position.first >= 'A' && position.first <= 'H' && position.second >= 1 && position.second <= 8);
  }

  void Board::remove_piece(const Position& position) {
    occ.erase(position);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }


  

}
