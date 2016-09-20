// main commands for atom-build, currently only tested on linux
var cmdPre = "cd build && ";
var cmdBuild = "clang ../src/cg_app.c ";
var cmdFlags = "-std=c89 -pedantic -Werror "; // -fsanitize=address
var cmdLibs = "`pkg-config --cflags --libs --static glfw3 glew x11 xxf86vm` ";
var cmdOut = "-o cgim";

module.exports = {
   preBuild: function() {},
   postBuild: function() {},
   targets: {
      "Run ": {
         cmd: cmdPre + "./cgim",
         keymap: "f4",
         atomCommandName: "CGIM:run"
      },
      "Debug and Run": {
         cmd: cmdPre + cmdBuild + "-g " + cmdFlags + cmdLibs + cmdOut +
            " && ./cgim",
         name: "Build",
         sh: true,
         keymap: "f5",
         atomCommandName: "CGIM:debug and run"
      },
      "Build Optimized Assembly": {
         "cmd": cmdPre + cmdBuild + "-g -O3 " + cmdFlags + cmdLibs + cmdOut,
         keymap: "f6",
         atomCommandName: "CGIM:build optimized assembly"
      },
      "View Assembly": {
         cmd: cmdPre +
            "gdb --batch -ex \"set disassembly-flavor intel\" -ex \"disas /s {SELECTION}\" cgim > out.asm",
         keymap: "f7",
         atomCommandName: "CGIM:view assembly"
      },
      "Run Preprocessor": {
         preBuild: function () {

            var editor = atom.workspace.getActiveTextEditor();
            var lines = editor.buffer.lines;

            var file = editor.buffer.file.path;
            /* editor.buffer.setText("kittens"); */
            console.log(file);

            // (optional 1) put strings into string
            // replace strings with code

            // for each character,
            // if { found add func
            // then find }         (skips nested ones)
            // append to functionsOrStructsTable

            // insert header code (commentsTable)

            // for each functionOrStruct
            // get T1 or T2 types
            // for each pair
            // paste forward declaration
            // (advanced) pad forward declarations by max of column sizes

            // insert implementations code (commentsTable)

            // for each functionOrStruct
            // get T1 or T2 types
            // for each pair
            // paste function and replace T, T1, or T2

            // insert footer code (comments table)

         },
         "cmd": "echo prc preprocessor complete!",
         keymap: "f8",
         atomCommandName: "CGIM:run preprocessor"
      }
   }
};
