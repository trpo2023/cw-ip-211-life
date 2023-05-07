project(prog.exe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

file(GLOB CPPS "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})

target_include_directories(${PROJECT_NAME} PRIVATE includes includes/database)

# ****** CTESTS ******

add_executable(test.exe ./test/main.cpp ./src/input.cpp ./src/logics.cpp ./test/test.cpp)

target_include_directories(test.exe PRIVATE thirdparty includes/database includes)

# add_test(NAME test COMMAND test)

