
### callpython3
set(gsl_callpython3_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/python/callpython3 "${gsl_callpython3_files}" gsl_callpython3_files_filepaths)

add_executable(callpython3
        ${gsl_callpython3_files_filepaths}
        )

target_link_libraries(callpython3
        ${PYTHON_LIBRARIES}
        )

mc_target_link_libraries(callpython3)

#compile static
mc_build_with_cc_static()
