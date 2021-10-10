#include "consulta.h"
#include "ui_consulta.h"
#include <QDebug>
#include <QDate>
#include <QProcess>

Consulta::Consulta(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Consulta)
{
    ui->setupUi(this);
    pacienteId = 0;
    funcion.funcionaDB();
    configuracion.clear();
    //directorioTrabajo = funcion.getDirectorioTrabajo();
    cargarConfiguracion();
}

Consulta::~Consulta()
{
    delete ui;
}


void Consulta::on_pbPacientes_clicked()
{
    pacienteDlg = new Pacientes(this);
    if(pacienteDlg->exec()){
        pacienteId = pacienteDlg->pacienteId;
        qDebug() << pacienteId;
        rellenarDatosPaciente(pacienteId);
    }

    return;

}

void Consulta::rellenarDatosPaciente(int idPaciente)
{
    QStringList datosPaciente = funcion.datosPaciente(idPaciente);
    paciente = "";
    paciente = (datosPaciente.at(1)+" "+datosPaciente.at(2)+" "+datosPaciente.at(3)).simplified();
    ui->lNombre->setText(datosPaciente.at(1)+" "+datosPaciente.at(2)+" "+datosPaciente.at(3));
    qint64 edad = QDate::fromString(datosPaciente.at(11),"yyyy-MM-dd").daysTo(QDate::currentDate())/365;
    ui->lEdad->setText(QString::number(edad));
    llenarIris();
    llenarAnalisis();
    llenarInforme();
}

void Consulta::cargarConfiguracion()
{
    configuracion = funcion.getConfiguracion();
    directorioTrabajo = configuracion.at(1);
    appPdf = configuracion.at(2);
    appUrl = configuracion.at(3);
    appImagen = configuracion.at(4);
    appVideo = configuracion.at(5);
    qDebug() << configuracion;
}

void Consulta::llenarIris()
{
    ui->lvIris->clear();
    QDir directorioIris;
    directorioIris.setCurrent(directorioTrabajo+"/"+paciente+"/Iris");
      for(const QFileInfo finfo : directorioIris.entryList(QDir::Files)){
          ui->lvIris->addItem(finfo.fileName());
      }
}

void Consulta::llenarAnalisis()
{
    ui->lvAnalisis->clear();
    QDir directorioAnalisis;
    directorioAnalisis.setCurrent(directorioTrabajo+"/"+paciente+"/Analisis");
    for(const QFileInfo finfo : directorioAnalisis.entryList(QDir::Files)){
        ui->lvAnalisis->addItem(finfo.fileName());
    }

}

void Consulta::llenarInforme()
{
    ui->lvInformes->clear();
    QDir directorioInforme;
    directorioInforme.setCurrent(directorioTrabajo+"/"+paciente+"/Informes");
    for(const QFileInfo finfo : directorioInforme.entryList(QDir::Files)){
    ui->lvInformes->addItem(finfo.fileName());
    }
}


void Consulta::on_pbConfiguracion_clicked()
{
    confDlg = new Configuracion(configuracion,this);
    if (confDlg->exec() && confDlg->Accepted) {
        QStringList setConfiguracion = confDlg->configuracion;
        //setConfiguracion.removeAt(0);
        qDebug() << setConfiguracion;
    funcion.setConfiguracion(setConfiguracion);
    cargarConfiguracion();
    }
    directorioTrabajo = funcion.getDirectorioTrabajo();
}

;

void Consulta::on_lvIris_itemDoubleClicked(QListWidgetItem *item)
{
    QString ojo = directorioTrabajo+"/"+paciente+"/"+"Iris/"+item->text();
    QFileInfo info(ojo);
    if(info.completeSuffix() == "jpg" or info.completeSuffix() == "png"){
    QString programa = appImagen;
    QStringList arg;
    arg << ojo.toLocal8Bit().constData();
    QProcess *proc = new QProcess(this);
    proc->start(programa,arg);
    }
    if(info.completeSuffix() == "avi"){
        QString programa = appVideo;
        QStringList arg;
        arg << ojo.toLocal8Bit().constData();
        QProcess *proc = new QProcess(this);
        proc->start(programa,arg);
    }
}


void Consulta::on_lvAnalisis_itemDoubleClicked(QListWidgetItem *item)
{
    QString analisis = directorioTrabajo+"/"+paciente+"/"+"Analisis/"+item->text();
    QFileInfo info(analisis);
    if (info.completeSuffix() == "jpg" or info.completeSuffix() == "png") {
        QString programa = appImagen;
        QStringList arg;
        arg << analisis.toLocal8Bit().constData();
        QProcess *proc = new QProcess(this);
        proc->start(programa,arg);
    }
    if (info.completeSuffix() == "pdf") {
        QString programa = appPdf;
        QStringList arg;
        arg << analisis.toLocal8Bit().constData();
        QProcess *proc = new QProcess(this);
        proc->start(programa,arg);
    }
}


void Consulta::on_lvInformes_itemDoubleClicked(QListWidgetItem *item)
{
    QString informe = directorioTrabajo+"/"+paciente+"/"+"/Informes/"+item->text();
    QString programa = appPdf;
    QStringList arg;
    arg << informe.toLocal8Bit().constData();
    QProcess *proc = new QProcess(this);
    proc->start(programa,arg);

}


void Consulta::on_lvOtros_itemDoubleClicked(QListWidgetItem *item)
{

}

