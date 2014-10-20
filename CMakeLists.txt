cmake_minimum_required(VERSION 2.8.4)
project(TakeOne)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-DENABLE_DEBUG")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

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
    lib/GLFW/lib/${PLATFORM}
    lib/GLEW/lib/${PLATFORM}
    )

set(INCLUDE_DIRS
    include
    lib/GLFW/include
    lib/GLEW/include
    )

set(SOURCE_FILES
    src/Engine.cpp
    src/main.cpp
    )

if(PLATFORM STREQUAL "Win32")
    set(LINK_FILES
        glfw3dll
        glew32
        opengl32
        )
else(PLATFORM STREQUAL "Win32")
    set(LINK_FILES
        glfw
        GLEW
        GL
        )
endif(PLATFORM STREQUAL "Win32")


include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})

add_executable(TakeOne ${SOURCE_FILES})
target_link_libraries(TakeOne ${LINK_FILES})


#postbuild commands; copy dll's
if(PLATFORM STREQUAL "Win32")
    add_custom_command(TARGET TakeOne POST_BUILD            # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
            ${CMAKE_CURRENT_LIST_DIR}/lib/GLEW/lib/glew32.dll                 # <--this is in-file
            ${CMAKE_CURRENT_LIST_DIR}/bin/                                            # <--this is out-file path
            )

    add_custom_command(TARGET TakeOne POST_BUILD            # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
            ${CMAKE_CURRENT_LIST_DIR}/lib/GLFW/lib/dynamic/glfw3.dll                  # <--this is in-file
            ${CMAKE_CURRENT_LIST_DIR}/bin/                                            # <--this is out-file path
            )
endif(PLATFORM STREQUAL "Win32")