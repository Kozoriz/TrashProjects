#include "filterdialog.h"
#include "mainwindow.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(const QStringList& fields, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::FilterDialog)
    , parent_(static_cast<MainWindow*>(parent)) {
  ui->setupUi(this);

  QVBoxLayout* layout = ui->verticalLayout;

  for (int i = 0; i < fields.size(); ++i) {
    QLineEdit* text_field = new QLineEdit;
    text_field->setPlaceholderText(fields[i]);
    added_buttons.append(text_field);
    layout->addWidget(text_field);
  }

  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OnAccepted()));
}

FilterDialog::~FilterDialog() {
  delete ui;
}

void FilterDialog::OnAccepted() {
  QMap<QString, QString> filter;
  for (int i = 0; i < added_buttons.size(); ++i) {
    const QString& placeHolder = added_buttons[i]->placeholderText();
    const QString& data = added_buttons[i]->text();
    if (data.size() > 0) {
      filter.insert(placeHolder, data);
    }
  }
  parent_->OnFilterGenerated(filter);
}
