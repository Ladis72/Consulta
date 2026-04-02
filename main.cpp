#include "conexion.h"
#include "consulta.h"

#include <QApplication>
#include <QFile>

#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile styleFile(":/style.qss");
  if (styleFile.open(QFile::ReadOnly)) {
    QString styleSheet = QLatin1String(styleFile.readAll());
    a.setStyleSheet(styleSheet);
  }

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "Consulta_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  Conexion *conn = new Conexion();
  conn->conectar();
  Consulta w;
  w.show();
  return a.exec();
}
