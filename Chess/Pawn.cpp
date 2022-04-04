//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"

// Implement method definitions here

int Pawn::validMove(int to_x, int to_y) { //checks valid moves for pawn
	//if block for white pawns
	if (this->m_is_white and (to_x < 8) and (to_y < 8) and (to_x > -1) and (to_y > -1)) {
		if (to_x == (this->m_x-1) and (to_y == this->m_y)) {
			if ((((*this->m_board->state()(to_x, to_y)).latin1Representation() == '.'))) {
				return 1; //if the move is within the board and the pawn takes one step to an empty square it is valid
			}
		}
		else if(to_x == (this->m_x - 2) and (to_y == this->m_y) and (this->m_x == 6)) {
			if (((*this->m_board->state()(to_x + 1, to_y)).latin1Representation() != '.')) {
				return 0; //if the pawn tries to take two steps but there is a blocking piece in the way the move is not valid
			}
			else if ((((*this->m_board->state()(to_x, to_y)).latin1Representation() == '.'))) {
				return 1; //if the pawn tries to take two steps and land on an empty square and the pawn is on the right row the move is valid
			}
		}
		else if (to_x == (this->m_x - 1) and ((to_y == this->m_y + 1) or (to_y == this->m_y - 1))) {
			if ((( * this->m_board->state()(to_x, to_y)).m_is_white != this->m_is_white) and ((*this->m_board->state()(to_x, to_y)).latin1Representation() != '.')) {
				return 1; //if there is a piece of the opposite color diagonaly in front of the pawn a capturing move is valid
			}
		}
	}
	//if block for black pawns, same logic as the logic for white pawns but adjusted for black pawns
	if (!(this->m_is_white) and (to_x < 8) and (to_y < 8) and (to_x > -1) and (to_y > -1)) {
		if (to_x == (this->m_x + 1) and (to_y == this->m_y)) {
			if ((((*this->m_board->state()(to_x, to_y)).latin1Representation() == '.'))) {
				return 1;
			}
		}
		else if (to_x == (this->m_x + 2) and (to_y == this->m_y) and (this->m_x == 1)) {
			if (((*this->m_board->state()(to_x - 1, to_y)).latin1Representation() != '.')) {
				return 0;
			}
			else if ((((*this->m_board->state()(to_x, to_y)).latin1Representation() == '.'))) {
				return 1;
			}
		}
		else if (to_x == (this->m_x + 1) and ((to_y == this->m_y + 1) or (to_y == this->m_y - 1))) {
			if (((*this->m_board->state()(to_x, to_y)).m_is_white != this->m_is_white) and ((*this->m_board->state()(to_x, to_y)).latin1Representation() != '.')) {
				return 1;
			}
		}
	}
	return 0;
}

char Pawn::latin1Representation() {//latin1representation of a pawn
	if (m_is_white == true) {
		return 'P';
	}
	else {
		return 'p';
	}
}

string Pawn::utfRepresentation() { //utfrepresentation of a pawn
	if (m_is_white == true) {
		return "&#x2659;";
	}
	else {
		return "&#x265F;";
	}
}

vector<ChessMove> Pawn::capturingMoves() {//all capturing moves for a pawn
	vector<ChessMove> chess_moves;
	bool c1 = this->capturingMove(this->m_x + 1,this->m_y + 1);
	//every of the four if block checks if one of the diagonal moves of the pawn is a capturing move
	if (c1) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y + 1;
		chess_moves.push_back(x);
	}
	bool c2 = this->capturingMove(this->m_x + 1, this->m_y - 1);
	if (c2) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y - 1;
		chess_moves.push_back(x);
	}
	bool c3 = this->capturingMove(this->m_x - 1, this->m_y + 1);
	if (c3) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y + 1;
		chess_moves.push_back(x);
	}
	bool c4 = this->capturingMove(this->m_x - 1, this->m_y - 1);
	if (c4) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y - 1;
		chess_moves.push_back(x);
	}
	return chess_moves;
}
vector<ChessMove> Pawn::nonCapturingMoves() { //all non capturing moves of a pawn
	vector<ChessMove> chess_moves;
	//every if block checks if the pawns can move one or two squares up or down the board for a total of four if blocks
	bool c1 = this->nonCapturingMove(this->m_x + 1, this->m_y);
	if (c1) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 1;
		x.to_y = this->m_y;
		chess_moves.push_back(x);
	}
	bool c2 = this->nonCapturingMove(this->m_x + 2, this->m_y);
	if (c2) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x + 2;
		x.to_y = this->m_y;
		chess_moves.push_back(x);
	}
	bool c3 = this->nonCapturingMove(this->m_x - 1, this->m_y);
	if (c3) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 1;
		x.to_y = this->m_y;
		chess_moves.push_back(x);
	}
	bool c4 = this->nonCapturingMove(this->m_x - 2, this->m_y);
	if (c4) {
		ChessMove x;
		x.from_x = this->m_x;
		x.from_y = this->m_y;
		x.to_x = this->m_x - 2;
		x.to_y = this->m_y;
		chess_moves.push_back(x);
	}
	return chess_moves;
}