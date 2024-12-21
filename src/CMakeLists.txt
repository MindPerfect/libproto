
file(GLOB libSrcs *.cc)
file(GLOB libHdrs *.h *.hh *.hpp)

# Target Library name
set(tgt proto)


add_library(${tgt} STATIC)
# https://cmake.org/cmake/help/latest/command/target_sources.html
# https://stackoverflow.com/questions/10487256/cmake-how-to-properly-copy-static-librarys-header-file-into-usr-include
target_sources(${tgt}
    PRIVATE ${libSrcs}
    PUBLIC FILE_SET HEADERS FILES ${libHdrs}
)
set_target_properties(${tgt} PROPERTIES LINKER_LANGUAGE CXX)


target_link_libraries(${tgt} PUBLIC absl::base absl::log absl::strings absl::random_random)


install(
  TARGETS ${tgt}
  EXPORT ${TARGETS_EXPORT_NAME}
  ARCHIVE  DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
  FILE_SET HEADERS DESTINATION ${INSTALL_INCDIR}
)
