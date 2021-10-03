#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <QDialog>

namespace Ui {
class Configuracion;
}

class Configuracion : public QDialog
{
    Q_OBJECT

public:
    explicit Configuracion(QStringList directorio, QWidget *parent = nullptr);
    ~Configuracion();
    QStringList configuracion;

private slots:

    void leerConfiguracion();
    void on_pbDirectorioTrabajo_clicked();

    void on_pbPdf_clicked();

    void on_pbUrl_clicked();

    void on_pbImagen_clicked();

    void on_pbVideo_clicked();

    void on_leDirectorioTrabajo_editingFinished();

    void on_lePdf_editingFinished();

    void on_leUrl_editingFinished();

    void on_leImagen_editingFinished();

    void on_leVideo_editingFinished();

private:
    Ui::Configuracion *ui;
    void rellenarCampos();

};

#endif // CONFIGURACION_H
