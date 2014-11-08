#ifndef STORAGE_H
#define STORAGE_H

#include <QDialog>
#include "mngrquerys.h"

namespace Ui {
class Storage;
}

class Storage : public QDialog
{
    Q_OBJECT

    QSqlQueryModel *_storageModel;
    qlonglong _currentId;
public:
    explicit Storage(QWidget *parent = 0);
    ~Storage();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_TButton_Add_clicked();

    void on_TButton_Remove_clicked();

private:
    Ui::Storage *ui;
};

#endif // STORAGE_H
