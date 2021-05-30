#ifndef CONSULTA_H
#define CONSULTA_H

#include "dbfunc.h"
#include "conexion.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Consulta; }
QT_END_NAMESPACE

class Consulta : public QMainWindow
{
    Q_OBJECT

public:
    Consulta(QWidget *parent = nullptr);
    ~Consulta();

private:
    Ui::Consulta *ui;
    Conexion *conexion;
    dbFunc funcion;
};
#endif // CONSULTA_H
