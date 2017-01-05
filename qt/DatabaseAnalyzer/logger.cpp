#include "logger.h"
#include <iostream>

Logger* Logger::instance_ = NULL;

Logger::Logger(QObject* parent, QString fileName) : QObject(parent) {
  std::cout << "Logger created (" + fileName.toStdString() + ")\n";
  m_showDate = true;
  if (!fileName.isEmpty()) {
    file = new QFile;
    file->setFileName(fileName);
    file->open(QIODevice::Append | QIODevice::Text);
  }
}

void Logger::write(const std::string& value) {
  std::cout << "Log message " + value << std::endl;
  QString text = value.c_str();  // + "";
  if (m_showDate) {
    text = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ") + text;
  }
  QTextStream out(file);
  out.setCodec("UTF-8");
  if (file != 0) {
    out << text << "\n";
  }
}

Logger* Logger::instance(QObject* parent) {
  if (instance_) {
    return instance_;
  }
  instance_ = new Logger(parent, "log_file.log");
  return instance_;
}

Logger::~Logger() {
  std::cout << "Logger destroyed\n";
  if (file != 0) {
    file->close();
  }
}
