#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void buildCentralWidget();
    void creatTable();
    void createToolbar();    
    void loadData();
    void addDataToNode(QString, QString, QString, bool);


    ~MainWindow();
public slots:
    void addNewNode();
    void deleteNode();
    void sortTable();
    void editNode();
    void save();
    void changeTableState();

private:
    Ui::MainWindow *ui;
    QWidget *m_widget = nullptr;
    QVBoxLayout *m_vlayout = nullptr;
    QTableWidget *tableWidget = nullptr;
    QToolBar* m_toolBar = nullptr;
    QAction* m_AddAction = nullptr;
    QAction* m_ClearAction = nullptr;
    QAction* m_ExitAction = nullptr;

};
#endif // MAINWINDOW_H
