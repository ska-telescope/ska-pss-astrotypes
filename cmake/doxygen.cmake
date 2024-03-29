if(NOT PSS_ASTROTYPES_DOXYGEN_GUARD_VAR)
    set(PSS_ASTROTYPES_DOXYGEN_GUARD_VAR TRUE)
else()
    return()
endif()

if(CMAKE_BUILD_TYPE MATCHES documentation)
    set(ENABLE_DOC TRUE)
    set(doc_all_target "ALL")
else()
    set(doc_all_target "")
endif()

# Search for the DoxyfileAPI.in by looking through CMAKE_MODULE_PATH
find_file(doxyfile_in "DoxyfileAPI.in" ${CMAKE_MODULE_PATH})

message("Doxyfile set to " ${doxyfile_in})

if(ENABLE_DOC)

    find_package(Doxygen)

    # Add a target to generate API documentation with Doxygen
    if(DOXYGEN_FOUND)
        set(doxygen_build_dir ${CMAKE_BINARY_DIR}/doc)
        file(MAKE_DIRECTORY ${doxygen_build_dir})
        configure_file(${doxyfile_in} ${CMAKE_BINARY_DIR}/DoxyfileAPI @ONLY)
        add_custom_target(doc ${doc_all_target}
                          ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/DoxyfileAPI
                          WORKING_DIRECTORY ${doxygen_build_dir}
                          COMMENT "Generating documentation with Doxygen" VERBATIM
        )
        add_custom_target(publish_doc
                          COMMAND git clone -b gh-pages git@github.com:PulsarSearchSoft/astrotypes.git gh-pages
                          COMMAND cp -r ${doxygen_build_dir}/html gh-pages/
                          DEPENDS doc
                          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                          COMMENT "Publishing documentation on GitHub pages" VERBATIM
        )
        add_custom_command(TARGET publish_doc POST_BUILD
                           COMMAND git add html
                           COMMAND git commit -a -m "Updating documentation."
                           COMMAND git push
                           COMMAND rm -rf ${CMAKE_BINARY_DIR}/gh-pages
                           WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gh-pages
        )
        install(DIRECTORY ${doxygen_build_dir}/
                DESTINATION ${DOC_INSTALL_DIR}
                PATTERN "${doxygen_build_dir}/*"
        )
    else()
        add_custom_target(doc ${doc_all_target}
                          COMMAND ${CMAKE_COMMAND} -E echo
                          COMMENT "No doc target configured. Doxygen not found" VERBATIM
        )
    endif()

else(ENABLE_DOC)
    add_custom_target(doc ${doc_all_target}
                      COMMAND ${CMAKE_COMMAND} -E echo
                      COMMENT "No doc target configured. Rebuild with -DENABLE_DOC=true" VERBATIM
    )
endif(ENABLE_DOC)
