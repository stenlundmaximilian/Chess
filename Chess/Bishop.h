//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
    // Override virtual methods from ChessPiece here
public:
    using ChessPiece::ChessPiece;
    int validMove(int to_x, int to_y);
    string utfRepresentation();     // may be implemented as string
    char latin1Representation();
    vector<ChessMove> capturingMoves();
    vector<ChessMove> nonCapturingMoves();
};


#endif //BISHOP_H
