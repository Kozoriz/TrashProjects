#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class FilterDialog;
}
class MainWindow;

class FilterDialog : public QDialog {
  Q_OBJECT

 public:
  explicit FilterDialog(const QStringList& fields, QWidget* parent);
  ~FilterDialog();

 private slots:
  void OnAccepted();

 private:
  Ui::FilterDialog* ui;
  MainWindow* parent_;
  QList<QLineEdit*> added_buttons;
};

#endif  // FILTERDIALOG_H
