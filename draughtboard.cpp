/*
 * draughtBoard.cpp
 * Represent a checkers gameboard.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#include <iostream>
#include <stdlib.h>
#include "draughtBoard.h"


void DraughtBoard::init() {
    for(int i = 0 ; i < DB_LENGTH ; ++i) {
        for(int j = 0 ; j < DB_LENGTH ; ++j) {
            gameboard_[i][j] = NULL;
        }
    }
}


DraughtBoard::DraughtBoard() {
    gameboard_ = (Piece ***) malloc(DB_LENGTH * sizeof(Piece **));
    if(gameboard_) {
        for(int i = 0 ; i < DB_LENGTH ; ++i) {
            gameboard_[i] = (Piece **) malloc(DB_LENGTH * sizeof(Piece *));
            if(!gameboard_[i]) {
                std::cerr << "Memory allocation fail." << std::endl;
                break;
            }
        }
    } else {
        std::cerr << "Memory allocation fail." << std::endl;
    }
    init();
}


color_t DraughtBoard::getColor(const position_t & inPos) const {
    return (inPos.i + inPos.j) % 2 != BLACK;
}


std::string * DraughtBoard::draw() const {
    std::string *res = new std::string("");
    for(int j = 0 ; j < DB_LENGTH ; ++j) {
        for(int i = 0 ; i < DB_LENGTH ; ++i) {
            if(gameboard_[i][j]) {
                *res += gameboard_[i][j]->draw();
            } else {
                if(getColor((position_t){i,j}) == WHITE) {
                    *res += "W";
                } else {
                    *res += "B";
                }
            }
            *res += "\t";
        }
        *res += "\n";
    }
    return res;
}


DraughtBoard::~DraughtBoard() {
    for(int i = 0 ; i < DB_LENGTH ; ++i) {
        delete gameboard_[i];
        gameboard_[i] = NULL;
    }
    delete gameboard_;
    gameboard_ = NULL;
}


bool DraughtBoard::isFree(const position_t & inPos) const throw(std::out_of_range) {
    if( inPos.i < 0 || inPos.i > DB_LENGTH - 1 || inPos.j < 0 || inPos.j > DB_LENGTH - 1) {
        throw std::out_of_range("The given position is out of range.");
    }
    return gameboard_[inPos.i][inPos.j] == NULL;
}


void DraughtBoard::addPiece(Piece & inPiece) throw(SquareNotEmpty) {
    position_t tmpPos = inPiece.getPosition();
    if(!isFree(tmpPos)) {
        throw SquareNotEmpty("The square is busy by another piece.");
    } else {
        // We add the piece to the draughtboard
        gameboard_[tmpPos.i][tmpPos.j] = &inPiece;
    }
}


void DraughtBoard::deletePiece(const position_t & inPos) throw(SquareEmpty) {
    if(isFree(inPos)) {
        throw SquareEmpty("The square is empty.");
    } else {
        gameboard_[inPos.i][inPos.j] = NULL;
    }
}


void DraughtBoard::move(const position_t & inSrc, const position_t & inDst) throw(SquareNotEmpty, SquareEmpty) {
    if(isFree(inSrc)) {
        throw SquareEmpty("The square is empty.");
    }
    if(!isFree(inDst)) {
        throw SquareNotEmpty("The square is busy by another piece.");
    }
    // Move the Piece to its destination square
    gameboard_[inDst.i][inDst.j] = gameboard_[inSrc.i][inSrc.j];
    gameboard_[inSrc.i][inSrc.j] = NULL;
    // Update the position of the piece
    gameboard_[inDst.i][inDst.j]->setPosition(inDst);
}


const Piece * DraughtBoard::getPiece(const position_t & inPosition) const {
    if(isFree(inPosition)) {
        throw SquareEmpty("The square is empty.");
    }
    return gameboard_[inPosition.i][inPosition.j];
}
