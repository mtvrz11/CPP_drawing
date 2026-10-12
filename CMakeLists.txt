cmake_minimum_required(VERSION 3.15)
project(DrawingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tento øádek øíká kompilátoru, kde má hledat hlavièkové soubory.
# Díky tomu mùžeš v main.cpp napsat jen #include "math/Math.h"
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Seznam všech souborù projektu
add_executable(
    drawing 
    "src/main.cpp" 
    src/math/Math.h
    src/math/Math.cpp
    src/shapes/Line.h
    src/shapes/Line.cpp
    src/shapes/IShape.h
    src/shapes/Rect.h
    src/shapes/Rect.cpp
    src/shapes/Circle.h
    src/shapes/Circle.cpp
    src/core/App.h
    src/core/App.cpp
 "src/renderer/ICanvas.h" "src/renderer/SvgCanvas.h" "src/renderer/SvgCanvas.cpp" "src/renderer/PgmCanvas.h" "src/renderer/PgmCanvas.cpp")

if(MSVC)
    target_compile_options(drawing PRIVATE /W4 /WX)
else()
    target_compile_options(drawing PRIVATE -Wall -Wextra -Werror)
endif()