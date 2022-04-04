//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

ChessBoard::ChessBoard() { //creates chessboard
    Matrix<shared_ptr<ChessPiece>> board(8); 
    m_state = board;
}

Matrix<shared_ptr<ChessPiece>> ChessBoard::state() { //access the board
    return m_state;
}

vector<ChessPiece*> ChessBoard::white_pieces() {//access white pieces 
    return this->m_white_pieces;
}

vector<ChessPiece*> ChessBoard::black_pieces() {//access black pieces
    return this->m_black_pieces;
}

void ChessBoard::movePiece(ChessMove chess_move) { //move a piece
    ChessPiece* y = &(*m_state(chess_move.to_x, chess_move.to_y)); 
    if (y->latin1Representation() != '.') { //this if-block deletes a piece from the m_white_pieces/m_black_pieces if the move is a capturing move
        if (y->m_is_white) { 
            for (int i = 0; i < size(this->m_white_pieces); i++) { 
                if (this->m_white_pieces[i] == y) {
                    this->m_white_pieces.erase(this->m_white_pieces.begin() + i);
                }
            }
        }
        if (!y->m_is_white) {
            for (int i = 0; i < size(this->m_black_pieces); i++) {
                if (this->m_black_pieces[i] == y) {
                    this->m_black_pieces.erase(this->m_black_pieces.begin() + i);
                }
            }
        }
    }

    if (tolower(m_state(chess_move.from_x, chess_move.from_y)->latin1Representation()) == 'p' and chess_move.to_x == 0) { // block for promoting a white pawn
        //srand(time(0));
        int p = rand() % 4;
        ChessPiece* z1 = &(*m_state(chess_move.from_x, chess_move.from_y));
        
        if (p == 0) { //block for promoting to bishop
            m_state(chess_move.from_x, chess_move.from_y).reset(new Bishop(chess_move.from_x, chess_move.from_y, true, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_white_pieces.push_back(z2);
        }
        if (p == 1) { //block for promoting to knight
            m_state(chess_move.from_x, chess_move.from_y).reset(new Knight(chess_move.from_x, chess_move.from_y, true, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_white_pieces.push_back(z2);
        }

        if (p == 2) { //block for promoting to queen
            m_state(chess_move.from_x, chess_move.from_y).reset(new Queen(chess_move.from_x, chess_move.from_y, true, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_white_pieces.push_back(z2);
        }

        if (p == 3) { // block for promoting to rook
            m_state(chess_move.from_x, chess_move.from_y).reset(new Rook(chess_move.from_x, chess_move.from_y, true, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_white_pieces.push_back(z2);
        }
        
        for (int i = 0; i < size(this->m_white_pieces); i++) { //delete the pawn
            if (this->m_white_pieces[i] == z1) {
                this->m_white_pieces.erase(this->m_white_pieces.begin() + i);
            }
        }
    }

    if (tolower(m_state(chess_move.from_x, chess_move.from_y)->latin1Representation()) == 'p' and chess_move.to_x == 7) { // block for promoting a black pawn same logic as the one for white pawn

        //srand(time(0));
        int p = rand() % 4;
        ChessPiece* z1 = &(*m_state(chess_move.from_x, chess_move.from_y));

        if (p == 0) { //promote to bishop
            m_state(chess_move.from_x, chess_move.from_y).reset(new Bishop(chess_move.from_x, chess_move.from_y, false, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_black_pieces.push_back(z2);
        }
        if (p == 1) { // promote to knight
            m_state(chess_move.from_x, chess_move.from_y).reset(new Knight(chess_move.from_x, chess_move.from_y, false, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_black_pieces.push_back(z2);
        }

        if (p == 2) { // promote to queen
            m_state(chess_move.from_x, chess_move.from_y).reset(new Queen(chess_move.from_x, chess_move.from_y, false, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_black_pieces.push_back(z2);
        }

        if (p == 3) { // promote to rook 
            m_state(chess_move.from_x, chess_move.from_y).reset(new Rook(chess_move.from_x, chess_move.from_y, false, this));
            ChessPiece* z2 = &(*m_state(chess_move.from_x, chess_move.from_y));
            m_black_pieces.push_back(z2);
        }

        for (int i = 0; i < size(this->m_black_pieces); i++) { // delete the pawn
            if (this->m_black_pieces[i] == z1) {
                this->m_black_pieces.erase(this->m_black_pieces.begin() + i);
            }
        }
    }

    m_state(chess_move.to_x, chess_move.to_y).swap(m_state(chess_move.from_x, chess_move.from_y)); //swap places between from and too positions chesspieces
    m_state(chess_move.to_x, chess_move.to_y)->m_x = chess_move.to_x; //replace the m_x and m_y attributes for the moved piece
    m_state(chess_move.to_x, chess_move.to_y)->m_y = chess_move.to_y;
    shared_ptr<ChessPiece> x = make_shared<ChessPiece>(chess_move.from_x, chess_move.from_y, true, this); 
    m_state(chess_move.from_x, chess_move.from_y) = x; //add an empty square to the from position
}

vector<ChessMove> ChessBoard::capturingMoves(bool is_white) { //all the capturing moves for a piece of a given color
    vector<ChessMove> moves;
    if (is_white) {
        for (ChessPiece* i : this->m_white_pieces) { //goes through all the capturing moves of every piece and adds them to a vector
            vector<ChessMove> new_moves = i->capturingMoves(); 
            for (ChessMove i : new_moves) {
                moves.push_back(i); 
            }
        }
        return moves;
    }
    else if(!is_white) {
        for (ChessPiece* i : this->m_black_pieces) { //goes through all the capturing moves of every piece and adds them to a vector
            vector<ChessMove> new_moves = i->capturingMoves();
            for (ChessMove i : new_moves) {
                moves.push_back(i);
            }
        }
        return moves;
    }
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) { //the same as capturing moves but for non capturing moves
    vector<ChessMove> moves;
    if (is_white) {
        for (ChessPiece* i : this->m_white_pieces) {
            vector<ChessMove> new_moves = i->nonCapturingMoves();
            for (ChessMove i : new_moves) {
                moves.push_back(i);
            }
        }
        return moves;
    }
    else {
        for (ChessPiece* i : this->m_black_pieces) {
            vector<ChessMove> new_moves = i->nonCapturingMoves();
            for (ChessMove i : new_moves) {
                moves.push_back(i);
            }
        }
        return moves;
    }
}

ChessBoard& operator>>(istream& is, ChessBoard& cb) { //reads a chess board in latin1Representation
    string row;
    ChessBoard * cb_ptr = &cb;
    for (int i = 0; i < 8; i++) {
        is >> row;
        for (int j = 0; j < 8; j++) {
            //the logic for all the if blocks below are the same

            if (row[j] == 'P') { //if the piece at the given row,column is a white pawn
                shared_ptr<ChessPiece> x = make_shared<Pawn>(i,j,true,cb_ptr);
                cb.m_state(i, j) = x; //add a white pawn to the board at the right index
                ChessPiece* y = &(*x);
                cb.m_white_pieces.push_back(y); //add a white pawn to the m_white_pieces vector
            }
            else if (row[j] == 'p') {
                shared_ptr<ChessPiece> x = make_shared<Pawn>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_black_pieces.push_back(y);
            }
            else if (row[j] == 'B') {
                shared_ptr<ChessPiece> x = make_shared<Bishop>(i, j, true, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_white_pieces.push_back(y);
            }
            else if (row[j] == 'b') {
                shared_ptr<ChessPiece> x = make_shared<Bishop>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_black_pieces.push_back(y);
            }
            else if (row[j] == 'K') {
                shared_ptr<ChessPiece> x = make_shared<King>(i, j, true, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_white_pieces.push_back(y);
            }
            else if (row[j] == 'k') {
                shared_ptr<ChessPiece> x = make_shared<King>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_black_pieces.push_back(y);
            }
            else if (row[j] == 'N') {
                shared_ptr<ChessPiece> x = make_shared<Knight>(i, j, true, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_white_pieces.push_back(y);
            }
            else if (row[j] == 'n') {
                shared_ptr<ChessPiece> x = make_shared<Knight>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_black_pieces.push_back(y);
            }
            else if (row[j] == 'Q') {
                shared_ptr<ChessPiece> x = make_shared<Queen>(i, j, true, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_white_pieces.push_back(y);
            }
            else if (row[j] == 'q') {
                shared_ptr<ChessPiece> x = make_shared<Queen>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_black_pieces.push_back(y);
            }
            else if (row[j] == 'R') {
                shared_ptr<ChessPiece> x = make_shared<Rook>(i, j, true, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_white_pieces.push_back(y);
            }
            else if (row[j] == 'r') {
                shared_ptr<ChessPiece> x = make_shared<Rook>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
                ChessPiece* y = &(*x);
                cb.m_black_pieces.push_back(y);
            }
            else if (row[j] == '.') {
                shared_ptr<ChessPiece> x = make_shared<ChessPiece>(i, j, false, cb_ptr);
                cb.m_state(i, j) = x;
            }
        }
    }
    return cb;
}

ChessBoard& operator<<(ostream& os, ChessBoard& cb) { //writes the board to the console in latin1representation (for utf representation see the method chess_to_file())
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            os <<  (* cb.state()(i, j)).latin1Representation();
        }
        os << endl;
    }
    os << endl;
    return cb;
}

void ChessBoard::Ai1(bool is_white) { //defines a move for a random ai according to lab instructions for a given color of the ai
    //srand(time(0));
    vector<ChessMove> x = this->capturingMoves(is_white);
    vector<ChessMove> y = this->nonCapturingMoves(is_white);
    ChessMove move;
    if (size(x) == 0) { //if there are no capturing moves make a random non capturing move
        if (size(y) != 0) {
            move = y[rand() % size(y)];
            this->movePiece(move);
        }
    }
    else { //otherwise make a random capturing move
        move = x[rand() % size(x)];
        this->movePiece(move);
    }
}
void ChessBoard::Ai2(bool is_white) {
    vector<ChessMove> x1 = this->capturingMoves(is_white);
    vector<ChessMove> x2 = this->capturingMoves(!is_white);
    vector<ChessMove> y1 = this->nonCapturingMoves(is_white);
    vector<ChessMove> y2 = this->nonCapturingMoves(!is_white);
    ChessMove move;
    if (size(x1) == 0) { //if there are no capturing moves make a non capturing move where the piece can be captured
        for (ChessMove i : y1) {
            for (ChessMove j : y2) {
                if (tolower(this->m_state(j.from_x, j.from_y)->latin1Representation()) != 'p') { 
                    if (i.to_x == j.to_x and i.to_y == j.to_y) { //if the non capturing move is a non capturing move for the other color as well it should move there except if the other piece is a pawn
                        this->movePiece(i);
                        return;
                    }
                }
                else { //if the other colors piece is a pawn it should check if it could move to one of the squares where the pawn can capture it
                    if (((i.to_x == j.to_x and i.to_y == j.to_y + 1) or (i.to_x == j.to_x and i.to_y == j.to_y - 1)) and abs(j.from_x-j.to_x) != 2) {
                        this->movePiece(i);
                        return;
                    }
                }
            }
        }
    }
    else {//if there are capturing moves it should capture the piece where it can be recaptured by the other color
        for (ChessMove i : x1) { 
            ChessPiece temp = (*this->m_state(i.to_x, i.to_y));
            char temp_char = (*this->m_state(i.to_x, i.to_y)).latin1Representation();
            char temp_char2 = (*this->m_state(i.from_x, i.from_y)).latin1Representation();
            bool bool2 = this->m_state(i.from_x, i.from_y)->m_is_white;
            this->movePiece(i); //make a capturing move
            x2 = this->capturingMoves(!is_white); 
            for (ChessMove j : x2) {
                if (i.to_x == j.to_x and i.to_y == j.to_y) {
                    return; //if the moved piece can now be captured the ai is done
                }
            }
            ChessMove move;
            move.from_x = i.to_x;
            move.from_y = i.to_y;
            move.to_x = i.from_x;
            move.to_y = i.from_y;
            this->movePiece(move); //if the piece can't be captured it should be moved back and the board should be restored
            
            if (tolower(temp_char2) == 'p' and (i.to_x == 0 or i.to_x == 7)) {
                ChessPiece* piece2 = &(*this->m_state(i.from_x, i.from_y));
                for (int i = 0; i < size(this->m_white_pieces); i++) {
                    if (this->m_white_pieces[i] == piece2) {
                        this->m_white_pieces.erase(this->m_white_pieces.begin() + i);
                    }
                }
                for (int i = 0; i < size(this->m_black_pieces); i++) {
                    if (this->m_black_pieces[i] == piece2) {
                        this->m_black_pieces.erase(this->m_black_pieces.begin() + i);
                    }
                }
                m_state(i.from_x, i.from_y).reset(new Pawn(i.from_x, i.from_y, bool2, this));
                ChessPiece* z2 = &(*m_state(i.from_x, i.from_y));
                if (bool2) {
                    m_white_pieces.push_back(z2);
                }
                else {
                    m_black_pieces.push_back(z2);
                }
            }
            //the logic of the blocks below restors the captured piece to it's original position
            if (tolower(temp_char) == 'b') {
                this->m_state(i.to_x, i.to_y).reset(new Bishop(temp.m_x, temp.m_y, temp.m_is_white, temp.m_board));
            }
            if (tolower(temp_char) == 'k') {
                this->m_state(i.to_x, i.to_y).reset(new King(temp.m_x, temp.m_y, temp.m_is_white, temp.m_board));
            }
            if (tolower(temp_char) == 'n') {
                this->m_state(i.to_x, i.to_y).reset(new Knight(temp.m_x, temp.m_y, temp.m_is_white, temp.m_board));
            }
            if (tolower(temp_char) == 'p') {
                this->m_state(i.to_x, i.to_y).reset(new Pawn(temp.m_x, temp.m_y, temp.m_is_white, temp.m_board));
            }
            if (tolower(temp_char) == 'q') {
                this->m_state(i.to_x, i.to_y).reset(new Queen(temp.m_x, temp.m_y, temp.m_is_white, temp.m_board));
            }
            if (tolower(temp_char) == 'r') {
                this->m_state(i.to_x, i.to_y).reset(new Rook(temp.m_x, temp.m_y, temp.m_is_white, temp.m_board));
            }
            ChessPiece* z3 = &(*m_state(i.to_x, i.to_y)); //the restored piece gets added to white or black pieces
            if (temp.m_is_white) {
                m_white_pieces.push_back(z3);
            }
            else {
                m_black_pieces.push_back(z3);
            }
        }
    }
    this->Ai1(is_white); //if no piece can place itself where it can be captured a random move should happen
    }

void ChessBoard::chess_to_file(fstream &myFile) { //writes a chess_board to an html file
    myFile.open("chessboard.htm", std::ios_base::app);
    if (myFile.is_open()) {
        for (int i = 0; i < 8; i++) {
            myFile << "<p>";
            for (int j = 0; j < 8; j++) {
                myFile << (*this->state()(i, j)).utfRepresentation(); //add a utf piece at the right index in a paragraph
            }
            myFile << "</p>" << endl;
        }
        myFile << "<p>&#x2800</p>" << endl; //add some empty lines to the next board
        myFile << "<p>&#x2800</p>" << endl;
        myFile << "<p>&#x2800</p>" << endl;
        myFile << "<p>&#x2800</p>" << endl;
        myFile << "<p>&#x2800</p>" << endl;
        myFile << "<p>&#x2800</p>" << endl;
        myFile << "<p>&#x2800</p>" << endl;
        myFile << "<p>&#x2800</p>" << endl;
        myFile.close();
    }
}

