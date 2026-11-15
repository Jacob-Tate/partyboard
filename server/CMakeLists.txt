# Party Board netplay relay server. Builds on its own (no game sources or GPU libraries):
#   cmake -S server -B build/server -DCMAKE_BUILD_TYPE=Release
#   cmake --build build/server
cmake_minimum_required(VERSION 3.20)
project(partyboard_server CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(enet
        GIT_REPOSITORY https://github.com/lsalzman/enet.git
        GIT_TAG v1.3.18
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(enet)

add_executable(partyboard-server main.cpp)
target_include_directories(partyboard-server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${enet_SOURCE_DIR}/include)
target_link_libraries(partyboard-server PRIVATE enet)
if (WIN32)
    target_link_libraries(partyboard-server PRIVATE ws2_32 winmm)
endif ()

add_executable(partyboard-server-test test_client.cpp)
target_include_directories(partyboard-server-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${enet_SOURCE_DIR}/include)
target_link_libraries(partyboard-server-test PRIVATE enet)
if (WIN32)
    target_link_libraries(partyboard-server-test PRIVATE ws2_32 winmm)
endif ()

install(TARGETS partyboard-server RUNTIME DESTINATION bin)
