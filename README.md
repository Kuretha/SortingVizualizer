# Sorting Visualizer
- This visualizer simply create a bar representing each generated number of array and highlight current index to be sorted

## Visualizer Library
- SDL2

## How to run this code
to run code you need to have SDL2 installed
- https://www.youtube.com/watch?v=N5CZLSVU0DA CLion SDL2 set environment
- https://gist.github.com/416rehman/4b5a88f5e5f033dfe8f7abd7bb768bde FindSDL2.cmake
- https://github.com/libsdl-org/SDL/releases/tag/release-2.30.0 SDL 2 library download (SDL2-devel-2.30.0-mingw.zip)

## How to use the function (for simple sort)
- call renderBars(v, renderer) v = array size, renderer is to render the bar
- tested on selection sort and bubble sort

## How to use the function (for complex looking sort)
- there are no way to use it
- ~~maybe i need to customize it, sigh...~~
- the complex function example can be found in the code with TimSort name

### Cmake Config
- can be found in CmakeLists.txt
- cmake_modules (SDL2)

### Known issues in v1
- defined array cannot reach 1000
- max array tested 800
- window cant be dragged
- pressing the window will make the app crashing

### External library version
- SDL2 2.30.0