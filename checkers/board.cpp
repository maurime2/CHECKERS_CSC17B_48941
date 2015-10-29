

#include "board.h"

Board::Board(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent,f){
    // Set the default background images
    lightSquare = new QString(":/images/whiteSquare.png");
    darkSquare = new QString(":/images/greenSquare.png");

    //playableSquares = new QMap;
    //nonPlayableSquares = new QMap;
    // For layout the game board
    QGridLayout *mainLayout = new QGridLayout;

    // Start the squares at 1
    int count = 1;
    int countNonPlay=1;
    // Set the size of the board to default size
    int size = DEFAULTSIZE;

    // Fill the squares with default images and add them to the board
    for(int i = 0; i<size; i++){
        for(int j=0; j < size; j++){
            // Add and determine whether square will be playable
            if(i%2==0&&j%2==1){
                BoardSquare *square = new BoardSquare(true,*darkSquare, parent);
                mainLayout->addWidget(square,i,j);
                playableSquares.insert(count,square);
                count++;
            }
            else if(i%2==1&&j%2==0){
                BoardSquare *square = new BoardSquare(true,*darkSquare, parent);
                mainLayout->addWidget(square,i,j);
                playableSquares.insert(count,square);
                count++;
            }
            else{
                // Create a non-playable square
                BoardSquare *square = new BoardSquare(true, *lightSquare, parent);
                mainLayout->addWidget(square,i,j);
                nonPlayableSquares.insert(countNonPlay,square);
                countNonPlay++;
            }
        }
    }
    // Set the layout to a fixed size so it cannot be resized
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    // Set the horizontal and vertical spacing between the squares
    mainLayout->setHorizontalSpacing(0);
    mainLayout->setVerticalSpacing(0);

    // Set the layout for the board
    this->setLayout(mainLayout);
}

// Destructor
Board::~Board(){

    // Create iterators to go through the Qmaps
    QMap<int,BoardSquare*>::iterator i=playableSquares.begin();
    QMap<int,BoardSquare*>::iterator j=nonPlayableSquares.begin();

	// delete the playable and non playable squares
    while(i!=playableSquares.end()){
        // Delete the BoardSquare value
        delete i.value();
        // Now delete the key
        i=playableSquares.erase(i);
    }
    while(j!=nonPlayableSquares.end()){
        // Delete the BoardSquare value
        delete j.value();
        // Now delete the key
        j=nonPlayableSquares.erase(j);
    }
	// Now delete the Qmaps
    delete playableSquares;
    delete nonPlayableSquares;
}
