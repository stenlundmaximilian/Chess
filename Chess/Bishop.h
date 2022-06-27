//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop :virtual public ChessPiece {
    // Override virtual methods from ChessPiece here
public:
    using ChessPiece::ChessPiece;
    virtual int validMove(int to_x, int to_y);
    virtual string utfRepresentation();     // may be implemented as string
    virtual char latin1Representation();
    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();
};


#endif //BISHOP_H
