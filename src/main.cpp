#include <emscripten/bind.h>

#include "sam.cpp"

string str2sam_dot(const string &str) {
  SAM sam;
  for (auto i : str)
    sam.insert(i);
  return sam.to_dot();
}

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::function("str2sam_dot", &str2sam_dot);
}
