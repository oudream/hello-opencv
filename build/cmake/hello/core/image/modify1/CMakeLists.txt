
set(gsl_core_image_modify1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/image/modify1 "${gsl_core_image_modify1_files}" gsl_core_image_modify1_files_filepaths)

add_executable(core_image_modify1
        ${gsl_core_image_modify1_files_filepaths}
        )

mc_target_link_libraries(core_image_modify1)
mc_target_link_opencv(core_image_modify1)
