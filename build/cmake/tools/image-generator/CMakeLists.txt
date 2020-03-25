
set(gsl_tool_image_generator_files
        main.cpp
        )

mc_merge_file_path(${gs_tools_path}/image-generator "${gsl_tool_image_generator_files}" gsl_tool_image_generator_files_filepaths)

add_executable(tool_image_generator
        ${gsl_tool_image_generator_files_filepaths}
        )

mc_target_link_libraries(tool_image_generator)
mc_target_link_opencv(tool_image_generator)
