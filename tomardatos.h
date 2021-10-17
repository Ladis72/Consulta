#ifndef TOMARDATOS_H
#define TOMARDATOS_H

#include <QDialog>

namespace Ui {
class tomarDatos;
}

class tomarDatos : public QDialog
{
    Q_OBJECT

public:
    explicit tomarDatos(QWidget *parent = nullptr);
    ~tomarDatos();
    QStringList datos;

private slots:
    void on_lePeso_editingFinished();

    void on_leAltura_editingFinished();

    void on_leSist_editingFinished();

    void on_leDiast_editingFinished();

    void on_lePulso_editingFinished();

    void on_leEstomago_editingFinished();

private:
    Ui::tomarDatos *ui;
    void llenarDatos();
};

#endif // TOMARDATOS_H
