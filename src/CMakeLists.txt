#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
#aux_source_directory(<dir> <variable>)
aux_source_directory(. DIR_SRCS)
aux_source_directory(./json DIR_SRCS)
#---------------------------------------------------------------------------
#generate static library
#add_library(libname ${<dir>})
set(LIBNAME base)
add_library(${LIBNAME} ${DIR_SRCS})
#---------------------------------------------------------------------------
#install target 
install(TARGETS ${LIBNAME} DESTINATION ${LIBRARY_OUTPUT_PATH_LIB})

#base
set(HEADERS
    any.h
    computer_info.h
    crc64.h
    file_helper.h
    function.h
    logger.h
    md5.h
    memory_block.h
    noncopyable.h
    thread.h
    thread_local.h
    timestamp.h
    )

#json
set(HEADERS_JSON
    json/json_reader.h
    json/json_writer.h
    json/value.h
    )
install(FILES ${HEADERS} DESTINATION ${LIBRARY_OUTPUT_PATH_INC})
install(FILES ${HEADERS_JSON} DESTINATION ${LIBRARY_OUTPUT_PATH_INC}/json)
#---------------------------------------------------------------------------

