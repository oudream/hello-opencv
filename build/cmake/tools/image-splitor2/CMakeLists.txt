
set(gsl_tool_image_splitor2_files
        main.cpp
        )

mc_merge_file_path(${gs_tools_path}/image-splitor2 "${gsl_tool_image_splitor2_files}" gsl_tool_image_splitor2_files_filepaths)

add_executable(tool_image_splitor2
        ${gsl_tool_image_splitor2_files_filepaths}
        )

mc_target_link_libraries(tool_image_splitor2)
mc_target_link_opencv(tool_image_splitor2)
