/**
 * *yaml-parser.hpp*
 *
 * =======  ========================================================================================
 * @file    sturdr/yaml-parser.hpp
 * @brief   Basic yaml parsing utility for basic c-types.
 * @date    January 2025
 * @author  Daniel Sturdivant <sturdivant20@gmail.com>
 * =======  ========================================================================================
 */

#ifndef STURDIO_YAML_PARSER_HPP
#define STURDIO_YAML_PARSER_HPP

#include <iostream>
#include <map>
#include <sstream>

namespace sturdio {

class YamlParser {
 public:
  /**
   * *=== YamlParser ===*
   * @brief Constructor
   * @param fname string containing yaml file name
   * @param fpath (optional) string containing yaml file path (directory)
   */
  YamlParser(const std::string fname, const std::string fpath);
  YamlParser(const std::string fname);

  /**
   * *=== ~YamlParser ===*
   * @brief destructor
   */
  ~YamlParser();

  /**
   * *=== parse ===*
   * @brief parses the yaml file into a map of string-(string-string)
   *        -> only supports 1 sub-layer
   *        -> assumes the separators to be either ': ' for key-value pairs OR ':\n' for major
   *           groupings distinctions
   */
  void parse();

  /**
   * *=== Exists ===*
   * @brief Query wether paramater name exists
   * @returns True|False based on parameter existence
   */
  bool Exists(const std::string &name);

  /**
   * *=== GetVar ===*
   * @brief Get variable as specified type
   * @param val   Item to place value into
   * @param name  Name of variable to grab
   * @return True|False based on successful extraction
   */
  template <typename T>
  bool GetVar(T &val, const std::string name) {
    try {
      // make sure variable exists
      if (Exists(name)) {
        std::istringstream iss(root_[name]);
        iss >> std::boolalpha >> val;
        return true;
      } else {
        std::cerr << "yaml-parser.hpp YamlParser::GetVar no keyword " << name << " in file!\n";
        return false;
      }
    } catch (std::exception const &e) {
      std::cerr << "yaml-parser.hpp YamlParser::GetVar failed. Error -> " << e.what() << "\n";
      return false;
    }
  };
  template <typename T>
  T GetVar(const std::string name) {
    T var;
    GetVar(var, name);
    return var;
  };

 private:
  std::string fname_;
  std::map<std::string, std::string> root_;

};  // end class YamlParser

}  // namespace sturdio

#endif