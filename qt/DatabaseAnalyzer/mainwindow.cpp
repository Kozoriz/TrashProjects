#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "filterdialog.h"
#include "hight_level/databasereporter.h"
#include "logger.h"

namespace {
typedef std::map<std::string, std::string> Filter;

QStringList StdToQtStringArray(const std::vector<std::string>& keys) {
  QStringList list;
  for (size_t i = 0; i < keys.size(); ++i) {
    list << keys[i].c_str();
  }
  return list;
}

Filter QMapToFilter(const QMap<QString, QString>& q_filter) {
  Filter filter;
  QList<QString> keys = q_filter.keys();
  for (int i = 0; i < keys.size(); ++i) {
    std::pair<std::string, std::string> pair;
    pair.first = keys[i].toStdString();
    pair.second = q_filter[keys[i]].toStdString();
    filter.insert(pair);
  }
  return filter;
}
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(Import()));
  connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(Export()));
  connect(ui->actionFilter, SIGNAL(triggered()), this, SLOT(Filter()));
  connect(ui->actionGenerate_Repor, SIGNAL(triggered()), this, SLOT(Report()));
  connect(ui->actionShowErrors, SIGNAL(triggered()), this, SLOT(ShowErrors()));
  connect(ui->tableWidget,
          SIGNAL(cellChanged(int, int)),
          this,
          SLOT(OnCellChanged(int, int)));

  ui->actionFilter->setEnabled(false);
  ui->actionSave->setEnabled(false);
  ui->actionGenerate_Repor->setEnabled(false);
  ui->actionShowErrors->setEnabled(false);


  /// NEW
  const std::vector<std::string>& table_list = analyzer_.GetTableList();

  LOG_MESSAGE("MainWindow::MainWindow::table got");
  for (auto str : table_list) {
    LOG_MESSAGE("MainWindow::MainWindow add " + str);
    ui->tables_combo_box->addItem(str.c_str());
  }
  connect(ui->tables_combo_box, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnTableChanged(const QString&)));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::OnTableChanged(const QString& new_value) {
    LOG_MESSAGE("MainWindow::OnTableChanged");
    analyzer_.ImportData(new_value.toStdString());
    const Table& table = analyzer_.GetData();

    FillUITable(ui->tableWidget, table);
    ui->actionSave->setEnabled(true);
}

void MainWindow::Import() {
  LOG_MESSAGE("MainWindow::Import");
  QString q_file_name = QFileDialog::getOpenFileName(
      this, tr("Open Database"), "/home", tr("Sqlite files (*.sqlite)"));
  const std::string database_filename = q_file_name.toStdString();

  LOG_MESSAGE("File for import : " + database_filename);
  analyzer_.ImportData(database_filename);

  const Table& table = analyzer_.GetData();

  FillUITable(ui->tableWidget, table);
}

void MainWindow::Export() {
  LOG_MESSAGE("MainWindow::Export");
  analyzer_.ExportData();
}
void MainWindow::Filter() {
  LOG_MESSAGE("MainWindow::Filter");
  QStringList list = StdToQtStringArray(analyzer_.GetData()[0].Keys());
  FilterDialog* dialog = new FilterDialog(list, this);
  dialog->showNormal();
}
void MainWindow::Report() {
  LOG_MESSAGE("MainWindow::Report");

  DatabaseReporter reporter(analyzer_);
  reporter.GenerateReport();
}

void MainWindow::FillUITable(QTableWidget* ui_table, const Table& data_table) {
  LOG_MESSAGE("MainWindow::FillUITable");
  ui_table->clear();

  if (0 == data_table.Size()) {
    LOG_MESSAGE("MainWindow::FillUITable::EmptyTable");
    return;
  }

  const std::vector<std::string> keys = data_table[0].Keys();
  const size_t col_count = keys.size();

  LOG_MESSAGE("MainWindow::FillUITable::SetupTableParams");
  ui_table->setRowCount(data_table.Size());
  ui_table->setColumnCount(col_count);
  ui_table->setHorizontalHeaderLabels(StdToQtStringArray(keys));
  ui_table->setShowGrid(true);

  LOG_MESSAGE("MainWindow::FillUITable::Fullfilling");
  for (size_t rows_index = 0; rows_index < data_table.Size(); ++rows_index) {
    const TableRow& row = data_table[rows_index];
    for (size_t cols_index = 0; cols_index < col_count; ++cols_index) {
      const PrimitiveType* cell_data = row[keys[cols_index]];
      QTableWidgetItem* item = ui_table->item(rows_index, cols_index);
      if (NULL == item) {
        ui_table->setItem(
            rows_index,
            cols_index,
            new QTableWidgetItem(QString(cell_data->asString().c_str())));
      } else {
        item->setText(QString(cell_data->asString().c_str()));
      }
    }
  }
}

void MainWindow::OnFilterGenerated(const QMap<QString, QString>& q_filter) {
  LOG_MESSAGE("MainWindow::OnFilterGenerated");
  if (0 == q_filter.size()) {
    LOG_MESSAGE("MainWindow::OnFilterGenerated::EmptyFilter");
    FillUITable(ui->tableWidget, analyzer_.GetData());
    return;
  }
  ::Filter filter = QMapToFilter(q_filter);
  analyzer_.FilterData(filter);
  FillUITable(ui->tableWidget, analyzer_.GetFilteredData());
}

void MainWindow::ShowErrors() {
  LOG_MESSAGE("MainWindow::ShowErrors");
  analyzer_.FilterErrorData();
  FillUITable(ui->tableWidget, analyzer_.GetFilteredData());
}

void MainWindow::OnCellChanged(int row, int column) {
  QString text = ui->tableWidget->item(row, column)->text();
  analyzer_.OnCellChanged(row, column, text.toStdString());
}
