#include "consulta.h"
#include "ui_consulta.h"
#include <QDebug>
#include <QDate>

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
        rellenarDatosPaciente(pacienteId);
    }

    return;

}

bool Consulta::rellenarDatosPaciente(int idPaciente)
{
    QStringList datosPaciente = funcion.datosPaciente(idPaciente);
    ui->lNombre->setText(datosPaciente.at(1));
    ui->lApellido1->setText(datosPaciente.at(2));
    ui->lApellido2->setText(datosPaciente.at(3));
    qint64 edad = QDate::fromString(datosPaciente.at(11),"yyyy-MM-dd").daysTo(QDate::currentDate())/360;
    ui->lEdad->setText(QString::number(edad));
}

