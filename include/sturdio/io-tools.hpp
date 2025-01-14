/**
 * *io-tools.hpp*
 *
 * =======  ========================================================================================
 * @file    sturdr/io-tools.hpp
 * @brief   File tools.
 * @date    January 2025
 * @author  Daniel Sturdivant <sturdivant20@gmail.com>
 * =======  ========================================================================================
 */

#ifndef STURDIO_IO_TOOLS_HPP
#define STURDIO_IO_TOOLS_HPP

#include <string>

namespace sturdio {

/**
 * *=== EnsurePathExists ===*
 * @brief Makes sure directory exists
 * @param path  String containing directory
 */
void EnsurePathExists(std::string path);
}  // namespace sturdio

#endif