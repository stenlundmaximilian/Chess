//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <vector>
#include <istream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "ChessMove.h"
#include "Matrix.h"   // Use the "-I ../02" flag to let the compiler find Matrix.h
#include <fstream>
using namespace std;

class ChessPiece;

class ChessBoard {
    // add additional members or functions of your choice

private:
    // Alternative 1 (the matrix owns the chess pieces):
    Matrix<shared_ptr<ChessPiece>> m_state; // Matrix from lab 2
    vector<ChessPiece*> m_white_pieces;
    vector<ChessPiece*> m_black_pieces;

    // Alternative 2 (the vectors own the chess pieces):
    // Matrix<ChessPiece *> m_state; // Matrix from lab 2
    // vector<shared_ptr<ChessPiece>> m_white_pieces;
    // vector<shared_ptr<ChessPiece>> m_black_pieces;

public:
    //added by me
    ChessBoard();
    Matrix<shared_ptr<ChessPiece>> state();
    vector<ChessPiece*> white_pieces();
    vector<ChessPiece*> black_pieces();
    friend ChessBoard& operator>>(istream& is, ChessBoard& cb);
    friend ChessBoard& operator<<(ostream& os, ChessBoard& cb);
    void Ai1(bool is_white);
    void Ai2(bool is_white);
    void chess_to_file(fstream &myFile);
    //void play(int argc, char* argv[]);
    //was there before
    void movePiece(ChessMove chess_move);
    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);

};

ChessBoard& operator>>(istream& is, ChessBoard& cb);
ChessBoard& operator<<(ostream& os, ChessBoard& cb);

#endif //CHESSBOARD_H
