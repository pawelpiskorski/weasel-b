cmake_minimum_required(VERSION 3.10)

project (weasel-b LANGUAGES C)

add_executable(weasel-b
    ./weasel_b.c)

  add_custom_target(symlink ALL
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "gcc"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "c++"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "c89-gcc"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "c99-gcc"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "cc"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "clang"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "clang-6.0"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "clang++-6.0"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "g++"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "g++-7"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "gcc"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "gcc-7"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "gcc_backup"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "x86_64-linux-gnu-g++"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "x86_64-linux-gnu-g++-7"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "x86_64-linux-gnu-gcc"
  COMMAND ${CMAKE_COMMAND} -E create_symlink  "${CMAKE_CURRENT_BINARY_DIR}/weasel-b" "x86_64-linux-gnu-gcc-7"
  COMMENT "creating symbolic links to weasel"
  )
