
set(gsl_core_mat_create1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/mat/create1 "${gsl_core_mat_create1_files}" gsl_core_mat_create1_files_filepaths)

add_executable(core_mat_create1
        ${gsl_core_mat_create1_files_filepaths}
        )

mc_target_link_libraries(core_mat_create1)
mc_target_link_opencv(core_mat_create1)
