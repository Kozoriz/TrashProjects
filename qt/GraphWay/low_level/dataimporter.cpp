#include "low_level/dataimporter.h"
#include <QDebug>
#include <QString>

#include "logger.h"

namespace {
std::string GetExtention(const std::string& filename) {
  return filename.substr(filename.find_last_of('.'));
}

void QStringListToStd(const QStringList& q_list,
                      std::vector<std::string>& out_list) {
  for (int i = 0; i < q_list.size(); ++i) {
    out_list.push_back(q_list[i].toStdString());
  }
}
}

DataImporter::DataImporter() {}

void DataImporter::ImportFile(const std::__cxx11::string& filename) {
  LOG_MESSAGE("DataImporter::ImportFile");
  const std::string ext = GetExtention(filename);
  LOG_MESSAGE(ext);

  if (".csv" == ext) {
    data_ = ImportCsv(filename);
  }
}

const DataImporter::RawImportData& DataImporter::data() {
  return data_;
}

DataImporter::RawImportData DataImporter::ImportCsv(
    const std::__cxx11::string& filename) {
  LOG_MESSAGE("DataImporter::ImportCsv");
  RawImportData data;

  QFile file(filename.c_str());
  file.open(QFile::ReadOnly);
  QTextStream in(&file);

  while (!in.atEnd()) {
    QString q_line = in.readLine();
    QStringList q_str_list = q_line.split(',');

    std::vector<std::string> str_list;
    QStringListToStd(q_str_list, str_list);
    data.push_back(str_list);
  }

  return data;
}
