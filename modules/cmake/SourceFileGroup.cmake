function(setup_source_group target src_group_name)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ARG "" "" "${multiValueArgs}" ${ARGN})

    message(STATUS "Setting up source group ${src_group_name}, from SOURCES: ${ARG_SOURCES}")
    target_sources(${target} PRIVATE ${ARG_SOURCES})
    set_source_files_properties(
        ${ARG_SOURCES}
        TARGET_DIRECTORY ${target}
        PROPERTIES UNITY_GROUP "${src_group_name}"
    )
endfunction(setup_source_group)
