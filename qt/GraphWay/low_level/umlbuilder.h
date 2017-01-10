#ifndef UMLBUILDER_H
#define UMLBUILDER_H

#include <QFile>
#include <QTextStream>

class UmlBuilder {
 public:
  UmlBuilder(const std::string& filename);
  ~UmlBuilder();

  void AddClass(const std::string name);
  void AddLink(const std::string from,
               const std::string to,
               const std::string comment);

 private:
  const std::string filename_;
  QFile file_;
  QTextStream stream_;
  void GeneratePngFile(const std::string& uml_filename);
};

#endif  // UMLBUILDER_H
