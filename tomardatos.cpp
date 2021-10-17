#include "tomardatos.h"
#include "ui_tomardatos.h"
#include <QMessageBox>

tomarDatos::tomarDatos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tomarDatos)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    ui->lePeso->setFocus();
    llenarDatos();
}

tomarDatos::~tomarDatos()
{
    delete ui;
}

void tomarDatos::on_lePeso_editingFinished()
{
    llenarDatos();
}


void tomarDatos::on_leAltura_editingFinished()
{
    llenarDatos();
}


void tomarDatos::on_leSist_editingFinished()
{
    llenarDatos();
}


void tomarDatos::on_leDiast_editingFinished()
{
    llenarDatos();
}


void tomarDatos::on_lePulso_editingFinished()
{
    llenarDatos();
}


void tomarDatos::on_leEstomago_editingFinished()
{
    if (ui->leEstomago->text() != "B" && ui->leEstomago->text() != "C") {
        QMessageBox::information(this,"Dato erroneo","Las opciones del stómago son B o C");
        ui->leEstomago->setFocus();
        return;
    }
    llenarDatos();
}

void tomarDatos::llenarDatos()
{
    datos.clear();
    datos << ui->dateEdit->text();
    datos << ui->timeEdit->text();
    datos << ui->lePeso->text();
    datos << ui->leAltura->text();
    datos << ui->leSist->text();
    datos << ui->leDiast->text();
    datos << ui->lePulso->text();
    datos << ui->leEstomago->text();
}

