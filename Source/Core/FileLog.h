#pragma once

#include "Log.h"
#include "Singleton.h"

namespace Core {

  class File;

  class FileLog : public Singleton<FileLog>, public Log::Observer {
    friend Singleton;
  protected:
          FileLog       ();

    void  PrintMessage  (const std::string&) final override;
    void  PrintSuccess  (const std::string&) final override;
    void  PrintWarning  (const std::string&) final override;
    void  PrintError    (const std::string&) final override;
    void  PrintAssert   (const std::string&) final override;
    void  PrintBreak    (                  ) final override;
  private:
    void CreateFile();

    /// <summary>
    /// Concats the provided message to the log file.
    /// </summary>
    /// <param = "message">The message to be printed to the console.</param>
    /// <param = "type">The type of message being logged to the file.</param>
    void  Log           (const std::string&, const std::string&);

    File* m_file        { nullptr };
  };
}