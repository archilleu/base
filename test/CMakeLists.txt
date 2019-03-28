#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
aux_source_directory(. DIR_TESTS)
#---------------------------------------------------------------------------
#generate test
set(TEST_computer_info test_computer_info)
add_executable(${TEST_computer_info} test_computer_info.cc)

set(TEST_file_helper test_file_helper)
add_executable(${TEST_file_helper} test_file_helper.cc)

set(TEST_logger test_logger)
add_executable(${TEST_logger} test_logger.cc)

set(TEST_md5 test_md5)
add_executable(${TEST_md5} test_md5.cc)
#---------------------------------------------------------------------------
#add include path
#include_directories(${LIBRARY_OUTPUT_PATH_INC})
#---------------------------------------------------------------------------
#add lib path
#link_directories(${CMAKE_INSTALL_PREFIX}/src})
#---------------------------------------------------------------------------
#add link lib
set(LIBNAME base)
target_link_libraries(${TEST_computer_info} ${LIBNAME})

target_link_libraries(${TEST_file_helper} ${LIBNAME})

target_link_libraries(${TEST_logger} ${LIBNAME})

target_link_libraries(${TEST_md5} ${LIBNAME})
#---------------------------------------------------------------------------
#add test
add_test(test_run ${EXECUTABLE_OUTPUT_PATH}/${TEST_computer_info})

add_test(test_run ${EXECUTABLE_OUTPUT_PATH}/${TEST_file_helper})

add_test(test_run ${EXECUTABLE_OUTPUT_PATH}/${TEST_logger})

add_test(test_run ${EXECUTABLE_OUTPUT_PATH}/${TEST_logger})
#---------------------------------------------------------------------------
