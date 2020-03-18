
set(gsl_core_color_addWeighted1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/color/addWeighted1 "${gsl_core_color_addWeighted1_files}" gsl_core_color_addWeighted1_files_filepaths)

add_executable(core_color_addWeighted1
        ${gsl_core_color_addWeighted1_files_filepaths}
        )

mc_target_link_libraries(core_color_addWeighted1)
mc_target_link_opencv(core_color_addWeighted1)
