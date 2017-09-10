#include "FileLog.h"

#include "File.h"
#include "StringUtil.h"

namespace Core {

  FileLog::FileLog() : Log::Observer(~(Log::LOW)) {

  }

  void FileLog::PrintMessage(const std::string& message) {
    Log(message, "Message");
  }

  void FileLog::PrintSuccess(const std::string& message) {
    Log(message, "Success");
  }

  void FileLog::PrintWarning(const std::string& message) {
    Log(message, "Warning");
  }

  void FileLog::PrintError(const std::string& message) {
    Log(message, "Error");
  }

  void FileLog::PrintAssert(const std::string& message) {
    Log(message, "Assert");
  }

  void FileLog::PrintBreak() {}

  void FileLog::CreateFile() {
    m_file = Handler<File>::Create("../Logs/Log.html");
    m_file->Create(true);

    auto createStyle = [](const char* type, const char* colour1, const char* colour2) {
      return String::Format(
        ".%s, .%s *{ border-color: #%s; color: #%s; background-color: #%s; }",
        type, type, colour1, colour1, colour2
      );
    };

    std::string style;
    style += "<style>";
    style += "body { padding: 0; margin: 0; }";
    style += "div{ border-style: solid; border-width: 2px; padding: 0px 10px 0px 10px; }";

    style += createStyle("Message", "333333", "888888");
    style += createStyle("Success", "22aa22", "77ff77");
    style += createStyle("Warning", "aa8800", "ffdd00");
    style += createStyle("Error", "aa2222", "ff7777");
    style += createStyle("Assert", "880000", "dd00bb");

    style += "</style>";

    m_file->InsertLine(style);
  }

  void FileLog::Log(const std::string& message, const std::string& type) {
    if (!m_file) {
      CreateFile();
    }

    m_file->InsertLine(String::Format(
      "<div class = '%s'><h3>%s</h3><hr/><p>%s</p></div>",
      type.c_str(), type.c_str(), message.c_str()
      )
    );
  }


}