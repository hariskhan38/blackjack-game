BLACK-JACK
==========

PROJECT OVERVIEW

BLACK-JACK is a C++ desktop game developed as a Programming Fundamentals project. It uses the SFML (Simple and Fast Multimedia Library) to provide a graphical user interface.

The project demonstrates the use of C++ programming concepts, functions, game logic, and graphical elements to create an interactive game.

TECHNOLOGIES USED

Programming Language: C++
IDE: Microsoft Visual Studio 2026
C++ Standard: C++20
Graphics Library: SFML 2.6.2

PROJECT FILES

main.cpp - Main program entry point.
game.h - Contains game function declarations.
game.cpp - Contains game functions and game logic.
GUI.cpp - Handles the graphical user interface.
playerData - Stores player data.
lib/SFML - Contains the external SFML library files.

PREREQUISITES

Microsoft Visual Studio 2026
Desktop Development with C++ workload
C++20 support
SFML 2.6.2 library

INSTALLATION AND SETUP

First, copy or download the complete BLACK-JACK project folder to your computer.

Make sure the project contains the source files, Visual Studio project files, and the lib/SFML folder.

Open the BLACK-JACK.slnx file in Visual Studio 2026.

Wait for Visual Studio to load the project.

Select x64 as the target platform.

Select either Debug or Release as the build configuration.

SFML CONFIGURATION

The project uses relative paths to locate the SFML library inside its own directory.

Additional Include Directories:
$(ProjectDir)lib\SFML\include

Additional Library Directories:
$(ProjectDir)lib\SFML\lib

Required SFML Libraries:

Debug Configuration:
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib

Release Configuration:
sfml-graphics.lib
sfml-window.lib
sfml-system.lib

BUILDING AND RUNNING THE PROJECT

Open BLACK-JACK.slnx in Visual Studio.

Select the x64 platform and choose the Debug or Release configuration.

Go to Build and select Build Solution.

Wait for Visual Studio to complete the build.

Make sure the required SFML DLL files are available beside the generated executable. These files can be found in the lib/SFML/bin directory. Use the Debug DLL versions for Debug builds and the Release DLL versions for Release builds.

After a successful build, select Debug and then Start Without Debugging to run the game.

CONFIGURATION AND ENVIRONMENT

The project is configured for a 64-bit Windows environment using Visual Studio 2026 and SFML 2.6.2.

The graphical interface uses the Arial font available in the Windows Fonts directory.

The project uses the playerData file for storing player information.

TROUBLESHOOTING

If Visual Studio cannot find SFML header files, check the Additional Include Directories setting.

If the linker reports that SFML libraries cannot be found, check the Additional Library Directories setting.

If the program builds successfully but does not start because an SFML DLL is missing, copy the required DLL files from lib/SFML/bin into the executable's directory.

If the project does not open, make sure you are opening the BLACK-JACK.slnx file and that the Visual Studio C++ workload is installed.

If the graphical interface cannot find the Arial font, make sure Arial is installed on the Windows system.

SCREENSHOTS

Screenshots of the running game and its graphical interface should be included here to demonstrate the final application.

LIBRARY INFORMATION

The external library used in this project is SFML (Simple and Fast Multimedia Library), version 2.6.2.

The project uses the SFML Graphics, Window, and System modules.

For additional library information, refer to LIBRARIES.txt and the SFML documentation.

GITHUB REPOSITORY

Project repository:
https://github.com/hariskhan38/blackjack-game