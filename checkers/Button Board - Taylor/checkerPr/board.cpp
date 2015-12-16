#include "board.h"
#include <QtGlobal>
#include <QTime>

Board::Board(QWidget *parent) : QWidget(parent)
{
    QString s;
    for (int i = 0; i < 32; i++)
    {

        // create Tile with board parent. Add tile to vector
        tiles.push_back(new Tile(this));
        // set tile location to index
        tiles[i]->location = i;
        // set tile activity enum to NoActivity
        tiles[i]->activity = Tile::NOACTIVITY;

        // set the black piece icons. set tile state to blackpiece
        if (i < 12)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/blackPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::BLACKPIECE;
        }


        // set red pieces.
        else if (i>19)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/checkersPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::REDPIECE;
        }
        // set black piece to test jumping
        // set state of all empty tiles to empty

        else
        {
            tiles[i]->state = Tile::EMPTY;
        }

    }

    QString n1;
    QString n2;
    QString n;
    for (int j = 0; j < 32; j++)
    {
        switch (j/4)
        {
        case 0: n1 = "A";
            break;
        case 1: n1 = "B";
            break;
        case 2: n1 = "C";
            break;
        case 3: n1 = "D";
            break;
        case 4: n1 = "E";
            break;
        case 5: n1 = "F";
            break;
        case 6: n1 = "G";
            break;
        case 7: n1 = "H";
            break;
        }
        switch ((j - ((j/4)*4))*2 + (j/4)%2)
        {
        case 0: n2 = "1";
            break;
        case 1: n2 = "2";
            break;
        case 2: n2 = "3";
            break;
        case 3: n2 = "4";
            break;
        case 4: n2 = "5";
            break;
        case 5: n2 = "6";
            break;
        case 6: n2 = "7";
            break;
        case 7: n2 = "8";
            break;
        }
        n = n1+n2;
        moveNames.push_back(n);
    }
    // set startSelected to false. indicates that no start tile has been clicked
    startSelected = false;
    playersTurn = true;
    playerWins = false;
    jumpOcc = false;
    computersMove = false;
    // create game over dialog which is shown when game ends
    over = new GameOverDialog(this);
    // at this point nothing happens until the user clicks
    QObject::connect(this, SIGNAL(updateLastMoves(QString,QString)), parent, SLOT(updateLastMove(QString,QString)));
    QObject::connect(this, SIGNAL(endScreen(bool)), over, SLOT(show()));
    QObject::connect(this, SIGNAL(endScreen(bool)), over, SLOT(winOrLoss(bool)));
    QObject::connect(this, SIGNAL(toClose()), parent, SLOT(close()));
    QObject::connect(this,SIGNAL(returnToMenu()),parent,SLOT(showMenu()));

}

void Board::handleClick(int loc)
{
    playersTurn = true;
    if (setStartLoc(loc))
    {
        // if true then, one of the player's own pieces has been selected and should have been set
        // if not true then the selected tile is either empty or an enemy's. We check for this and act accordingly in a following
        // else statement
    }
    else if (startSelected || jumpTurn)
    {
        // tile selected is either empty or an enemy's piece.
        // check whether or not the tile is an enemy's piece. If it is do nothing.
        // If the tile is empty, check whether or not it is a valid move. If it is a valid move, make move,
        // check for king, check for win, update the pieces, and to end turn delete possible moves, undo highlights
        // set start selected to false, unset startLoc and switch to other player's turn.
        if (tileIsEmpty(loc))
        {
            // checkMove determines whether the move is valid
            // and if it is, changes the activity enums of each relevant
            // tile (MOVEDFROM,MOVEDTO...) and returns true, indicating
            // that a move can be made and will be. makeMove() then
            // goes through the board and finds the tiles with
            // MOVEDFROM etc. and
            if(checkMove(startLoc, loc))
            {
                lastMovePlayer = moveNames[startLoc]+ " to "+moveNames[loc];
                // here we need to send this string to mainWindow so that the enemy label
                // may be updated with last move.
                makeMove();
                if (checkForWin())
                {
                    // if win is found set player wins to true which precludes any
                    // more turns being taken and ends the game
                    playerWins = true;
                    gameOver(playerWins);
                }
                else
                {
                    if (checkForKing(loc)) updateBoard();
                }
                startSelected = false;
                playersTurn = false;
                // after making move we wish to start
                // to the AI's turn. To make it's move
                // we find all of the available move locations
                // for each piece and perhaps after checking whether
                // any of these moves will result in a jump
                // or a kinging, we pick one at random
                // make the move, update the board, check for a win
                // and if no win, switch back to the players turn

            }
        }
        else
        {
            // tile selected is an enemy piece and startLoc should remain the same without anything happening
        }
    }
    // at the end of this loop we check if playerWins is true and if it is we show splash screen,
    // save game, end game etc.
    // then we check if jumpTurn is true. if it is then skip changing turns. if not
    // continue on to the computers turn
    if (!jumpTurn && !playersTurn)
    {
       computerTurn();
    }
}
bool Board::checkForWin()
{
    int i = 0;
    while (i < 32)
    {
        if (tiles[i]->state == Tile::BLACKPIECE || tiles[i]->state == Tile::BLACKKING)
        {
            return false;
        }
        i++;
    }
    return true;
}

bool Board::checkForLoss()
{
    bool loss = true;
    for (int i = 0; i < 32; i++)
    {
        if (tiles[i]->state == Tile::REDPIECE || tiles[i]->state == Tile::REDKING)
        {
            loss = false;
        }
    }
    return loss;
}

bool Board::checkForKing(int loc)
{
    if (loc>= 0 && loc < 4 && !(computersMove))
    {
        // check that piece is not already king
        if (tiles[loc]->state != Tile::REDKING)
        {
            // update piece.
            //tiles[loc]->setIcon(QIcon("blackKing.png"));
            tiles[loc]->state = Tile::REDKING;
            return true;
        }
    }
    else if (loc >= 28 && loc < 32 && computersMove)
    {
        if (tiles[loc]->state != Tile::BLACKKING)
        {
            // update piece.
            //tiles[loc]->setIcon(QIcon("blackKing.png"));
            tiles[loc]->state = Tile::BLACKKING;
            return true;
        }
    }
    return false;
}

bool Board::setStartLoc(int loc)
{
    if (jumpTurn)
    {
        return false;
    }
    if (tiles[loc]->state == Tile::REDPIECE || tiles[loc]->state == Tile::REDKING)
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
        //  with actions that apply regardless of whether or not the start loc had been set already
        //  ths includes: set startLoc = loc
        //                determine moves
        //                highlight valid spaces and start location
        //                set startSelected to true
        startLoc = loc;
        determineMoves(loc);
        /*
        if (!determineMoves(loc))
        {
            if (computersMove)
            {
                playerWins = true;
            }
            gameOver(playerWins);
        }
        */
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
    else if (end == backwardLeft(start) && backwardLeftisValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        madeMove = true;
    }
    else if (end == backwardRight(start) && backwardRightisValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        madeMove = true;
    }
    else if (end == backwardLeftJump(start) && backwardLeftJumpisValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        jumpedTile = start+(3+((start/4))%2);
        tiles[jumpedTile]->activity = Tile::JUMPED;
        madeMove = true;
    }
    else if (end == backwardRightJump(start) && backwardRightJumpisValid(start))
    {
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        jumpedTile = start+(4+((start/4)%2));
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

// fills the moves list with the location/index
// of each valid move given the start location
// of loc
bool Board::determineMoves(int loc)
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
    if (moves.size() >=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Board::makeMove()
{
    // here we want to go through each tile and check it's activity enum; If it is MOVEDTO || MOVEDFROM
    // we save it and
    jumpOcc = false;
    jumpTurn = false;
    int startLoc;
    int endLoc;
    int jumpedLoc,jumpLanding;
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
        jumpOcc = true;
        jumpLanding = endLoc;
     }
    // the states have been updated so no we need change the icons.
    updateBoard();
    tiles[startLoc]->activity = Tile::NOACTIVITY;
    tiles[endLoc]->activity = Tile::NOACTIVITY;
    // once the icons have been changed we need to remove the highlights, and clear the possible moves
    unhighlight();
    clearMoves();
    if (jumpOcc)
    {
        if (checkForJump(jumpLanding))
        {
             jumpTurn = true;
             highlight();
        }

    }
}
bool Board::checkForJump(int loc)
{
    bool foundJump = false;
    if (forwardLeftJumpIsValid(loc))
    {
       foundJump = true;
       moves.push_back(loc-9);
    }
    if (forwardRightJumpIsValid(loc))
    {
        foundJump = true;
        moves.push_back(loc-7);
    }
    if (backwardLeftJumpisValid(loc) && tiles[loc]->state == Tile::REDKING)
    {
        foundJump = true;
        moves.push_back(loc+7);
    }
    if (backwardRightJumpisValid(loc) && tiles[loc]->state == Tile::REDKING)
    {
        foundJump = true;
        moves.push_back(loc+9);
    }
    if (foundJump) startLoc = loc;
    return foundJump;
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
            tiles[i]->setIcon(QIcon(":/images/icons/King.png"));
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
int Board::backwardLeft(int loc)
{
    int moveLoc;
    if (loc % 8 != 0 && loc < 28)
    {
        moveLoc = loc + (3 + ((loc/4)%2));
        return moveLoc;
    }
    return -1;
}
int Board::backwardRight(int loc)
{
    int moveLoc;
    if ((loc+1) % 8 != 0 && loc < 28)
    {
        moveLoc = loc + (4 + ((loc/4)%2));
        return moveLoc;
    }
    return -1;
}
int Board::backwardLeftJump(int loc)
{
    int moveLoc;
    if (loc%4 != 0 && loc < 24)
    {
        moveLoc = loc+7;
        return moveLoc;
    }
    return -1;
}
int Board::backwardRightJump(int loc)
{
    int moveLoc;
    if ((loc+1)%4 != 0 && loc < 24)
    {
        moveLoc = loc + 9;
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
        if (!computersMove)
        {
            // check that forward left tile is occupied by enemy piece (the piece to be jumped)
            if ((tiles[start-9]->state==Tile::EMPTY ) && (tiles[start-(5 - ((start/4)%2))]->state==Tile::BLACKPIECE || tiles[start-(5 - ((start/4)%2))]->state==Tile::BLACKKING))
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((tiles[start-9]->state==Tile::EMPTY ) && (tiles[start-(5 - ((start/4)%2))]->state==Tile::REDPIECE || tiles[start-(5 - ((start/4)%2))]->state==Tile::REDKING))
            {
                return true;
            }
            return false;
        }
    }
    return false;
}
bool Board::forwardRightJumpIsValid(int start)
{
    if ((start+1)%4 != 0 && start > 7)
    {
        if (!computersMove)
        {
            if ((tiles[start-7]->state == Tile::EMPTY) && (tiles[start-(4-((start/4)%2))]->state == Tile::BLACKPIECE || tiles[start-(4-((start/4)%2))]->state == Tile::BLACKKING))
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((tiles[start-7]->state == Tile::EMPTY) && (tiles[start-(4-((start/4)%2))]->state == Tile::REDPIECE || tiles[start-(4-((start/4)%2))]->state == Tile::REDKING))
            {
                return true;
            }
            return false;
        }
    }
        return false;
}
bool Board::backwardLeftisValid(int start)
{
    if (start % 8 != 0 && start < 28 && (tiles[start]->state == Tile::REDKING || computersMove))
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
    if ((start+1) % 8 != 0 && start < 28 && (tiles[start]->state == Tile::REDKING|| computersMove))
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
    if (!computersMove)
    {
        if (start%4 != 0 && start < 24 && (tiles[start]->state == Tile::REDKING|| computersMove))
        {
            if ((tiles[start+7]->state==Tile::EMPTY ) && (tiles[start+(3+((start/4)%2))]->state==Tile::BLACKPIECE || tiles[start+(3+((start/4)%2))]->state==Tile::BLACKKING))
            {
                    return true;
            }
            return false;
        }
    }
    else
    {
        if (start%4 != 0 && start < 24 && (tiles[start]->state == Tile::REDKING|| computersMove))
        {
            if ((tiles[start+7]->state==Tile::EMPTY ) && (tiles[start+(3+((start/4)%2))]->state==Tile::REDPIECE || tiles[start+(3+((start/4)%2))]->state==Tile::REDKING))
            {
                    return true;
            }
            return false;
        }
    }

    return false;
}
bool Board::backwardRightJumpisValid(int start)
{
    if ((start+1)%4 != 0 && start < 24 && (tiles[start]->state == Tile::REDKING || computersMove))
        {
        if (!computersMove)
        {
            if ((tiles[start+9]->state == Tile::EMPTY) && (tiles[start+(4+((start/4)%2))]->state == Tile::BLACKPIECE || tiles[start+(4+((start/4)%2))]->state == Tile::BLACKKING))
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((tiles[start+9]->state == Tile::EMPTY) && (tiles[start+(4+((start/4)%2))]->state == Tile::REDPIECE || tiles[start+(4+((start/4)%2))]->state == Tile::REDKING))
            {
                return true;
            }
            return false;
        }
    }
        return false;
}

void Board::computerTurn()
{
    bool madeMove = false;
    computersMove = true;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    QList<int> shuffledTiles;
    for (int i = 0; i < tiles.size();i++)
    {
        shuffledTiles.insert(qrand()%32,i);
    }
    // first we check for valid moves. This means for each piece we must find every possible move
    int i = 0;
    while (!(madeMove) && i < 32)
    {
        // shuffledTiles.insert();
        // generate set of integers randomly ordered from 0 to 32.
        // then go through that set and once we find a move, make it.
        if (tiles[shuffledTiles[i]]->state == Tile::BLACKPIECE || tiles[shuffledTiles[i]]->state == Tile::BLACKKING)
        {
            madeMove = determineComputerMoves(shuffledTiles[i]);
        }
        i++;
    }
    computersMove = false;
    if (playerLoses)
    {
        playerWins = false;
        gameOver(playerWins);
    }
}
bool Board::determineComputerMoves(int i)
{
    int start = i;
    int end,jumpedTile;
    bool found = false, jump = false;
    if(backwardLeftJumpisValid(i))
    {
        end = i + 7;
        jumpedTile = start+(3+((start/4))%2);
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[jumpedTile]->activity = Tile::JUMPED;
        tiles[end]->activity = Tile::MOVEDTO;
        found = true;
        jump = true;
    }
    else if(backwardRightJumpisValid(i))
    {
        end = i+9;
        jumpedTile = start+(4+((start/4))%2);
        tiles[jumpedTile]->activity = Tile::JUMPED;
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        found = true;
        jump = true;
    }
    else if(forwardLeftJumpIsValid(i)&& tiles[i]->state == Tile::BLACKKING)
    {
        end = i -9;
        jumpedTile = start-(5-((start/4)%2));
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        tiles[jumpedTile]->activity = Tile::JUMPED;
        found = true;
        jump = true;
    }
    else if(forwardRightJumpIsValid(i)&& tiles[i]->state == Tile::BLACKKING)
    {
        // then we perform backward left jump
        end = i-7;
        jumpedTile = start-(4-((start/4)%2));

        tiles[jumpedTile]->activity = Tile::JUMPED;
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;

        found = true;
        jump = true;
    }
    // if no success on jumps go to the other moves
    else if (forwardLeftisValid(i)&& tiles[i]->state == Tile::BLACKKING)
    {
        end = i-(5-(i/4)%2);
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        found = true;
    }
    else if (forwardRightisValid(i) && tiles[i]->state == Tile::BLACKKING)
    {
        end = i-(4-(i/4)%2);
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        found = true;
    }

    else if(backwardLeftisValid(i))
    {
        // then perform forward right
        end = i+(3+(i/4)%2);
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        found = true;
    }

    else if(backwardRightisValid(i))
    {
        // perform forward left
        end = i+(4+(i/4)%2);
        tiles[start]->activity = Tile::MOVEDFROM;
        tiles[end]->activity = Tile::MOVEDTO;
        found = true;
    }
    if (found)
    {
        tiles[end]->state = tiles[start]->state;
        tiles[start]->state = Tile::EMPTY;
        if (jump)
        {
            tiles[jumpedTile]->state = Tile::EMPTY;
            tiles[jumpedTile]->activity = Tile::NOACTIVITY;
            playerLoses = checkForLoss();
        }
        updateBoard();
        tiles[start]->activity = Tile::NOACTIVITY;
        tiles[end]->activity = Tile::NOACTIVITY;
        if (checkForKing(end)) {updateBoard();}
        lastMoveEnemy = moveNames[start] + " to " + moveNames[end];
        return true;
    }
   return false;
}



void Board::em()
{
    emit updateLastMoves(lastMovePlayer,lastMoveEnemy);
}

void Board::resetBoard()
{
    playerWins = false;
    playerLoses = false;
    startSelected = false;
    lastMoveEnemy = " ";
    lastMovePlayer = " ";
    emit updateLastMoves(lastMoveEnemy,lastMovePlayer);
    for (int i = 0; i < 32; i ++)
    {
        QPalette pal = tiles[i]->palette();
        pal.setColor(QPalette::Button, Qt::darkRed);
        tiles[i]->setPalette(pal);

        if (i < 12)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/blackPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::BLACKPIECE;
        }

        // set red pieces.

        else if (i>19)
        {
            tiles[i]->setIcon(QIcon(":/images/icons/checkersPiece.png"));
            tiles[i]->setIconSize(QSize(30,30));
            tiles[i]->state = Tile::REDPIECE;
        }

        else
        {
            tiles[i]->setIcon(QIcon());
            tiles[i]->state = Tile::EMPTY;
        }
    }
}

void Board::gameOver(bool playerWins)
{
    emit endScreen(playerWins);
    //over->show();
}

void Board::backToMenu()
{
    emit returnToMenu();
}
void Board::leave()
{
    emit toClose();
}
