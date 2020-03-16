
### callpython1
set(gsl_callpython1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/python/callpython1 "${gsl_callpython1_files}" gsl_callpython1_files_filepaths)

add_executable(callpython1
        ${gsl_callpython1_files_filepaths}
        )

target_link_libraries(callpython1
        ${PYTHON_LIBRARIES}
        )

mc_target_link_libraries(callpython1)

#compile static
mc_build_with_cc_static()
