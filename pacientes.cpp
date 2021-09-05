#include "pacientes.h"
#include "ui_pacientes.h"
#include <QDebug>

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
}

Pacientes::~Pacientes()
{
    delete ui;
}




void Pacientes::on_nuevoBtn_clicked()
{

}


void Pacientes::on_tableView_clicked(const QModelIndex &index)
{
    pacienteId = modeloPacientes->data(modeloPacientes->index(index.row(),0),Qt::EditRole).toInt();
}

