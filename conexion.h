#ifndef CONEXION_H
#define CONEXION_H

#include <QObject>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>


class Conexion : public QObject
{
    Q_OBJECT
public:
    explicit Conexion(QObject *parent = nullptr);
    bool conectar();
    QSqlDatabase base();

signals:

private:
    QSettings configDb;
    QString dbHost;
    QString dbBase;
    QString dbContrasena;
    QString dbUsuario;
    QString dbPuerto;
    QMessageBox mensaje;
};

#endif // CONEXION_H
