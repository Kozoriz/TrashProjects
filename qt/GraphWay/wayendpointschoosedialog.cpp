#include "wayendpointschoosedialog.h"
#include "mainwindow.h"
#include "ui_wayendpointschoosedialog.h"

WayEndpointsChooseDialog::WayEndpointsChooseDialog(QStringList& list,
                                                   QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::WayEndpointsChooseDialog)
    , parent_(static_cast<MainWindow*>(parent))
    , variants_(list) {
  ui->setupUi(this);

  ui->comboBoxFrom->addItems(list);
  ui->comboBoxTo->addItems(list);

  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OnAccepted()));

  ui->buttonBox->setEnabled(false);
  ui->comboBoxFrom->setEnabled(false);
  ui->comboBoxTo->setEnabled(false);
  ui->label->setEnabled(false);
  ui->label_2->setEnabled(false);
}

WayEndpointsChooseDialog::~WayEndpointsChooseDialog() {
  delete ui;
}

void WayEndpointsChooseDialog::EnableEditing() {
  ui->buttonBox->setEnabled(true);
  ui->comboBoxFrom->setEnabled(true);
  ui->comboBoxTo->setEnabled(true);
  ui->label->setEnabled(true);
  ui->label_2->setEnabled(true);

  ui->label_3->setHidden(true);
}

void WayEndpointsChooseDialog::OnAccepted() {
  QString from = ui->comboBoxFrom->currentText();
  QString to = ui->comboBoxTo->currentText();
  parent_->OnEndpointsChoosen(from, to);
}
