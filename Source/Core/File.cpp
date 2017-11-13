#include "File.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#define stat _stat
#else
#include <unistd.h>
#endif

struct file_status {
  bool success;
  struct stat status;
};

const file_status& details(const DTU::String& path) {
  static file_status file;
  file.success = stat(path.c_str(), &file.status) == 0;
  return file;
}

namespace Core {

  File::File(const DTU::String& fullPath) : m_file(new std::fstream(fullPath.str())) {
    SplitPath(fullPath);
  }

  File::~File() {
    Close();
    delete m_file;
  }

  bool File::Exists() const {
    return std::fstream(getFullPath().c_str()).good();
  }

  bool File::Create(bool overwrite) {
    if (!Exists() || (overwrite && Delete())) {
      BuildDirectory();
      m_file->open(getFullPath().c_str(), std::fstream::out);
      return Close() && Open();
    }
    return false;
  }

  bool File::Open(bool create) {
    if (isOpen()) {
      LOG->PrintWarning(DTU::String("File {%s} is already open.", getFullPath().c_str()));
      return false;
    }
    
    if (Exists()) {
      BuildDirectory();
      m_file->open(getFullPath().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
      return true;
    }
    else if (create) {
      return Create();
    }
    return false;
  }

  bool File::Close() {
    if (Exists()) {
      m_file->close();
      return true;
    }
    return false;
  }

  bool File::Delete() {
    if (Close()) {
      return std::remove(getFullPath().c_str()) == 0;
    }
    return false;
  }

  void File::InsertLine(const DTU::String& content) {
    if (isOpen()) {
      *m_file << content.str();

      if (!content.endsWith("\n"))
        *m_file << "\n";
      m_file->flush();
    }
    else {
      LOG->PrintWarning(DTU::String("Contents was not written to file: %s", getFullPath().c_str()));
    }
  }

  void File::InsertLine(const DTU::String& content, const size_t line) {
    LOG->PrintAssert("Function (File::InsertLine) not implemented.");
  }

  void File::RemoveLine() {
    LOG->PrintAssert("Function (File::RemoveLine) not implemented.");
  }

  void File::RemoveLine(const size_t line, const size_t count) {
    LOG->PrintAssert("Function (File::RemoveLine) not implemented.");
  }

  const bool File::isOpen() const {
    return m_file->is_open();
  }

  const bool File::isModified() const {
    const auto file = details(getFullPath());
    return file.status.st_mtime != m_lastCheck;
  }

  const bool File::isEmpty() const {
    m_file->seekg(0, std::ios::beg);
    return m_file->peek() == std::string::npos;
  }

  void File::getContent(DTU::String& buffer) {
    m_file->seekg(0, std::ios::beg);
    buffer = std::string(std::istreambuf_iterator<char>(*m_file),
      std::istreambuf_iterator<char>());
  }

  void File::getContent(std::vector<DTU::String>& buffer) {
    m_file->seekg(0, std::ios::beg);
    buffer.clear();
    std::string line;
    while (std::getline(*m_file, line)) {
      buffer.push_back(line);
    }
  }

  const DTU::String& File::getName() const {
    return m_fullPath[NAME];
  }

  const DTU::String& File::getLocation() const {
    return m_fullPath[PATH];
  }

  const DTU::String& File::getExtension() const {
    return m_fullPath[EXT];
  }

  const DTU::String File::getFullPath() const {
    return m_fullPath[PATH] + m_fullPath[NAME] + m_fullPath[EXT];
  }

  void File::SplitPath(const DTU::String& fullPath) {
    size_t extStart = fullPath.str().find_last_of('.');
    LOG->PrintAssert(extStart != std::string::npos, "File path requires a valid extension.");

    size_t dirEnd = fullPath.str().find_last_of("/\\");
    dirEnd = dirEnd != std::string::npos ? dirEnd + 1 : 0;

    m_fullPath[PATH] = fullPath.str().substr(0, dirEnd);
    m_fullPath[NAME] = fullPath.str().substr(dirEnd, extStart - dirEnd);
    m_fullPath[EXT] = fullPath.str().substr(extStart, fullPath.size() - extStart);
  }

  void File::BuildDirectory() {
    if (!details(m_fullPath[PATH]).success) {
#ifdef _WIN32 
      system(DTU::String("md \"%s\"", m_fullPath[PATH].c_str()).c_str());
#else
      system(DTU::String("mkdir -p \"%s\"", m_fullPath[PATH].c_str()).c_str());
#endif
    }
  }

}