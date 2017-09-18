#include "File.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

#include "StringUtil.h"

#ifdef _WIN32
#define stat _stat
#else
#include <unistd.h>
#endif

struct file_status {
  bool success;
  struct stat status;
};

const file_status& details(const std::string& path) {
  static file_status file;
  file.success = stat(path.c_str(), &file.status) == 0;
  return file;
}

namespace Core {

  File::File(const std::string& fullPath) : m_file(new std::fstream(fullPath)) {
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
      LOG->PrintWarning(String::Format("File {%s} is already open.", getFullPath().c_str()));
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

  void File::InsertLine(const std::string& content) {
    if (isOpen()) {
      *m_file << content;

      if (!String::EndsWith(content, "\n"))
        *m_file << "\n";
      m_file->flush();
    }
    else {
      LOG->PrintWarning(String::Format("Contents was not written to file: %s", getFullPath().c_str()));
    }
  }

  void File::InsertLine(const std::string& content, const size_t line) {
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

  void File::getContent(std::string& buffer) {
    m_file->seekg(0, std::ios::beg);
    buffer = std::string(std::istreambuf_iterator<char>(*m_file),
      std::istreambuf_iterator<char>());
  }

  void File::getContent(std::vector<std::string>& buffer) {
    m_file->seekg(0, std::ios::beg);
    buffer.clear();
    std::string line;
    while (std::getline(*m_file, line)) {
      buffer.push_back(line);
    }
  }

  const std::string& File::getName() const {
    return m_fullPath[NAME];
  }

  const std::string& File::getLocation() const {
    return m_fullPath[PATH];
  }

  const std::string& File::getExtension() const {
    return m_fullPath[EXT];
  }

  const std::string File::getFullPath() const {
    return m_fullPath[PATH] + m_fullPath[NAME] + m_fullPath[EXT];
  }

  void File::SplitPath(const std::string& fullPath) {
    size_t extStart = fullPath.find_last_of('.');
    LOG->PrintAssert(extStart != std::string::npos, "File path requires a valid extension.");

    size_t dirEnd = fullPath.find_last_of("/\\");
    dirEnd = dirEnd != std::string::npos ? dirEnd + 1 : 0;

    m_fullPath[PATH] = fullPath.substr(0, dirEnd);
    m_fullPath[NAME] = fullPath.substr(dirEnd, extStart - dirEnd);
    m_fullPath[EXT] = fullPath.substr(extStart, fullPath.size() - extStart);
  }

  void File::BuildDirectory() {
    if (!details(m_fullPath[PATH]).success) {
      system(String::Format("md \"%s\"", m_fullPath[PATH].c_str()).c_str());
    }
  }

}