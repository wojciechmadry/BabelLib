// Copyright [2021] <Wojtek>"
#ifndef BABLIB_FILE_SYSTEM_HPP_
#define BABLIB_FILE_SYSTEM_HPP_

#include <fstream>
#include <filesystem>
#include <vector>
#include "concepts/concepts.hpp"

namespace babel::FILE_SYS{

    /**
*  @brief  Close file
*  @param  Fstream ifstream/ofstream/fstream to close
*/
    template< typename Filestream >
    requires babel::CONCEPTS::MEMBER::HAS_CLOSE<Filestream>
    inline void close_file(Filestream &FileStream) noexcept
    {
        if constexpr( babel::CONCEPTS::IS_POINTER<Filestream> )
            FileStream->close();
        else
            FileStream.close();
    }

    /**
   *  @brief  Close multiple file
   *  @param  Fstream ifstream/ofstream/fstream to close
   *  @param arg ifstream/ofstream/fstream to close
   */
    template< typename Filestream, typename ... Args >
    requires babel::CONCEPTS::MEMBER::HAS_CLOSE<Filestream>
    inline void close_file(Filestream &FileStream, Args &... arg) noexcept//NOLINT
    {
        close_file(FileStream);
        close_file(arg...);
    }

    /**
*  @brief  Scan folder and return filename
*  @param  path Folder to scan
*  @return Vector of filename with extension in folder
*/
    inline std::vector<std::string> scan_folder(const std::string &path) noexcept
    {
        std::vector<std::string> res;
        auto Directory = std::filesystem::directory_iterator(path);
        std::transform(begin(Directory), end(Directory), std::back_inserter(res),
                       [](const auto &FILE_PATH) -> std::string {
                           return FILE_PATH.path().filename().string();
                       });
        return res;
    }

    /**
*  @brief  If filename has extension ex.: .exe that return exe
*  if filename is ex.: folder that return "none"
*  @param  filename filename with extension or without.
*  @return File extension ex: .exe, .txt etc.
*/
    inline std::string file_extension(const std::string &filename) noexcept
    {
        auto found_dot = filename.find('.');
        if ( found_dot != std::string::npos )
            return filename.substr(found_dot + 1, filename.size());
        else
            return "";
    }

    /**
*  @brief  Convert filename with extension to just filename
*  @param  filename filename with extension or without.
*  @return Filename without extension ex.: test.txt -> test
*/
    inline std::string file_without_extension(const std::string &filename) noexcept
    {
        auto found_dot = filename.find('.');
        if ( found_dot != std::string::npos )
            return filename.substr(0, found_dot);
        else
            return filename;
    }

    /**
*  @brief  ex.: filename = "test.txt" /
*    \Example_1 contain = "te" -> return 1 /
*    \Example_2 contain = "txt" -> return 1/
*   \Example_3 contain = "test.txtt" -> return 0
*  @param  filename filename with extension or without.
*  @param  contain text we want to find in filename.
*  @return If filename contains contain return 1 otherwise return 0
*/
    inline bool filename_contain(const std::string_view filename, const std::string_view contain) noexcept
    {
        return filename.find(contain) != std::string::npos;
    }

    /**
*  @brief  Load file to std::vector, size of vector = number of lines in file
*  @param  filename File to load
*  @return Loaded file to vector
*/
    inline std::vector<std::string> load_txt_to_vector(const std::string &filename) noexcept
    {
        std::vector<std::string> out;
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if ( !( file.good() && file.is_open() ) )
            return { };
        out.emplace_back("");
        while ( std::getline(file, out[out.size() - 1]) )
            out.emplace_back("");
        out.pop_back();
        close_file(file);
        return out;
    }

    /**
*  @brief  Load file to std::string, every line is end with new line
*  @param  filename File to load
*  @return Loaded file to string
*/
    inline std::string load_txt(const std::string &filename) noexcept
    {
        std::string out, line;
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if ( !( file.good() && file.is_open() ) )
            return out;
        while ( std::getline(file, line) )
        {
            out += line;
            if ( line[line.size() - 1] != '\n' )
                out += '\n';
        }
        close_file(file);
        return out;
    }

    /**
*  @brief  Check if file with this filename exist
*  @param  filename File to check
*  @return True if Exist, False in otherwise
*/
    [[nodiscard]] inline bool file_exist(const std::string &filename) noexcept
    {
        return std::filesystem::is_regular_file(filename);
    }

    /**
*  @brief  Check if folder with this foldername exist
*  @param  foldername Folder to check
*  @return True if Exist, False in otherwise
*/
    [[nodiscard]] inline bool folder_exist(const std::string &foldername) noexcept
    {
        return std::filesystem::is_directory(foldername);
    }


    /**
*  @brief  Check if file or folder with this name exist
*  @param  name File/Folder to check
*  @return True if Exist, False in otherwise
*/
    [[nodiscard]] inline bool file_folder_exist(const std::string &name) noexcept
    {
        return folder_exist(name) || file_exist(name);
    }
}  // namespace babel::FILE_SYS

#endif  // BABLIB_FILE_SYSTEM_HPP_
