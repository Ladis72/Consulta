#ifndef CONSULTA_H
#define CONSULTA_H

#include "dbfunc.h"
#include "conexion.h"
#include "pacientes.h"
#include "configuracion.h"
#include "tomardatos.h"
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

    void on_lvAnalisis_itemDoubleClicked(QListWidgetItem *item);

    void on_lvInformes_itemDoubleClicked(QListWidgetItem *item);

    void on_lvOtros_itemDoubleClicked(QListWidgetItem *item);

    void on_pbGuardar_clicked();

    void on_pbCapurarIris_clicked();

    void on_pbTomarDatos_clicked();

    void on_tWHistoricoDatos_doubleClicked(const QModelIndex &index);

    void on_twVisitas_clicked(const QModelIndex &index);


private:
    void rellenarDatosPaciente(int idPaciente);
    void cargarConfiguracion();
    void llenarIris();
    void llenarAnalisis();
    void llenarInforme();
    void llenarOtros();
    void llenarHistoricoDatos();

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
    QStringList configuracion;
    QSqlTableModel *historicoDatos;
    //QFileSystemModel *dirIris;
};
#endif // CONSULTA_H
