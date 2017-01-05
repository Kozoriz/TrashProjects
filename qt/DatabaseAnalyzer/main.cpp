#include <QApplication>
#include <QtWidgets/QWidget>

#include "logger.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
  LOG_MESSAGE("START");
  QApplication app(argc, argv);

  QWidget* widget = new MainWindow;
  widget->show();

  app.installEventFilter(widget);

  return app.exec();
}
