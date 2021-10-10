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
    ui->teNotaPaciente->setText(datosPaciente.at(17));
    QFile foto(directorioTrabajo+"/"+paciente+"/Foto.png");
    if (foto.exists()) {
        QPixmap pixmap(foto.fileName());
        ui->label->setPixmap(pixmap.scaled(200,200,Qt::KeepAspectRatio));
    }
    llenarIris();
    llenarAnalisis();
    llenarInforme();
    llenarOtros();

}

void Consulta::cargarConfiguracion()
{
    configuracion = funcion.getConfiguracion();
    directorioTrabajo = configuracion.at(1);
    appPdf = configuracion.at(2);
    appUrl = configuracion.at(3);
    appImagen = configuracion.at(4);
    appVideo = configuracion.at(5);
    appTexto = configuracion.at(6);
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
      ui->lvIris->sortItems(Qt::DescendingOrder);
}

void Consulta::llenarAnalisis()
{
    ui->lvAnalisis->clear();
    QDir directorioAnalisis;
    directorioAnalisis.setCurrent(directorioTrabajo+"/"+paciente+"/Analisis");
    for(const QFileInfo finfo : directorioAnalisis.entryList(QDir::Files)){
        ui->lvAnalisis->addItem(finfo.fileName());
    }
    ui->lvAnalisis->sortItems(Qt::DescendingOrder);
}

void Consulta::llenarInforme()
{
    ui->lvInformes->clear();
    QDir directorioInforme;
    directorioInforme.setCurrent(directorioTrabajo+"/"+paciente+"/Informes");
    for(const QFileInfo finfo : directorioInforme.entryList(QDir::Files)){
    ui->lvInformes->addItem(finfo.fileName());
    }
    ui->lvInformes->sortItems(Qt::DescendingOrder);
}

void Consulta::llenarOtros()
{
    ui->lvOtros->clear();
    QDir directorioOtros;
    directorioOtros.setCurrent(directorioTrabajo+"/"+paciente);
    qDebug() << directorioOtros;
    for(const QFileInfo finfo : directorioOtros.entryInfoList(QDir::Files)){
        ui->lvOtros->addItem(finfo.fileName());
    }
    ui->lvOtros->sortItems(Qt::DescendingOrder);
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
    QString otros = directorioTrabajo+"/"+paciente+"/"+item->text();
    QFileInfo info(otros);
    if (info.completeSuffix() == "jpg" or info.completeSuffix() == "png") {
        QString programa = appImagen;
        QStringList arg;
        arg << otros.toLocal8Bit().constData();
        QProcess *proc = new QProcess(this);
        proc->start(programa,arg);
    }
    if (info.completeSuffix() == "pdf") {
        QString programa = appPdf;
        QStringList arg;
        arg << otros.toLocal8Bit().constData();
        QProcess *proc = new QProcess(this);
        proc->start(programa,arg);
    }
    if (info.completeSuffix() == "txt") {
        QString programa = appTexto;
        QStringList arg;
        arg << otros.toLocal8Bit().constData();
        QProcess *proc = new QProcess(this);
        proc->start(programa, arg);
    }
}


void Consulta::on_pbGuardar_clicked()
{
    if (pacienteId==0) {
        return;
    }
    qDebug() << (funcion.guardarDatosPaciente(pacienteId,ui->teNotaPaciente->toPlainText()) ? "Guardado" : "No guardado");
}


void Consulta::on_pbCapurarIris_clicked()
{
    QProcess *proc = new QProcess(this);
    QStringList arg;
//    arg << "v4l2:///dev/video0 --sout #transcode{vcodec=mp1v,vb=1024,scale=1,acodec=mpga,ab=192,channels=2}:duplicate{dst=std{access=file,mux=mpeg1,dst="+directorioTrabajo+"/"+paciente+"/tmp/test.mpg}}" ;
    arg << "v4l2:///dev/video0" << " --sout=#transcode{vcodec=mp1v,vb=1024,scale=1,acodec=mpga,ab=192,channels=2}" << " --duplicate{dst=std{access=file,mux=mpeg1,dst="+directorioTrabajo+"/"+paciente+"/test.mpg}}" ;
    proc->start(appVideo,arg);
}

