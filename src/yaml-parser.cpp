/**
 * *yaml-parser.cpp*
 *
 * =======  ========================================================================================
 * @file    sturdr/yaml-parser.cpp
 * @brief   Basic yaml parsing utility for basic c-types.
 * @date    January 2025
 * @author  Daniel Sturdivant <sturdivant20@gmail.com>
 * =======  ========================================================================================
 */

#include "sturdio/yaml-parser.hpp"

#include <fstream>

namespace sturdio {

// *=== YamlParser ===*
YamlParser::YamlParser(const std::string fname, const std::string fpath) {
  std::stringstream tmp;
  tmp << fpath << "/" << fname;
  fname_ = tmp.str();

  // parse file
  parse();
}
YamlParser::YamlParser(const std::string fname) : fname_{fname} {
  // parse file
  parse();
}

// *=== ~YamlParser ===*
YamlParser::~YamlParser() {
}

// *=== parse ===*
void YamlParser::parse() {
  try {
    // open file
    std::ifstream fid_(fname_);
    if (!fid_.is_open() || !fid_.good()) {
      std::cerr << "yaml-parser.cpp YamlParser unable to open file\n";
    }

    // read line by line
    std::string line, key, val;
    std::size_t pos;
    while (std::getline(fid_, line)) {
      // Skip lines that are empty or start with '#'
      if (line.empty() || line[0] == '#') {
        continue;
      }

      // ensure there is a keyword and a value
      pos = line.find(":");
      if (pos != std::string::npos) {
        key = line.substr(0, pos);
        val = line.substr(pos + 1);

        // trim whitespace
        key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));
        key.erase(key.find_last_not_of(" \t\n\r\f\v") + 1);
        val.erase(0, val.find_first_not_of(" \t\n\r\f\v"));
        val.erase(val.find_last_not_of(" \t\n\r\f\v") + 1);

        // add to map
        root_[key] = val;
      }
    }

    // close file
    fid_.close();

  } catch (std::exception const &e) {
    std::cerr << "yaml-parser.cpp YamlParser::parse failed. Error -> " << e.what() << "\n";
  }
}

// *=== Exists ===*
bool YamlParser::Exists(const std::string &name) {
  return (root_.find(name) != root_.end());
}

}  // namespace sturdio