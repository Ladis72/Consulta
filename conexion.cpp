#include "conexion.h"
#include "loggin.h"
#include <QDebug>

Conexion::Conexion(QObject *parent) : QObject(parent)
{
    dbHost = "127.0.0.1"; // configDb.value("host").toString();
    dbBase = "consulta"; // configDb.value("base").toString();
    dbUsuario = "ladis"; // configDb.value("usuario").toString();
    dbContrasena = "meganizado72"; // configDb.value("contrasena").toString();
    dbPuerto = "3306"; // configDb.value("puerto").toString();

    qDebug() << dbHost;
    qDebug() << dbBase;
    qDebug() << dbUsuario;
    qDebug() << dbContrasena;
    qDebug() << dbPuerto;

}

bool Conexion::conectar()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","DB");
    db.setHostName(dbHost);
    db.setDatabaseName(dbBase);
    db.setUserName(dbUsuario);
    db.setPassword(dbContrasena);
    db.setPort(dbPuerto.toInt());

    if (!db.open()) {
        mensaje.setText("Error de conexion");
        mensaje.setInformativeText(db.lastError().text());
        mensaje.exec();
        Loggin *loggin = new Loggin();
        loggin->exec();
        conectar();
    }
    qDebug() << "conectando..";
    return true;
}

QSqlDatabase Conexion::base()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","DB");
    db.setHostName(dbHost);
    db.setDatabaseName(dbBase);
    db.setUserName(dbUsuario);
    db.setPassword(dbContrasena);
    db.setPort(dbPuerto.toInt());

    if (!db.open()) {
        mensaje.setText("Error de conexion");
        mensaje.setInformativeText(db.lastError().text());
        mensaje.exec();
        Loggin *loggin = new Loggin();
        loggin->exec();
        conectar();
    }
    qDebug() << "conectando..";
    return db;
}
