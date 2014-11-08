#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mngrconnection.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    MngrConnection db;
    QSqlTableModel _tableModelAll;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_actionExit_triggered();

    void on_actionShowFind_triggered(bool checked);

    void on_actionStaffManagement_triggered();

    void on_actionStorageManagement_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
