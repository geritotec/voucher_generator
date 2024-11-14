cmake_minimum_required(VERSION 3.10)

project(MyCrowApp)

set(CMAKE_CXX_STANDARD 17)

# Include the directories for Crow and any other dependencies
include_directories(/Users/geronimosotelolopez/Desktop/pdf_generator/include)
include_directories(/usr/local/Cellar/asio/1.30.2/include)

# Add your main source file
add_executable(my_crow_app src/main.cpp)

# Link any necessary libraries (if you're using Boost or Asio, for example)
# target_link_libraries(my_crow_app boost_system pthread)
