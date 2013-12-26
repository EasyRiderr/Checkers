/*
 * draughtpiece.h
 * The draught pieces to move on the gameboard.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#ifndef DRAUGHTPIECE_H
#define DRAUGHTPIECE_H


#include <vector>
#include <string>
#include "rules.h"
#include "piece.h"


class DraughtPiece : public Piece
{

public:

    /**
     * The constructor of draught piece.
     * @param inPosition, the position of the draught piece on the draught board.
     * @param inColor, the color of the draught.
     * @param inState, the state of the draught.
     */
    DraughtPiece(const position_t & inPosition, const color_t & inColor, const state_t & inState);


    /**
     * Copy constructor of Draughtpiece.
     * @param inDraughtpiece, the draughtpiece to copy.
     */
    DraughtPiece(const DraughtPiece & inDraughtpiece);


    /**
     * the destructor of draught piece.
     */
    virtual ~DraughtPiece();


    /**
     * returns the state of the draught.
     * @return The state of the draught.
     */
    state_t getState() const;


    /**
     * Changes the states of the draught.
     * @param inState, the new state of the draught.
     */
    void setState(const state_t & inState);


    /**
     * Draws the Piece
     */
    virtual std::string draw() const;


    /**
     * Returns all the positions reachable by the Piece on the draught board.
     * @return The vector containg all positions reachable by the Piece.
     */
    virtual std::vector<position_t> getReachablePosition() const;


    /**
     * Returns the value of the Piece.
     * @return The value of the Piece.
     */
    virtual int getValue() const;


    /**
     * Permits to clone the draught.
     * @return The clone of the draught.
     */
    Piece* Clone() const;




private:


    /** The state of the draught. */
    state_t state_;


    /** Used to calculate the reachable positions. */
    bool isReachableIter(const int & direction, const int & orientation) const;
    std::vector<position_t> isReachable(const int & direction) const;
};

#endif // DRAUGHTPIECE_H
