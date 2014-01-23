/*
 * draughtBoard.h
 * Represent a checkers gameboard.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#ifndef DRAUGHTBOARD_H
#define DRAUGHTBOARD_H

#include <string>
#include <sstream>
#include <QtGui>
#include <stdexcept>
#include "rules.h"
#include "piece.h"
#include "clickablelabel.h"


class SquareNotEmpty : public std::exception {

public:

    /**
     * Constructor of square not empty exception.
     * @param msg, the log of the error.
     */
    SquareNotEmpty(const char * msg) {
        std::ostringstream oss;
        oss << msg;
        this->msg_ = oss.str();
    }


    /**
     * Destructor of the exception.
     */
    virtual ~SquareNotEmpty() throw(){}


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




class SquareEmpty : public std::exception {

public:

    /**
     * Constructor of square is empty exception.
     * @param msg, the log of the error.
     */
    SquareEmpty(const char * msg) {
        std::ostringstream oss;
        oss << msg;
        this->msg_ = oss.str();
    }


    /**
     * Destructor of the exception.
     */
    virtual ~SquareEmpty() throw(){}


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




class DraughtBoard {

public:

    /**
     * Constructor of draughtboard.
     */
    DraughtBoard(/*QObject * parent = 0*/);


    /**
     * Retunrs the color of the selected square.
     * @return The color of the selected square.
     */
    color_t getColor(const position_t & inPos) const;


    /**
     * Draws the draughtpiece.
     */
    QWidget * draw() const;


    /**
     * Destructor of draughtboard.
     */
    ~DraughtBoard();


    /**
     * Permits to know if the position passed in parameter is filled by a Piece.
     * @return true if the square is free.
     * @throw std::out_of_range
     */
    bool isFree(const position_t & inPos) const throw(std::out_of_range);


    /**
     * Permits to add a new Piece to the draughtboard.
     * @param inPiece, the Piece to add.
     * @throw SquareNotEmpty exception if the square is not empty.
     */
    void addPiece(Piece & inPiece) throw(SquareNotEmpty);


    /**
     * Permits to delete a Piece from the draughtboard.
     * @param inPos, the position of the Piece to delete.
     * @throw SquareEmpty exception if the square is empty.
     */
    void deletePiece(const position_t & inPos) throw(SquareEmpty);


    /**
     * Permits to move a Piece from a given position to another.
     * @param inSrc, the source position of the Piece.
     * @param inDst, the destination position of the Piece.
     */
    void move(const position_t & inSrc, const position_t & inDst) throw(SquareNotEmpty, SquareEmpty);


    /**
     * Returns the Piece contained in the square to the given position.
     * @param inPosition, the position of the Piece on the draughtboard.
     * @return The piece wished.
     */
    const Piece * getPiece(const position_t & inPosition) const;




    /**
     * Return the table of clickable labels.
     * @return The table of clickable labels.
     */
    ClickableLabel ** getLabelTable();




private:

    /**
     * The gameboard.
     */
    Piece *** gameboard_;


    /**
     * Initialyzes all sqares of the draughtboard to NULL.
     */
    void init();


    /**
     * ClickableLabel table.
     */
    ClickableLabel ** labelTable_;

};


#endif // DRAUGHTBOARD_H
