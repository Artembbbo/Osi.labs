cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("lab1")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (Creator creator.cpp)
add_executable (Reporter reporter.cpp)
add_executable (MainApp main.cpp)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set_target_properties(Creator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set_target_properties(Reporter PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set_target_properties(MainApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
