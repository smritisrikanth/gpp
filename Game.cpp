#include <cassert>
#include "Game.h"

namespace Chess
{
	Game::Game(const Game& copy_game) {
		board = Board(copy_game.board);
		is_white_turn = copy_game.is_white_turn;
	}
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

		const Piece* curr_piece = board(start);
		if (!is_legal_move(start, end)) {
			if (!curr_piece){
			throw Exception("no piece at start position");
			}
			if (!board.is_valid_position(start)){
				throw Exception("start position is not on board");
			}
			if (!board.is_valid_position(end)){
				throw Exception("end position is not on board");
			}
			if (board(end)) {
				if(curr_piece->is_white() == board(end)->is_white()){
					throw Exception("cannot capture own piece");
				}
				if (!curr_piece->legal_capture_shape(start, end)){
					throw Exception("illegal capture shape");
				}
			} else {
				if (!curr_piece->legal_move_shape(start, end)){
					throw Exception ("illegal move shape");
				}
			}
			if (!path_clear(start,end)) {
				throw Exception("path is not clear");
			}
		}



		//check if exposes check
		Game new_game = Game(*this);

		if(new_game.board(end)) {
			new_game.board.remove_piece(end);
			new_game.board.add_piece(end, new_game.board(start)->to_ascii());
			new_game.board.remove_piece(start);
		} else {
			new_game.board.add_piece(end, new_game.board(start)->to_ascii());
			new_game.board.remove_piece(start);
		}

		if (new_game.in_check(Game::is_white_turn)) {
			throw Exception ("move exposes check");
		}

		// pawn promotion
		if (board(start)->to_ascii() == 'P' && curr_piece->is_white() && end.second == '8') {
			board.add_piece(end, 'Q');
			board.remove_piece(start);
		} else if (board(start)->to_ascii() == 'p' && !curr_piece->is_white() && end.second == '1') {
			board.add_piece(end, 'q');
			board.remove_piece(start);
		// capture
		} else if(board(end)) {
			board.remove_piece(end);
			board.add_piece(end, board(start)->to_ascii());
			board.remove_piece(start);
		// move
		} else{
			board.add_piece(end, board(start)->to_ascii());
			board.remove_piece(start);
		}

		// switch turn
		if(turn_white()){
			Game::is_white_turn = false;
		} else{
			Game::is_white_turn = true;
		}
		
	}

	bool Game::in_check(const bool& white) const {
		Position& target = *(board.begin());
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			if (board(*it)) {
				if ((white && board(*it)->to_ascii() == 'K') || (!white && board(*it)->to_ascii() == 'k')) {
					target = *it;
				}
			}
		}
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			if (board(*it)) {
				if ((white && !board(*it)->is_white()) || (!white && board(*it)->is_white())) {
					if (is_legal_move(*it, target)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Game::in_mate(const bool& white) const {
		
		if (in_stalemate(white) && in_check(white)){
			return true;
		}
		return false;
	}


	bool Game::in_stalemate(const bool& white) const {
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			if (board(*it)) {
				if ((white && board(*it)->is_white()) || (!white && !board(*it)->is_white())) {
					std::vector<Position> moves = possible_moves(*it);
					for (std::vector<Position>::iterator move = moves.begin(); move != moves.end(); ++move) {
						Game new_game = Game(*this);

						if(new_game.board(*move)) {
							new_game.board.remove_piece(*move);
							new_game.board.add_piece(*move, new_game.board(*it)->to_ascii());
							new_game.board.remove_piece(*it);
						} else{
							
							new_game.board.add_piece(*move, new_game.board(*it)->to_ascii());
							new_game.board.remove_piece(*it);
						}
						if (!new_game.in_check(white)) {
							return false;
						}
					}
				}
			}
		}
		return true;
	}

	

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		int total = 0;
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			if (board(*it)) {
				if ((white && board(*it)->is_white()) || (!white && !board(*it)->is_white())) {
					total += board(*it)->point_value();
				}
			}
		}
		return total;
    }

	std::vector<Position> Game::possible_moves(Position& start) const {

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

	bool Game::path_clear(const Position& start, const Position& end) const{
		//vertical movement
		if(start.first == end.first){
			Position P;
			P.first = start.first;
			for (int i = 1; i < abs(start.second - end.second); i++){
				if (start.second < end.second){
					P.second = start.second + i;
				}else{
					P.second = start.second - i;
				}
				if(board(P)){
					return false;
				}
			}
		}
		//horizontal movement
		if (start.second == end.second){
			Position P;
			P.second = start.second;
			for (int i = 1; i < abs(start.first - end.first); i++){
				if (start.first < end.first){
					P.first = start.first + i;
				} else {
					P.first = start.first - i;
				}	
				if(board(P)){
					return false;
				}
			}
		}
		//diagonal movement
		if (abs(start.first - end.first) == abs(start.second - end.second)){
			Position P;
			for (int i = 1; i < abs(start.second - end.second); i++){
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
				if(board(P)){
					return false;
				}
			}
		}
		return true;
	}

	//must either remove exceptions or catch them when used
	bool Game::is_legal_move(const Position& start, const Position& end) const {
		const Piece* curr_piece = board(start);
		if (!curr_piece){
			return false;
		}
		if (!board.is_valid_position(start)){
			return false;
		}
		if (!board.is_valid_position(end)){
			return false;
		}

		if(board(end)) {
			if(curr_piece->is_white() == board(end)->is_white()){
				return false;
			} else if (!curr_piece->legal_capture_shape(start, end)){
				return false;
			}
		} else {
			if (!curr_piece->legal_move_shape(start, end)){
				return false;
			}
		}

		if (!path_clear(start,end)) {
			return false;
		}

		return true;
	}


    std::istream& operator>>(std::istream& is, Game& game) {
		char piece_desig; 
		is >> piece_desig;
		for (Board::iterator it = game.board.begin(); it != game.board.end(); ++it){
			(game.board).remove_piece(*it);
			if(piece_desig != '-'){
				(game.board).add_piece(*it, piece_desig);
			}
			is >> piece_desig;
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
