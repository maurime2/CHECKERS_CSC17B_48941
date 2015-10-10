/* 
 * File:   board.h
 * Author: Joseph Keller
 * Project 1 - CIS 17A - Connect Four
 * Created on May 4, 2015, 2:42 PM
 */

#ifndef BOARD_H
#define	BOARD_H

struct Display{
    static const int ROWS = 6;
    static const int COLS = 7;
    char** board;
};

#endif	/* BOARD_H */

