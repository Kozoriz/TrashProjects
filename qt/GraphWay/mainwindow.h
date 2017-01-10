#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "hight_level/graphbuilder.h"
#include "hight_level/wayfinder.h"
#include "low_level/dataimporter.h"

namespace Ui {
class MainWindow;
}
class WayEndpointsChooseDialog;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  void UpdateGraphView(const std::string filename);

  void resizeEvent(QResizeEvent* event);
  void OnEndpointsChoosen(const QString& from, const QString& to);
 private slots:
  void Import();
  void GetWay();

 private:
  // View
  Ui::MainWindow* ui;

  // Model
  DataImporter* importer_;
  GraphBuilder* builder_;
  WayFinder* way_finder_;

  WayEndpointsChooseDialog* way_choose_dialog_;
};

#endif  // MAINWINDOW_H
