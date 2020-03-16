
### callpython2
set(gsl_callpython2_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/python/callpython2 "${gsl_callpython2_files}" gsl_callpython2_files_filepaths)

add_executable(callpython2
        ${gsl_callpython2_files_filepaths}
        )

target_link_libraries(callpython2
        ${PYTHON_LIBRARIES}
        )

mc_target_link_libraries(callpython2)

#compile static
mc_build_with_cc_static()
