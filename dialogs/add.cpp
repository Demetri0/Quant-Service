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
            << "Восстановление информации с USB накопителя или Flash накопителя"
            << "Восстановление информации с поврежденного жесткого диска"
            << "Восстановление операционной системы"
            << "Диагностика ноутбука (нетбука)"
            << "Диагностика ПК и оборудования"
            << "Замена матрицы ноутбука (нетбука)"
            << "Замена системной платы или корпуса ПК"
            << "Заправка картриджа"
            << "Настройка ПО"
            << "Перепрошивка BIOS"
            << "Поиск и лечение вирусов на ПК или Ноутбуке"
            << "Поиск и установка драйверов ПК"
            << "Прошивка BIOS системной платы"
            << "Ремонт окустической системы (Колонки наушники)"
            << "Ремонт БП ноутбука (нетбука)"
            << "Ремонт БП ПК"
            << "Ремонт видеоадаптера"
            << "Ремонт ЖД"
            << "Ремонт ЗУ"
            << "Ремонт модема (роутера)"
            << "Ремонт монитора"
            << "Ремонт ноутбука (нетбука)"
            << "Ремонт планшета"
            << "Ремонт принтера"
            << "Ремонт цифрового фотоапарата"
            << "Сохранение информации на другой носитель"
            << "Установка и настройка USB модема"
            << "Форматирование и разбивка жесткого диска"
            << "Чистка от пыли системного блока"
            << "Чистка системы охлаждения ноутбука";

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



    /*
    QMap<QString, QVariant> MasterList;
    MasterList["FirstName"] = "Максим";
    MasterList["LastName"] = "Шапилявин";
    MngrQuerys::insert(Tables::master, MasterList);
    MasterList["FirstName"] = "Артём";
    MasterList["LastName"] = "Погорелов";
    MngrQuerys::insert(Tables::master, MasterList);
    */
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


void DialogAdd::on_PBtn_Close_clicked()
{
    this->close();
}

void DialogAdd::on_PBtn_SelectModel_clicked()
{
    QMessageBox::information(this, this->windowTitle(), "Model");
    QWidget wgt(this);
    wgt.setGeometry(0,0, 200, 400);
    wgt.setWindowModality(Qt::WindowModal);
    wgt.show();
}

void DialogAdd::on_PBtn_Write_clicked()
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
}
