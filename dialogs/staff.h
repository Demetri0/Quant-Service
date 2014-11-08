#ifndef STAFF_H
#define STAFF_H

#include <QDialog>
#include "mngrquerys.h"

namespace Ui {
class Staff;
}

class Staff : public QDialog
{
    Q_OBJECT

    QSqlQueryModel *_staffModel;
    qlonglong _currentId;
public:
    explicit Staff(QWidget *parent = 0);
    ~Staff();

private slots:
    void on_PBtn_Clear_clicked();
    void on_LView_Staff_clicked(const QModelIndex &index);
    void on_PBtn_Add_clicked();
    void on_PBtn_Update_clicked();

    void on_CheckBox_ShowFired_toggled(bool checked);

private:
    Ui::Staff *ui;
};

#endif // STAFF_H
