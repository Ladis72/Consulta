#ifndef LOGGIN_H
#define LOGGIN_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Loggin;
}

class Loggin : public QDialog
{
    Q_OBJECT

public:
    explicit Loggin(QWidget *parent = nullptr);
    ~Loggin();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Loggin *ui;
    QSettings configDb;
};

#endif // LOGGIN_H
