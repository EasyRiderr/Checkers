/*
 * draughtpiece.cpp
 * The draught pieces to move on the gameboard.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#include "draughtpiece.h"


DraughtPiece::DraughtPiece(const position_t & inPosition, const color_t & inColor, const state_t & inState) :
    Piece(inPosition, inColor),
    state_(inState)
{}


DraughtPiece::DraughtPiece(const DraughtPiece & inDraughtpiece) :
    Piece( inDraughtpiece),
    state_(inDraughtpiece.getState())
{}


DraughtPiece::~DraughtPiece() {}


state_t DraughtPiece::getState() const {
    return state_;
}


void DraughtPiece::setState(const state_t & inState) {
    state_ = inState;
}


std::string DraughtPiece::draw() const {
    return (isBlack()) ? (state_ == NORMAL)? "o" : "O" : (state_ == NORMAL)? "x" : "X";
}


bool DraughtPiece::isReachableIter(const int & direction, const int & orientation) const {
    position_t p = getPosition();
    if(p.i + orientation >= 0 && p.i + orientation < DB_LENGTH
            && p.j + direction >= 0 && p.j + direction < DB_LENGTH) {
        return true;
    }
    return false;
}


std::vector<position_t> DraughtPiece::isReachable(const int & direction) const {
    std::vector<position_t> vect;
    position_t p = getPosition(), pToAdd;
    for( int orientation = -1 ; orientation < 2 ; orientation += 2) {
        if(isReachableIter(direction, orientation)) {
            pToAdd.i = p.i + orientation;
            pToAdd.j = p.j + direction;
            vect.push_back(pToAdd);
        }
    }
    return vect;
}


std::vector<position_t> DraughtPiece::getReachablePosition() const {
    std::vector<position_t> reachablePos, v;
    if(state_ == NORMAL) {
        int direction = (isBlack()) ? 1 : -1;   // The direction top / bot
        v = isReachable(direction);
        reachablePos.insert(reachablePos.end(), v.begin(), v.end());
    } else {
        // We don't care about the direction
        for( int direction = -1 ; direction < 2 ; direction += 2) {
            v = isReachable(direction);
            reachablePos.insert(reachablePos.end(), v.begin(), v.end());
        }
    }
    return reachablePos;
}


int DraughtPiece::getValue() const {
    return (state_ == NORMAL) ? 1 : 2;
}


Piece* DraughtPiece::Clone() const {
    return new DraughtPiece(*this);
}
