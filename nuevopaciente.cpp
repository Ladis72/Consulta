#include "nuevopaciente.h"
#include "ui_nuevopaciente.h"
#include <QDebug>
#include <QFileSystemModel>

NuevoPaciente::NuevoPaciente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoPaciente)
{
    ui->setupUi(this);
    idPaciente=0;
}

NuevoPaciente::NuevoPaciente(int idP, QWidget *parent) :
    QDialog(parent),ui(new Ui::NuevoPaciente)
{
    ui->setupUi(this);
    idPaciente = idP;
    datosPaciente = funcion->datosPaciente(idPaciente);
    llenarFormulario(datosPaciente);
}

NuevoPaciente::~NuevoPaciente()
{
    delete ui;
}

void NuevoPaciente::on_pbAceptar_clicked()
{
    recogerDatosFormulario();
    if (idPaciente == 0){
    if(funcion->grabarPaciente(datosPaciente) == true){
        qDebug() << "Paciente grabado";
        QFileSystemModel *modeloDirectorio = new QFileSystemModel;
        QString directorio = (datosPaciente.at(0)+" "+datosPaciente.at(1)+" "+datosPaciente.at(2)).simplified();
        qDebug() << directorio;
        modeloDirectorio->mkdir(modeloDirectorio->setRootPath(funcion->getDirectorioTrabajo()),directorio);
        modeloDirectorio->mkdir(modeloDirectorio->setRootPath(funcion->getDirectorioTrabajo()+"/"+directorio),"Iris");
        modeloDirectorio->mkdir(modeloDirectorio->setRootPath(funcion->getDirectorioTrabajo()+"/"+directorio),"Analisis");
        modeloDirectorio->mkdir(modeloDirectorio->setRootPath(funcion->getDirectorioTrabajo()+"/"+directorio),"Informes");

    }else {
        qDebug() << "Error al grabar";
        }
    return;
    }else {
        if(funcion->modificarPaciente(idPaciente,datosPaciente) == true){
            qDebug() << "Paciente modificado";
        }else {
            qDebug() << "Error al modificar";
            }
        return;
}

}

QStringList NuevoPaciente::recogerDatosFormulario()
{
    datosPaciente.clear();
    datosPaciente.append(ui->leNombre->text());
    datosPaciente.append(ui->leApellido1->text());
    datosPaciente.append(ui->leApellido2->text());
    datosPaciente.append(ui->leDNI->text());
    datosPaciente.append(ui->leLocalidad->text());
    datosPaciente.append(ui->leProvincia->text());
    datosPaciente.append(ui->leCP->text());
    datosPaciente.append(ui->leTlfn->text());
    datosPaciente.append(ui->leMail->text());
    datosPaciente.append(ui->leProfesion->text());
    datosPaciente.append(ui->deNacimiento->date().toString("yyyy-MM-dd"));
    if (ui->cbSexo->currentText() == "Masculino") {
        datosPaciente.append("M");
    }else{
        datosPaciente.append("F");
    }
    if (ui->cbECivil->currentText() == "Soltero/a") {
        datosPaciente.append("S");
    }
    if (ui->cbECivil->currentText() == "Casado/a") {
        datosPaciente.append("C");
    }
    if (ui->cbECivil->currentText() == "Divorciado/a") {
        datosPaciente.append("D");
    }if (ui->cbECivil->currentText() == "Viudo/a") {
        datosPaciente.append("V");
    }if (ui->cbECivil->currentText() == "Separado/a") {
        datosPaciente.append("SE");
    }if (ui->cbECivil->currentText() == "En pareja") {
        datosPaciente.append("P");
    }
    datosPaciente.append(ui->sbHijos->text());
    datosPaciente.append(ui->cbGrupoSanguineo->currentText());
    datosPaciente.append(ui->cbRH->currentText());
    datosPaciente.append(ui->textEdit->toPlainText());

    qDebug() << datosPaciente;
    return datosPaciente;
}

void NuevoPaciente::llenarFormulario(QStringList datosPaciente)
{
    ui->leNombre->setText(datosPaciente.at(1));
    ui->leApellido1->setText(datosPaciente.at(2));
    ui->leApellido2->setText(datosPaciente.at(3));
    ui->leDNI->setText(datosPaciente.at(4));
    ui->leLocalidad->setText(datosPaciente.at(5));
    ui->leProvincia->setText(datosPaciente.at(6));
    ui->leCP->setText(datosPaciente.at(7));
    ui->leTlfn->setText(datosPaciente.at(8));
    ui->leMail->setText(datosPaciente.at(9));
    ui->leProfesion->setText(datosPaciente.at(10));
    ui->deNacimiento->setDate(QDate::fromString(datosPaciente.at(11),"yyyy-MM-dd"));
    if (datosPaciente.at(12) == "M") {
        ui->cbSexo->setCurrentIndex(0);
    } else {ui->cbSexo->setCurrentIndex(1);
    }
    if (datosPaciente.at(13) == "S") {
        ui->cbECivil->setCurrentIndex(0);
    }if (datosPaciente.at(13) == "C") {
        ui->cbECivil->setCurrentIndex(1);
    }if (datosPaciente.at(13) == "D") {
        ui->cbECivil->setCurrentIndex(2);
    }if (datosPaciente.at(13) == "V") {
        ui->cbECivil->setCurrentIndex(3);
    }if (datosPaciente.at(13) == "SE") {
        ui->cbECivil->setCurrentIndex(4);
    }if (datosPaciente.at(13) == "P") {
         ui->cbECivil->setCurrentIndex(5);
    }
    ui->sbHijos->setValue(datosPaciente.at(14).toInt());
    if (datosPaciente.at(15) == "A") {
        ui->cbGrupoSanguineo->setCurrentIndex(1);
    }
    if (datosPaciente.at(15) == "B") {
        ui->cbGrupoSanguineo->setCurrentIndex(1);
    }
    if (datosPaciente.at(15) == "AB") {
        ui->cbGrupoSanguineo->setCurrentIndex(2);
    }
    if (datosPaciente.at(15) == "0") {
        ui->cbGrupoSanguineo->setCurrentIndex(3);
    }
    if (datosPaciente.at(15) == "NS") {
        ui->cbGrupoSanguineo->setCurrentIndex(0);
    }
    if (datosPaciente.at(16) == "NS") {
        ui->cbRH->setCurrentIndex(0);
    }
    if (datosPaciente.at(16) == "+") {
        ui->cbRH->setCurrentIndex(1);
    }
    if (datosPaciente.at(16) == "-") {
        ui->cbRH->setCurrentIndex(2);
    }
    ui->textEdit->setText(datosPaciente.at(17));
}

