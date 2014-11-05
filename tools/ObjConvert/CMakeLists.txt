cmake_minimum_required(VERSION 2.8.4)
project(ObjConvert)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

if(UNIX)
  if(APPLE)
    set(PLATFORM "Apple")
  else(APPLE)
    set(PLATFORM "Linux")
  endif(APPLE)
else(UNIX)
  if(WIN32)
    set(PLATFORM "Win32")
  else(WIN32)
    set(PLATFORM "Unknown")
  endif(WIN32)
endif(UNIX)

set(LINK_DIRS
    lib/assimp/lib/${PLATFORM}
    )

set(INCLUDE_DIRS
    lib/assimp/include
    )

FILE(GLOB SOURCE_FILES "src/*.cpp")

if(PLATFORM STREQUAL "Win32")
    set(LINK_FILES
        assimp
        )
else(PLATFORM STREQUAL "Win32")
    set(LINK_FILES
        assimp
        )
endif(PLATFORM STREQUAL "Win32")

link_directories(${LINK_DIRS})
add_executable(ObjConvert ${SOURCE_FILES})
target_link_libraries(ObjConvert ${LINK_FILES})

if(PLATFORM STREQUAL "Win32")
    add_custom_command(TARGET ObjConvert POST_BUILD            # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
            ${CMAKE_CURRENT_LIST_DIR}/lib/assimp/lib/Win32/assimp.dll                 # <--this is in-file
            ${CMAKE_CURRENT_LIST_DIR}/bin/                                            # <--this is out-file path
            )
endif(PLATFORM STREQUAL "Win32")