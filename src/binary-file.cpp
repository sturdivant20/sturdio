/**
 * *binary-file.cpp*
 *
 * =======  ========================================================================================
 * @file    sturdr/binary-file.cpp
 * @brief   Tool for parsing binary files of arbitrary types.
 * @date    January 2025
 * @author  Daniel Sturdivant <sturdivant20@gmail.com>
 * =======  ========================================================================================
 */

#include "sturdio/binary-file.hpp"

#include <sstream>

namespace sturdio {

// *=== BinaryFile ===*
BinaryFile::BinaryFile(const std::string fname, const std::string fpath) {
  std::stringstream tmp;
  tmp << fpath << "/" << fname;
  fname_ = tmp.str();
  fopen();
}
BinaryFile::BinaryFile(const std::string fname) : fname_{fname} {
  fopen();
}

// *=== ~BinaryFile ===*
BinaryFile::~BinaryFile() {
  fclose();
}

//  *=== fopen ===*
bool BinaryFile::fopen() {
  try {
    // reading file
    fid_ = std::ifstream(fname_, std::ios::binary);
    if (fid_.is_open() || fid_.good()) {
      return true;
    }
    return false;
  } catch (std::exception const &e) {
    std::cerr << "binary-file.cpp BinaryFile::fopen unable to open file. Error -> " << e.what()
              << "\n";
    return false;
  }
}

// *=== fclose ===*
bool BinaryFile::fclose() {
  try {
    fid_.close();
    return true;
  } catch (std::exception const &e) {
    std::cerr << "binary-file.cpp BinaryFile::fopen unable to close file. Error -> " << e.what()
              << "\n";
    return false;
  }
}

}  // namespace sturdio