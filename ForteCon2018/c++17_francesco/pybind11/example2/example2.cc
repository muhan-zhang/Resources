#include <pybind11/pybind11.h>

namespace py = pybind11;

class A {
public:
  A(int i) : i_(i) {}
  int i() const { return i_; }
  void set(int i) { i_ = i; }

private:
  int i_;
};

int add(int i, int j) { return i + j; }

PYBIND11_MODULE(example2, m) {
  m.doc() = "pybind11 example plugin"; // optional module docstring

  m.def("add", &add, "A function which adds two numbers");

  py::class_<A>(m, "A")
      .def(py::init<int>()).def("sqr", [](const A &a) { return a.i() * a.i(); });
}

// Expose class functions
// .def("i", &A::i, "Get i")
// .def("set", &A::set, "Set i")

// Adorn the class with python functions
//
// .def("__str__", [](const A &a) { return std::to_string(a.i()); })
// .def("__repr__", [](const A &a) { return "A -> { i_ = " + std::to_string(a.i()) + "}"; });
