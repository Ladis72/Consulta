#ifndef DBFUNC_H
#define DBFUNC_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>

class dbFunc : public QObject
{
    Q_OBJECT
public:
    explicit dbFunc(QObject *parent = nullptr);
    bool funcionaDB();
    QSqlTableModel *pacientesTableModel();
    bool grabarPaciente(QStringList datosPaciente);
    QStringList datosPaciente(int idPaciente);
    bool modificarPaciente(int idPaciente, QStringList datosPaciente);
    QString getDirectorioTrabajo();
    bool setDirectorioTrabajo(QString directorio);
    QStringList getConfiguracion();
    bool setConfiguracion(QStringList configuracion);
    bool guardarDatosPaciente(int idPaciente, QString datos);
    bool guardarDatosHoy(QStringList datos);
    QSqlTableModel *llenarHistoricoDatos(int filtro);
    int idVisitaActual(int idPaciente);
    bool finalizarVisita(int visita, QString tipo);

signals:

private:

    QSqlDatabase db;
    QSqlQuery consulta;
    QSqlQueryModel modelo;
    QString cod;
};

#endif // DBFUNC_H
