/*
 * controller.h
 * Control the game, move pieces, etc.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 20/12/2013
 */


#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <map>
#include "rules.h"
#include "piece.h"
#include "draughtBoard.h"


class NotReachableSquare : public std::exception {

public:

    /**
     * Constructor of not reachable square exception.
     * @param msg, the log of the error.
     */
    NotReachableSquare(const char * msg) {
        std::ostringstream oss;
        oss << msg;
        this->msg_ = oss.str();
    }


    /**
     * Destructor of the exception.
     */
    virtual ~NotReachableSquare() throw(){}


    /**
     * Permits to describe the error.
     * @return The log of the error.
     */
    virtual const char * what() const throw() {
        return this->msg_.c_str();
    }




private:

    /** The log of the error. */
    std::string msg_;

};


class IllegalMove : public std::exception {

public:

    /**
     * Constructor of illegal move exception.
     * @param msg, the log of the error.
     */
    IllegalMove(const char * msg) {
        std::ostringstream oss;
        oss << msg;
        this->msg_ = oss.str();
    }


    /**
     * Destructor of the exception.
     */
    virtual ~IllegalMove() throw(){}


    /**
     * Permits to describe the error.
     * @return The log of the error.
     */
    virtual const char * what() const throw() {
        return this->msg_.c_str();
    }




private:

    /** The log of the error. */
    std::string msg_;

};


class WrongPlayer : public std::exception {

public:

    /**
     * Constructor of wrong player exception.
     * @param msg, the log of the error.
     */
    WrongPlayer(const char * msg) {
        std::ostringstream oss;
        oss << msg;
        this->msg_ = oss.str();
    }


    /**
     * Destructor of the exception.
     */
    virtual ~WrongPlayer() throw(){}


    /**
     * Permits to describe the error.
     * @return The log of the error.
     */
    virtual const char * what() const throw() {
        return this->msg_.c_str();
    }




private:

    /** The log of the error. */
    std::string msg_;

};


class Controller
{

public:

    /**
     * Default constructor of Controller.
     */
    Controller();


    /**
     * Destructor of Controller.
     */
    ~Controller();


    /**
     * Permits to move a Piece from a source to a destination.
     * @param inSrc, the source square of the Piece.
     * @param inDst, the destination square of the Piece.
     * @throw SquareEmpty if the source position does not contain a Piece.
     * @throw std::out_of_range if a given position is out of range.
     * @throw WrongPlayer if the source position contains a wrong color Piece.
     * @throw SquareNotEmpty if the destination position is occuped by another Piece.
     * @throw NotReachableSquare if the square is not reachble by the Piece.
     */
    void move(const position_t & inSrc, const position_t & inDst) throw(SquareNotEmpty, SquareEmpty, std::out_of_range, WrongPlayer, NotReachableSquare, IllegalMove);


    /**
     * Displays the draughtboard.
     */
    void display() const;


    /**
     * Permits to know if the game is end.
     * @return True of the game is end.
     */
    bool isEnd() const;


    /**
     * Returns the number of remaining black pieces.
     * @return The number of remaining black pieces.
     */
    int getBlackPiecesNumber() const;


    /**
     * Returns the number of remaining white pieces.
     * @return The number of remaining white pieces.
     */
    int getWhitePiecesNumber() const;




private:

    /** The map containing all white Pieces. */
    std::map<int, Piece *> whitePieces_;


    /** The map containing all black Pieces. */
    std::map<int, Piece *> blackPieces_;


    /** Permits to know who does play (white or black). */
    color_t next_;


    /** The draughtboard. */
    DraughtBoard db_;


    /**
     * Permits to initialize the draughtboard and maps of Pieces.
     */
    void initDraughtboard();


    /**
     * Verifies that the position are valid to move a Piece.
     * @param inSrc, the source square of the Piece.
     * @param inDst, the destination square of the Piece.
     * @throw SquareEmpty if the source position does not contain a Piece.
     * @throw std::out_of_range if a given position is out of range.
     * @throw WrongPlayer if the source position contains a wrong color Piece.
     * @throw SquareNotEmpty if the destination position is occuped by another Piece.
     */
    void verifyPositions(const position_t & inSrc, const position_t & inDst) const throw(SquareEmpty, std::out_of_range, WrongPlayer, SquareNotEmpty);


    /**
     * Returns true if the position given in parameter is reachable the Piece.
     * @param inPiece, The Piece to test if it can reach the position given in parameter.
     * @param inPos, The position to reach.
     * @return True if the position given in parameter is reachable the Piece.
     */
    bool pieceCanReachPosition(const Piece & inPiece, const position_t & inPos) const;


};

#endif // CONTROLLER_H
