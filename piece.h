/*
 * piece.h
 * Pieces to move on the gameboard.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#ifndef PIECE_H
#define PIECE_H


#include <vector>
#include <string>
#include "rules.h"
#include "prototype.h"


class Piece : public Prototype<Piece> {

public:

    /**
     * Default constructor of Piece.
     */
    Piece();


    /**
     * Destructor of Piece.
     */
    virtual ~Piece();


    /**
     * Parametrable constructor of Piece.
     * @param inPosition, the position on the draught board of the Piece.
     * @param inColor, the color of the Piece.
     */
    Piece(const position_t & inPosition, const color_t & inColor);


    /**
     * Copy constructor of Piece.
     * @param inPiece, the Piece to copy.
     */
    Piece(const Piece & inPiece);


    /**
     * Draws the Piece
     */
    virtual std::string draw() const = 0;


    /**
     * Returns the color of the Piece.
     * @return The color of the Piece.
     */
    color_t getColor() const;


    /**
     * Returns the identifier of the Piece.
     * @return The identifier of the Piece.
     */
    int getID() const;


    /**
     * Returns true if the Piece is white.
     * @return true if the Piece is white, false in other cases.
     */
    bool isWhite() const;


    /**
     * Returns true if the Piece is black.
     * @return true if the Piece is black, false in other cases.
     */
    bool isBlack() const;


    /**
     * Returns all the positions reachable by the Piece on the draught board.
     * @return The vector containg all positions reachable by the Piece.
     */
    virtual std::vector<position_t> getReachablePosition() const = 0;


    /**
     * Returns the position of the Piece.
     * @return The position of the Piece.
     */
    position_t getPosition() const;


    /**
     * Returns the value of the Piece.
     * @return The value of the Piece.
     */
    virtual int getValue() const = 0;


    /**
     * Changes the color of the Piece.
     * @param inColor, the new color of the Piece.
     */
    void setColor(const color_t & inColor);


    /**
     * Changes the position of the Piece.
     * @param inPos, the new position of the Piece.
     */
    void setPosition(const position_t & inPos);




private:

    /** The current position of the Piece on the draught board. */
    position_t pos_;


    /** The unique identifier of the Piece. */
    const int ID_;


    /** The color of the Piece. */
    color_t color_;


    /** The counter of Piece, incremented every creation of a new Piece. */
    static int counter_s;

};

#endif // PIECE_H
