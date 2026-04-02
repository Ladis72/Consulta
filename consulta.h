#ifndef CONSULTA_H
#define CONSULTA_H

#include "conexion.h"
#include "configuracion.h"
#include "dbfunc.h"
#include "pacientes.h"
#include "tomardatos.h"
#include <QFileSystemModel>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class Consulta;
}
QT_END_NAMESPACE

class Consulta : public QMainWindow {
  Q_OBJECT

public:
  Consulta(QWidget *parent = nullptr);
  ~Consulta();

private slots:
  void on_pbPacientes_clicked();

  void on_pbConfiguracion_clicked();

  void on_lvIris_itemDoubleClicked(QListWidgetItem *item);

  void on_lvAnalisis_itemDoubleClicked(QListWidgetItem *item);

  void on_lvInformes_itemDoubleClicked(QListWidgetItem *item);

  void on_lvOtros_itemDoubleClicked(QListWidgetItem *item);

  void on_pbGuardar_clicked();

  void on_pbCapurarIris_clicked();

  void on_pbTomarDatos_clicked();

  void on_tWHistoricoDatos_doubleClicked(const QModelIndex &index);

  void on_twVisitas_clicked(const QModelIndex &index);

  void onVlcFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
  void rellenarDatosPaciente(int idPaciente);
  void cargarConfiguracion();
  void llenarIris();
  void llenarAnalisis();
  void llenarInforme();
  void llenarOtros();
  void llenarHistoricoDatos();
  void renombrarUltimoArchivo(QString directorio, QString paciente);

  Ui::Consulta *ui;
  Conexion *conexion;
  dbFunc funcion;
  Pacientes *pacienteDlg;
  Configuracion *confDlg;
  tomarDatos *datosDlg;
  int pacienteId;
  int idVisita;
  QString paciente;
  QString directorioTrabajo;
  QString appPdf;
  QString appUrl;
  QString appImagen;
  QString appVideo;
  QString appTexto;
  QString comandoVideo;
  QStringList configuracion;
  QSqlTableModel *historicoDatos;
  QString irisPath;
  QString pacienteActual;
  // QFileSystemModel *dirIris;
};
#endif // CONSULTA_H
