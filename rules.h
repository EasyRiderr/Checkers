/*
 * rules.h
 * Rules and definitions.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 18/12/2013
 */


#ifndef RULES_H
#define RULES_H


/**
 * By convention the top letf square is black.
 * We play only on white squares.
 * Black draught begin on top.
 */


// The draughtboard is a square of 8 * 8
#define DB_LENGTH 8


// Definition of the color type
#define WHITE true
#define BLACK false


#define NORMAL true     // The draught is normal
#define SUPER false     // The draught can move back


typedef bool color_t;

// Definition of the position type
typedef struct position_t {
    int i;  // The line in the matrix representing the draught board
    int j;  // The column in the matrix representing the draught board
} position_t;


// Definition of the state type
typedef bool state_t;

#endif // RULES_H
