//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"

// Implement method definitions here

Queen::Queen(int x, int y, bool is_white, ChessBoard* board) //constructor for the queen which uses the constructor of the baseclasses
	:ChessPiece(x,y,is_white,board),Rook(x,y,is_white,board),Bishop(x,y,is_white,board) {}

char Queen::latin1Representation() {//latin1representation for the queen
	if (ChessPiece::m_is_white == true) { //need to specify that m_is_white is from chesspiece because of diamond inheritance
		return 'Q';
	}
	else {
		return 'q';
	}
}

string Queen::utfRepresentation() { //utf representation for the queen
	if (ChessPiece::m_is_white == true) {
		return "&#x2655;";
	}
	else {
		return "&#x265B;";
	}
}

//all of the functions bellow combines the bishop and the rooks corresponding functions into a function for the queen with diamond inheritance
int Queen::validMove(int to_x,int to_y) {
	int x = Bishop::validMove(to_x, to_y);
	int y = Rook::validMove(to_x, to_y);
	if ((x == 1) or (y == 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

vector<ChessMove> Queen::capturingMoves() {
	vector<ChessMove> chess_moves;
	for (auto element : Bishop::capturingMoves()) {
		chess_moves.push_back(element);
	}
	for (auto element : Rook::capturingMoves()) {
		chess_moves.push_back(element);
	}
	return chess_moves;
}

vector<ChessMove> Queen::nonCapturingMoves() {
	vector<ChessMove> chess_moves;
	for (auto element : Bishop::nonCapturingMoves()) {
		chess_moves.push_back(element);
	}
	for (auto element : Rook::nonCapturingMoves()) {
		chess_moves.push_back(element);
	}
	return chess_moves;
}