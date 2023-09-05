#ifndef DONEBOX_H
#define DONEBOX_H
#include <QTableWidgetItem>
#include <QCheckBox>

class DoneBox : public QTableWidgetItem
{

public:
    DoneBox();

    QCheckBox* getCheckBox();


private:
    QCheckBox *checkBox = nullptr;


};

#endif // DONEBOX_H
