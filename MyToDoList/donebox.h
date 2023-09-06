#ifndef DONEBOX_H
#define DONEBOX_H
#include <QTableWidgetItem>
#include <QCheckBox>



class StatusBox : public QTableWidgetItem
{
public:

    StatusBox();
    QCheckBox* getCheckBox();
    ~StatusBox();

private:
    QCheckBox *checkBox = nullptr;
};

#endif // DONEBOX_H
