#include "consulta.h"
#include "ui_consulta.h"
#include <QDebug>

Consulta::Consulta(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Consulta)
{
    ui->setupUi(this);
    pacienteId = 0;
    funcion.funcionaDB();

}

Consulta::~Consulta()
{
    delete ui;
}


void Consulta::on_pushButton_clicked()
{
    pacienteDlg = new Pacientes;
    if(pacienteDlg->exec()){
        pacienteId = pacienteDlg->pacienteId;
        qDebug() << pacienteId;

    }

    return;

}

