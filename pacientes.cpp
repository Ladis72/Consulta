#include "pacientes.h"
#include "ui_pacientes.h"
#include <QDebug>
#include <QMessageBox>

Pacientes::Pacientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pacientes)
{
    ui->setupUi(this);
    pacienteId = 0;
    modeloPacientes = funcion.pacientesTableModel();
    modeloPacientes->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(modeloPacientes);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->filtroLe->setFocus();
}

Pacientes::~Pacientes()
{
    delete ui;
}




void Pacientes::on_nuevoBtn_clicked()
{
    dialogNuevoPaciente = new NuevoPaciente();
    dialogNuevoPaciente->exec();
    modeloPacientes = funcion.pacientesTableModel();
    ui->tableView->setModel(modeloPacientes);


}


void Pacientes::on_tableView_clicked(const QModelIndex &index)
{
    pacienteId = modeloPacientes->data(modeloPacientes->index(index.row(),0),Qt::EditRole).toInt();
    qDebug() << pacienteId;
}


void Pacientes::on_filtroLe_textEdited(const QString &arg1)
{
    modeloPacientes->setFilter("nombre LIKE '%"+arg1+"%' or apellido1 LIKE '%"+arg1+"%' or apellido2 LIKE '%"+arg1+"%'");
}


void Pacientes::on_pushButton_clicked()
{
    if (pacienteId == 0) {
       QMessageBox::warning(this,"Error: seleccione un paciente","Debe seleccionar un paciente para poder editar");
    }
    qDebug() << funcion.datosPaciente(pacienteId);
    dialogNuevoPaciente = new NuevoPaciente(pacienteId);
    dialogNuevoPaciente->exec();
    modeloPacientes = funcion.pacientesTableModel();
    ui->tableView->setModel(modeloPacientes);


}

