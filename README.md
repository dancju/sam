# sam

![license](https://img.shields.io/github/license/nerddan/sam.svg)

This is a tool that converts strings to images of [suffix automaton](https://en.wikipedia.org/wiki/Suffix_automaton).

It is a pure front-end application, i.e. the server only hosts static assets while all logics are executed on the browser. The process of "from string to automaton" can be split into three steps:

1. Transforming the string to the corresponding suffix automaton, where the time complexity is a linear function to the length of the string.
1. Serialising the topological structure of the automaton into [DOT format](https://en.wikipedia.org/wiki/DOT_%28graph_description_language%29).
1. Transforming the DFA from DOT to SVG format with the help of [Viz.js](https://github.com/mdaines/viz.js).

The first two steps were implemented in C++ and compiled into WebAssembly with the help of [Emscripten](https://github.com/kripken/emscripten).

## License

This repository is distributed under a WTFPL.
