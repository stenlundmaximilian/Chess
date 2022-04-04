//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include "ChessMove.h"
#include "ChessBoard.h"
#include <string>
using namespace std;

class ChessPiece {
    friend void ChessBoard::movePiece(ChessMove p);
public:                               // protected will cause problems
    int m_x, m_y;
    bool m_is_white;
    ChessBoard* m_board;
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    
    virtual int validMove(int to_x, int to_y);
    virtual string utfRepresentation();     // may be implemented as string
    virtual char latin1Representation();
public:
    // Constructor
    ChessPiece(int x, int y, bool is_white, ChessBoard* board);
    /**
     * Checks if this move is valid for this piece and captures
     * a piece of the opposite color.
     */
    bool capturingMove(int to_x, int to_y);
    /**
     * Checks if this move is valid but does not capture a piece.
     */
    bool nonCapturingMove(int to_x, int to_y);
    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();

    /**
    * For testing multiple inheritance
    */
    int unnecessary_int;
};

#endif //CHESSPIECE_H