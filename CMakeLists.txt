cmake_minimum_required (VERSION 3.10)
project(mandelbrot)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# export settings for clangd LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# fetch matplot++
include(FetchContent)
set(MATPLOTPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(MATPLOTPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(MATPLOTPP_WITH_BOOST OFF CACHE BOOL "" FORCE)
set(MATPLOTPP_WITH_OPENGL OFF CACHE BOOL "" FORCE)
set(MATPLOTPP_WITH_LAPACK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
    GIT_TAG v1.2.2 # latest
)
FetchContent_MakeAvailable(matplotplusplus)


find_package(Threads REQUIRED)
find_package(TBB REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE  
Matplot++::matplot
TBB::tbb
Threads::Threads
)

