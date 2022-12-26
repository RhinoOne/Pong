# Pong
Pong is a table tennis–themed twitch arcade sports video game, featuring simple two-dimensional graphics, manufactured by Atari and originally released in 1972.\
This implementation has two modes: PVP and PVE
# Installation
To build, you need Cmake and vcpkg, in which the libraries are installed:
1. SDL2
2. SDL2-mixer
3. SDL2-ttf
4. Clone the repository
5. Using Cmake (gui), specify the path of the cloned repository in the line "Where is the source code"
6. Specify the path where you want to get the finished project in the line "Where to build the binaries"
7. In the "Environment" section, find "CMAKE_PREFIX_PATH" and set the value by specifying the path to vcpkg (..\vcpkg\installed\x:64-winwows)
8. Now everything is ready. We press the "Generate" button and we get the assembly project in the folder that was previously specified.
# Possible problems
In debug mode, if you have the above libraries not fully loaded, problems may arise. Often there may be a shortage of files with the suffix d (SDL2d.dll). To do this, you can manually add the missing dll files or use vcpkg
