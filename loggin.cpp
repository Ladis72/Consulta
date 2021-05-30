#include "loggin.h"
#include "ui_loggin.h"

Loggin::Loggin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loggin)
{
    ui->setupUi(this);
}

Loggin::~Loggin()
{
    delete ui;
}

void Loggin::on_buttonBox_accepted()
{
    configDb.setValue("host",ui->leServidor->text());
    configDb.setValue("base",ui->leBase->text());
    configDb.setValue("usuario",ui->leUsuario->text());
    configDb.setValue("contrasena",ui->leContrasena->text());
    configDb.setValue("puerto",ui->lePuerto->text());
}


void Loggin::on_buttonBox_rejected()
{

}

