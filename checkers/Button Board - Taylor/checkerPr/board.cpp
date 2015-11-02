#include "board.h"


Board::Board(QWidget *parent) : QWidget(parent)
{
    QString s;
    for (int i = 0; i < 32; i++)
    {
        tiles.push_back(new Tile(this));
        tiles[i]->location = i;
        tiles[i]->activity = Tile::NOACTIVITY;

        if (i <12)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/blackPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::BLACKPIECE;
        }
        else if (i>19)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/checkersPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::REDPIECE;
        }
        else if (i == 17)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/blackPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::BLACKPIECE;
        }
        else
        {
            tiles[i]->state = Tile::EMPTY;
        }
    }
    startSelected = false;
}

void Board::handleClick(int loc)
{   
    if (setStartLoc(loc))
    {
        // if true then, one of the player's own pieces has been selected and should have been set
        // if not true then the selected tile is either empty or an enemy's. We check for this and act accordingly in a following
        // else statement

    }
    else if (startSelected)
    {


        // tile selected is either empty or an enemy's piece.
        // check whether or not the tile is an enemy's piece. If it is do nothing.
        // If the tile is empty, check whether or not it is a valid move. If it is a valid move, make move,
        // check for king, check for win, update the pieces, and to end turn delete possible moves, undo highlights
        // set start selected to false, unset startLoc and switch to other player's turn.
        if (tileIsEmpty(loc))
        {
            if(checkMove(startLoc, loc))
            {

                makeMove();
                startSelected = false;
            }
        }
        else
        {
            // tile selected is an enemy piece and startLoc should remain the same without anything happening
        }
    }

}

bool Board::setStartLoc(int loc)
{
    // first we want to determine whether or not the piece is one of the player's own
    if (tiles[loc]->state == Tile::REDPIECE)
    {
        // once we determine that the tile is one of the player's own we want
        // to check whether the start location has been set yet.
        if (startSelected)
        {
            // if the start location has already been selected, then we want to clear everything including
            // the list of valid moves, and unhighlight the valid spaces as well as the original start location.
            // last we want to change start selected to false.
            unhighlight();
            clearMoves();
            startSelected = false;
            // last we want to unset the startLoc.
            // however we cannot simply set it to zero since that is a valid location.
        }
        // after unsetting the previous startLocations details we can move on
        // with actions that apply regardless of whether or not the start loc had been set already
        //  ths includes: set startLoc = loc
        //                determine moves
        //                highlight valid spaces and start location
        //                set startSelected to true
        startLoc = loc;
        determineMoves(loc);
        highlight();
        startSelected = true;
        return true;
    }
    return false;
}
void Board::highlight()
{
    for (int i = 0; i < moves.size(); i++)
    {

        QPalette pal = tiles[moves[i]]->palette();
        pal.setColor(QPalette::Button, Qt::green);
        tiles[moves[i]]->setPalette(pal);
    }
    QPalette palette = tiles[startLoc]->palette();
    palette.setColor(QPalette::Button, Qt::yellow);
    tiles[startLoc]->setPalette(palette);
    tiles[startLoc]->setIconSize(QSize(30,30));
}

void Board::unhighlight()
{
    for (int i = 0; i < moves.size(); i++)
    {
        QPalette pal = tiles[moves[i]]->palette();
        pal.setColor(QPalette::Button, Qt::darkRed);
        tiles[moves[i]]->setPalette(pal);
    }
    QPalette palette = tiles[startLoc]->palette();
    palette.setColor(QPalette::Button, Qt::darkRed);
    tiles[startLoc]->setPalette(palette);
    tiles[startLoc]->setIconSize(QSize(30,30));
}
bool Board::tileIsEmpty(int loc)
{
    if (tiles[loc]->state == Tile::EMPTY)
    {
        return true;
    }
    return false;
}

bool Board::checkMove(int start, int end)
{
    bool madeMove = false;
    int jumpedTile;
    // check each in succession. If there is a match, we can set the activity enums for the specified tiles.
    if (end == forwardLeft(start) && forwardLeftisValid(start))
    {
        // set start to MOVEDFROM, end to MOVEDTO.
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        madeMove = true;
    }
    else if (end == forwardRight(start) && forwardRightisValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        madeMove = true;
    }
    else if (end == forwardLeftJump(start) && forwardLeftJumpIsValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        jumpedTile = start-(5-((start/4)%2));
        tiles[jumpedTile]->activity = Tile::JUMPED;
        madeMove = true;
    }
    else if (end == forwardRightJump(start) && forwardRightJumpIsValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        jumpedTile = start-(4-((start/4)%2));
        tiles[jumpedTile]->activity = Tile::JUMPED;
        madeMove = true;
    }
    return madeMove;
    
}

void Board::clearMoves()
{
    moves.clear();
    /*for (int i = 0; i < moves.size(); i++)
    {
       moves.removeAt(i);
    }
    */
}

void Board::determineMoves(int loc)
{
    if (forwardLeftisValid(loc))
    {
        moves.push_back(loc-(5-(loc/4)%2));
    }
    if (forwardRightisValid(loc))
    {
        moves.push_back(loc-(4-(loc/4)%2));
    }
    if(forwardLeftJumpIsValid(loc))
    {
        moves.push_back(loc-9);
    }

    if(forwardRightJumpIsValid(loc))
    {
        moves.push_back(loc-7);
    }
    if(backwardLeftisValid(loc))
    {
        moves.push_back(loc+(3+(loc/4)%2));
    }

    if(backwardRightisValid(loc))
    {
        moves.push_back(loc+(4+(loc/4)%2));
    }
    if(backwardLeftJumpisValid(loc))
    {
        moves.push_back(loc+7);
    }
    if(backwardRightJumpisValid(loc))
    {
        moves.push_back(loc+9);
    }

}
void Board::makeMove()
{
    // here we want to go through each tile and check it's activity enum; If it is MOVEDTO || MOVEDFROM
    // we save it and
    int startLoc;
    int endLoc;
    int jumpedLoc;
    bool jumped = false;
    for (int i = 0; i< 32; i++)
    {

        if (tiles[i]->activity == Tile::MOVEDFROM)
        {
            startLoc = i;

        }
        else if (tiles[i]->activity == Tile::MOVEDTO)
        {
            endLoc = i;
        }
        else if (tiles[i]->activity == Tile::JUMPED)
        {
            jumpedLoc = i;
            jumped = true;
        }
    }
    // after this for loop runs, we should have the location of the start, the end, and possibly the jumped.
    // using these we update the board. This involves swapping the states of MOVEDTO & MOVEDFROM.
    tiles[endLoc]->state = tiles[startLoc]->state;
    tiles[startLoc]->state = Tile::EMPTY;
    if (jumped)
    {
        tiles[jumpedLoc]->state = Tile::EMPTY;
        tiles[jumpedLoc]->activity = Tile::NOACTIVITY;
    }
    // the states have been updated so no we need change the icons.
    updateBoard();
    tiles[startLoc]->activity = Tile::NOACTIVITY;
    tiles[endLoc]->activity = Tile::NOACTIVITY;
    // once the icons have been changed we need to remove the highlights, and clear the possible moves
    unhighlight();
    clearMoves();
}
void Board::kingCheck(int loc)
{
    // right now this only applies to the red player for whom a kinging
    // occurs when her piece lands within the locations 0-3
    if (loc> 0 && loc <4)
    {
        // check that piece is not already king
        if (tiles[loc]->state != Tile::REDKING)
        {
            tiles[loc]->setIcon(QIcon("redKing.jpg"));
        }
    }
}
void Board::updateBoard()
{
    for (int i = 0; i < 32; i++)
    {
        if (tiles[i]->state == Tile::EMPTY)
        {
            tiles[i]->setIcon(QIcon());
        }
        else if (tiles[i]->state == Tile::REDPIECE)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/checkersPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
        }
        else if (tiles[i]->state == Tile::REDKING)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/redKing.jpg"));
            tiles[i]->setIconSize(QSize(30,30));
        }
        else if (tiles[i]->state == Tile::BLACKPIECE)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/blackPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
        }
        else if (tiles[i]->state == Tile::BLACKKING)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/blackKing.png"));
            tiles[i]->setIconSize(QSize(30,30));
        }
    }
}

void Board::updatePiece(int loc)
{
    // remove icon from newly empty tiles
    if (tiles[loc]->state == Tile::EMPTY)
    {
        tiles[loc]->setIcon(QIcon());
    }
    else if (tiles[loc]->state == Tile::REDPIECE)
    {
        tiles[loc]->setText("red");
        tiles[loc]->setIcon(QIcon(":/images/icons/checkersPiece.png"));
        tiles[loc]->setIconSize(QSize(30,30));
    }
    else if (tiles[loc]->state == Tile::REDKING)
    {
        tiles[loc]->setIcon(QIcon(":/images/icons/redKing.jpg"));
        tiles[loc]->setIconSize(QSize(30,30));
    }
    else if (tiles[loc]->state == Tile::BLACKPIECE)
    {
        tiles[loc]->setIcon(QIcon(":/images/icons/blackPiece.png"));
        tiles[loc]->setIconSize(QSize(30,30));
    }
    else if (tiles[loc]->state == Tile::BLACKKING)
    {
        tiles[loc]->setIcon(QIcon(":/images/icons/blackKing.png"));
        tiles[loc]->setIconSize(QSize(30,30));
    }
}

int Board::forwardLeft(int loc)
{
    // returns the location of the tile that would result from such a move. We use this to check
    int moveLoc;
    if (loc % 8 != 0 && loc > 3)
    {
        moveLoc = loc - (5 - ((loc/4)%2));
        return moveLoc;
    }
    return -1;
}
int Board::forwardRight(int loc)
{
    int moveLoc;
    if ((loc+1) + 1 % 8 != 0 && loc > 3)
    {
        moveLoc = loc - (4-((loc/4)%2));
        return moveLoc;
    }
    return -1;
}
int Board::forwardLeftJump(int loc)
{
    int moveLoc;
    if(loc%4 != 0 && loc > 7)
    {
        moveLoc = loc-9;
        return moveLoc;
    }
    return -1;
}
int Board::forwardRightJump(int loc)
{
    int moveLoc;
    if ((loc+1)%4 != 0 && loc > 7)
    {
        moveLoc = loc - 7;
        return moveLoc;
    }
    return -1;
}

bool Board::forwardLeftisValid(int start)
{
    // check that start tile is not on left or far border

    if (start % 8 != 0 && start > 3)
    {
        // check that forward left tile is open
        if (tiles[start - (5 - ((start/4)%2))]->state == Tile::EMPTY)
        {
            return true;
        }
        return false;
    }
    return false;
}
bool Board::forwardRightisValid(int start)
{
    if ((start+1) % 8 != 0 && start > 3)
    {
        // check that forward right tile is open
        if (tiles[start - (4-((start/4)%2))]->state == Tile::EMPTY)
        {
            return true;
        }
        return false;
    }
    return false;
}
bool Board::forwardLeftJumpIsValid(int start)
{
    // check that start location is not on two leftmost borders nor two furthest
    if (start%4 != 0 && start > 7)
    {
        // check that forward left tile is occupied by enemy piece (the piece to be jumped)
        if ((tiles[start-9]->state==Tile::EMPTY ) && (tiles[start-(5 - ((start/4)%2))]->state==Tile::BLACKPIECE || tiles[start-(5 - ((start/4)%2))]->state==Tile::BLACKKING))
        {
                return true;
        }
        return false;
    }
    return false;
}
bool Board::forwardRightJumpIsValid(int start)
{
    if ((start+1)%4 != 0 && start > 7)
        {
            if ((tiles[start-7]->state == Tile::EMPTY) && (tiles[start-(4-((start/4)%2))]->state == Tile::BLACKPIECE || tiles[start-(4-((start/4)%2))]->state == Tile::BLACKKING))
            {
                return true;
            }
            return false;
        }
        return false;
}
bool Board::backwardLeftisValid(int start)
{
    if (start % 8 != 0 && start < 28 && tiles[start]->state == Tile::REDKING)
    {
        if (tiles[start + (3 + ((start/4)%2))]->state == Tile::EMPTY)
        {
            return true;
        }
        return false;
    }
    return false;
}
bool Board::backwardRightisValid(int start)
{
    if ((start+1) % 8 != 0 && start < 28 && tiles[start]->state == Tile::REDKING)
    {
        // check that forward right tile is open
        if (tiles[start + (4 + ((start/4)%2))]->state == Tile::EMPTY)
        {
            return true;
        }
        return false;
    }
    return false;
}
bool Board::backwardLeftJumpisValid(int start)
{
    if (start%4 != 0 && start < 24 && tiles[start]->state == Tile::REDKING)
    {
        if ((tiles[start+7]->state==Tile::EMPTY ) && (tiles[start+(3+((start/4)%2))]->state==Tile::BLACKPIECE || tiles[start+(3+((start/4)%2))]->state==Tile::BLACKKING))
        {
                return true;
        }
        return false;
    }
    return false;
}
bool Board::backwardRightJumpisValid(int start)
{
    if ((start+1)%4 != 0 && start < 24 && tiles[start]->state == Tile::REDKING)
        {
            if ((tiles[start+9]->state == Tile::EMPTY) && (tiles[start+(4+((start/4)%2))]->state == Tile::BLACKPIECE || tiles[start+(4+((start/4)%2))]->state == Tile::BLACKKING))
            {
                return true;
            }
            return false;
        }
        return false;
}
