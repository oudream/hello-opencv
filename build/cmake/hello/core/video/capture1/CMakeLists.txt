
set(gsl_core_video_capture1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/video/capture1 "${gsl_core_video_capture1_files}" gsl_core_video_capture1_files_filepaths)

add_executable(core_video_capture1
        ${gsl_core_video_capture1_files_filepaths}
        )

mc_target_link_libraries(core_video_capture1)
mc_target_link_opencv(core_video_capture1)
