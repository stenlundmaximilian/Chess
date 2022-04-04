//
// DD1388 - Lab 4: Losing Chess
//
#include <fstream>
#include "ChessMove.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include <sstream>
using std::vector; using std::stringstream; using std::cout; using std::endl;
int main(int argc, char* argv[]) { // choose the commandline arguments as "white-ai black-ai starting-color" for example "ai1 ai2 white" or "ai1 ai1 black"
    srand(time(0));
    fstream myFile;
    myFile.open("chessboard.htm", std::ios::out); //writes the start of an html file
    if (myFile.is_open()) {
        myFile << "<!DOCTYPE html>" << endl;
        myFile << "<html>" << endl;
        myFile << "<head>" << endl;
        myFile << "<style>" << endl;
        myFile << "p{" << endl;
        myFile << "  font-size: 80px;" << endl; //sets fontsize of chesspieces
        myFile << "  line-height: 0;" << endl; //sets line-hight between chesspieces
        myFile << "}" << endl;
        myFile << "</style>" << endl;
        myFile << "</head>" << endl;
        myFile << "<body>" << endl;
        myFile.close();
    }

    ChessBoard chess; //creates the chess board
    stringstream s;

    s << "rnbqkbnr" << endl; //read in your chessboard here
    s << "pppppppp" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "PPPPPPPP" << endl;
    s << "RNBQKBNR";

    //s << "........" << endl; //read in your chessboard here
    //s << "PPPPPPPP" << endl;
    //s << "........" << endl;
    //s << "........" << endl;
    //s << "........" << endl;
    //s << "........" << endl;
    //s << "pppppppp" << endl;
    //s << "........";

    s >> chess;
    cout << chess; //the chessboard gets printed to the console
    chess.chess_to_file(myFile); //the chessboard gets written to myFile
    
    //the logic is the same for every if block below. Each block corresponds to a choice of ai and a starting color.

    if (argv[1][2] == '1' and argv[2][2] == '2' and argv[3][0] == 'w') { //checks if the white player is ai1, if the black player is ai2 and if the startingcolor is white
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) { //checks if the program should end
            chess.Ai1(true); //ai 1 makes a move as white
            cout << chess; 
            chess.chess_to_file(myFile); //write to file
            if (size(chess.black_pieces()) != 0) {
                chess.Ai2(false); //ai 2 makes a move as black
                cout << chess;
                chess.chess_to_file(myFile); //write to file
            }
        }
    }
    //cout << size(chess.black_pieces()) << endl;
    //cout << size(chess.white_pieces()) << endl;

    if (argv[1][2] == '2' and argv[2][2] == '1' and argv[3][0] == 'w') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai2(true);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.black_pieces()) != 0) {
                chess.Ai1(false); 
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    if (argv[1][2] == '1' and argv[2][2] == '1' and argv[3][0] == 'w') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai1(true);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.black_pieces()) != 0) {
                chess.Ai1(false); 
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    if (argv[1][2] == '2' and argv[2][2] == '2' and argv[3][0] == 'w') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai2(true);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.black_pieces()) != 0) {
                chess.Ai2(false); 
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    if (argv[1][2] == '1' and argv[2][2] == '2' and argv[3][0] == 'b') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai2(false);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.white_pieces()) != 0) {
                chess.Ai1(true);
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    if (argv[1][2] == '2' and argv[2][2] == '1' and argv[3][0] == 'b') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai1(false);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.white_pieces()) != 0) {
                chess.Ai2(true); 
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    if (argv[1][2] == '1' and argv[2][2] == '1' and argv[3][0] == 'b') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai1(false);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.white_pieces()) != 0) {
                chess.Ai1(true);
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    if (argv[1][2] == '2' and argv[2][2] == '2' and argv[3][0] == 'b') {
        while (size(chess.black_pieces()) != 0 and size(chess.white_pieces()) != 0) {
            chess.Ai2(false);
            cout << chess;
            chess.chess_to_file(myFile);
            if (size(chess.white_pieces()) != 0) {
                chess.Ai2(true); 
                cout << chess;
                chess.chess_to_file(myFile);
            }
        }
    }

    myFile.open("chessboard.htm", std::ios_base::app); //write the end of the html file
    if (myFile.is_open()) {
        myFile << "</body>" << endl;
        myFile << "</html>" << endl;
        myFile.close();
    }
}