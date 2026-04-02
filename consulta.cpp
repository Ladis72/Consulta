#include "consulta.h"
#include "ui_consulta.h"
#include <QColorDialog>
#include <QDate>
#include <QDebug>
#include <QDesktopServices>
#include <QFont>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QProcess>
#include <QShortcut>
#include <QToolBar>

Consulta::Consulta(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Consulta) {
  ui->setupUi(this);
  pacienteId = 0;
  idVisita = 0;
  funcion.funcionaDB();
  configuracion.clear();
  cargarConfiguracion();
  // QAction *accionGuardar = new QAction(this);
  // accionGuardar->setShortcut(QKeySequence("Ctrl+s"));
  // connect(accionGuardar, , this, &Consulta::on_pbGuardar_clicked);
  // this->addAction(accionGuardar);

  QShortcut *atajo = new QShortcut(QKeySequence("Ctrl+s"), this);
  connect(atajo, &QShortcut::activated, ui->pbGuardar, &QPushButton::click);

  ui->twVisitas->resizeColumnsToContents();
  ui->twVisitas->verticalHeader()->setDefaultSectionSize(40);
  ui->tWHistoricoDatos->verticalHeader()->setDefaultSectionSize(40);
  ui->twVisitas->setAlternatingRowColors(true);
  ui->tWHistoricoDatos->setAlternatingRowColors(true);

  // Rich Text Editor Toolbar for Notes
  QHBoxLayout *toolbarLayout = new QHBoxLayout();
  QPushButton *btnBold = new QPushButton("B", this);
  btnBold->setFixedWidth(30);
  btnBold->setStyleSheet("font-weight: bold; background-color: #f0f0f0; color: "
                         "black; border-radius: 4px;");

  QPushButton *btnItalic = new QPushButton("I", this);
  btnItalic->setFixedWidth(30);
  btnItalic->setStyleSheet("font-style: italic; background-color: #f0f0f0; "
                           "color: black; border-radius: 4px;");

  QPushButton *btnColor = new QPushButton("C", this);
  btnColor->setFixedWidth(30);
  btnColor->setStyleSheet(
      "color: red; background-color: #f0f0f0; border-radius: 4px;");

  toolbarLayout->addWidget(btnBold);
  toolbarLayout->addWidget(btnItalic);
  toolbarLayout->addWidget(btnColor);
  toolbarLayout->addStretch();

  // Find the layout containing teNotaPaciente or add it above
  // Assuming it's in a grid layout in tabDatosBasicos
  ui->gridLayout_13->addLayout(toolbarLayout, 3, 0);
  // Need to adjust save logic to use toHtml() if necessary, but keep it simple
  // for now

  connect(btnBold, &QPushButton::clicked, [this]() {
    QTextCharFormat format;
    format.setFontWeight(ui->teNotaPaciente->fontWeight() == QFont::Bold
                             ? QFont::Normal
                             : QFont::Bold);
    ui->teNotaPaciente->mergeCurrentCharFormat(format);
  });

  connect(btnItalic, &QPushButton::clicked, [this]() {
    QTextCharFormat format;
    format.setFontItalic(!ui->teNotaPaciente->fontItalic());
    ui->teNotaPaciente->mergeCurrentCharFormat(format);
  });

  connect(btnColor, &QPushButton::clicked, [this]() {
    QColor col = QColorDialog::getColor(ui->teNotaPaciente->textColor(), this);
    if (col.isValid()) {
      ui->teNotaPaciente->setTextColor(col);
    }
  });

  // llenarHistoricoDatos();
}

Consulta::~Consulta() { delete ui; }

void Consulta::on_pbPacientes_clicked() {
  pacienteDlg = new Pacientes(this);
  if (pacienteDlg->exec()) {
    pacienteId = pacienteDlg->pacienteId;
    qDebug() << pacienteId;
    llenarHistoricoDatos();
    rellenarDatosPaciente(pacienteId);
    idVisita = 0;
  }

  return;
}

void Consulta::llenarHistoricoDatos() {
  historicoDatos = funcion.llenarHistoricoDatos(pacienteId);
  ui->tWHistoricoDatos->setModel(historicoDatos);
  ui->tWHistoricoDatos->hideColumn(0);
  ui->tWHistoricoDatos->hideColumn(1);
  for (int i = 10; i < 14; i++) {
    ui->tWHistoricoDatos->hideColumn(i);
  }
  ui->twVisitas->setModel(historicoDatos);
  ui->twVisitas->hideColumn(0);
  ui->twVisitas->hideColumn(1);
  for (int i = 3; i < 10; i++) {
    ui->twVisitas->hideColumn(i);
  }
  ui->twVisitas->resizeColumnsToContents();
  ui->tWHistoricoDatos->resizeColumnsToContents();
}

void Consulta::rellenarDatosPaciente(int idPaciente) {
  QStringList datosPaciente = funcion.datosPaciente(idPaciente);
  paciente = "";
  paciente = (datosPaciente.at(1) + " " + datosPaciente.at(2) + " " +
              datosPaciente.at(3))
                 .simplified();
  ui->lNombre->setText(datosPaciente.at(1) + " " + datosPaciente.at(2) + " " +
                       datosPaciente.at(3));
  qint64 edad = QDate::fromString(datosPaciente.at(11), "yyyy-MM-dd")
                    .daysTo(QDate::currentDate()) /
                365;
  ui->lEdad->setText(QString::number(edad));
  ui->lOtrosDatos->setText(datosPaciente.at(5) + "  " + datosPaciente.at(6) +
                           "  " + datosPaciente.at(10));
  ui->labelTelefono->setText(datosPaciente.at(8));
  ui->teNotaPaciente->setText(datosPaciente.at(17));
  ui->label->clear();
  QFile foto(directorioTrabajo + "/" + paciente + "/XFoto.png");
  if (foto.exists()) {
    QPixmap pixmap(foto.fileName());
    ui->label->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
  }
  llenarIris();
  llenarAnalisis();
  llenarInforme();
  llenarOtros();
  historicoDatos->setFilter("idPaciente = '" + QString::number(pacienteId) +
                            "'");
  ui->tWHistoricoDatos->resizeColumnsToContents();
  ui->twVisitas->resizeColumnsToContents();
}

void Consulta::cargarConfiguracion() {
  configuracion = funcion.getConfiguracion();
  directorioTrabajo = configuracion.at(1);
  appPdf = configuracion.at(2);
  appUrl = configuracion.at(3);
  appImagen = configuracion.at(4);
  appVideo = configuracion.at(5);
  appTexto = configuracion.at(6);
  comandoVideo = configuracion.at(7);
  qDebug() << configuracion;
}

void Consulta::llenarIris() {
  ui->lvIris->clear();
  QDir directorioIris(directorioTrabajo + "/" + paciente + "/Iris");
  QStringList elementos =
      directorioIris.entryList(QStringList() << "*.*", QDir::Files);
  ui->lvIris->addItems(elementos);
  ui->lvIris->sortItems(Qt::DescendingOrder);
}

void Consulta::llenarAnalisis() {
  ui->lvAnalisis->clear();
  QDir directorioAnalisis(directorioTrabajo + "/" + paciente + "/Analisis");
  QStringList elementos =
      directorioAnalisis.entryList(QStringList() << "*.*", QDir::Files);
  ui->lvAnalisis->addItems(elementos);
  ui->lvIris->sortItems(Qt::DescendingOrder);
}

void Consulta::llenarInforme() {
  ui->lvInformes->clear();
  QDir directorioInforme(directorioTrabajo + "/" + paciente + "/Informes");
  QStringList elementos =
      directorioInforme.entryList(QStringList() << "*.*", QDir::Files);
  ui->lvInformes->addItems(elementos);
  ui->lvInformes->sortItems(Qt::DescendingOrder);
}

void Consulta::llenarOtros() {
  ui->lvOtros->clear();
  QDir directorioOtros(directorioTrabajo + "/" + paciente);
  QStringList elementos =
      directorioOtros.entryList(QStringList() << "*.*", QDir::Files);
  ui->lvOtros->addItems(elementos);
  ui->lvIris->sortItems(Qt::DescendingOrder);
}

void Consulta::on_pbConfiguracion_clicked() {
  confDlg = new Configuracion(configuracion, this);
  if (confDlg->exec() && confDlg->Accepted) {
    QStringList setConfiguracion = confDlg->configuracion;
    // setConfiguracion.removeAt(0);
    qDebug() << setConfiguracion;
    funcion.setConfiguracion(setConfiguracion);
    cargarConfiguracion();
  }
  directorioTrabajo = funcion.getDirectorioTrabajo();
}

;

void Consulta::on_lvIris_itemDoubleClicked(QListWidgetItem *item) {
  QString ojo =
      directorioTrabajo + "/" + paciente + "/" + "Iris/" + item->text();
  //    QFileInfo info(ojo);
  //    if(info.completeSuffix() == "jpg" or info.completeSuffix() == "png"){
  //    QString programa = appImagen;
  //    QStringList arg;
  //    arg << ojo.toLocal8Bit().constData();
  //    QDesktopServices::openUrl(QUrl::fromLocalFile(ojo));

  //    QProcess *proc = new QProcess(this);
  //    proc->start(programa,arg);
  //    }
  //    if(info.completeSuffix() == "avi"){
  //        QString programa = appVideo;
  //        QStringList arg;
  //        arg << ojo.toLocal8Bit().constData();
  //        qDebug() << programa;
  //        qDebug() << arg;
  QDesktopServices::openUrl(QUrl::fromLocalFile(ojo));

  //        QProcess *proc = new QProcess(this);
  //        proc->start(programa,arg);
  //    }
}

void Consulta::on_lvAnalisis_itemDoubleClicked(QListWidgetItem *item) {
  QString analisis =
      directorioTrabajo + "/" + paciente + "/" + "Analisis/" + item->text();
  //    QFileInfo info(analisis);
  //    if (info.completeSuffix() == "jpg" or info.completeSuffix() == "png") {
  //        QString programa = appImagen;
  //        QStringList arg;
  //        arg << analisis.toLocal8Bit().constData();
  //        QProcess *proc = new QProcess(this);
  //        proc->start(programa,arg);
  //    }
  //    if (info.completeSuffix() == "pdf") {
  //        QString programa = appPdf;
  //        QStringList arg;
  //        arg << analisis.toLocal8Bit().constData();
  //        QProcess *proc = new QProcess(this);
  //        proc->start(programa,arg);
  //    }
  QDesktopServices::openUrl(QUrl::fromLocalFile(analisis));
}

void Consulta::on_lvInformes_itemDoubleClicked(QListWidgetItem *item) {
  QString informe =
      directorioTrabajo + "/" + paciente + "/" + "/Informes/" + item->text();
  //    QString programa = appPdf;
  //    QStringList arg;
  //    arg << informe.toLocal8Bit().constData();
  //    QProcess *proc = new QProcess(this);
  //    proc->start(programa,arg);
  QDesktopServices::openUrl(QUrl::fromLocalFile(informe));
}

void Consulta::on_lvOtros_itemDoubleClicked(QListWidgetItem *item) {
  QString otros = directorioTrabajo + "/" + paciente + "/" + item->text();
  //    QFileInfo info(otros);
  //    if (info.completeSuffix() == "jpg" or info.completeSuffix() == "png") {
  //        QString programa = appImagen;
  //        QStringList arg;
  //        arg << otros.toLocal8Bit().constData();
  //        QProcess *proc = new QProcess(this);
  //        proc->start(programa,arg);
  //    }
  //    if (info.completeSuffix() == "pdf") {
  //        QString programa = appPdf;
  //        QStringList arg;
  //        arg << otros.toLocal8Bit().constData();
  //        QProcess *proc = new QProcess(this);
  //        proc->start(programa,arg);
  //    }
  //    if (info.completeSuffix() == "txt") {
  //        QString programa = appTexto;
  //        QStringList arg;
  //        arg << otros.toLocal8Bit().constData();
  //        QProcess *proc = new QProcess(this);
  //        proc->start(programa, arg);
  //    }
  QDesktopServices::openUrl(QUrl::fromLocalFile(otros));
}

void Consulta::on_pbGuardar_clicked() {
  if (pacienteId == 0) {
    return;
  }
  qDebug() << (funcion.guardarDatosPaciente(pacienteId,
                                            ui->teNotaPaciente->toHtml())
                   ? "Guardado"
                   : "No guardado");
}

void Consulta::on_pbCapurarIris_clicked() {
  if (pacienteId == 0) {
    QMessageBox::warning(this, "Seleccione paciente",
                         "Debe seleccionar un paciente para capturar vídeo.");
    return;
  }

  QString subDir = directorioTrabajo + "/" + paciente + "/Iris";
  QDir dir;
  if (!dir.exists(subDir)) {
    dir.mkpath(subDir);
  }

  QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
  QString filename = subDir + "/Iris_" + timestamp + ".mpg";

  QString comando = comandoVideo;
  if (comando.contains("%1")) {
    comando = comando.arg(filename);
  } else {
    // Fallback or warning if %1 is not present
    qDebug() << "Warning: comandoVideo does not contain %1 placeholder";
  }

  QProcess *proc = new QProcess(this);
  QString fullCommand = appVideo + " " + comando;

  qDebug() << "Ejecutando via shell:" << fullCommand;
  proc->start("/bin/sh", QStringList() << "-c" << fullCommand);
}

void Consulta::on_pbTomarDatos_clicked() {
  if (pacienteId == 0) {
    QMessageBox::information(
        this, "Seleccione paciente",
        "Debe seleccionar un paciente al que asignarle los datos");
    return;
  }
  QStringList datosHoy;
  datosHoy.clear();
  datosDlg = new tomarDatos(this);
  if (datosDlg->exec() && datosDlg->Accepted) {
    datosHoy << QString::number(pacienteId);
    datosHoy << datosDlg->datos;
    qDebug() << datosHoy;
    funcion.guardarDatosHoy(datosHoy);
  }
  historicoDatos->setFilter("idPaciente = '" + QString::number(pacienteId) +
                            "'");
  ui->tWHistoricoDatos->resizeColumnsToContents();
  ui->twVisitas->resizeColumnsToContents();
  idVisita = funcion.idVisitaActual(pacienteId);
}

void Consulta::on_tWHistoricoDatos_doubleClicked(const QModelIndex &index) {
  qDebug() << pacienteId;
  qDebug() << idVisita;
}

void Consulta::on_twVisitas_clicked(const QModelIndex &index) {
  ui->twVisitas->resizeColumnsToContents();
}
