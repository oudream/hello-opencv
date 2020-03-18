
set(gsl_core_color_inrange1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/color/inrange1 "${gsl_core_color_inrange1_files}" gsl_core_color_inrange1_files_filepaths)

add_executable(core_color_inrange1
        ${gsl_core_color_inrange1_files_filepaths}
        )

mc_target_link_libraries(core_color_inrange1)
mc_target_link_opencv(core_color_inrange1)
