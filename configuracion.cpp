#include "configuracion.h"
#include "ui_configuracion.h"
#include <QFileDialog>
#include <QDebug>

Configuracion::Configuracion(QStringList direct , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configuracion)
{
    ui->setupUi(this);
    configuracion = direct;
    qDebug() << configuracion;

    rellenarCampos();
}

Configuracion::~Configuracion()
{
    delete ui;
}

void Configuracion::leerConfiguracion()
{
    configuracion.replace(1, ui->leDirectorioTrabajo->text());
    configuracion.replace(2, ui->lePdf->text());
    configuracion.replace(3, ui->leUrl->text());
    configuracion.replace(4, ui->leImagen->text());
    configuracion.replace(5, ui->leVideo->text());
    configuracion.replace(6, ui->leTexto->text());
    configuracion.replace(7, ui->leComandoVideo->text());
    qDebug() << configuracion;
}



void Configuracion::on_pbDirectorioTrabajo_clicked()
{
    QString directorio = QFileDialog::getExistingDirectory(this);
    ui->leDirectorioTrabajo->setText(directorio);
    leerConfiguracion();
}

void Configuracion::rellenarCampos()
{
    ui->leDirectorioTrabajo->setText(configuracion.at(1));
    ui->lePdf->setText(configuracion.at(2));
    ui->leUrl->setText(configuracion.at(3));
    ui->leImagen->setText(configuracion.at(4));
    ui->leVideo->setText(configuracion.at(5));
    ui->leTexto->setText(configuracion.at(6));
    ui->leComandoVideo->setText(configuracion.at(7));
}


void Configuracion::on_pbPdf_clicked()
{
    QString directorio = QFileDialog::getOpenFileName(this);
    ui->lePdf->setText(directorio);
    leerConfiguracion();
}


void Configuracion::on_pbUrl_clicked()
{
    QString directorio = QFileDialog::getOpenFileName(this);
    ui->leUrl->setText(directorio);
    leerConfiguracion();
}


void Configuracion::on_pbImagen_clicked()
{
    QString directorio = QFileDialog::getOpenFileName(this);
    ui->leImagen->setText(directorio);
    leerConfiguracion();
}


void Configuracion::on_pbVideo_clicked()
{
    QString directorio = QFileDialog::getOpenFileName(this);
    ui->leVideo->setText(directorio);
    leerConfiguracion();
}


void Configuracion::on_leDirectorioTrabajo_editingFinished()
{
    leerConfiguracion();

}


void Configuracion::on_lePdf_editingFinished()
{
    leerConfiguracion();

}



void Configuracion::on_leUrl_editingFinished()
{
    leerConfiguracion();

}


void Configuracion::on_leImagen_editingFinished()
{
    leerConfiguracion();

}


void Configuracion::on_leVideo_editingFinished()
{
    leerConfiguracion();

}


void Configuracion::on_pushButton_clicked()
{
    QString directorio = QFileDialog::getOpenFileName(this);
    ui->leTexto->setText(directorio);
    leerConfiguracion();
}


void Configuracion::on_leTexto_editingFinished()
{
    leerConfiguracion();
}


void Configuracion::on_pushButtonVideo_clicked()
{
    QString directorio = QFileDialog::getOpenFileName(this);
    ui->leComandoVideo->setText(directorio);
    leerConfiguracion();
}


void Configuracion::on_leComandoVideo_editingFinished()
{
    leerConfiguracion();
}

