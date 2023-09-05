#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QDate>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QCalendarWidget>
#include <QDialog>
#include "donebox.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    m_widget = new QWidget(this);
    m_vlayout = new QVBoxLayout(this);
    //m_toolBar = new QToolBar(this);

    setCentralWidget(m_widget);

    m_widget->setLayout(m_vlayout);
    buildCentralWidget();

}

void MainWindow::buildCentralWidget()
{
    creatTable();
    createToolbar();

}

void MainWindow::creatTable()
{    
    tableWidget = new QTableWidget(0, 4, this);
    QStringList headerLabels;
    headerLabels << "Name" << "Description" << "Date of events" << "Status";
    tableWidget->setHorizontalHeaderLabels(headerLabels);
    tableWidget->setColumnWidth(0, 60); // Column 0 width is set to 60 pixels
    tableWidget->setColumnWidth(1, 300); // Column 1 width is set to 300 pixels
    tableWidget->setColumnWidth(2, 100); // Column 2 width is set to 100 pixels
    tableWidget->setColumnWidth(3, 40); // Column 3 width is set to 40 pixels


    m_vlayout->addWidget(tableWidget);
    loadData();

}

void MainWindow::createToolbar()
{
    //creat actions
    QAction* _add = new QAction(QString("Line"), this);
    QAction* _edit = new QAction(QString("Rectangle"), this);
    QAction* _delete = new QAction(QString("Clear"), this);
    QAction* _save = new QAction(QString("Save"), this);
    QAction* _sort = new QAction(QString("Save"), this);

    //set icons for Actions
    QIcon addIcon("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Icons/ADD");
    _add->setIcon(addIcon);
    QIcon editIcon("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Icons/EDIT");
    _edit->setIcon(editIcon);
    QIcon deleteIcon("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Icons/DELETE");
    _delete->setIcon(deleteIcon);
    QIcon saveIcon("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Icons/SAVE");
    _save->setIcon(saveIcon);
    QIcon sortIcon("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Icons/SORT");
    _sort->setIcon(sortIcon);

    m_toolBar = new QToolBar(this);
    m_toolBar->addAction(_add);
    m_toolBar->addAction(_edit);
    m_toolBar->addAction(_delete);
    m_toolBar->addAction(_save);
    m_toolBar->addAction(_sort);
    this->addToolBar(m_toolBar);

    //connections tool bar
    QObject::connect(_add, &QAction::triggered, this, &MainWindow::addNewNode);
    QObject::connect(_edit, &QAction::triggered, this, &MainWindow::changeTableState);
    QObject::connect(_delete, &QAction::triggered, this, &MainWindow::deleteNode);
    QObject::connect(_save, &QAction::triggered, this, &MainWindow::save);
    QObject::connect(_sort, &QAction::triggered, this, &MainWindow::sortTable);
}

void MainWindow::changeTableState()
{
    int rowCount = tableWidget->rowCount();   
    for (int row = 0; row < rowCount; ++row) {
        tableWidget->item(row, 2)->setFlags(tableWidget->item(row, 2)->flags() & ~Qt::ItemIsEditable);
    }

}

void MainWindow::loadData()
{
    QFile file("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Resource/table_data.txt");

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            while (!in.atEnd()){
                QString line = in.readLine();
                QStringList segment = line.split("::");
                if(segment.count() == 4){
                    QString name        = segment[0];
                    QString description = segment[1];
                    QString date        = segment[2];
                    bool state          = segment[3].toInt();
                    addDataToNode(name, description, date, state);
                }

            }

            file.close();
        } else {
            // Handle file open error here
        }
}

void MainWindow::addDataToNode(QString _name, QString _description, QString _date = QDate::currentDate().toString(), bool _state = false){

    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
    QTableWidgetItem *itemName = new QTableWidgetItem(_name);
    QTableWidgetItem *itemDescription = new QTableWidgetItem(_description);
    QTableWidgetItem *itemDate = new QTableWidgetItem(_date);
    itemDate->setFlags(itemDate->flags() & ~Qt::ItemIsEditable);
    DoneBox *itemState = new DoneBox();

    tableWidget->setItem(rowCount, 0, itemName);//name
    tableWidget->setItem(rowCount, 1, itemDescription);//description
    tableWidget->setItem(rowCount, 2, itemDate);//ata
    tableWidget->setItem(rowCount, 3, itemState);//State


    if(_state){
        itemState->getCheckBox()->setCheckState(Qt::Checked);
    }
    tableWidget->setCellWidget(rowCount, 3, itemState->getCheckBox());
}

void MainWindow::addNewNode(){

    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
    QTableWidgetItem *itemName = new QTableWidgetItem("name");
    QTableWidgetItem *itemDescription = new QTableWidgetItem("description");
    QDate date = QDate::currentDate();//get current date
    QTableWidgetItem *itemDate = new QTableWidgetItem(date.toString());
    itemDate->setFlags(itemDate->flags() & ~Qt::ItemIsEditable);
    DoneBox *itemState = new DoneBox();

    tableWidget->setItem(rowCount, 0, itemName);//name
    tableWidget->setItem(rowCount, 1, itemDescription);//description
    tableWidget->setItem(rowCount, 2, itemDate);//date
    tableWidget->setItem(rowCount, 3, itemState);//State

    tableWidget->setCellWidget(rowCount, 3, itemState->getCheckBox());
}

void MainWindow::deleteNode()
{
    int currentRow = tableWidget->currentRow();
    if(currentRow >=0){
        tableWidget->removeRow(currentRow);
        currentRow--;
    }
}

void MainWindow::sortTable(){
    static bool sortFlag = true;
    if(sortFlag){
        tableWidget->sortItems(2, Qt::AscendingOrder);
        sortFlag = false;
    } else {
        tableWidget->sortItems(2, Qt::DescendingOrder);
        sortFlag = true;
    }



}



void MainWindow::editNode()
{
    int currentRow = tableWidget->currentRow();



}

void MainWindow::save()
{
    QFile file("C:/Users/home_/Desktop/Edgar/To Do List/MyToDoList/Resource/table_data.txt");

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // Loop through the table and write data to the file
            for (int row = 0; row < tableWidget->rowCount(); ++row) {

                QString separator = "::";
                out << tableWidget->item(row, 0)->text();//write Name
                out << separator;
                out << tableWidget->item(row, 1)->text();//write Description
                out << separator;
                out << tableWidget->item(row, 2)->text();//write Date
                out << separator;
                out << reinterpret_cast<DoneBox*>(tableWidget->item(row, 3))->getCheckBox()->isChecked();//write State
                out << "\n"; // End of row
            }
            file.close();
        } else {
            // Handle file open error here
        }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_widget;
}

