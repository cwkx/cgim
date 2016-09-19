// main commands for atom-build, currently only tested on linux
var cmdPre = "cd build && ";
var cmdBuild = "clang ../src/cg_app.c ";
var cmdFlags = "-std=c89 -pedantic -Werror ";
var cmdLibs = "`pkg-config --cflags --libs --static glfw3 glew x11 xxf86vm` ";
var cmdOut = "-o cgim";

module.exports = {
   cmd: cmdPre + cmdBuild + "-g " + cmdFlags + cmdLibs + cmdOut,
   name: "Build",
   sh: true,
   keymap: "f5",
   atomCommandName: "CGIM:debug build",
   preBuild: function() {},
   postBuild: function() {},
   targets: {
      "Run": {
         cmd: cmdPre + "./cgim",
         keymap: "f6",
         atomCommandName: "CGIM:run"
      },
      "View Assembly": {
         cmd: cmdPre +
            "gdb --batch -ex \"disas {SELECTION}\" cgim > out.asm",
         atomCommandName: "CGIM:view assembly"
      },
      "View Assembly CLANG TEST": {
         cmd: cmdPre + cmdBuild + "-g -S -emit-llvm " + cmdFlags,
         keymap: "f7",
         atomCommandName: "CGIM:view assembly clang test"
      },
      "Release Build": {
         "cmd": cmdPre + cmdBuild + "-O2 " + cmdFlags + cmdLibs + cmdOut,
         keymap: "f8",
         atomCommandName: "CGIM:release build"
      }
   }
};
