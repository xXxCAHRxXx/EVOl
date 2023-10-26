#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Server)

#--------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries include
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Sources include
add_executable(${PROJECT_NAME} main.cpp draw.cpp draw.hpp emptiness.cpp emptiness.hpp food.cpp food.hpp object.cpp object.hpp poison.cpp poison.hpp wall.cpp wall.hpp world.cpp world.hpp direction.cpp direction.hpp bot.cpp bot.hpp crossover_mutation.cpp crossover_mutation.hpp processing_world.hpp processing_world.cpp) ###тут

# Libraries include
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# Output file name settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .exe)

#--------------------------------------------------------------------------------
