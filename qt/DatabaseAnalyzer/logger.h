#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QPlainTextEdit>
#include <QTextStream>

class Logger : public QObject {
  Q_OBJECT

 public:
  static Logger* instance(QObject* parent);
  ~Logger();

 private:
  explicit Logger(QObject* parent,
                  QString fileName,
                  QPlainTextEdit* editor = 0);

  QFile* file;
  QPlainTextEdit* m_editor;
  bool m_showDate;

  Logger* instance_ = NULL;

 signals:

 public slots:
  void write(const QString& value);
};

#define LOG_MESSAGE(parent, message) Logger::instance().write(message);

#endif  // LOGGER_H
