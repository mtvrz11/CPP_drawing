cmake_minimum_required(VERSION 3.15)
project(DrawingApp)

# Nastavení standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Hlavní spustitelný soubor
add_executable(drawing main.cpp)

# Zapnutí užiteèných varování pro rùzné pøekladaèe
if(MSVC)
    target_compile_options(drawing PRIVATE /W4 /WX)
else()
    target_compile_options(drawing PRIVATE -Wall -Wextra -Werror)
endif()