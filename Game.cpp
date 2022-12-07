#include <cassert>
#include "Game.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	void Game::make_move(const Position& start, const Position& end) {
		/////////////////////////
		const Piece* curr_piece = board.operator() (start);
		// check if piece exists at position, and if start and end are valid
		if (!curr_piece){
			throw Exception("no piece at start position");
		}
		if (!board.is_valid_position(start)){
			throw Exception("start position is not on board");
		}
		if (!board.is_valid_position(end)){
			throw Exception("end position is not on board");
		}

		// we might have to switch the order, im not sure
		//vertical movement
		if(start.first == end.first && curr_piece->legal_move_shape(start, end)){
			Position P;
			P.first = start.first;
			for (int i = 1; i < abs(start.second - end.second) - 1; i++){
				if (start.second < end.second){
					P.second = start.second + i;
				}else{
					P.second = start.second - i;
				}
				if(board.operator()(P)){
					throw Exception("path is not clear");
				}
			}
		}
		//horizontal movement
		else if (start.second == end.second && curr_piece->legal_move_shape(start, end)){
			Position P;
			P.second = start.second;
			for (int i = 1; i < abs(start.first - end.first) - 1; i++){
				if (start.first < end.first){
					P.first = start.first + i;
				} else {
					P.first = start.first - i;
				}	
				if(board.operator()(P)){
					throw Exception("path is not clear");
				}
			}
		}
		//diagonal movement
		else if ((start.first - end.first) == (start.second - end.second) && curr_piece->legal_move_shape(start, end)){
			Position P;
			for (int i = 1; i < abs(start.second - end.second) - 1; i++){
				if (start.first < end.first){ // to the right
					if (start.second < end.second){ // up and right
						P.first = start.first + i;
						P.second = start.second + i;
					} else { // down and right
						P.first = start.first - i;
						P.second = start.second + i;
					}
				} else { // to the left
					if (start.second < end.second){ // up and left
						P.first = start.first - i;
						P.second = start.second + i;
					} else { // down and left
						P.first = start.first - i;
						P.second = start.second - i;
					}
				}
				if(board.operator()(P)){
					throw Exception("path is not clear");
				}
			}
		}

		//check if exposes check
		Board old_board = Board(board);


		// Check if there is a piece
		if(board.operator()(end)){
			// then attempt to capture piece
			if(curr_piece->is_white() == board.operator()(end)->is_white()){
				throw Exception("cannot capture own piece");
			}
			if(curr_piece->legal_capture_shape(start, end)){
				board.remove_piece(end);
				board.add_piece(end, curr_piece->to_ascii());
				board.remove_piece(start);
			}else{
				throw Exception("illegal capture shape");
			}
		} else{
			// else attempt to move piece
			if (curr_piece->legal_move_shape(start, end)){
				board.remove_piece(start);
				board.add_piece(end, curr_piece->to_ascii());
			}else {
				throw Exception ("illegal move shape");
			}
		}

		if (in_check(Game::is_white_turn)) {
			board = Board(old_board);
			throw Exception ("move exposes check");
		}

		// switch turn
		if(turn_white()){
			Game::is_white_turn = false;
		} else{
			Game::is_white_turn = true;
		}
		//TODO: move exposes check
		/////////////////////////
	}

	bool Game::in_check(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		// I think for this, an efficient way for doing it is by having a small if statemnt
		// for just switching between black and white, where can just add a variable to make the characters 
		// for the piece representation lower case for black and upper case for white and then 
		// only have to write the in_check implementation once
		int black;
		if (white){
			black = 0;
		} else{
			black = 'a' - 'A';
		}
		/////////////////////////

		//iterate through pieces on board, for each piece of opposite color iterate through possible moves
		//check if any of the positions returned have a king in them
		return false;
	}


	bool Game::in_mate(const bool& white) const {
		/////////////////////////
		if (in_stalemate(white) && in_check(white)){
			return true;
		}
		/////////////////////////
		return false;
	}


	bool Game::in_stalemate(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////

		

		//iterate through pieces on board, for each piece of same color iterate through possible moves
		//check if vector returned is empty
		return false;
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		int total = 0;
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			if (white && board.operator()(*it)->is_white() || !white && !board.operator()(*it)->is_white()) {
				total += board.operator()(*it)->point_value();
			}
		}
		return total;
    }

	std::vector<Position> Game::possible_moves(Position& start) {
		const Piece* piece = board.operator() (start);
		std::vector<Position> moves;
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			try {
				if (is_legal_move(start, *it)) {
					moves.push_back(*it);
				}
			} catch (Exception& ex) {
				
			}
		}
		return moves;
	}

	//must either remove exceptions or catch them when used
	bool Game::path_clear(Position& start, Position& end) {
		const Piece* curr_piece = board.operator() (start);
		// we might have to switch the order, im not sure
		//vertical movement
		if(start.first == end.first && curr_piece->legal_move_shape(start, end)){
			Position P;
			P.first = start.first;
			for (int i = 1; i < abs(start.second - end.second) - 1; i++){
				if (start.second < end.second){
					P.second = start.second + i;
				}else{
					P.second = start.second - i;
				}
				if(board.operator()(P)){
					throw Exception("path is not clear");
					return false;
				}
			}
		}
		//horizontal movement
		else if (start.second == end.second && curr_piece->legal_move_shape(start, end)){
			Position P;
			P.second = start.second;
			for (int i = 1; i < abs(start.first - end.first) - 1; i++){
				if (start.first < end.first){
					P.first = start.first + i;
				} else {
					P.first = start.first - i;
				}	
				if(board.operator()(P)){
					throw Exception("path is not clear");
					return false;
				}
			}
		}
		//diagonal movement
		else if ((start.first - end.first) == (start.second - end.second) && curr_piece->legal_move_shape(start, end)){
			Position P;
			for (int i = 1; i < abs(start.second - end.second) - 1; i++){
				if (start.first < end.first){ // to the right
					if (start.second < end.second){ // up and right
						P.first = start.first + i;
						P.second = start.second + i;
					} else { // down and right
						P.first = start.first - i;
						P.second = start.second + i;
					}
				} else { // to the left
					if (start.second < end.second){ // up and left
						P.first = start.first - i;
						P.second = start.second + i;
					} else { // down and left
						P.first = start.first - i;
						P.second = start.second - i;
					}
				}
				if(board.operator()(P)){
					throw Exception("path is not clear");
					return false;
				}
			}
		}
		return true;
	}

	//must either remove exceptions or catch them when used
	bool Game::is_legal_move(Position& start, Position& end) {
		const Piece* curr_piece = board.operator() (start);
		if (!curr_piece){
			throw Exception("no piece at start position");
			return false;
		}
		if (!board.is_valid_position(start)){
			throw Exception("start position is not on board");
			return false;
		}
		if (!board.is_valid_position(end)){
			throw Exception("end position is not on board");
			return false;
		}

		Board old_board = Board(board);


		// Check if there is a piece
		if(board.operator()(end)){
			// then attempt to capture piece
			if(curr_piece->is_white() == board.operator()(end)->is_white()){
				throw Exception("cannot capture own piece");
				return false;
			}
			if(curr_piece->legal_capture_shape(start, end)){
				board.remove_piece(end);
				board.add_piece(end, curr_piece->to_ascii());
				board.remove_piece(start);
			}else{
				throw Exception("illegal capture shape");
				return false;
			}
		} else{
			// else attempt to move piece
			if (curr_piece->legal_move_shape(start, end)){
				board.remove_piece(start);
				board.add_piece(end, curr_piece->to_ascii());
			}else {
				throw Exception ("illegal move shape");
				return false;
			}
		}

		if (in_check(Game::is_white_turn)) {
			throw Exception ("move exposes check");
			return false;
		}

		board = Board(old_board);


		return true;
	}


    std::istream& operator>>(std::istream& is, Game& game) {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		char piece_desig; 
		Board::iterator it = game.board.begin();
		while (piece_desig != 'w' || piece_desig != 'b'){
			is >> piece_desig;
			++it;
			if (piece_desig != '-') {
				(game.board).add_piece(*it, piece_desig);
			}
		}
		if (piece_desig == 'w'){
			game.is_white_turn = true;
		} else if (piece_desig == 'b') {
			game.is_white_turn = false;
		}
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
