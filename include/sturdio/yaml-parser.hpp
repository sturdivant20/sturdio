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

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

namespace sturdio {

template <typename>
struct is_std_vector : std::false_type {};

template <typename T, typename A>
struct is_std_vector<std::vector<T, A>> : std::true_type {};

class YamlParser {
 public:
  /**
   * *=== YamlParser ===*
   * @brief Constructor
   * @param fname string containing yaml file name
   */
  YamlParser(const std::string fname);
  YamlParser();

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
  void parse(const std::string fname);

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
        // check if desired output is a  std::vector
        if constexpr (is_std_vector<T>::value) {
          // remove "[]- " characters
          std::string unwanted_char = "[] ";
          root_[name].erase(
              std::remove_if(
                  root_[name].begin(),
                  root_[name].end(),
                  [&](char c) { return unwanted_char.find(c) != std::string::npos; }),
              root_[name].end());

          // create stringstream (delimiter must be space)
          std::replace(root_[name].begin(), root_[name].end(), ',', ' ');
          std::istringstream iss(root_[name]);
          iss >> std::boolalpha;

          // read items into std::vector
          using VecType = T::value_type;
          VecType item;
          while (iss >> item) {
            val.push_back(item);
          }

        } else {
          std::istringstream iss(root_[name]);
          iss >> std::boolalpha >> val;
        }
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