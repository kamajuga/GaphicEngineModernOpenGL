#Mother
cmake_minimum_required(VERSION 3.30.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    add_compile_options(/W4)
    add_compile_options(/wd4505)
    add_compile_options(/WX)
endif()

project(ProjetModernOpenGL)

set(CMAKE_CXX_STANDARD 11)				
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXE_NAME Core)

add_subdirectory(Dependencies)
add_subdirectory(LibMath)
add_subdirectory(Physics)
add_subdirectory(Resources)
add_subdirectory(LowRenderer)
add_subdirectory(DataStructure)
add_subdirectory(Core)




if(MSVC)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXE_NAME})
endif()