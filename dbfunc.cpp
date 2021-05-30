#include "dbfunc.h"

#include <QDebug>

dbFunc::dbFunc(QObject *parent) : QObject(parent)
{

}

bool dbFunc::funcionaDB()
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    if(consulta.exec("SELECT * FROM pacientes")){
        qDebug() << "Funciona";
        return true;
    }
    qDebug() << "No funciona";
    return false;

}
