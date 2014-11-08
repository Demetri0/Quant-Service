#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>

namespace Ui {
class DialogAdd;
}

class DialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdd(QWidget *parent = 0);
    ~DialogAdd();

    QMap<QString, QVariant> getData();

private slots:

    void on_PBtn_Close_clicked();
    void on_PBtn_SelectModel_clicked();

    void on_PBtn_Write_clicked();

private:
    Ui::DialogAdd *ui;
};

#endif // DIALOGADD_H
