#include "dbfunc.h"
#include <QTime>

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

bool dbFunc::setDirectorioTrabajo(QString directorio)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.exec("UPDATE `consulta`.`configuracion` SET `directorio`="+directorio+" WHERE  `id`=0");
    if (!consulta.isValid()) {
        qDebug() << consulta.lastQuery();
        qDebug() << consulta.lastError();
        return false;
    }
    return true;
}

QStringList dbFunc::getConfiguracion()
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.exec("SELECT * FROM configuracion");
    consulta.first();
    QStringList configuracion;
    configuracion.clear();
    QSqlRecord record = consulta.record();
    for (int i = 0;i < record.count() ;i++ ) {
        configuracion.append(record.value(i).toString());
    }
    return configuracion;
}

bool dbFunc::setConfiguracion(QStringList configuracion)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("UPDATE configuracion SET directorio = ? , pdf = ? , web = ? , imagen = ? , video = ? , texto = ? WHERE id = 0");
    for (int i = 0;i < configuracion.length()-1 ;i++ ) {
        consulta.bindValue(i,configuracion.at(i+1));
        }
    if (consulta.exec()) {
        return true;
    } else {
        qDebug() << consulta.lastQuery();

        qDebug() << consulta.lastError().text();
        return false;
    }
}

bool dbFunc::guardarDatosPaciente(int idPaciente, QString datos)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("UPDATE pacientes SET notas = ? WHERE idPaciente = ?");
    consulta.bindValue(0,datos);
    consulta.bindValue(1,idPaciente);
    return consulta.exec() ? true : false;
}

bool dbFunc::guardarDatosHoy(QStringList datos)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("INSERT INTO visitas (idPaciente, fecha, hora, peso, altura, sist, diast, pulsaciones, estomago) VALUES (?,?,?,?,?,?,?,?,?)");
    for (int i = 0 ;i < datos.count() ;i++ ) {
        consulta.bindValue(i,datos.at(i));
    }
    if (consulta.exec()) {
        return true;
    }
    qDebug() << consulta.lastError().text();
    return false;
}

QSqlTableModel *dbFunc::llenarHistoricoDatos(int filtro)
{
    QSqlTableModel *historicoDatosTableModel = new QSqlTableModel(this, QSqlDatabase::database("DB"));
    historicoDatosTableModel->setTable("visitas");
    historicoDatosTableModel->setSort(0,Qt::DescendingOrder);
    historicoDatosTableModel->select();
    return historicoDatosTableModel;
}

int dbFunc::idVisitaActual(int idPaciente)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("SELECT idVisita FROM visitas WHERE idPaciente = ?");
    consulta.bindValue(0,QString::number(idPaciente));
    if (consulta.exec()) {
        consulta.last();
        qDebug() << consulta.lastError().text();
        return consulta.value(0).toInt();
    }
    return 0;
}

bool dbFunc::finalizarVisita(int visita, QString tipo)
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.prepare("SELECT hora FROM visitas WHERE idVisita = ?");
    consulta.bindValue(0,visita);
    if (!consulta.exec()) {
        consulta.first();
        qDebug() << consulta.lastError();
        return false;
        }
    consulta.first();
    int duracion = consulta.value(0).toTime().msecsTo(QTime::currentTime());
    qDebug() << consulta.value(0);
    qDebug() << consulta.value(0).toTime();
    qDebug() << QTime::currentTime();
    qDebug() << "Duraciom = " << duracion;
    consulta.clear();
    consulta.prepare("UPDATE visitas SET tipoVisita =? , duracion =? WHERE idVisita = ?");
    consulta.bindValue(0,tipo);
    consulta.bindValue(1,(duracion/60000));
    consulta.bindValue(2,visita);
    if (!consulta.exec()) {
        qDebug() << "ERROR " << consulta.lastError();
        qDebug() << "ERROR " << consulta.lastError().text();
        return false;
        }
    return true;
}

QString dbFunc::getDirectorioTrabajo()
{
    QSqlQuery consulta(QSqlDatabase::database("DB"));
    consulta.exec("select directorio from configuracion");
    consulta.first();
    QString directorio = consulta.value(0).toString();
    return directorio;
}
