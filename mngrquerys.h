#ifndef MNGRQUERYS_H
#define MNGRQUERYS_H

#include <QtSql>
#include <QSqlQueryModel>
#include <QString>

namespace Tables {
    enum table{none = 0, master, storage, product, booking};
}

class MngrQuerys
{
private:
    static QMap<QString, QString> getFields(const Tables::table table);
    static QMap<QString, QString> getFields_master();
    static QMap<QString, QString> getFields_storage();
    static QMap<QString, QString> getFields_product();
    static QMap<QString, QString> getFields_booking();
    static bool createTable(const QString, const QMap<QString, QString> fieldsAndTypes);
    static bool createTable(const Tables::table);
public:
    static bool createTables();
    static QString getTableName(const Tables::table table);
    static QMap<qint64, QString> getMasters();
    static QMap<qint64, QString> getStorages();


    static bool insert(Tables::table table, const QMap<QString, QVariant> &data);
    static bool update(Tables::table table, const QMap<QString, QVariant> &data, qlonglong id);
};

#endif // MNGRQUERYS_H
