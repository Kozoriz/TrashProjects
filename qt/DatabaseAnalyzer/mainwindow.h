#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include "hight_level/databaseanalyzer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
  void OnFilterGenerated(const QMap<QString, QString>& q_filter);

 private slots:
  void Import();
  void Export();
  void Filter();
  void Report();
  void ShowErrors();
  void OnCellChanged(int row, int column);

 private:
  Ui::MainWindow* ui;
  DatabaseAnalyzer analyzer_;
  void FillUITable(QTableWidget* ui_table, const Table& data_table);
};

#endif  // MAINWINDOW_H
