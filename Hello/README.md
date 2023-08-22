
# Hello

This project contains the basic "Hello, World" program that prints a one line greeting on the
console and exits. Getting this simple program to work is an important first step when learning
C++, because it verifies that your development environment is set up correctly and that you know
how to use it.

This folder contains build control files for several build systems:

+ A Makefile for use with the `make` utility (and also used indirection by Visual Studio Code,
  Eclipse/CDT, and CLion).

+ A .vscode folder for Visual Studio Code settings.

+ A CDT project for Eclipse (defined to use the Cygwin toolchain). The files are .project,
  .cproject, and the folder .settings.

+ A solution and project file for Visual Studio. The files are Hello.sln, Hello.vcxproj,
  and Hello.vcxproj.filters.

+ A CodeBlocks project file. The file is Hello.cbp.

To use CLion on this project, simply ask CLion to open the folder containing the Makefile. It
will know what to do. CLion may ask you which toolchain you want to use. On Windows, be sure to
select Cygwin. CLion will create a .idea folder where it puts all its project-specific settings.
If you change things like the window layout, the projet code style, etc., CLion will write
information into the .idea folder to record those changes. CLion will automatically generate
"run configurations" based on the Makefile targets it finds. You can build the program by
selecting the "all" run configuration.

The doc folder contains the documentation for the program. Obviously a trivial program like this
does not require any documentation, but the folder is here anyway as a place holder and a
reminder to include documentation on more complex programs. The file Doxyfile is a configuration
file for the doxygen documentation generator tool. When the tool is run it extracts
documentation from the source files and places it into the doc/HTML folder.

Yes, all of this is overkill for such a simple program, of course. However, the intent is to
provide a framework for future projects. By copying this folder and renaming/editing various
files, you can create working environment for a new project using your development system of
choice. You might (or might not) find this easier than trying to configure a new project from
scratch with all your desired settings.

Note that the .gitignore file shows which file name patterns can be ignored by version control.
It is only relevant if you are using version control. If you use a version control system (VCS)
other than Git, you will have to adapt the information in .gitignore to whichever VCS you are
using.

Peter Chapin  
spicacality@kelseymountain.org  
