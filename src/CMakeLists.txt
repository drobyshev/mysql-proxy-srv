project(ProxySrv)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(Boost 1.64.0 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIR})

set(SRC
    Optional.h
    Config.h
    Config.cpp
    Parser.h
    Parser.cpp
    Logger.h
    Logger.cpp
    Session.h
    Session.cpp
    SessionManager.h
    SessionManager.cpp
    Server.h
    Server.cpp
    Main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -Wpedantic)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
