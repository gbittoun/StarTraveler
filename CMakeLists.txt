cmake_minimum_required(VERSION 2.8)

project(StarTraveler)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB StarTraveler_files "*.cpp")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${SDL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${StarTraveler_files})

target_link_libraries(${PROJECT_NAME}
                      ${SDL_LIBRARY}
                      ${GLEW_LIBRARIES}
                      ${OPENGL_LIBRARIES}
)