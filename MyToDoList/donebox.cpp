#include "donebox.h"
#include <QCheckBox>
#include <QVBoxLayout>

StatusBox::StatusBox() : QTableWidgetItem()
{
   checkBox = new QCheckBox();
   //QVBoxLayout *layout = new QVBoxLayout();
   //layout->addWidget(checkBox);
   //layout->setAlignment(Qt::AlignCenter);
   //checkBox->setAl
}

QCheckBox *StatusBox::getCheckBox(){
    return this->checkBox;
}

StatusBox::~StatusBox()
{
    delete checkBox;
}
