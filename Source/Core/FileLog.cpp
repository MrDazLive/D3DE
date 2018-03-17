#include "FileLog.h"

#include "File.h"
#include "Command.h"

namespace Core {

  FileLog::FileLog() : Log::Observer(~Log::Flags(0)) {

  }

  void FileLog::PrintMessage(const DTU::String& message) {
    Log(message, "Message");
  }

  void FileLog::PrintSuccess(const DTU::String& message) {
    Log(message, "Success");
  }

  void FileLog::PrintWarning(const DTU::String& message) {
    Log(message, "Warning");
  }

  void FileLog::PrintError(const DTU::String& message) {
    Log(message, "Error");
  }

  void FileLog::PrintAssert(const DTU::String& message) {
    Log(message, "Assert");
  }

  void FileLog::PrintBreak() {}

  void FileLog::CreateFile() {
    const DTU::String& appPath =  Command::Fetch(0);
    size_t extStart = appPath.str().find_last_of('.');
    size_t dirEnd = appPath.str().find_last_of("/\\");
    dirEnd = dirEnd != std::string::npos ? dirEnd + 1 : 0;
    const std::string& appName = appPath.str().substr(dirEnd, extStart - dirEnd);

    m_file = Handler<File>::Create(DTU::String("%s/%s.html", LOG_OUTPUT_DIRECTORY, appName.c_str()));
    m_file->Create(true);

    auto createStyle = [](const char* type, const char* colour1, const char* colour2) -> DTU::String {
      return DTU::String(
        ".%s, .%s *{ border-color: #%s; color: #%s; background-color: #%s; }",
        type, type, colour1, colour1, colour2
      );
    };

    DTU::String style;
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

  void FileLog::Log(const DTU::String& message, const DTU::String& type) {
    if (!m_file) {
      CreateFile();
    }

    m_file->InsertLine(DTU::String(
      "<div class = '%s'><h3>%s</h3><hr/><p>%s</p></div>",
      type.c_str(), type.c_str(), message.c_str()
      )
    );
  }

}