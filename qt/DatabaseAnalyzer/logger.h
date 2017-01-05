#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QTextStream>

class Logger : public QObject {
  Q_OBJECT

 public:
  static Logger* instance(QObject* parent);
  ~Logger();

 private:
  explicit Logger(QObject* parent, QString fileName);

  QFile* file;
  bool m_showDate;

  static Logger* instance_;

 signals:

 public slots:
  void write(const std::string& value);
};

#define LOG_MESSAGE(message) Logger::instance(NULL)->write(message);

#endif  // LOGGER_H
