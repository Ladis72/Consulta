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

QSqlTableModel* dbFunc::pacientesTableModel()
{
    QSqlTableModel *pacientesTableModel = new QSqlTableModel(this, QSqlDatabase::database("DB"));
    pacientesTableModel->setTable("pacientes");
    pacientesTableModel->select();
    return pacientesTableModel;
}

bool dbFunc::grabarPaciente(QStringList datosPaciente)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("INSERT INTO `consulta`.`pacientes` (`nombre`, `apellido1`, `apellido2`, `dni`, `localidad`, `provincia`, `cp`, `telefono`, `correo`, `profesion` , `nacimiento`, `sexo`, `eCivil`, `hijos`, `grupoS` , `rh` ,`notas`) "
                     "VALUES (?, ?, ?, ?, ?,?, ?, ?, ?, ?, ?, ?, ?, ?,?,?,?);");
    for (int i = 0; i < datosPaciente.length() ; i++ ) {
        consulta.bindValue(i,datosPaciente.at(i));
    }
    if (consulta.exec()) {
        return true;
    }else {
        qDebug() << consulta.lastQuery();

        qDebug() << consulta.lastError().text();
        return false;
    }
}

QStringList dbFunc::datosPaciente(int idPaciente)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));

    consulta.exec("SELECT * FROM pacientes WHERE idPaciente ="+QString::number(idPaciente));
    qDebug() << consulta.lastError();
    consulta.first();
    QStringList datosPaciente;
    datosPaciente.clear();
    QSqlRecord record = consulta.record();
    for (int i = 0 ;i < record.count() ;i++ ) {
        datosPaciente.append(record.value(i).toString());
    }
    return datosPaciente;
}

bool dbFunc::modificarPaciente(int idPaciente , QStringList datosPaciente)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("UPDATE `consulta`.`pacientes` SET `nombre` = ? , `apellido1` = ? , `apellido2` = ? , `dni` = ? , `localidad` = ? , `provincia` = ? , `cp` = ? , `telefono` = ? , `correo` = ? , `profesion` = ? , `nacimiento` = ? , `sexo` = ? , `eCivil` = ? , `hijos` = ? , `grupoS` = ? , `rh` = ? , `notas` = ? WHERE `idPaciente` = ?");
    for (int i = 0;i < datosPaciente.length() ;i++ ) {
        consulta.bindValue(i,datosPaciente.at(i));
    }
    consulta.bindValue(datosPaciente.length(),QString::number(idPaciente));
    if (consulta.exec()) {
        return true;
    } else {
        qDebug() << consulta.lastQuery();

        qDebug() << consulta.lastError().text();
        return false;
    }
}
