//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

int ChessPiece::validMove(int to_x, int to_y) {
    return 0;
}

//char32_t ChessPiece::utfRepresentation() {
    // Implementation goes here
//}

char ChessPiece::latin1Representation() {
    return '.';
}

string ChessPiece::utfRepresentation() {
    return "&nbsp;..&nbsp;";
}

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard* board)
    :m_x(x)
    ,m_y(y)
    ,m_is_white(is_white)
    ,m_board(board)
    {}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    if (to_x < 8 and to_x > -1 and to_y <8 and to_y > -1) {
        if ((*this->m_board->state()(to_x, to_y)).latin1Representation() != '.') {
            if (this->validMove(to_x, to_y) == 1) {
                return true;
            }
        }
    }
    return 0;
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    if (to_x < 8 and to_x > -1 and to_y <8 and to_y > -1) {
        if ((*this->m_board->state()(to_x, to_y)).latin1Representation() == '.') {
            if (this->validMove(to_x, to_y) == 1) {
                return true;
            }
        }
    }
    return 0;
}

vector<ChessMove> ChessPiece::capturingMoves() {
    vector<ChessMove> x;
    return x;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    vector<ChessMove> x;
    return x;
}