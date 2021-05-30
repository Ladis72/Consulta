#include "consulta.h"
#include "ui_consulta.h"

Consulta::Consulta(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Consulta)
{
    ui->setupUi(this);

    funcion.funcionaDB();
}

Consulta::~Consulta()
{
    delete ui;
}

