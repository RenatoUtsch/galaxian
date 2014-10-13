##
 # Autor: Renato Utsch Gonçalves
 # Ciência da Computação, UFMG
 # Computação Gráfica
 # Trabalho Prático 1 - Galaxian
 #
 # Copyright (c) 2014 Renato Utsch
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documentation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 # copies of the Software, and to permit persons to whom the Software is
 # furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 # THE SOFTWARE.
 ##

# CMakeLists.txt file for compiling the project with CMake.

# Basic configuration
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
project( galaxian C )

set( GALAXIAN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( GALAXIAN_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set( GALAXIAN_DEFINITIONS "" )

# Add gcc options
if( UNIX )
    set( GALAXIAN_DEFINITIONS
        "${GALAXIAN_DEFINITIONS} -Wall -Wextra -Werror -Wno-deprecated-declarations -Wno-unused-parameter -Wno-comment -g -pg" )
endif()

# Fix compilation on windows.
if(WIN32)
    if(MSVC)
        set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
            "${GALAXIAN_SOURCE_DIR}/w32/msvc/freeglut/lib" )
        set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
            "${GALAXIAN_SOURCE_DIR}/w32/msvc/freeglut/include" )
    endif()
    if(MINGW)
        set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
            "${GALAXIAN_SOURCE_DIR}/w32/mingw/freeglut/lib" )
        set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
            "${GALAXIAN_SOURCE_DIR}/w32/mingw/freeglut/include" )
    endif()
endif()

# Include glfw
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "no examples" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "no tests" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL "no docs" )
set( GLFW_INSTALL OFF CACHE BOOL "no installation" )
add_subdirectory( "${GALAXIAN_SOURCE_DIR}/3rdparty/glfw" )

# Include soil.
add_subdirectory( "${GALAXIAN_SOURCE_DIR}/3rdparty/soil" )

# Find glut.
find_package( OpenGL REQUIRED )
find_package( GLUT REQUIRED )

# galaxian sources
set( GALAXIAN_SOURCE_FILES "${GALAXIAN_SOURCE_DIR}/source/engine.c"
    "${GALAXIAN_SOURCE_DIR}/source/main.c"
    "${GALAXIAN_SOURCE_DIR}/source/objects.c"
    "${GALAXIAN_SOURCE_DIR}/source/util.c"
    "${GALAXIAN_SOURCE_DIR}/source/vector.c"
    "${GALAXIAN_SOURCE_DIR}/source/system/ai.c"
    "${GALAXIAN_SOURCE_DIR}/source/system/animation.c"
    "${GALAXIAN_SOURCE_DIR}/source/system/input.c"
    "${GALAXIAN_SOURCE_DIR}/source/system/physics.c"
    "${GALAXIAN_SOURCE_DIR}/source/system/renderer.c" )


# Compile
add_definitions( ${GALAXIAN_DEFINITIONS} )
include_directories( "${GALAXIAN_SOURCE_DIR}/3rdparty/glfw/include"
                     "${GALAXIAN_SOURCE_DIR}/3rdparty/soil/include"
                     ${OPENGL_INCLUDE_DIRS}
                     ${GLUT_INCLUDE_DIRS}
                     ${GLUT_INCLUDE_DIR} )
add_executable( galaxian ${GALAXIAN_SOURCE_FILES} )
target_link_libraries( galaxian glfw SOIL ${GLFW_LIBRARIES} ${SOIL_LIBRARIES}
                       ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )

# Resource files.
add_custom_command( TARGET galaxian PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/resource $<TARGET_FILE_DIR:galaxian> )
