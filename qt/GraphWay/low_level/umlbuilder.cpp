#include "low_level/umlbuilder.h"

#include <stdlib.h>
#include "logger.h"

UmlBuilder::UmlBuilder(const std::__cxx11::string& filename)
    : filename_(filename), file_(filename_.c_str()), stream_(&file_) {
  file_.open(QFile::WriteOnly);
  stream_ << "@startuml\n"
          << "scale max 1366*960\n"
          << "skinparam linetype polyline\n";
}

UmlBuilder::~UmlBuilder() {
  stream_ << "@enduml";
  file_.flush();
  file_.close();

  GeneratePngFile(filename_);
}

void UmlBuilder::AddClass(const std::string name) {
  stream_ << "class " << QString(name.c_str()).remove('-') << "\n";
}

void UmlBuilder::AddLink(const std::string from,
                         const std::string to,
                         const std::string comment) {
  stream_ << QString(from.c_str()).remove('-') << "--"
          << QString(to.c_str()).remove('-') << ":"
          << QString(comment.c_str()).remove('-') << "\n";
}

void UmlBuilder::GeneratePngFile(const std::string& uml_filename) {
  const std::string command = "java -jar ~/git/plantuml.jar " + uml_filename;
  system(command.c_str());
}
