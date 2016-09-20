# cgim
please don't use this yet! it's an experimental framework for my own personal research in computer graphics, image processing, machine learning and pattern analysis

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
- see .atom-build.js for a list of command line commands
- recommended to use formatter-astyle atom package
  - allman brackets
  - all unchecked except keep one line blocks and keep one line statements

### debugging instructions
- install atom package "dbg-gdb"
- press ````F9```` somewhere in code to set a breakpoint
- right click build/cgim in atom, and ````Debug>Build```` with GDB
- double click a function name and press  ````F7```` then open "build > out.asm"
 - output assembly is pretty with "language-assembly" installed
 - output assembly is good on a right panel
