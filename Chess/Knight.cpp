//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"

// Implement method definitions here
int Knight::validMove(int to_x, int to_y) {
	if ((to_x < 8) and (to_y < 8) and (to_x > -1) and (to_y > -1) and (((this->m_x - to_x)*(this->m_x - to_x))+(this->m_y - to_y)*(this->m_y - to_y)) == 5) {
		if ((((*this->m_board->state()(to_x,to_y)).latin1Representation() == '.') or ((*this->m_board->state()(to_x, to_y)).m_is_white != this->m_is_white))) {
			return 1; //if the move is within the board and the the distance of the move squared is five and the square that it moves to is empty or have a piece of the opposite color then it is a valid move
		}
	}
	return 0; //otherwise it is not a valid move
}
char Knight::latin1Representation() { //latin one representation for the knight
	if (m_is_white == true) {
		return 'N';
	}
	else {
		return 'n';
	}
}

string Knight::utfRepresentation() { //utf representation for the knight
	if (m_is_white == true) {
		return "&#x2658;";
	}
	else {
		return "&#x265E;";
	}
}

vector<ChessMove> Knight::capturingMoves() { //all the capturing moves for the knight
	vector<ChessMove> chess_moves;
	bool c1 = this->capturingMove(this->m_x + 1, this->m_y + 2);
	//every if block checks for one of the eight knight moves and checks if the move is a capturing move and adds it to the vector
	if (c1) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y + 2;
		chess_moves.push_back(x);
	}
	bool c2 = this->capturingMove(this->m_x + 1, this->m_y - 2);
	if (c2) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y - 2;
		chess_moves.push_back(x);
	}
	bool c3 = this->capturingMove(this->m_x + -1, this->m_y + 2);
	if (c3) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y + 2;
		chess_moves.push_back(x);
	}

	bool c4 = this->capturingMove(this->m_x - 1, this->m_y - 2);
	if (c4) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y - 2;
		chess_moves.push_back(x);
	}

	bool c5 = this->capturingMove(this->m_x + 2, this->m_y + 1);
	if (c5) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 2;
		x.to_y = this->m_y + 1;
		chess_moves.push_back(x);
	}

	bool c6 = this->capturingMove(this->m_x + 2, this->m_y - 1);
	if (c6) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 2;
		x.to_y = this->m_y - 1;
		chess_moves.push_back(x);
	}

	bool c7 = this->capturingMove(this->m_x - 2, this->m_y + 1);
	if (c7) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 2;
		x.to_y = this->m_y + 1;
		chess_moves.push_back(x);
	}

	bool c8 = this->capturingMove(this->m_x - 2, this->m_y - 1);
	if (c8) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 2;
		x.to_y = this->m_y - 1;
		chess_moves.push_back(x);
	}
	return chess_moves;
}

vector<ChessMove> Knight::nonCapturingMoves() { //same logic as capturing moves but checks for non capturing moves instead
	vector<ChessMove> chess_moves;
	bool c1 = this->nonCapturingMove(this->m_x + 1, this->m_y + 2);
	if (c1) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y + 2;
		chess_moves.push_back(x);
	}
	bool c2 = this->nonCapturingMove(this->m_x + 1, this->m_y - 2);
	if (c2) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y - 2;
		chess_moves.push_back(x);
	}
	bool c3 = this->nonCapturingMove(this->m_x + -1, this->m_y + 2);
	if (c3) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y + 2;
		chess_moves.push_back(x);
	}

	bool c4 = this->nonCapturingMove(this->m_x - 1, this->m_y - 2);
	if (c4) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y - 2;
		chess_moves.push_back(x);
	}

	bool c5 = this->nonCapturingMove(this->m_x + 2, this->m_y + 1);
	if (c5) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 2;
		x.to_y = this->m_y + 1;
		chess_moves.push_back(x);
	}

	bool c6 = this->nonCapturingMove(this->m_x + 2, this->m_y - 1);
	if (c6) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 2;
		x.to_y = this->m_y - 1;
		chess_moves.push_back(x);
	}

	bool c7 = this->nonCapturingMove(this->m_x - 2, this->m_y + 1);
	if (c7) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 2;
		x.to_y = this->m_y + 1;
		chess_moves.push_back(x);
	}

	bool c8 = this->nonCapturingMove(this->m_x - 2, this->m_y - 1);
	if (c8) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 2;
		x.to_y = this->m_y - 1;
		chess_moves.push_back(x);
	}
	return chess_moves;
}