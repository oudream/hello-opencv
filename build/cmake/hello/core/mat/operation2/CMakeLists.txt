
set(gsl_core_mat_operation2_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/mat/operation2 "${gsl_core_mat_operation2_files}" gsl_core_mat_operation2_files_filepaths)

add_executable(core_mat_operation2
        ${gsl_core_mat_operation2_files_filepaths}
        )

mc_target_link_libraries(core_mat_operation2)
mc_target_link_opencv(core_mat_operation2)
