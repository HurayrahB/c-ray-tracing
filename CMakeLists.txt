cmake_minimum_required ( VERSION 3.23 )

project ( raytracing
  VERSION 0.1
  LANGUAGES CXX
)

set ( CMAKE_CXX_STANDARD 17 )

add_executable( myScene src/main.cpp )