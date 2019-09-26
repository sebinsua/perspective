set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

set(ARROW_SRCS
    src/arrow/array.cc
    src/arrow/builder.cc
    src/arrow/array/builder_adaptive.cc
    src/arrow/array/builder_base.cc
    src/arrow/array/builder_binary.cc
    src/arrow/array/builder_decimal.cc
    src/arrow/array/builder_dict.cc
    src/arrow/array/builder_nested.cc
    src/arrow/array/builder_primitive.cc
    src/arrow/array/builder_union.cc
    src/arrow/array/concatenate.cc
    src/arrow/buffer.cc
    src/arrow/compare.cc
    src/arrow/extension_type.cc
    src/arrow/memory_pool.cc
    src/arrow/pretty_print.cc
    src/arrow/record_batch.cc
    src/arrow/result.cc
    src/arrow/scalar.cc
    src/arrow/sparse_tensor.cc
    src/arrow/status.cc
    src/arrow/table.cc
    src/arrow/table_builder.cc
    src/arrow/tensor.cc
    src/arrow/type.cc
    src/arrow/visitor.cc
    src/arrow/csv/converter.cc
    src/arrow/csv/chunker.cc
    src/arrow/csv/column-builder.cc
    src/arrow/csv/options.cc
    src/arrow/csv/parser.cc
    src/arrow/csv/reader.cc
    src/arrow/filesystem/filesystem.cc
    src/arrow/filesystem/localfs.cc
    src/arrow/filesystem/mockfs.cc
    src/arrow/filesystem/path-util.cc
    src/arrow/filesystem/util-internal.cc
    src/arrow/json/options.cc
    src/arrow/json/chunked-builder.cc
    src/arrow/json/chunker.cc
    src/arrow/json/converter.cc
    src/arrow/json/parser.cc
    src/arrow/json/reader.cc
    src/arrow/io/buffered.cc
    src/arrow/io/compressed.cc
    src/arrow/io/file.cc
    src/arrow/io/interfaces.cc
    src/arrow/io/memory.cc
    src/arrow/io/readahead.cc
    src/arrow/ipc/reader.cc
    src/arrow/testing/util.cc
    src/arrow/util/basic_decimal.cc
    src/arrow/util/bit-util.cc
    src/arrow/util/compression.cc
    src/arrow/util/cpu-info.cc
    src/arrow/util/decimal.cc
    src/arrow/util/int-util.cc
    src/arrow/util/io-util.cc
    src/arrow/util/logging.cc
    src/arrow/util/key_value_metadata.cc
    src/arrow/util/memory.cc
    src/arrow/util/string_builder.cc
    src/arrow/util/task-group.cc
    src/arrow/util/thread-pool.cc
    src/arrow/util/trie.cc
    src/arrow/util/utf8.cc
    src/arrow/vendored/datetime/tz.cpp)

function(ARROW_INSTALL_ALL_HEADERS PATH)
    set(options)
    set(one_value_args)
    set(multi_value_args PATTERN)
    cmake_parse_arguments(ARG
                          "${options}"
                          "${one_value_args}"
                          "${multi_value_args}"
                          ${ARGN})
    if(NOT ARG_PATTERN)
      # The .hpp extension is used by some vendored libraries
      set(ARG_PATTERN "*.h" "*.hpp")
    endif()
    file(GLOB CURRENT_DIRECTORY_HEADERS ${ARG_PATTERN})
  
    set(PUBLIC_HEADERS)
    foreach(HEADER ${CURRENT_DIRECTORY_HEADERS})
      get_filename_component(HEADER_BASENAME ${HEADER} NAME)
      if(HEADER_BASENAME MATCHES "internal")
        continue()
      endif()
      list(APPEND PUBLIC_HEADERS ${HEADER})
    endforeach()
    install(FILES ${PUBLIC_HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PATH}")
endfunction()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")

set_property(SOURCE util/io_util.cc
           APPEND_STRING
           PROPERTY COMPILE_FLAGS " -Wno-unused-macros ")

include_directories(src)
set(ARROW_BUILD_STATIC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_library(arrow STATIC ${ARROW_SRCS})
target_compile_definitions(arrow PUBLIC ARROW_NO_DEPRECATED_API)
target_compile_definitions(arrow PUBLIC ARROW_STATIC)

target_link_libraries(arrow
    ${double-conversion_LIBRARIES}
    ${BOOST_FILESYSTEM_LIBRARY}
    ${BOOST_SYSTEM_LIBRARY}
    ${ARROW_TEST_LINK_TOOLCHAIN})


	include_directories("/Users/r599507/homebrew/include")
	include_directories("/boost_includes")
	include_directories("/usr/local/include")

    include(FindPackageHandleStandardArgs)

    find_library(FLATBUFFERS_LIB NAMES flatbuffers PATH_SUFFIXES ${LIB_PATH_SUFFIXES})
    find_path(FLATBUFFERS_INCLUDE_DIR
                NAMES flatbuffers/flatbuffers.h
                PATH_SUFFIXES ${INCLUDE_PATH_SUFFIXES})
    find_program(FLATC NAMES flatc PATHS PATH_SUFFIXES "bin")

    find_package_handle_standard_args(FlatbuffersAlt
                                    REQUIRED_VARS
                                    FLATBUFFERS_LIB
                                    FLATBUFFERS_INCLUDE_DIR
                                    FLATC)

    if(FlatbuffersAlt_FOUND)
    add_library(flatbuffers::flatbuffers UNKNOWN IMPORTED)
    set_target_properties(flatbuffers::flatbuffers
                            PROPERTIES IMPORTED_LOCATION "${FLATBUFFERS_LIB}"
                                    INTERFACE_INCLUDE_DIRECTORIES
                                    "${FLATBUFFERS_INCLUDE_DIR}")
    add_executable(flatbuffers::flatc IMPORTED)
    set_target_properties(flatbuffers::flatc PROPERTIES IMPORTED_LOCATION "${FLATC}")
    endif()


    # add_arrow_test(feather_test)
    # add_arrow_test(read_write_test PREFIX "arrow-ipc")
    # add_arrow_test(json_simple_test PREFIX "arrow-ipc")
    # add_arrow_test(json_test PREFIX "arrow-ipc")
    
    # # json_integration_test is two things at the same time:
    # # - an executable that can be called to answer integration test requests
    # # - a self-(unit)test for the C++ side of integration testing
    # if(ARROW_BUILD_TESTS)
    #   add_arrow_test(json_integration_test EXTRA_LINK_LIBS ${GFLAGS_LIBRARIES})
    #   add_dependencies(arrow-integration arrow-json-integration-test)
    # elseif(ARROW_BUILD_INTEGRATION)
    #   add_executable(arrow-json-integration-test json_integration_test.cc)
    #   target_link_libraries(arrow-json-integration-test ${ARROW_TEST_LINK_LIBS}
    #                         ${GFLAGS_LIBRARIES} GTest::GTest)
    
    #   add_dependencies(arrow-json-integration-test arrow arrow_testing)
    #   add_dependencies(arrow-integration arrow-json-integration-test)
    # endif()
    
    # make clean will delete the generated file
    set_source_files_properties(src/arrow/ipc/Message_generated.h PROPERTIES GENERATED TRUE)
    set_source_files_properties(src/arrow/ipc/feather_generated.h PROPERTIES GENERATED TRUE)
    set_source_files_properties(src/arrow/ipc/File_generated.h PROPERTIES GENERATED TRUE)
    
    set(OUTPUT_DIR ${ARROW_BINARY_DIR}/src/arrow/ipc)
    set(FBS_OUTPUT_FILES "${OUTPUT_DIR}/File_generated.h" "${OUTPUT_DIR}/Message_generated.h"
                         "${OUTPUT_DIR}/feather_generated.h")
    
    set(FBS_SRC
        ${ARROW_SOURCE_DIR}/../format/Message.fbs
        ${ARROW_SOURCE_DIR}/../format/File.fbs
        ${ARROW_SOURCE_DIR}/../format/Schema.fbs
        ${ARROW_SOURCE_DIR}/../format/Tensor.fbs
        ${ARROW_SOURCE_DIR}/../format/SparseTensor.fbs
        ${CMAKE_CURRENT_SOURCE_DIR}/feather.fbs)
    
    foreach(FIL ${FBS_SRC})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      list(APPEND ABS_FBS_SRC ${ABS_FIL})
    endforeach()
    
    get_target_property(FLATC_EXECUTABLE flatbuffers::flatc IMPORTED_LOCATION)
    if(NOT FLATC_EXECUTABLE)
      get_target_property(FLATC_EXECUTABLE flatbuffers::flatc IMPORTED_LOCATION_RELEASE)
    endif()
    message(STATUS "flatc: ${FLATC_EXECUTABLE}")
    add_custom_command(OUTPUT ${FBS_OUTPUT_FILES}
                       COMMAND ${FLATC_EXECUTABLE}
                               -c
                               -o
                               ${OUTPUT_DIR}
                               ${ABS_FBS_SRC}
                       DEPENDS flatbuffers::flatc ${ABS_FBS_SRC}
                       COMMENT "Running flatc compiler on ${ABS_FBS_SRC}"
                       VERBATIM)
    
    add_custom_target(metadata_fbs DEPENDS ${FBS_OUTPUT_FILES})
    
    # Headers: top level
    arrow_install_all_headers("arrow/ipc")
    
    #if(ARROW_BUILD_STATIC)
    set(ARROW_UTIL_LIB arrow_static)
    # else()
    #   set(ARROW_UTIL_LIB arrow_shared)
    # endif()
    
    # if(ARROW_BUILD_UTILITIES OR ARROW_BUILD_INTEGRATION)
    #   add_executable(arrow-file-to-stream file_to_stream.cc)
    #   target_link_libraries(arrow-file-to-stream ${ARROW_UTIL_LIB})
    #   add_executable(arrow-stream-to-file stream_to_file.cc)
    #   target_link_libraries(arrow-stream-to-file ${ARROW_UTIL_LIB})
    
    #   if(ARROW_BUILD_INTEGRATION)
    #     add_dependencies(arrow-integration arrow-file-to-stream)
    #     add_dependencies(arrow-integration arrow-stream-to-file)
    #   endif()
    # endif()
    
    # add_arrow_benchmark(read_write_benchmark PREFIX "arrow-ipc")
    # add_arrow_fuzzing(fuzzing_test PREFIX "arrow-ipc")