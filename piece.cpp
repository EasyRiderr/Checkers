/*
 * piece.h
 * Pieces to move on the gameboard.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#include "piece.h"
#include <iostream>


// Initition of the counter
int Piece::counter_s = 1;


Piece::Piece() :
    ID_(counter_s++),
    color_(WHITE)
{
    pos_.i = -1;
    pos_.j = -1;
}


Piece::~Piece() {
    pos_.i = -1;
    pos_.j = -1;
}


Piece::Piece(const position_t & inPosition, const color_t & inColor) :
    pos_(inPosition),
    ID_(counter_s++),
    color_(inColor)
{}


Piece::Piece(const Piece & inPiece) :
    pos_(inPiece.getPosition()),
    ID_(counter_s++),
    color_(inPiece.getColor())
{}


color_t Piece::getColor() const {
    return color_;
}


int Piece::getID() const {
    return ID_;
}


bool Piece::isWhite() const {
    return color_==WHITE;
}


bool Piece::isBlack() const {
    return color_==BLACK;
}


position_t Piece::getPosition() const {
    return pos_;
}


void Piece::setColor(const color_t & inColor) {
    color_ = inColor;
}


void Piece::setPosition(const position_t & inPos) {
    pos_ = inPos;
}
