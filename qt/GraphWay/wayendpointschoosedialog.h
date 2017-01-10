#ifndef WAYENDPOINTSCHOOSEDIALOG_H
#define WAYENDPOINTSCHOOSEDIALOG_H

#include <QDialog>

namespace Ui {
class WayEndpointsChooseDialog;
}
class MainWindow;

class WayEndpointsChooseDialog : public QDialog {
  Q_OBJECT

 public:
  explicit WayEndpointsChooseDialog(QStringList& list, QWidget* parent);
  ~WayEndpointsChooseDialog();

  void EnableEditing();
 private slots:
  void OnAccepted();

 private:
  Ui::WayEndpointsChooseDialog* ui;

  MainWindow* parent_;
  QStringList variants_;
};

#endif  // WAYENDPOINTSCHOOSEDIALOG_H
