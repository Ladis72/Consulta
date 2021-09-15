#ifndef NUEVOPACIENTE_H
#define NUEVOPACIENTE_H

#include "dbfunc.h"

#include <QDialog>

namespace Ui {
class NuevoPaciente;
}

class NuevoPaciente : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoPaciente(QWidget *parent = nullptr);
    explicit NuevoPaciente(int idP, QWidget *parent = nullptr);
    ~NuevoPaciente();

private slots:
    void on_pbAceptar_clicked();

private:
    Ui::NuevoPaciente *ui;
    QStringList recogerDatosFormulario();
    void llenarFormulario(QStringList datosPaciente);

    QStringList datosPaciente;
    dbFunc *funcion;
    int idPaciente;
};

#endif // NUEVOPACIENTE_H
