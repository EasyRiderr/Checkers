/*
 * controller.cpp
 * Control the game, move pieces, etc.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 20/12/2013
 */


#include <iostream>
#include <stdlib.h>
#include "controller.h"
#include "factory.h"
#include "draughtpiece.h"


Controller::Controller() :
    next_(WHITE)
{
    initDraughtboard();
}


Controller::~Controller() {
    for(std::map<int, Piece *>::iterator it = whitePieces_.begin() ; it != whitePieces_.end() ; ++it) {
        delete (*it).second;
    }
    for(std::map<int, Piece *>::iterator it = blackPieces_.begin() ; it != blackPieces_.end() ; ++it) {
        delete (*it).second;
    }
}


void Controller::initDraughtboard() {
    Factory<Piece> fac;
    fac.record("WhiteDraught", new DraughtPiece((position_t){-1, -1}, WHITE, NORMAL));
    fac.record("BlackDraught", new DraughtPiece((position_t){-1, -1}, BLACK, NORMAL));

    Piece * p;
    // Create and place black pieces
    for(int i = 0 ; i < 12 ; ++i) {
        p = fac.create("BlackDraught");
        p->setPosition((position_t){(i < 4 || i > 7) ? 2 * (i % 4) + 1 : 2 * (i % 4), i / 4});
        db_.addPiece(*p);
        blackPieces_[p->getID()] = p;
    }

    // Same thing for the white pieces
    for(int i = 0 ; i < 12 ; ++i) {
        p = fac.create("WhiteDraught");
        p->setPosition((position_t){(i >= 4 && i <= 7) ? 2 * (i % 4) + 1: 2 * (i % 4), i / 4 + 5});
        db_.addPiece(*p);
        whitePieces_[p->getID()] = p;
    }
}


void Controller::verifyPositions(const position_t & inSrc, const position_t & inDst) const throw(SquareEmpty, std::out_of_range, WrongPlayer, SquareNotEmpty) {
    // Verify that the source position contains a Piece
    if(db_.isFree(inSrc)) {
        std::string tmp = "You must select a " + (std::string)((next_ == WHITE)? "white" : "black") + " piece to move.";
        throw SquareEmpty(tmp.c_str());
    }

    // Verify that the source position contains a Piece which can move this turn
    if(db_.getPiece(inSrc)->getColor() != next_) {
        std::string tmp = "It is not your turn to play, you must move a " + (std::string)((next_ == WHITE)? "white" : "black") + " piece.";
        throw WrongPlayer(tmp.c_str());
    }

    if(!db_.isFree(inDst)) {
        throw SquareNotEmpty("The destination square must be unoccuped.");
    }
}


void Controller::move(const position_t & inSrc, const position_t & inDst) throw(SquareNotEmpty, SquareEmpty, std::out_of_range, WrongPlayer, NotReachableSquare, IllegalMove) {
    verifyPositions(inSrc, inDst);
    bool throwError = false;
    position_t pieceToEat;

    // Verify that the destination is reachable by the Piece
    if(pieceCanReachPosition(*db_.getPiece(inSrc), inDst)) {
        db_.move(inSrc, inDst);
    } else {
        // The position is perhaps reachable by eating an ennemy piece.
        position_t diff = {inDst.i - inSrc.i, inDst.j - inSrc.j};

        if(abs(diff.i) == 2) {
            pieceToEat.i = inSrc.i + diff.i / 2;
            if(((DraughtPiece*)db_.getPiece(inSrc))->getState() == SUPER) {
                if(abs(diff.j) == 2) {
                    pieceToEat.j = inSrc.j + diff.j / 2;
                } else {
                    throwError = true;
                }
            } else if( db_.getPiece(inSrc)->getColor() == WHITE) {
                if(diff.j == -2) {
                    pieceToEat.j = inSrc.j - 1;
                } else {
                    throwError = true;
                }
            } else {
                // The Piece is black
                if(diff.j == 2) {
                    pieceToEat.j = inSrc.j + 1;
                } else {
                    throwError = true;
                }
            }
        } else {
            throwError = true;
        }

        if(throwError) {
            throw NotReachableSquare("The square is not reachable by the Piece.");
        }

        if(db_.isFree(pieceToEat)) {
            throw IllegalMove("You cannot reach this square.");
        }
        if(db_.getPiece(pieceToEat)->getColor() == db_.getPiece(inSrc)->getColor()) {
            throw IllegalMove("You cannot eat a Piece of the same color.");
        }

        // Delete the eaten Piece and make the move
        int id = db_.getPiece(pieceToEat)->getID();
        if(db_.getPiece(pieceToEat)->getColor() == WHITE) {
            delete whitePieces_[id];
            whitePieces_.erase(id);
        } else {
            delete blackPieces_[id];
            blackPieces_.erase(id);
        }
        db_.deletePiece(pieceToEat);
        db_.move(inSrc, inDst);

    }

    // Check the state of the Piece
    if((inDst.j == 0 || inDst.j == DB_LENGTH - 1) && ((DraughtPiece *)db_.getPiece(inDst))->getState() == NORMAL) {
        ((DraughtPiece *)db_.getPiece(inDst))->setState(SUPER);
    }

    // Change player
    next_ = !next_;
}


bool Controller::pieceCanReachPosition(const Piece & inPiece, const position_t & inPos) const {
    std::vector<position_t> reachablePositions = inPiece.getReachablePosition();
    bool find = false;
    for(std::vector<position_t>::const_iterator it = reachablePositions.begin() ; it != reachablePositions.end() && !find ; ++it) {
        if(it->i == inPos.i && it->j == inPos.j) {
            find = true;
        }
    }
    return find;
}


void Controller::display() const {
    std::cout << *db_.draw() << std::endl;
}


bool Controller::isEnd() const {
    return blackPieces_.size() == 0 || whitePieces_.size() == 0;
}


int Controller::getBlackPiecesNumber() const {
    return blackPieces_.size();
}


int Controller::getWhitePiecesNumber() const {
    return whitePieces_.size();
}
