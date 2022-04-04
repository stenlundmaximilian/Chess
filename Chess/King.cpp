//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"

int King::validMove(int to_x, int to_y) {
	if ((to_x < 8) and (to_y < 8) and (to_x > -1) and (to_y > -1) and (((abs((this->m_x - to_x) * (this->m_y - to_y)) == 1) or (abs((this->m_x - to_x) + (this->m_y - to_y))==1)))) {
		if ((((*this->m_board->state()(to_x, to_y)).latin1Representation() == '.') or ((*this->m_board->state()(to_x, to_y)).m_is_white != this->m_is_white))) {
			return 1; //if abs(delta_X*delta_Y) = 1 or abs(delta_X + delta_Y = 1) and the square is empty or have a piece of the opposite color and the move is within the board then the move is valid
		}
	}
	return 0; //otherwise it is not valid
}
char King::latin1Representation() {//latin1representation for king
	if (m_is_white == true) {
		return 'K';
	}
	else {
		return 'k';
	}
}

string King::utfRepresentation() { //utfrepresentation for king
	if (m_is_white == true) {
		return "&#x2654;";
	}
	else {
		return "&#x265A;";
	}
}

vector<ChessMove> King::capturingMoves() { //all capturing moves for the king
	vector<ChessMove> chess_moves;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if ((this->m_x + i)>-1 and (this->m_x + i) < 8 and (this->m_y + i) > -1 and (this->m_y + i) < 8) {
				bool c = this->capturingMove(this->m_x + i, this->m_y + j); //check if a move around the king is a capturing move
				if (c) {
					ChessMove x;
					x.from_x = this->m_x;
					x.from_y = this->m_y;
					x.to_x = this->m_x + i;
					x.to_y = this->m_y + j;
					chess_moves.push_back(x); //if any of the move around the king is a capturing move add the move
				}
			}
		}
	}
	return chess_moves;
}
vector<ChessMove> King::nonCapturingMoves() { //same logic as for capturing move but checks for non capturing moves instead
	vector<ChessMove> chess_moves;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			//cout << this->m_x + i <<endl;
			bool c = this->nonCapturingMove(this->m_x + i, this->m_y + j);
			if (c) {
				ChessMove x;
				x.from_x = this->m_x;
				x.from_y = this->m_y;
				x.to_x = this->m_x + i;
				x.to_y = this->m_y + j;
				chess_moves.push_back(x);
			}
		}
	}
	return chess_moves;
}

