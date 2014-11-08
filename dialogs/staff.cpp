#include "dialogs/staff.h"
#include "ui_staff.h"


Staff::Staff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);
    ui->PBtn_Update->setVisible(false);

    _staffModel = new QSqlQueryModel(this);
    ui->LView_Staff->setModel( _staffModel );

    QSettings s;
    s.beginGroup("DialogStaff");
        this->restoreGeometry( s.value("WindowGeometry").toByteArray() );
        ui->splitter->restoreGeometry( s.value("SplitterGeometry").toByteArray() );
        ui->splitter->restoreState( s.value("SplitterState").toByteArray() );

        ui->CheckBox_ShowFired->setChecked( s.value("ShowFired", false).toBool() );
        emit ui->CheckBox_ShowFired->toggled( ui->CheckBox_ShowFired->isChecked() );
    s.endGroup();
}

Staff::~Staff()
{
    QSettings s;
    s.beginGroup("DialogStaff");
        s.setValue( "WindowGeometry", this->saveGeometry() );
        s.setValue( "SplitterGeometry", ui->splitter->saveGeometry() );
        s.setValue( "SplitterState", ui->splitter->saveState() );
        s.setValue( "ShowFired", ui->CheckBox_ShowFired->isChecked() );
    s.endGroup();

    delete ui;
}

void Staff::on_CheckBox_ShowFired_toggled(bool checked)
{
    QString sql("SELECT rowid, FirstName || ' ' || LastName FROM %1");
    sql = sql.arg( MngrQuerys::getTableName(Tables::master) );
    if( !checked )
        sql += " WHERE Fired=0";

    _staffModel->setQuery( sql );
    ui->LView_Staff->setModelColumn(1);
}

void Staff::on_PBtn_Clear_clicked()
{
    ui->Txt_Address->clear();
    ui->Txt_FName->clear();
    ui->Txt_LName->clear();
    ui->Txt_MName->clear();
    ui->Txt_MPhone->clear();
    ui->Txt_Phone->clear();

    ui->LView_Staff->clearSelection();

    ui->PBtn_Add->setVisible(true);
    ui->PBtn_Update->setVisible(false);
}


void Staff::on_LView_Staff_clicked(const QModelIndex&)
{
    //SELECT last_insert_rowid()

//    QVariant x = _staffModel->data(index).
    _currentId = ui->LView_Staff->selectionModel()->selectedIndexes().at(0).data().toInt();

    QString sql("SELECT FirstName, MiddleName, LastName, MobilePhone, Phone, Address, Fired "
                "FROM %1 "
                "WHERE rowid=%2");
    sql = sql.arg( MngrQuerys::getTableName( Tables::master ) ).arg( _currentId );

    QSqlQueryModel qm;
    qm.setQuery( sql );

    ui->Txt_FName->setText( qm.record(0).value("FirstName").toString() );
    ui->Txt_MName->setText( qm.record(0).value("MiddleName").toString() );
    ui->Txt_LName->setText( qm.record(0).value("LastName").toString() );

    ui->Txt_Phone->setText( qm.record(0).value("Phone").toString() );
    ui->Txt_MPhone->setText( qm.record(0).value("MobilePhone").toString() );
    ui->Txt_Address->setText( qm.record(0).value("Address").toString() );

    ui->CheckBox_Fired->setChecked( qm.record(0).value("Fired").toBool() );

    ui->PBtn_Add->setVisible(false);
    ui->PBtn_Update->setVisible(true);
}

void Staff::on_PBtn_Add_clicked()
{
    QMap<QString, QVariant> data;

    data["FirstName"] = ui->Txt_FName->text();
    data["MiddleName"] = ui->Txt_MName->text();
    data["LastName"] = ui->Txt_LName->text();

    data["Phone"] = ui->Txt_Phone->text();
    data["MobilePhone"] = ui->Txt_MPhone->text();
    data["Address"] = ui->Txt_Address->text();

    data["Fired"] = ui->CheckBox_Fired->isChecked();

    MngrQuerys::insert( Tables::master, data );
    _staffModel->setQuery( _staffModel->query().executedQuery() );
}

void Staff::on_PBtn_Update_clicked()
{
    QMap<QString, QVariant> data;

    data["FirstName"] = ui->Txt_FName->text();
    data["MiddleName"] = ui->Txt_MName->text();
    data["LastName"] = ui->Txt_LName->text();

    data["Phone"] = ui->Txt_Phone->text();
    data["MobilePhone"] = ui->Txt_MPhone->text();
    data["Address"] = ui->Txt_Address->text();

    data["Fired"] = ui->CheckBox_Fired->isChecked();

    MngrQuerys::update( Tables::master, data, _currentId );
    _staffModel->setQuery( _staffModel->query().executedQuery() );
}
