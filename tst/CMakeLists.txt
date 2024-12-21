
file(GLOB tgtSrcs *.cc)
#file(GLOB tgtHdrs *.h *.hh *.hpp)
#message(STATUS "tgtSrcs: ${tgtSrcs}")
set(tgt proto_test)

add_executable(${tgt})
add_test(NAME ${tgt} COMMAND ${tgt})

target_sources(${tgt} PRIVATE ${tgtSrcs})
target_include_directories(${tgt}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PrjSrc}
)

target_link_libraries(${tgt} PUBLIC proto GTest::gtest
  absl::flags_parse
  absl::log
  absl::log_initialize
  absl::log_severity
  absl::log_internal_globals
)


