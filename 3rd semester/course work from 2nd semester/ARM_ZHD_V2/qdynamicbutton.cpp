#include "qdynamicbutton.h"

QdynamicButton::QdynamicButton(QWidget *parent) :
    QPushButton(parent)
{

}

QdynamicButton::~QdynamicButton()
{

}

int QdynamicButton::getID()
{
    return buttonID;
}

void QdynamicButton::setID(int id)
{
    buttonID = id;
}



