//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"

// Implement method definitions here
int Queen::validMove(int to_x, int to_y) {
	if ((to_x > this->m_x) and (to_y > this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_x + i) != 8 and (this->m_y + i) != 8) {
				if ((this->m_x + i == to_x) and (this->m_y + i == to_y) and (((*this->m_board->state()(this->m_x + i, this->m_y + i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x + i, this->m_y + i)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x + i, this->m_y + i)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}

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

	if ((to_x == this->m_x) and (to_y > this->m_y)) {
		for (int i = 1; i < 8; i++) {
			if ((this->m_y + i) != 8) {
				if ((this->m_y + i == to_y) and (((*this->m_board->state()(this->m_x, this->m_y + i)).latin1Representation() == '.') or ((*this->m_board->state()(this->m_x, this->m_y + i)).m_is_white != this->m_is_white))) {
					return 1;
				}
				else if (((*this->m_board->state()(this->m_x, this->m_y + i)).latin1Representation() != '.')) {
					return 0;
				}
			}
		}
	}

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

char Queen::latin1Representation() {
	if (m_is_white == true) {
		return 'Q';
	}
	else {
		return 'q';
	}
}

string Queen::utfRepresentation() {
	if (m_is_white == true) {
		return "&#x2655;";
	}
	else {
		return "&#x265B;";
	}
}

vector<ChessMove> Queen::capturingMoves() {
	vector<ChessMove> chess_moves;
	int minimum = min(this->m_x, this->m_y);
	for (int i = 0; i < (8 - (abs(this->m_x - this->m_y))); i++) {
		bool c = this->capturingMove((this->m_x - minimum) + i, (this->m_y - minimum) + i);
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
	for (int i = 0; i < 8; i++) {
		bool c1 = this->capturingMove(i, this->m_y);
		if (c1) {
			ChessMove x;
			x.from_x = this->m_x;
			x.from_y = this->m_y;
			x.to_x = i;
			x.to_y = this->m_y;
			chess_moves.push_back(x);
		}
		bool c2 = this->capturingMove(this->m_x, i);
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
vector<ChessMove> Queen::nonCapturingMoves() {
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