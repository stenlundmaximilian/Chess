//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"

// Implement method definitions here
int Bishop::validMove(int to_x,int to_y) { //checks valid moves for the bishop
	if ((to_x > this->m_x) and (to_y > this->m_y)) { //if block for the diagonal below and to the right of the bishop
		for (int i = 1; i < 8; i++) {
			if ((this->m_x + i) != 8 and (this->m_y + i) != 8) {
				if ((this->m_x + i == to_x) and (this->m_y + i == to_y) and (((*this->m_board->state()(this->m_x + i, this->m_y + i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x + i, this->m_y + i)).m_is_white != this->m_is_white))) { 
					return 1; //if the to position is on the diagonal and is empty or have a piece of the opposite color it is a valid move
				}
				else if (((*this->m_board->state()(this->m_x + i, this->m_y + i)).latin1Representation() != '.')) {
					return 0; //if there is a piece blocking the path it is not a valid move
				}
			}
		}
	}

	//the logic for the three blocks below is the same as the one above but for different diagonals.
	if ((to_x > this->m_x) and (to_y < this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_x + i) != 8 and (this->m_y - i) != -1) {
				if ((this->m_x + i == to_x) and (this->m_y - i == to_y) and (((*this->m_board->state()(this->m_x + i, this->m_y - i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x + i, this->m_y - i)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x + i, this->m_y - i)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}

	if ((to_x < this->m_x) and (to_y > this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_x - i) != -1 and (this->m_y + i) != 8) {
				if ((this->m_x - i == to_x) and (this->m_y + i == to_y) and (((*this->m_board->state()(this->m_x - i, this->m_y + i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x - i, this->m_y + i)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x - i, this->m_y + i)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}

	if ((to_x < this->m_x) and (to_y < this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_x - i) != -1 and (this->m_y - i) != -1) {
				if ((this->m_x - i == to_x) and (this->m_y - i == to_y) and (((*this->m_board->state()(this->m_x - i, this->m_y - i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x - i, this->m_y - i)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x - i, this->m_y - i)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}
	return 0; //if the to position was not on one of the diagonals it is not a valid move
}
char Bishop::latin1Representation() { //latin1representation for the bishop
	if (m_is_white == true) {
		return 'B';
	}
	else {
		return 'b';
	}
}

string Bishop::utfRepresentation() { //utfrepresentation for the bishop
	if (m_is_white == true) {
		return "&#x2657;";
	}
	else {
		return "&#x265D;";
	}
}

vector<ChessMove> Bishop::capturingMoves() { //all the capturing moves for a bishop
	vector<ChessMove> chess_moves;
	int minimum = min(this->m_x, this->m_y);
	for (int i = 0; i < (8 - (abs(this->m_x - this->m_y))); i++) {// goes through the move on one diagonal and checks for capturing moves
		bool c = this->capturingMove((this->m_x - minimum)+i,(this->m_y-minimum)+i);
		if (c) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = (this->m_x - minimum) + i;
			x.to_y = (this->m_y - minimum) + i;
			chess_moves.push_back(x); //if a move is a capturing move add it to the capturing moves
		}
	}

	//same logic as the logic above but for the other diagonal
	minimum = min(7-this->m_x, this->m_y);
	for (int i = 0; i < (8 - (abs(7-(this->m_x + this->m_y)))); i++) {
		bool c = this->capturingMove((this->m_x + minimum) - i, (this->m_y - minimum) + i);
		if (c) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = (this->m_x + minimum) - i;
			x.to_y = (this->m_y - minimum) + i;
			chess_moves.push_back(x);
		}
	}
	return chess_moves;
}

vector<ChessMove> Bishop::nonCapturingMoves() { //same logic as for capturing moves but looks for non capturing moves instead
	vector<ChessMove> chess_moves;
	int minimum = min(this->m_x, this->m_y);
	for (int i = 0; i < (8 - (abs(this->m_x - this->m_y))); i++) {
		bool c = this->nonCapturingMove((this->m_x - minimum) + i, (this->m_y - minimum) + i);
		if (c) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = (this->m_x - minimum) + i;
			x.to_y = (this->m_y - minimum) + i;
			chess_moves.push_back(x);
		}
	}
	minimum = min(7 - this->m_x, this->m_y);
	for (int i = 0; i < (8 - (abs(7 - (this->m_x + this->m_y)))); i++) {
		bool c = this->nonCapturingMove((this->m_x + minimum) - i, (this->m_y - minimum) + i);
		if (c) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = (this->m_x + minimum) - i;
			x.to_y = (this->m_y - minimum) + i;
			chess_moves.push_back(x);
		}
	}
	return chess_moves;
}