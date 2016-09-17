# cgim
an experimental framework for computer graphics, image processing, machine learning and pattern analysis

### about
- written in C89 for compatibility
- MIT license
- modular codebase as stb-style single-file headers

### roadmap
- profile and implement fast gaussian blur
- port our level set segmentation implementation
- port our path tracer
- MATLAB wrapper
- optional lua/squirrel bindings
- optional lua preprocessor

### compile instructions
- recommended to use atom or vim
- run the following from the build directory, or use cmake . && make && ./cgim
- ````clang ../src/cg_app.c -std=c89 -pedantic -Werror `pkg-config --cflags --libs --static glfw3 glew x11 xxf86vm` -o cgim && ./cgim````
- recommended to use formatter-astyle atom package
  - allman brackets
  - 3 indent, tab
  - all unchecked except keep one line blocks and keep one line statements
