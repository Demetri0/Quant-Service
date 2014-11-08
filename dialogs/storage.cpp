#include "storage.h"
#include "ui_storage.h"

Storage::Storage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Storage)
{
    ui->setupUi(this);

    _storageModel = new QSqlQueryModel(this);

    QString sql("SELECT rowid, Title, Address FROM %1 WHERE Deleded == 0");
    sql = sql.arg( MngrQuerys::getTableName(Tables::storage) );

    _storageModel->setQuery( sql );
    ui->tableView->setModel( _storageModel );
}

Storage::~Storage()
{
    delete ui;
}

void Storage::on_tableView_clicked(const QModelIndex &index)
{
    _currentId = ui->tableView->selectionModel()->selectedIndexes().at(0).data().toInt();
}

void Storage::on_TButton_Add_clicked()
{
    QMap<QString, QVariant> data;

    data["Title"] = ui->Txt_Title->text();
    data["Address"] = ui->Txt_Address->text();
    data["Deleded"]   = "0";

    ui->Txt_Title->clear();
    ui->Txt_Address->clear();

    MngrQuerys::insert( Tables::storage, data );
    _storageModel->setQuery( _storageModel->query().executedQuery() );
}

void Storage::on_TButton_Remove_clicked()
{
    QMap<QString, QVariant> data;
    data["Deleded"]   = "1";

    MngrQuerys::update(Tables::storage, data, _currentId);
    _storageModel->setQuery( _storageModel->query().executedQuery() );
}
