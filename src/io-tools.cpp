/**
 * *io-tools.cpp*
 *
 * =======  ========================================================================================
 * @file    sturdr/io-tools.hpp
 * @brief   File tools.
 * @date    December 2024
 * @author  Daniel Sturdivant <sturdivant20@gmail.com>
 * =======  ========================================================================================
 */

#include "sturdio/io-tools.hpp"

#include <filesystem>

namespace sturdio {

//*=== EnsurePathExists ===*
void EnsurePathExists(std::string path) {
  if (!std::filesystem::exists(path)) {
    std::filesystem::create_directory(path);
  }
}

}  // namespace sturdio