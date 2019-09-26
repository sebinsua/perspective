set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
set(FLATBUFFERS_LOCALE_INDEPENDENT 0)

add_definitions(-DFLATBUFFERS_LOCALE_INDEPENDENT=$<BOOL:${FLATBUFFERS_LOCALE_INDEPENDENT}>)

set(FlatBuffers_Library_SRCS
  include/flatbuffers/code_generators.h
  include/flatbuffers/base.h
  include/flatbuffers/flatbuffers.h
  include/flatbuffers/hash.h
  include/flatbuffers/idl.h
  include/flatbuffers/util.h
  include/flatbuffers/reflection.h
  include/flatbuffers/reflection_generated.h
  include/flatbuffers/stl_emulation.h
  include/flatbuffers/flexbuffers.h
  include/flatbuffers/registry.h
  include/flatbuffers/minireflect.h
  src/code_generators.cpp
  src/idl_parser.cpp
  src/idl_gen_text.cpp
  src/reflection.cpp
  src/util.cpp
)

set(FlatBuffers_Compiler_SRCS
  ${FlatBuffers_Library_SRCS}
  src/idl_gen_cpp.cpp
  src/idl_gen_dart.cpp
  src/idl_gen_general.cpp
  src/idl_gen_go.cpp
  src/idl_gen_js_ts.cpp
  src/idl_gen_kotlin.cpp
  src/idl_gen_php.cpp
  src/idl_gen_python.cpp
  src/idl_gen_lobster.cpp
  src/idl_gen_lua.cpp
  src/idl_gen_rust.cpp
  src/idl_gen_fbs.cpp
  src/idl_gen_grpc.cpp
  src/idl_gen_json_schema.cpp
  src/flatc.cpp
  src/flatc_main.cpp
  grpc/src/compiler/schema_interface.h
  grpc/src/compiler/cpp_generator.h
  grpc/src/compiler/cpp_generator.cc
  grpc/src/compiler/go_generator.h
  grpc/src/compiler/go_generator.cc
  grpc/src/compiler/java_generator.h
  grpc/src/compiler/java_generator.cc
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(FLATBUFFERS_PRIVATE_CXX_FLAGS -fsigned-char -fno-omit-frame-pointer -stdlib=libc++ -lc++abi)
# set(CMAKE_CXX_FLAGS
#   "${CMAKE_CXX_FLAGS} -faligned-new -Werror=implicit-fallthrough=2")

# # Certain platforms such as ARM do not use signed chars by default
# # which causes issues with certain bounds checks.
# set(CMAKE_CXX_FLAGS
#   "${CMAKE_CXX_FLAGS} -fsigned-char")

# if(MSVC)
#   # Visual Studio pedantic build settings
#   # warning C4512: assignment operator could not be generated
#   # warning C4316: object allocated on the heap may not be aligned
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /wd4512 /wd4316")
# endif()

include_directories(include)
include_directories(grpc)

add_library(flatbuffers STATIC ${FlatBuffers_Library_SRCS})
# CMake > 2.8.11: Attach header directory for when build via add_subdirectory().
target_include_directories(flatbuffers INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_options(flatbuffers PRIVATE "${FLATBUFFERS_PRIVATE_CXX_FLAGS}")

add_executable(flatc ${FlatBuffers_Compiler_SRCS})
target_compile_options(flatc PRIVATE "${FLATBUFFERS_PRIVATE_CXX_FLAGS}")
# if(MSVC)
#   # Make flatc.exe not depend on runtime dlls for easy distribution.
#   target_compile_options(flatc PUBLIC $<$<CONFIG:Release>:/MT>)
# endif()

# if(FLATBUFFERS_BUILD_SHAREDLIB)
#   add_library(flatbuffers_shared SHARED ${FlatBuffers_Library_SRCS})

#   # Shared object version: "major.minor.micro"
#   # - micro updated every release when there is no API/ABI changes
#   # - minor updated when there are additions in API/ABI
#   # - major (ABI number) updated when there are changes in ABI (or removals)
#   set(FlatBuffers_Library_SONAME_MAJOR "1")
#   set(FlatBuffers_Library_SONAME_FULL "${FlatBuffers_Library_SONAME_MAJOR}.11.0")
#   set_target_properties(flatbuffers_shared PROPERTIES OUTPUT_NAME flatbuffers
#                         SOVERSION "${FlatBuffers_Library_SONAME_MAJOR}"
#                         VERSION "${FlatBuffers_Library_SONAME_FULL}")
# endif()
