#ifndef DBFUNC_H
#define DBFUNC_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class dbFunc : public QObject
{
    Q_OBJECT
public:
    explicit dbFunc(QObject *parent = nullptr);
    bool funcionaDB();
    QSqlTableModel *pacientesTableModel();

signals:

private:

    QSqlDatabase db;
    QSqlQuery consulta;
    QSqlQueryModel modelo;
    QString cod;
};

#endif // DBFUNC_H
