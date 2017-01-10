#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H

#include <string>
#include <vector>

class DataImporter {
 public:
  typedef std::vector<std::vector<std::string> > RawImportData;
  DataImporter();
  void ImportFile(const std::__cxx11::string& filename);
  const RawImportData& data();

 private:
  RawImportData ImportCsv(const std::__cxx11::string& filename);

  RawImportData data_;
};

#endif  // DATAIMPORTER_H
