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
#include <QHeaderView>
#include <QCoreApplication>
#include "donebox.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_widget = new QWidget(this);
    m_vlayout = new QVBoxLayout(this);

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
    tableWidget->setColumnWidth(0, 100); // Column 0 width is set to 60 pixels
    tableWidget->setColumnWidth(1, 300); // Column 1 width is set to 300 pixels
    tableWidget->setColumnWidth(2, 100); // Column 2 width is set to 100 pixels
    tableWidget->setColumnWidth(3, 45); // Column 3 width is set to 40 pixels

    m_vlayout->addWidget(tableWidget);
    loadData();

}

void MainWindow::createToolbar()
{
    QString projectPath = QCoreApplication::applicationDirPath();
    projectPath = projectPath.remove(projectPath.split('/').last());

    //creat actions
    QAction* _add = new QAction(QString("Add"), this);
    QAction* _edit = new QAction(QString("Edit"), this);
    QAction* _delete = new QAction(QString("Delete"), this);
    QAction* _save = new QAction(QString("Save"), this);
    QAction* _sortByDate = new QAction(QString("Sort By Date"), this);
    QAction* _sortByName = new QAction(QString("Sort By Name"), this);
    QAction* _sortByDescription = new QAction(QString("Sort By Description"), this);
    QAction* _filter = new QAction(QString("Filter"), this);


    //set icons for Actions
    QIcon addIcon(projectPath + "/MyToDoList/Icons/ADD");
    _add->setIcon(addIcon);
    QIcon editIcon(projectPath + "/MyToDoList/Icons/EDIT");
    _edit->setIcon(editIcon);
    QIcon deleteIcon(projectPath + "/MyToDoList/Icons/DELETE");
    _delete->setIcon(deleteIcon);
    QIcon saveIcon(projectPath + "/MyToDoList/Icons/SAVE");
    _save->setIcon(saveIcon);
    //sort buttons
    QIcon _sortByNameIcon(projectPath + "/MyToDoList/Icons/SORTNAME");
    _sortByName->setIcon(_sortByNameIcon);
    QIcon _sortByDescriptionIcon(projectPath + "/MyToDoList/Icons/SORTDESCRIPTION");
    _sortByDescription->setIcon(_sortByDescriptionIcon);
    QIcon _sortByDateIcon(projectPath + "/MyToDoList/Icons/SORTDATE");
    _sortByDate->setIcon(_sortByDateIcon);
    QIcon filterIcon(projectPath + "/MyToDoList/Icons/Filter");
    _filter->setIcon(filterIcon);

    //add buttons to tool bar
    m_toolBar = new QToolBar(this);
    m_toolBar->addAction(_add);
    m_toolBar->addAction(_edit);
    m_toolBar->addAction(_delete);
    m_toolBar->addAction(_save);
    m_toolBar->addSeparator();
    m_toolBar->addAction(_sortByName);
    m_toolBar->addAction(_sortByDescription);
    m_toolBar->addAction(_sortByDate);
    m_toolBar->addAction(_filter);

    this->addToolBar(m_toolBar);


    //connections tool bar
    QObject::connect(_add, &QAction::triggered, this, &MainWindow::addNewNode);
    QObject::connect(_edit, &QAction::triggered, this, &MainWindow::editNode);
    QObject::connect(_delete, &QAction::triggered, this, &MainWindow::deleteNode);
    QObject::connect(_save, &QAction::triggered, this, &MainWindow::save);
    QObject::connect(_sortByDate, &QAction::triggered, this, &MainWindow::sortByDate);
    QObject::connect(_sortByName, &QAction::triggered, this, &MainWindow::sortByName);
    QObject::connect(_sortByDescription, &QAction::triggered, this, &MainWindow::sortByDescription);
    QObject::connect(_filter, &QAction::triggered, this, &MainWindow::filterByState);

}

void MainWindow::changeCoulumState(const int col)
{
    const int rowCount = tableWidget->rowCount();
    if(m_editFlag){
        for (int row = 0; row < rowCount; ++row) {
            tableWidget->item(row, col)->setFlags(tableWidget->item(row, col)->flags() & ~Qt::ItemIsEditable);
        }
    } else {
        for (int row = 0; row < rowCount; ++row) {
            tableWidget->item(row, col)->setFlags(tableWidget->item(row, col)->flags() | Qt::ItemIsEditable);
        }
    }
}

void MainWindow::loadData()
{
    //reade file
    QString projectPath = QCoreApplication::applicationDirPath();
    projectPath = projectPath.remove(projectPath.split('/').last());
    QString path = projectPath + "/MyToDoList/Resource/table_data.txt";
    QFile file(projectPath + "/MyToDoList/Resource/table_data.txt");

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
            qDebug() << "Can not open file!!";
        }
}

void MainWindow::addDataToNode(QString _name, QString _description, QString _date = QDate::currentDate().toString(), bool _state = false){

    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
    QTableWidgetItem *itemName = new QTableWidgetItem(_name);
    QTableWidgetItem *itemDescription = new QTableWidgetItem(_description);
    QTableWidgetItem *itemDate = new QTableWidgetItem(_date);
    itemDate->setFlags(itemDate->flags() & ~Qt::ItemIsEditable);
    StatusBox *itemState = new StatusBox();

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
    //creat items for new node
    QTableWidgetItem *itemName = new QTableWidgetItem("name");
    QTableWidgetItem *itemDescription = new QTableWidgetItem("description");
    QDate date = QDate::currentDate();//get current date
    QTableWidgetItem *itemDate = new QTableWidgetItem(date.toString());
    StatusBox *itemState = new StatusBox();

    //add items in Table Widget
    tableWidget->setItem(rowCount, 0, itemName);//name
    tableWidget->setItem(rowCount, 1, itemDescription);//description
    tableWidget->setItem(rowCount, 2, itemDate);//date
    tableWidget->setItem(rowCount, 3, itemState);//State

    tableWidget->setCellWidget(rowCount, 3, itemState->getCheckBox());

    // If edit not allowed then new row will be not editable as well
    if(!m_editFlag) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            tableWidget->item(rowCount, col)->setFlags(tableWidget->item(rowCount, col)->flags() & ~Qt::ItemIsEditable);

        }
    }
}

void MainWindow::deleteNode()
{
    //delete current selected node
    int currentRow = tableWidget->currentRow();
    if(currentRow >=0){
        tableWidget->removeRow(currentRow);
        currentRow--;
    }
}

void MainWindow::sortByDate(){
    static bool sortFlag = true;
    if(sortFlag){
        tableWidget->sortItems(2, Qt::AscendingOrder);
    } else {
        tableWidget->sortItems(2, Qt::DescendingOrder);
    }
    sortFlag = !sortFlag;
}

void MainWindow::sortByName(){
    static bool sortFlag = true;
    if(sortFlag){
        tableWidget->sortItems(0, Qt::AscendingOrder);
    } else {
        tableWidget->sortItems(0, Qt::DescendingOrder);
    }
    sortFlag = !sortFlag;
}

void MainWindow::sortByDescription(){
    static bool sortFlag = true;
    if(sortFlag){
        tableWidget->sortItems(1, Qt::AscendingOrder);
    } else {
        tableWidget->sortItems(1, Qt::DescendingOrder);
    }
    sortFlag = !sortFlag;
}



void MainWindow::editNode()
{
    for (int col = 0; col < tableWidget->columnCount(); ++col){
        changeCoulumState(col);
    }
    m_editFlag = !m_editFlag;
}

void MainWindow::save()
{
    QString projectPath = QCoreApplication::applicationDirPath();
    QFile file(projectPath + "/Resource/table_data.txt");

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
                out << reinterpret_cast<StatusBox*>(tableWidget->item(row, 3))->getCheckBox()->isChecked();//write State  // I know that this is bad practice to use reinterpret_cast, but in this case I don't have other choice.
                out << "\n"; // End of row
            }
            file.close();
        } else {
            qDebug() << "Can not open file!!";
        }
}

void MainWindow::filterByState()
{
    static bool filterFlag = false;

    for(int i = 0; i < tableWidget->rowCount(); ++i){
        if(reinterpret_cast<StatusBox*>(tableWidget->item(i, 3))->getCheckBox()->isChecked()){
            tableWidget->setRowHidden(i, filterFlag);
        }
    }
    filterFlag = !filterFlag;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_widget;
    delete m_vlayout;
    delete tableWidget;
    delete m_toolBar;

}

