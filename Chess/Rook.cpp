//
// DD1388 - Lab 4: Losing Chess
//

#include "Rook.h"

// Implement method definitions here
int Rook::validMove(int to_x, int to_y) {
	if ((to_x == this->m_x) and (to_y > this->m_y)) { //checks the squares to the right of the rook
		for (int i = 1; i < 8; i++) {
			if ((this->m_y + i) != 8) {
				if ((this->m_y + i == to_y) and (((*this->m_board->state()(this->m_x, this->m_y + i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x, this->m_y + i)).m_is_white != this->m_is_white))) {
					return 1; //if the move is to the right of the rook and it is an empty square or there is a piece of the opposite color on the square then the move is valid
				}
				else if (((*this->m_board->state()(this->m_x, this->m_y + i)).latin1Representation() != '.')) {
					return 0; //if there is a piece blocking the move then the move is not valid 
				}
			}
		}
	}

	//the three blocks below has the same logic as the block above but checks above the rook, to the left of the rook and below the rook.
	if ((to_x == this->m_x) and (to_y < this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_y - i) != -1) {
				if ((this->m_y - i == to_y) and (((*this->m_board->state()(this->m_x, this->m_y - i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x, this->m_y - i)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x, this->m_y - i)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}

	if ((to_x > this->m_x) and (to_y == this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_x + i) != 8) {
				if ((this->m_x + i == to_x) and (((*this->m_board->state()(this->m_x + i, this->m_y)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x + i, this->m_y)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x + i, this->m_y)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}

	if ((to_x < this->m_x) and (to_y == this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_x - i) != -1) {
				if ((this->m_x - i == to_x) and (((*this->m_board->state()(this->m_x - i, this->m_y)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x - i, this->m_y)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x - i, this->m_y)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}
	return 0;
}

char Rook::latin1Representation() {//latin1representation for the rook
	if (m_is_white == true) {
		return 'R';
	}
	else {
		return 'r';
	}
}

string Rook::utfRepresentation() {//utf representation for the rook
	if (m_is_white == true) {
		return "&#x2656;";
	}
	else {
		return "&#x265C;";
	}
}

vector<ChessMove> Rook::capturingMoves() {//all the capturing moves for the rook
	vector<ChessMove> chess_moves;
	for (int i = 0; i < 8; i++) {
		bool c1 = this->capturingMove(i,this->m_y);
		if (c1) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = i;
			x.to_y = this->m_y;
			chess_moves.push_back(x); //checks if any of the moves on the same column as the rook is a capturingmove and adds it to the v
		}
		bool c2 = this->capturingMove(this->m_x, i);
		if (c2) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = this->m_x;
			x.to_y = i;
			chess_moves.push_back(x); //checks if any of the moves on the same row as the rook is a capturing move and adds it to the vector
		}
	}
	return chess_moves;
}
vector<ChessMove> Rook::nonCapturingMoves() { //same logic as capturing moves but checks for non capturing moves instead
	vector<ChessMove> chess_moves;
	for (int i = 0; i < 8; i++) {
		bool c1 = this->nonCapturingMove(i, this->m_y);
		if (c1) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = i;
			x.to_y = this->m_y;
			chess_moves.push_back(x);
		}
		bool c2 = this->nonCapturingMove(this->m_x, i);
		if (c2) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = this->m_x;
			x.to_y = i;
			chess_moves.push_back(x);
		}
	}
	return chess_moves;
}