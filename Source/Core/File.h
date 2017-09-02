#pragma once

#include "Handler.h"

namespace std {
  typedef basic_fstream<char> fstream;
}

namespace Core {

  /// <summary>
  /// Class used for holding and managing file data.
  /// </summary>
  class File : public Handler<File> {
  public:
                        /// <summary>
                        /// Constructor.
                        /// </summary>
                        /// <param name = "fullPath">The full path to the desired file.</param>
                        File            (const std::string&);

                        /// <summary>
                        /// Virtual destructor.
                        /// Saves and closes the file unless overwise handled.
                        /// </summary>
    virtual             ~File           ();

    /// <summary>
    /// Checks whether the file exists.
    /// </summary>
    bool                Exists          () const;

    /// <summary>
    /// Creates the named file.
    /// If an instance of the file already exists, the file will be overwritten if specified, otherwise no file is created.
    /// </summary>
    /// <param name = "overwrite">Specifies whether to overwrite an existing copy.</param>
    bool                Create          (bool = false);

    /// <summary>
    /// Opens the named file.
    /// If the file does not exist, the file will be created if specified.
    /// </summary>
    /// <param name = "create">Specifies whether to create the file if not found.</param>
    bool                Open            (bool = false);

    /// <summary>
    /// Closes the opened file.
    /// If the file has been modified, the file will be saved if specified.
    /// </summary>
    bool                Close           ();

    /// <summary>
    /// Deletes the specified file.
    /// </summary>
    bool                Delete          ();

    /// <summary>
    /// Adds the desired contents to the end of the file.
    /// </summary>
    /// <param name = "content">The content to be inserted.</param>
    void                InsertLine      (const std::string&);


    /// <summary>
    /// Adds the desired contents to the specified point in the file.
    /// </summary>
    /// <param name = "content">The content to be inserted.</param>
    /// <param name = "line">The location to insert the new content.</param>
    void                InsertLine      (const std::string&, const size_t);

    /// <summary>
    /// Removes the last line of the file.
    /// </summary>
    void                RemoveLine      ();

    /// <summary>
    /// Removes the defined amount of lines from a specified point in the file.
    /// </summary>
    /// <param name = "line">The location of the line to remove.</param>
    /// <param name = "count">The amount of lines to remove.</param>
    void                RemoveLine      (const size_t, const size_t = 1);

    /// <summary>
    /// Returns whether the file is currently open.
    /// </summary>
    const bool          isOpen          () const;

    /// <summary>
    /// Returns whether the file has been modifed since it was created, opened or saved.
    /// </summary>
    const bool          isModified      () const;

    /// <summary>
    /// Returns whether the file is empty or not.
    /// </summary>
    const bool          isEmpty         () const;


    /// <summary>
    /// Collects the conent of the file.
    /// </summary>
    /// <param name = "buffer">The object to be provided with the content of the file.</param>
    /// <param name = "close">Prompts the file to close upon collecting contents.</param>
    template <typename T>
    void                getContent      (T&, bool);

    /// <summary>
    /// Returns the name of the file.
    /// </summary>
    const std::string&  getName         () const;

    /// <summary>
    /// Returns the path to the file.
    /// </summary>
    const std::string&  getLocation     () const;

    /// <summary>
    /// Returns the file extension.
    /// </summary>
    const std::string&  getExtension    () const;

    /// <summary>
    /// Returns the full path to the file.
    /// </summary>
    const std::string   getFullPath     () const;
  protected:
  private:
    enum                /*anonymous*/   { PATH = 0, NAME = 1, EXT = 2 };

    /// <summary>
    /// Collects the conent of the file.
    /// </summary>
    /// <param name = "buffer">The string to be provided with the content of the file.</param>
    void                getContent(std::string&);

    /// <summary>
    /// Collects the conent of the file.
    /// </summary>
    /// <param name = "buffer">The vector to be provided with the content of the file.</param>
    void                getContent(std::vector<std::string>&);

    void                SplitPath       (const std::string&);
    void                BuildDirectory  ();
    void                Reopen          ();

    size_t              m_length        { 0 };
    time_t              m_lastCheck     { 0 };
    std::string         m_fullPath[3]   {};
    std::fstream* const m_file          { nullptr };
  };

  template <typename T>
  void File::getContent(T& buffer, bool close) {
    // TODO : Not require reopening between read and write.
    if (Exists()) {
      Reopen();
      getContent(buffer);
      close ? Close() : Reopen();
    }
  }

}