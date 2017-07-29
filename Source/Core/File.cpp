#include "File.h"

namespace Core {

  File::File(const std::string& fullPath) {
    SplitPath(fullPath);
  }

  File::~File() {
    if (isModified()) {
      LOG->DebugWarning("File {" + getFullPath() + "} will save before closing.");
    }
    Close();
  }

  bool File::Exists() const {
    // TODO
    return false;
  }

  bool File::Create(bool overwrite) {
    // TODO
    if (overwrite || !Exists()) {

    }
    return false;
  }

  bool File::Open(bool create) {
    // TODO
    if (Exists()) {

    } else if (create) {
      Create();
    }
    return false;
  }

  bool File::Save(bool overwrite) {
    // TODO
    if (m_modified && overwrite) {

    }
    return false;
  }

  bool File::Close(bool save) {
    // TODO
    if (save && m_modified) {
      Save();
    }
    return false;
  }

  bool File::Delete() {
    // TODO
    if (Exists()) {

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

  const bool File::isModified() const {
    return m_modified;
  }

  const size_t File::getLength() const {
    return m_length;
  }

  const std::string& File::getContent() const {
    return m_content;
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