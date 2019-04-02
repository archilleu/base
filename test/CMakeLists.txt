#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
aux_source_directory(. DIR_TESTS)
#---------------------------------------------------------------------------
#generate test
set(TEST_function test_function)
add_executable(${TEST_function} test_function.cc)

set(TEST_computer_info test_computer_info)
add_executable(${TEST_computer_info} test_computer_info.cc)

set(TEST_file_helper test_file_helper)
add_executable(${TEST_file_helper} test_file_helper.cc)

set(TEST_logger test_logger)
add_executable(${TEST_logger} test_logger.cc)

set(TEST_md5 test_md5)
add_executable(${TEST_md5} test_md5.cc)

set(TEST_thread test_thread)
add_executable(${TEST_thread} test_thread.cc)

set(TEST_thread_local test_thread_local)
add_executable(${TEST_thread_local} test_thread_local.cc)

set(TEST_timestamp test_timestamp)
add_executable(${TEST_timestamp} test_timestamp.cc)

set(TEST_json test_json)
add_executable(${TEST_json} test_json.cc)
#---------------------------------------------------------------------------
#add include path
#include_directories(${LIBRARY_OUTPUT_PATH_INC})
#---------------------------------------------------------------------------
#add lib path
#link_directories(${CMAKE_INSTALL_PREFIX}/src})
#---------------------------------------------------------------------------
#add link lib
set(LIBNAME base)
target_link_libraries(${TEST_function} ${LIBNAME})

target_link_libraries(${TEST_computer_info} ${LIBNAME})

target_link_libraries(${TEST_file_helper} ${LIBNAME})

target_link_libraries(${TEST_logger} ${LIBNAME})

target_link_libraries(${TEST_md5} ${LIBNAME})

target_link_libraries(${TEST_thread} ${LIBNAME} pthread)

target_link_libraries(${TEST_thread_local} ${LIBNAME} pthread)

target_link_libraries(${TEST_timestamp} ${LIBNAME})

target_link_libraries(${TEST_json} ${LIBNAME})
#---------------------------------------------------------------------------
#add test
add_test(${TEST_function} ${EXECUTABLE_OUTPUT_PATH}/${TEST_function}
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_test(${TEST_computer_info} ${EXECUTABLE_OUTPUT_PATH}/${TEST_computer_info})

add_test(${TEST_file_helper} ${EXECUTABLE_OUTPUT_PATH}/${TEST_file_helper})

add_test(${TEST_logger} ${EXECUTABLE_OUTPUT_PATH}/${TEST_logger})

add_test(${TEST_md5} ${EXECUTABLE_OUTPUT_PATH}/${TEST_md5}
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_test(${TEST_thread} ${EXECUTABLE_OUTPUT_PATH}/${TEST_thread})

add_test(${TEST_thread_local} ${EXECUTABLE_OUTPUT_PATH}/${TEST_thread_local})

add_test(${TEST_timestamp} ${EXECUTABLE_OUTPUT_PATH}/${TEST_timestamp})

add_test(${TEST_json} ${EXECUTABLE_OUTPUT_PATH}/${TEST_json}
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
#---------------------------------------------------------------------------
