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
#include "draughtpiece.h"


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

    // Initialize the QLabel table
    labelTable_ = (ClickableLabel **) malloc(DB_LENGTH * DB_LENGTH * sizeof(ClickableLabel *));
    if(labelTable_) {
        bool shift = true;
        for(int i = 0 ; i < DB_LENGTH * DB_LENGTH ; ++i) {
            labelTable_[i] = new ClickableLabel((position_t){i / 8, i % 8});
            // Set the background color of the square.
            if(i % 8 == 0) {
                shift = !shift;
            }
            if((i % 2 == 0 && !shift) ||  ((i % 2 != 0 && shift))) {
                // The square is black
                labelTable_[i]->setStyleSheet("QLabel { background-color : black;}");
            } else {
                // The square is white
                labelTable_[i]->setStyleSheet("QLabel { background-color : white;}");
            }
        }
    } else {
        std::cerr << "Memory allocation fail." << std::endl;
    }
}


color_t DraughtBoard::getColor(const position_t & inPos) const {
    return (inPos.i + inPos.j) % 2 != BLACK;
}


QWidget * DraughtBoard::draw() const {
    QWidget * db = new QWidget;

    // Create the layout for the draughtboard
    QGridLayout * layout = new QGridLayout;

    // Add QLabels to the layout
    position_t p;
    for(int i = 0 ; i < DB_LENGTH * DB_LENGTH ; ++i) {
        p = (position_t){i / DB_LENGTH, i % DB_LENGTH};
        if(!isFree(p)) {
            labelTable_[i]->setPixmap(*getPiece(p)->draw());
        } else {
            labelTable_[i]->setPixmap(0);
        }
        layout->addWidget(labelTable_[i], i % DB_LENGTH, i / DB_LENGTH);
    }

    // Suppress margin and padding between sqares
    layout->setMargin(0);
    layout->setSpacing(0);

    db->setLayout(layout);

    return db;
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


ClickableLabel ** DraughtBoard::getLabelTable() {
    return labelTable_;
}
