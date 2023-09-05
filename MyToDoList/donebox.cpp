#include "donebox.h"
#include <QCheckBox>
#include <QVBoxLayout>

DoneBox::DoneBox() : QTableWidgetItem()
{
   checkBox = new QCheckBox();
   //QVBoxLayout *layout = new QVBoxLayout();
   //layout->addWidget(checkBox);
   //layout->setAlignment(Qt::AlignCenter);
   //checkBox->setAl
}

QCheckBox *DoneBox::getCheckBox(){
    return this->checkBox;
}
