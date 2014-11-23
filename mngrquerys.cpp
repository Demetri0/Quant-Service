#include "mngrquerys.h"

QMap<QString,QString> MngrQuerys::getFields(const Tables::table table)
{
    switch(table){
    case Tables::master :
        return getFields_master();
    case Tables::storage :
        return getFields_storage();
    case Tables::product :
        return getFields_product();
    case Tables::booking :
        return getFields_booking();
    default:
        QMap<QString,QString> empty;
        return empty;
    }
}

QMap<QString, QString> MngrQuerys::getFields_master()
{
    QMap<QString, QString> fields;

    fields["FirstName"]   = "VARCHAR(22)";
    fields["MiddleName"]  = "VARCHAR(32)";
    fields["LastName"]    = "VARCHAR(32)";

    fields["MobilePhone"] = "VARCHAR(11)";
    fields["Phone"]       = "VARCHAR(6)";

    fields["Address"]     = "VARCHAR(48)";

    fields["DateBeginWork"] = "INTEGER";
    fields["DateEndedWork"] = "INTEGER";

    fields["Fired"]   = "INTEGER";

    return fields;
}

QMap<QString, QString> MngrQuerys::getFields_storage()
{
    QMap<QString, QString> fields;

    fields["Title"]     = "VARCHAR(48)";
    fields["Address"]   = "VARCHAR(48)";

    fields["Deleded"]   = "INTEGER";

    return fields;
}

QMap<QString, QString> MngrQuerys::getFields_product()
{
    QMap<QString, QString> fields;

    fields["Type"]          = "VARCHAR(22)";
    fields["Model"]         = "VARCHAR(22)";
    fields["SerialNumber"]  = "VARCHAR(16)";

    return fields;
}

QMap<QString, QString> MngrQuerys::getFields_booking()
{
    QMap<QString, QString> fields;

    fields["Departure"]  = "INTEGER";
    fields["Warranty"]   = "INTEGER";
    fields["Task"]      = "VARCHAR(32)";

    /*=>User*/
        fields["kaName"]         = "VARCHAR(48)";
        fields["kaPhone"]        = "VARCHAR(48)";
        fields["kaAddress"]      = "VARCHAR(48)";
        fields["kaOrganization"] = "VARCHAR(48)";
    /**/

    fields["DateStart"]  = "INTEGER";
    fields["DateFinish"] = "INTEGER";

    fields["Appearance"] = "VARCHAR(255)";
    fields["Package"]    = "VARCHAR(255)";

    fields["Deffect"]    = "VARCHAR(128)";
    fields["Comment"]    = "VARCHAR(64)";

    fields["Status"]     = "INTEGER"; // Open(Working), Close(Finished), Canceled

    fields["idMaster"]   = "INTEGER";
    fields["idProduct"]  = "INTEGER";
    fields["idStorage"]  = "INTEGER";

    return fields;
}

bool MngrQuerys::createTable(const QString tableName, const QMap<QString, QString> fieldsAndTypes)
{
    QString sql("CREATE TABLE IF NOT EXISTS ");
    sql += tableName;
    sql += "(";
    QMapIterator<QString, QString> i(fieldsAndTypes);
    while( i.hasNext() ){
        i.next();
        sql += i.key() + " " + i.value();
        if( i.hasNext() ) sql += ",";
    }
    sql += ");";

    QSqlQuery q(sql);
    return q.exec();
}

bool MngrQuerys::createTable(const Tables::table table)
{
    return createTable( getTableName(table), getFields(table) );
}

bool MngrQuerys::insert(const Tables::table table, const QMap<QString, QVariant> &data)
{
    QString sql( QString("INSERT INTO %1(").arg(getTableName( table )) );
    QString values;

    QMapIterator<QString, QVariant> i(data);
    while( i.hasNext() ){
        i.next();

        sql += i.key();
        values += ":" + i.key();

        if( i.hasNext() ){
            sql += ",";
            values += ",";
        }
    }
    sql += ") VALUES (" + values + ");";

    QSqlQuery q;
    q.prepare(sql);

    QMapIterator<QString, QVariant> j(data);
    while( j.hasNext() ){
        j.next();
        q.bindValue( ":" + j.key(), j.value() );
    }

    bool ok = q.exec();
    if( !ok )
        qCritical() << q.lastError();
    return ok;
}

bool MngrQuerys::update(const Tables::table table, const QMap<QString, QVariant> &data, qlonglong id)
{
    QString sql( QString("UPDATE %1 SET ").arg(getTableName( table )) );
    QString values;

    QMapIterator<QString, QVariant> i(data);
    while( i.hasNext() ){
        i.next();

        sql += i.key();
        sql += "=";
        sql += ":" + i.key();

        if( i.hasNext() ) sql += ",";
    }
    sql += QString(" WHERE rowid=%1;").arg(id);

    QSqlQuery q;
    q.prepare(sql);

    QMapIterator<QString, QVariant> j(data);
    while( j.hasNext() ){
        j.next();
        q.bindValue( ":" + j.key(), j.value() );
    }

    qDebug() << sql;
    qDebug() << q.executedQuery();

    bool ok = q.exec();
    if( !ok )
        qCritical() << q.lastError();
    return ok;
}

bool MngrQuerys::createTables()
{
    bool isOk = true;

    if( !createTable(Tables::booking) ) isOk = false;
    if( !createTable(Tables::master)  ) isOk = false;
    if( !createTable(Tables::product) ) isOk = false;
    if( !createTable(Tables::storage) ) isOk = false;

    return isOk;
}

QString MngrQuerys::getTableName(const Tables::table table)
{
    switch (table) {
    case Tables::booking :
        return QString("Booking");
    case Tables::master :
        return QString("Master");
    case Tables::product :
        return QString("Product");
    case Tables::storage :
        return QString("Storage");
    default:
        return QString::null;
    }
}

QMap<qint64, QString> MngrQuerys::getMasters()
{
    QMap<qint64, QString> data;
    QSqlQuery q( QString("SELECT rowid, FirstName, LastName FROM %1 WHERE Fired=0").arg( getTableName(Tables::master) ) );

    if( q.exec() ){
        while( q.next() ){
            data[q.value("rowid").toInt()] = q.value("FirstName").toString() + " " + q.value("LastName").toString();
        }
    }

    return data;
}

QMap<qint64, QString> MngrQuerys::getStorages()
{
    QMap<qint64, QString> data;
    QSqlQuery q( QString("SELECT rowid, Title FROM %1 WHERE Deleded=0").arg( getTableName(Tables::storage) ) );

    if( q.exec() ){
        while( q.next() ){
            data[q.value("rowid").toInt()] = q.value("Title").toString();
        }
    }

    return data;
}
