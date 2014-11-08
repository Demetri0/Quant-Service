#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
//#include <QLibraryInfo>
#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QDir>

void LogOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile f( QDir::homePath() + QDir::separator()
             + "." + QApplication::organizationName()
             + QDir::separator() + QApplication::applicationName()
             + QDir::separator() + "log.txt" );
    f.open(QFile::Append);
    switch (type) {
     case QtDebugMsg:
        f.write( "[Debug]\n"
                 "Message: " + msg.toUtf8() + "\n"
                 + "File: " + context.file + "\n"
                 + "Line: " + QString::number(context.line).toUtf8() + "\n"
                 + "Function: " + context.function
                 + "\n-----\n" );
        break;
     case QtWarningMsg:
        f.write( "[Warning]\n"
                 "Message: " + msg.toUtf8() + "\n"
                 + "File: " + context.file + "\n"
                 + "Line: " + QString::number(context.line).toUtf8() + "\n"
                 + "Function: " + context.function
                 + "\n-----\n" );
        break;
     case QtCriticalMsg:
        f.write( "[Critical]\n"
                 "Message: " + msg.toUtf8() + "\n"
                 + "File: " + context.file + "\n"
                 + "Line: " + QString::number(context.line).toUtf8() + "\n"
                 + "Function: " + context.function
                 + "\n-----\n" );
        break;
     case QtFatalMsg:
        f.write( "[Fatal]\n"
                 "Message: " + msg.toUtf8() + "\n"
                 + "File: " + context.file + "\n"
                 + "Line: " + QString::number(context.line).toUtf8() + "\n"
                 + "Function: " + context.function
                 + "\n-----\n" );
        f.close();
        abort();
     }
    f.close();
}

int main(int argc, char *argv[])
{
    #ifndef QT_DEBUG
        qInstallMessageHandler(LogOutput);
    #endif

    QApplication app(argc, argv);

    app.setOrganizationName("Kvant");
    app.setOrganizationDomain("https://github.com/Demetri0");
    app.setApplicationName("QuantService");
    app.setApplicationVersion("0.0.0 Pre-Alpha");
    app.setApplicationDisplayName( QObject::tr("Quant Service") );
//    app.setWindowIcon( QIcon("://images/DBA_Icon.png") );


    QSettings settings;
    QString set_language       = settings.value( "Application/l10n", "<System>" ).toString();
    int     set_language_index = settings.value( "Application/l10n_index", 0 ).toInt();
    QTranslator qtTr;

    const QString sharePath( QApplication::applicationDirPath() + QDir::separator()
                             + ".." + QDir::separator()
                             + "share" + QDir::separator()
                             + QApplication::applicationName() + QDir::separator()
                             );

    if( set_language_index == 0 ){
        /*, QLibraryInfo::location(QLibraryInfo::TranslationsPath)*/
        qtTr.load( sharePath + "l10n" + QDir::separator()
                   + "qtbase_" + QLocale::system().name().section('_', 0, 0) + ".qm" );
    }else{
        qtTr.load( sharePath + "l10n" + QDir::separator()
                   + "qtbase_" + set_language + ".qm" );
    }
    app.installTranslator(&qtTr);

    QTranslator dbaTr;
    if( set_language_index == 0 ){
        dbaTr.load( sharePath + "l10n" + QDir::separator()
                    + "QuantService_" + QLocale::system().name().section('_', 0, 0) + ".qm" );
    }else{
        dbaTr.load( sharePath + "l10n" + QDir::separator()
                    + "QuantService_" + set_language + ".qm" );
    }
    app.installTranslator(&dbaTr);

    MainWindow w;
    w.show();

    return app.exec();
}
