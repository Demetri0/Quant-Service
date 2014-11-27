#include "dialogs/add.h"
#include "ui_add.h"
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QTreeWidget>
#include <mngrquerys.h>

namespace Status{
    enum status{open, close, canceled};
}

QStringList getTypeWork(){
    return QStringList()
            << QObject::tr("Recovery information from USB or Flash drive")
            << QObject::tr("Recovery information from hurt HDD/SSD")
            << QObject::tr("Recovery OS")
            << QObject::tr("Diagnostics notebook (laptop)")
            << QObject::tr("Diagnostics PC and devices")
            << QObject::tr("Replacing matrix notebook (laptop)")
            << QObject::tr("Replacing motherboard or casing PC")
            << QObject::tr("Priming of a cartridge")
            << QObject::tr("Configure software")
            << QObject::tr("Refirmware BIOS")
            << QObject::tr("Search and cleaning virus on PC or notebook")
            << QObject::tr("Search and install drivers on PC")
            << QObject::tr("Repair audio system")
            << QObject::tr("Repair power supply unit notebook (laptop)")
            << QObject::tr("Repair power supply unit PC")
            << QObject::tr("Repair videoadapter")
            << QObject::tr("Repair modem (router)")
            << QObject::tr("Repair monitor")
            << QObject::tr("Repair notebook (laptop)")
            << QObject::tr("Repair pad")
            << QObject::tr("Repair printer")
            << QObject::tr("Repair digital camera")
            << QObject::tr("Saving of information on other carrier")
            << QObject::tr("Installation and USB setup of the modem")
            << QObject::tr("Formatting and splitting of a hard drive")
            << QObject::tr("Cleaning from dust of a base unit")
            << QObject::tr("Cleaning notebook cooling systems");

}

DialogAdd::DialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdd)
{
    ui->setupUi(this);
    QStringListModel *m = new QStringListModel( getTypeWork(), ui->ComboBox_WorkType );
    ui->ComboBox_WorkType->setModel( m );

    ui->dateTimeEdit->setDateTime( QDateTime::currentDateTime() );
    ui->dateTimeEdit_2->setDateTime( QDateTime::currentDateTime().addDays(1) );

    {
        ui->ComboBox_Status->addItem(tr("Open"),Status::open);
        ui->ComboBox_Status->addItem(tr("Close"),Status::close);
        ui->ComboBox_Status->addItem(tr("Canceled"),Status::canceled);
    }
    {
        QMapIterator<qint64, QString> i( MngrQuerys::getMasters() );
        while(i.hasNext()){
            i.next();
            ui->ComboBox_Master->addItem( i.value(), i.key() );
        }
    }
    {
        QMapIterator<qint64, QString> i( MngrQuerys::getStorages() );
        while(i.hasNext()){
            i.next();
            ui->ComboBox_Storage->addItem( i.value(), i.key() );
        }
    }
}

DialogAdd::~DialogAdd()
{
    delete ui;
}

QMap<QString, QVariant> DialogAdd::getData()
{
    QMap<QString, QVariant> data;

    data["Departure"]  = ui->tabWidget->currentIndex();
    data["Warranty"]   = ui->ComboBox_Warranty->currentIndex();
    data["Task"]       = ui->ComboBox_WorkType->currentText();

    data["kaName"]     = ui->LineEdit_Kontragent->text();
    data["kaPhone"]    = ui->LineEdit_Phone->text();
    data["kaAddress"]  = ui->LineEdit_Address->text();
    data["kaOrganization"] = "";

    data["DateStart"]  = ui->dateTimeEdit->dateTime().toMSecsSinceEpoch();
    data["DateFinish"] = ui->dateTimeEdit_2->dateTime().toMSecsSinceEpoch();

//    data["Appearance"] = ui->LView_Appearance->currentIndex();
//    data["Package"]    = ui->LView_Package->currentIndex();

    data["Deffect"]    = ui->LineEdit_Deffect->text();
    data["Comment"]    = ui->LineEdit_Comment->text();

    data["Status"]     = 0; // Open(Working), Close(Finished), Canceled

    data["idMaster"]   = ui->ComboBox_Master->currentData();
    data["idProduct"]  = ui->LineEdit_SerialNumber->text();
    data["Package"]  = ui->LineEdit_Package->text();
    data["idStorage"]  = ui->ComboBox_Storage->currentData();

    return data;
}
/*
void DialogAdd::on_PBtn_SelectModel_clicked()
{
    QMessageBox::information(this, this->windowTitle(), "Model");
    QWidget wgt(this);
    wgt.setGeometry(0,0, 200, 400);
    wgt.setWindowModality(Qt::WindowModal);
    wgt.show();
}
*/
void DialogAdd::on_buttonBox_accepted()
{
    QMap<QString, QVariant> data;

    data["Departure"] = ui->tabWidget->currentIndex();
    data["Warranty"]  = ui->ComboBox_Warranty->currentIndex();
    data["Task"]      = ui->ComboBox_WorkType->currentText();

    /*=>User*/
        data["kaName"]         = ui->LineEdit_Kontragent->text();
        data["kaPhone"]        = ui->LineEdit_Phone->text();
        data["kaAddress"]      = ui->LineEdit_Address->text();
        //data["kaOrganization"] = "VARCHAR(48)";
    /**/

    data["DateStart"]  = ui->dateTimeEdit->dateTime().toMSecsSinceEpoch();
    data["DateFinish"] = ui->dateTimeEdit_2->dateTime().toMSecsSinceEpoch();

    data["Appearance"] = ui->LineEdit_Appearance->text();
    data["Package"]    = ui->LineEdit_Package->text();

    data["Deffect"]    = ui->LineEdit_Deffect->text();
    data["Comment"]    = ui->LineEdit_Comment->text();

    data["Status"]     = ui->ComboBox_Status->currentData().toInt(); // Open(Working), Close(Finished), Canceled

    data["idMaster"]   = ui->ComboBox_Master->currentIndex();
//    fields["idProduct"]  = "INTEGER";
    data["idStorage"]  = ui->ComboBox_Storage->currentData().toULongLong();


    MngrQuerys::insert(Tables::booking, data);
    this->close();
}

void DialogAdd::on_buttonBox_rejected()
{
    this->close();
}
