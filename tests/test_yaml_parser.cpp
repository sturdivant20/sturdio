
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "sturdio/yaml-parser.hpp"

// Helper function to trim whitespace from a string
std::string trim(const std::string& str) {
  std::string result;
  for (const char& c : str) {
    if (!std::isspace(c)) {
      result += c;
    }
  }
  return result;
}

int main() {
  std::string yaml_name = "config/thesis_sim_rcvr_array.yaml";
  sturdio::YamlParser yp(yaml_name);
  std::vector<double> ant_xyz_0;
  double pos_x;
  yp.GetVar<std::vector<double>>(ant_xyz_0, "ant_xyz_0");
  yp.GetVar<double>(pos_x, "reference_pos_x");
  std::string clock_type = yp.GetVar<std::string>("clock_model");
  std::vector<double> ant_xyz_1 = yp.GetVar<std::vector<double>>("ant_xyz_1");

  std::cout << std::setprecision(10) << std::endl;
  std::cout << "ant_xyz_0: [ ";
  std::copy(ant_xyz_0.begin(), ant_xyz_0.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << "]" << std::endl;
  std::cout << "reference_pos_x: " << pos_x << std::endl;
  std::cout << "clock_model: " << clock_type << std::endl;
  std::cout << "ant_xyz_1: [ ";
  std::copy(ant_xyz_1.begin(), ant_xyz_1.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << "]" << std::endl;

  return 0;
}