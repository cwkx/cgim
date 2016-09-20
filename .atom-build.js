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
         atomCommandName: "CGIM:debug build"
      },
      "Build Optimized Assembly": {
         "cmd": cmdPre + cmdBuild + "-g -O3 " + cmdFlags + cmdLibs + cmdOut,
         keymap: "f6",
         atomCommandName: "CGIM:release build"
      },
      "View Assembly": {
         cmd: cmdPre +
            "gdb --batch -ex \"set disassembly-flavor intel\" -ex \"disas /s {SELECTION}\" cgim > out.asm",
         keymap: "f7",
         atomCommandName: "CGIM:view assembly"
      }
   }
};
