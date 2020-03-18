
set(gsl_core_color_convert1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/color/convert1 "${gsl_core_color_convert1_files}" gsl_core_color_convert1_files_filepaths)

add_executable(core_color_convert1
        ${gsl_core_color_convert1_files_filepaths}
        )

mc_target_link_libraries(core_color_convert1)
mc_target_link_opencv(core_color_convert1)
