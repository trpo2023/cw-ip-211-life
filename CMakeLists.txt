project(prog.exe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

file(GLOB CPPS "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})

target_include_directories(${PROJECT_NAME} PRIVATE includes includes/database)



