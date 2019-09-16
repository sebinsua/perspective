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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")

set_property(SOURCE util/io_util.cc
           APPEND_STRING
           PROPERTY COMPILE_FLAGS " -Wno-unused-macros ")

include_directories(src)
set(ARROW_BUILD_STATIC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -stdlib=libc++")
add_library(arrow STATIC ${ARROW_SRCS})
target_compile_definitions(arrow PUBLIC ARROW_NO_DEPRECATED_API)
target_compile_definitions(arrow PUBLIC ARROW_STATIC)

target_link_libraries(arrow
    ${double-conversion_LIBRARIES}
    ${BOOST_FILESYSTEM_LIBRARY}
    ${BOOST_SYSTEM_LIBRARY}
    ${ARROW_TEST_LINK_TOOLCHAIN})
