
set(gsl_tool_image_background_files
        main.cpp
        )

mc_merge_file_path(${gs_tools_path}/image-background "${gsl_tool_image_background_files}" gsl_tool_image_background_files_filepaths)

add_executable(tool_image_background
        ${gsl_tool_image_background_files_filepaths}
        )

mc_target_link_libraries(tool_image_background)
mc_target_link_opencv(tool_image_background)
