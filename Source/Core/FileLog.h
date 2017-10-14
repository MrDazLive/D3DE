#pragma once

#include "Log.h"
#include "Singleton.h"

namespace Core {

  class File;

  class FileLog : public Singleton<FileLog>, public Log::Observer {
    friend Singleton;
  protected:
          FileLog       ();

    void  PrintMessage  (const DTU::String&) final override;
    void  PrintSuccess  (const DTU::String&) final override;
    void  PrintWarning  (const DTU::String&) final override;
    void  PrintError    (const DTU::String&) final override;
    void  PrintAssert   (const DTU::String&) final override;
    void  PrintBreak    (                  ) final override;
  private:
    void CreateFile();

    /// <summary>
    /// Concats the provided message to the log file.
    /// </summary>
    /// <param = "message">The message to be printed to the console.</param>
    /// <param = "type">The type of message being logged to the file.</param>
    void  Log           (const DTU::String&, const DTU::String&);

    File* m_file        { nullptr };
  };
}