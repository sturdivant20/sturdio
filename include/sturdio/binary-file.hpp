/**
 * *binary-file.hpp*
 *
 * =======  ========================================================================================
 * @file    sturdr/binary-file.hpp
 * @brief   Tool for parsing binary files of arbitrary types.
 * @date    January 2025
 * @author  Daniel Sturdivant <sturdivant20@gmail.com>
 * =======  ========================================================================================
 */

#ifndef STURDIO_BINARY_FILE_HPP
#define STURDIO_BINARY_FILE_HPP

#include <complex>
#include <fstream>
#include <iostream>
#include <string>

namespace sturdio {

class BinaryFile {
 public:
  /**
   * *=== BinaryFile ===*
   * @brief constructor
   * @param fname string containing signal file name
   */
  BinaryFile(const std::string fname);
  BinaryFile();

  /**
   * *=== ~BinaryFile ===*
   * @brief destructor
   */
  ~BinaryFile();

  /**
   * *=== fread ===*
   * @brief read data from file
   * @param buffer destination of data parsed from file
   * @param len    number of samples to read
   * @return True|False based upon reading/parsing success
   */
  template <typename T>
  bool fread(T *buffer, const int len) {
    try {
      if (!fid_.is_open() || fid_.bad()) {
        std::cerr << "binary-file.hpp BinaryFile::fread bad signal file.\n";
        return false;
      }
      // read into standard array
      fid_.read(reinterpret_cast<char *>(buffer), len * sizeof(T));
      return true;
    } catch (std::exception const &e) {
      std::cerr << "binary-file.hpp BinaryFile::fread unable to read file. Error -> " << e.what()
                << "\n";
      return false;
    }
  };
  template <typename T>
  bool freadc(std::complex<T> *buffer, const int len) {
    try {
      if (!fid_.is_open() || fid_.bad()) {
        std::cerr << "binary-file.hpp BinaryFile::freadc bad signal file.\n";
        return false;
      }
      // read into standard array
      fid_.read(reinterpret_cast<char *>(buffer), len * sizeof(std::complex<T>));
      return true;
    } catch (std::exception const &e) {
      std::cerr << "binary-file.hpp BinaryFile::freadc unable to read file. Error -> " << e.what()
                << "\n";
      return false;
    }
  };

  /**
   * *=== fseek ===*
   * @brief seek to a specific sample from the beginning of the file
   * @param len    number of samples to skip from beginning of file
   * @return True|False based upon seeking success
   */
  template <typename T>
  bool fseek(const int len) {
    try {
      if (!fid_.is_open() || fid_.bad()) {
        std::cerr << "binary-file.hpp BinaryFile::fseek bad signal file.";
        return false;
      }
      // seek to sample
      fid_.seekg(len * sizeof(T), fid_.beg);
      return true;
    } catch (std::exception const &e) {
      std::cerr << "binary-file.hpp BinaryFile::fseek unable to seek in file. Error -> " << e.what()
                << "\n";
      return false;
    }
  };
  template <typename T>
  bool fseekc(const int len) {
    try {
      if (!fid_.is_open() || fid_.bad()) {
        std::cerr << "binary-file.hpp BinaryFile::fseekc bad signal file.";
        return false;
      }
      // seek to sample
      fid_.seekg(len * sizeof(std::complex<T>), fid_.beg);
      return true;
    } catch (std::exception const &e) {
      std::cerr << "binary-file.hpp BinaryFile::fseekc unable to seek in file. Error -> "
                << e.what() << "\n";
      return false;
    }
  };

  /**
   * *=== ftell ===*
   * @brief retrieve sample number from the beginning of the file
   * @param location sample index from beginning of file
   * @return True|False based upon telling success
   */
  template <typename T>
  bool ftell(int &location) {
    try {
      if (!fid_.is_open() || fid_.bad()) {
        std::cerr << "binary-file.hpp BinaryFile::ftell bad signal file.";
        return false;
      }
      // tell sample
      location = fid_.tellg() / sizeof(T);
      return true;
    } catch (std::exception const &e) {
      std::cerr << "binary-file.hpp BinaryFile::ftell unable to tell in file. Error -> " << e.what()
                << "\n";
      return false;
    }
  };
  template <typename T>
  int ftell() {
    int location;
    if (ftell<T>(location)) {
      return location;
    } else {
      return -1;
    }
  };
  template <typename T>
  bool ftellc(int &location) {
    try {
      if (!fid_.is_open() || fid_.bad()) {
        std::cerr << "binary-file.hpp BinaryFile::ftell bad signal file.";
        return false;
      }
      // tell sample
      location = fid_.tellg() / sizeof(std::complex<T>);
      return true;
    } catch (std::exception const &e) {
      std::cerr << "binary-file.hpp BinaryFile::ftell unable to tell in file. Error -> " << e.what()
                << "\n";
      return false;
    }
  };
  template <typename T>
  int ftellc() {
    int location;
    if (ftellc<T>(location)) {
      return location;
    } else {
      return -1;
    }
  };

  /**
   *  *=== fopen ===*
   * @brief attempts to open signal file under specified fname_
   * @return True|False based upon opening success
   */
  bool fopen();
  bool fopen(const std::string fname);

  /**
   * *=== fclose ===*
   * @brief attempts to close active file identifier
   * @return True|False based upon closing success
   */
  bool fclose();

 private:
  std::string fname_;
  std::ifstream fid_;
};  // end class BinaryFile
}  // namespace sturdio

#endif