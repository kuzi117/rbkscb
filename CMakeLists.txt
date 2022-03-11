cmake_minimum_required(VERSION 3.15)
project(rbkscb)

set(CMAKE_CXX_STANDARD 17)

set(rbkscb_src
  "${CMAKE_CURRENT_SOURCE_DIR}/AppState.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Cube.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleCallbacks.cpp"
)

add_executable(rbkscb ${rbkscb_src})
target_link_libraries(rbkscb glut GLU GL)
