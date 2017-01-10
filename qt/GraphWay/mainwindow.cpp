#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logger.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QPixmap>

#include "wayendpointschoosedialog.h"

namespace {
QStringList StdToQtStringArray(const std::vector<std::string>& keys) {
  QStringList list;
  for (size_t i = 0; i < keys.size(); ++i) {
    list << keys[i].c_str();
  }
  return list;
}
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , importer_(new DataImporter)
    , builder_(new GraphBuilder)
    , way_finder_(new WayFinder(builder_->graph()))
    , way_choose_dialog_(NULL) {
  ui->setupUi(this);
  connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(Import()));
  connect(ui->actionWay, SIGNAL(triggered()), this, SLOT(GetWay()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete way_choose_dialog_;
  delete way_finder_;
    delete builder_;
    delete importer_;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  UpdateGraphView("/home/andrii/uml.png");
}

void MainWindow::Import() {
  LOG_MESSAGE("MainWindow::Import");
  QString q_file_name = QFileDialog::getOpenFileName(
      this, tr("Open Database"), "/home", tr("Sqlite files (*.csv)"));
  const std::string database_filename = q_file_name.toStdString();

  LOG_MESSAGE("File for import : " + database_filename);
  importer_->ImportFile(database_filename);
  builder_->BuildGraphFromRawData(importer_->data());
  way_finder_->OnGraphUpdated();

  UpdateGraphView("/home/andrii/uml.png");
}

void MainWindow::UpdateGraphView(const std::string filename) {
  QImage image;
  if (!image.load(filename.c_str())) {
    LOG_MESSAGE("MainWindow::UpdateGraphView::NotExists");
    return;
  }
  const int width = ui->centralWidget->width();
  const int height = ui->centralWidget->height();
  QPixmap pixm(QPixmap::fromImage(image.scaled(width, height)));

  ui->label->setGeometry(0, 0, width, height);
  ui->label->setPixmap(pixm);
}

void MainWindow::GetWay() {
  std::vector<std::string> ep_names = builder_->graph().EndpointsNames();
  QStringList q_list = StdToQtStringArray(ep_names);
  if (NULL == way_choose_dialog_) {
    way_choose_dialog_ = new WayEndpointsChooseDialog(q_list, this);
  }

  way_choose_dialog_->showNormal();

  way_finder_->CalculateAllWays();

  way_choose_dialog_->EnableEditing();
}

void MainWindow::OnEndpointsChoosen(const QString& from, const QString& to) {
  QMessageBox msg_box;
  const Way* way = way_finder_->getWay(from.toStdString(), to.toStdString());
  std::string text =
      (NULL != way) ? way->asString() + " : " + std::to_string(way->distance())
                    : "way to void";
  msg_box.setText(text.c_str());
  msg_box.exec();
}
