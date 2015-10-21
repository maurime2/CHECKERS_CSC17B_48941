#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPixmap>
#include <QApplication>
#include <QString>


#include <QDebug>
#include <QtSql>

#include <QPainter>
#include <QImage>
#include <QHBoxLayout>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int size=8;
    QWidget *board= new QWidget;
    QGridLayout *mainLayout = new QGridLayout;
    QPixmap whiteImage(":/images/whiteSquare.png");
    QPixmap greenImage(":/images/greenSquare.png");

    // Fill the QLabels
    for(int i = 0; i<size; i++){
        for(int j=0; j < size; j++){
            QLabel *label = new QLabel;
            if(i%2==0&&j%2==1){
                label->setPixmap(greenImage);
                mainLayout->addWidget(label,i,j);
            }
            else if(i%2==1&&j%2==0){
                label->setPixmap(greenImage);
                mainLayout->addWidget(label,i,j);
            }
            else{
                label->setPixmap(whiteImage);
                mainLayout->addWidget(label,i,j);
            }
        }

    }
    //Set a fixed size for the layour
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    QString myString(":/images/whiteSquare.png");
    QString myString2(":/images/redPiece.png");
    QImage mySquare;
    mySquare.load(myString);
    QImage myCircle;
    myCircle.load(myString2);
    QWidget *imageWidget = new QWidget;
    QHBoxLayout *sampleLayout = new QHBoxLayout;
    QPainter painter(&mySquare);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0,0,myCircle);


    imageWidget->setLayout(sampleLayout);
    imageWidget->show();


    board->setLayout(mainLayout);
    board->show();
    //qDebug() << QSqlDatabase::drivers;

    return a.exec();
}
