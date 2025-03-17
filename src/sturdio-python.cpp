/**
 * *sturdio-python.cpp*
 *
 * =======  ========================================================================================
 * @file    src/sturdio-python.cpp
 * @brief   PyBind11 wrapper for using SturdIO in python!
 * @date    March 2025
 * =======  ========================================================================================
 */

#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "sturdio/binary-file.hpp"
#include "sturdio/io-tools.hpp"
#include "sturdio/yaml-parser.hpp"

namespace py = pybind11;
using str = std::string;
using namespace sturdio;

PYBIND11_MODULE(_sturdio_core, h) {
  h.doc() = R"pbdoc(
      SturdIO
      ======
      
      Daniel Sturdivant's basic file reading/writing utilities

      Contains the following modules:

      1. `BinaryFile`
      2. `YamlParser`
      3. `iotools`
      )pbdoc";
  h.attr("__version__") = "1.0.0";

  // iotools
  py::module_ io = h.def_submodule("iotools");
  io.def(
      "EnsurePathExists",
      &EnsurePathExists,
      py::arg("path"),
      R"pbdoc(
      EnsurePathExists
      ================
      
      Makes sure directory exists

      Parameters
      ----------

      path : str

          String containing directory
      )pbdoc");

  // BinaryFile
  py::class_<BinaryFile>(h, "BinaryFile")
      .def(py::init<>())
      .def(py::init<const str>(), py::arg("fname"))
      .def("fread", &BinaryFile::fread<int8_t>)
      .def("fread", &BinaryFile::fread<int16_t>)
      .def("fread", &BinaryFile::fread<float>)
      .def("fread", &BinaryFile::fread<double>)
      .def("freadc", &BinaryFile::freadc<int8_t>)
      .def("freadc", &BinaryFile::freadc<int16_t>)
      .def("freadc", &BinaryFile::freadc<float>)
      .def("freadc", &BinaryFile::freadc<double>)
      .def("fseek", &BinaryFile::fseek<int8_t>)
      .def("fseek", &BinaryFile::fseek<int16_t>)
      .def("fseek", &BinaryFile::fseek<float>)
      .def("fseek", &BinaryFile::fseek<double>)
      .def("fseekc", &BinaryFile::fseekc<int8_t>)
      .def("fseekc", &BinaryFile::fseekc<int16_t>)
      .def("fseekc", &BinaryFile::fseekc<float>)
      .def("fseekc", &BinaryFile::fseekc<double>)
      .def("ftell", py::overload_cast<>(&BinaryFile::ftell<int8_t>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftell<int16_t>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftell<float>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftell<double>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftellc<int8_t>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftellc<int16_t>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftellc<float>))
      .def("ftell", py::overload_cast<>(&BinaryFile::ftellc<double>))
      .def("fopen", py::overload_cast<>(&BinaryFile::fopen))
      .def("fopen", py::overload_cast<const str>(&BinaryFile::fopen), py::arg("fname"))
      .def("fclose", &BinaryFile::fclose);

  // YamlParser
  py::class_<YamlParser>(h, "YamlParser")
      .def(py::init<>())
      .def(py::init<const str>(), py::arg("fname"))
      .def("parse", py::overload_cast<>(&YamlParser::parse))
      .def("parse", py::overload_cast<const str>(&YamlParser::parse), py::arg("fname"))
      .def("Exists", &YamlParser::Exists, py::arg("key"))
      .def("GetVar", py::overload_cast<const str>(&YamlParser::GetVar<str>), py::arg("key"))
      .def("GetVar", py::overload_cast<const str>(&YamlParser::GetVar<bool>), py::arg("key"))
      .def("GetVar", py::overload_cast<const str>(&YamlParser::GetVar<int>), py::arg("key"))
      .def("GetVar", py::overload_cast<const str>(&YamlParser::GetVar<float>), py::arg("key"))
      .def("GetVar", py::overload_cast<const str>(&YamlParser::GetVar<double>), py::arg("key"))
      .def(
          "GetVar",
          py::overload_cast<const str>(&YamlParser::GetVar<std::vector<bool>>),
          py::arg("key"))
      .def(
          "GetVar",
          py::overload_cast<const str>(&YamlParser::GetVar<std::vector<int>>),
          py::arg("key"))
      .def(
          "GetVar",
          py::overload_cast<const str>(&YamlParser::GetVar<std::vector<float>>),
          py::arg("key"))
      .def(
          "GetVar",
          py::overload_cast<const str>(&YamlParser::GetVar<std::vector<double>>),
          py::arg("key"));
}