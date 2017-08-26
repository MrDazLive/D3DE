#include "File.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

#include "StringUtil.h"

#ifdef _WIN32
#define stat _stat
#else
#include <unistd.h>
#endif

const struct stat details(const std::string& path) {
  static struct stat result;
  stat(path.c_str(), &result);
  return result;
}

namespace Core {

  File::File(const std::string& fullPath) : m_file(new std::fstream(fullPath)) {
    SplitPath(fullPath);
  }

  File::~File() {
    if (isOpen() && isModified()) {
      LOG->DebugWarning(String::Format("Changes to {%s} were not saved before closing.", getFullPath().c_str()));
    }
    Close();
    delete m_file;
  }

  bool File::Exists() const {
    return std::fstream(getFullPath().c_str()).good();
  }

  bool File::Create(bool overwrite) {
    if (!Exists() || (overwrite && Delete())) {
      m_file->open(getFullPath().c_str(), std::fstream::out);
      return true;
    }
    return false;
  }

  bool File::Open(bool create) {
    if (isOpen()) {
      LOG->DebugWarning(String::Format("File {%s} is already open.", getFullPath().c_str()));
      return false;
    }
    
    if (create || Exists()) {
      m_file->open(getFullPath().c_str(), std::fstream::out);
      return true;
    }
    return false;
  }

  bool File::Close(bool save) {
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
    // TODO
  }

  void File::InsertLine(const std::string& content, const size_t line) {
    // Adds content to end if specified line is not in range.
    if (line >= m_length) {
      InsertLine(content);
      return;
    }
    // TODO
  }

  void File::RemoveLine() {
    // TODO
  }

  void File::RemoveLine(const size_t line, const size_t count) {
    // Return if no lines are to be removed.
    if (count == 0 || line >= m_length) {
      return;
    }

    // Removes last line if desired.
    if (line == m_length - 1) {
      RemoveLine();
      return;
    }
    // TODO
  }

  const bool File::isOpen() const {
    return m_file->is_open();
  }

  const bool File::isModified() const {
    const auto file = details(getFullPath());
    return file.st_mtime != m_lastCheck;
  }

  const size_t File::getLength() const {
    return m_length;
  }

  const std::string File::getContent() const {
    // TODO
    return "";
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
    LOG->DebugAssert(extStart != std::string::npos, "File path requires a valid extension.");

    size_t dirEnd = fullPath.find_last_of("/\\");
    dirEnd = dirEnd != std::string::npos ? dirEnd + 1 : 0;

    m_fullPath[PATH] = fullPath.substr(0, dirEnd);
    m_fullPath[NAME] = fullPath.substr(dirEnd, extStart - dirEnd);
    m_fullPath[EXT] = fullPath.substr(extStart, fullPath.size() - extStart);
  }

}