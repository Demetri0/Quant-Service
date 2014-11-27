#include "mainwindow.h"
#include "mngrconnection.h"
#include "mngrquerys.h"
#include "ui_mainwindow.h"
#include "dialogs/add.h"
#include "dialogs/staff.h"
#include "dialogs/storage.h"

#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db.open();
    db.transaction();
        if ( MngrQuerys::createTables() == false ){
            qCritical() << "Database is can not created.";
            db.rollback();
        }
    db.commit();

    ui->setupUi(this);
    ui->LineEdit_Search->setVisible(false);

    _tableModelAll.setTable( MngrQuerys::getTableName(Tables::booking) );
    _tableModelAll.select();
    ui->TableView_All->setModel( &_tableModelAll );
    ui->TableView_All->setColumnHidden(1,1);

    QSettings settings;

    this->restoreGeometry( settings.value("MainWindow/Geometry").toByteArray() );
    this->restoreState( settings.value("MainWindow/State").toByteArray() );
}

MainWindow::~MainWindow()
{
    db.close();
    QSettings settings;

    settings.setValue("MainWindow/Geometry", this->saveGeometry() );
    settings.setValue("MainWindow/State", this->saveState() );

    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{
    DialogAdd *add = new DialogAdd(this);
    add->exec();
    _tableModelAll.select();
}

void MainWindow::on_actionExit_triggered()
{
    qApp ->quit();
}

void MainWindow::on_actionShowFind_triggered(bool checked)
{
    ui->LineEdit_Search->setVisible(checked);
}

void MainWindow::on_actionStaffManagement_triggered()
{
    Staff dlg;
    dlg.setModal(true);
    dlg.exec();
}

void MainWindow::on_actionStorageManagement_triggered()
{
    Storage dlg;
    dlg.setModal(true);
    dlg.exec();
}
