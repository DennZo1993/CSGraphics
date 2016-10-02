set(Main_SRCS main.cpp)

add_executable(SudokuSolver ${Main_SRCS})

if (("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang") OR
    ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU"))
  target_compile_options(SudokuSolver PRIVATE -Wall -Wextra -Werror)
endif()


target_link_libraries(SudokuSolver libSolver)

install(TARGETS SudokuSolver DESTINATION bin)
