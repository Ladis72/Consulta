#ifndef PACIENTES_H
#define PACIENTES_H

#include <QDialog>
#include "dbfunc.h"
#include "nuevopaciente.h"

namespace Ui {
class Pacientes;
}

class Pacientes : public QDialog
{
    Q_OBJECT

public:
    explicit Pacientes(QWidget *parent = nullptr);
    ~Pacientes();

    int pacienteId;

private slots:

    void on_nuevoBtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_filtroLe_textEdited(const QString &arg1);

    void on_pushButton_clicked();

private:

    Ui::Pacientes *ui;
    dbFunc funcion;
    QSqlTableModel *modeloPacientes;
    NuevoPaciente *dialogNuevoPaciente;
};

#endif // PACIENTES_H
