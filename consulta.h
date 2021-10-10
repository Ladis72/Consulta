#ifndef CONSULTA_H
#define CONSULTA_H

#include "dbfunc.h"
#include "conexion.h"
#include "pacientes.h"
#include "configuracion.h"
#include <QMainWindow>
#include <QFileSystemModel>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Consulta; }
QT_END_NAMESPACE

class Consulta : public QMainWindow
{
    Q_OBJECT

public:
    Consulta(QWidget *parent = nullptr);
    ~Consulta();

private slots:
    void on_pbPacientes_clicked();

    void on_pbConfiguracion_clicked();

    void on_lvIris_itemDoubleClicked(QListWidgetItem *item);

    void on_lvAnalisis_doubleClicked(const QModelIndex &index);

    void on_lvAnalisis_itemDoubleClicked(QListWidgetItem *item);

    void on_lvInformes_itemDoubleClicked(QListWidgetItem *item);

    void on_lvOtros_itemDoubleClicked(QListWidgetItem *item);

private:
    void rellenarDatosPaciente(int idPaciente);
    void cargarConfiguracion();
    void llenarIris();
    void llenarAnalisis();
    void llenarInforme();

    Ui::Consulta *ui;
    Conexion *conexion;
    dbFunc funcion;
    Pacientes *pacienteDlg;
    Configuracion *confDlg;
    int pacienteId;
    QString paciente;
    QString directorioTrabajo;
    QString appPdf;
    QString appUrl;
    QString appImagen;
    QString appVideo;
    QStringList configuracion;
    QFileSystemModel *dirIris;
};
#endif // CONSULTA_H
