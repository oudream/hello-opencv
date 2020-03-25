
set(gsl_imgproc_canny3_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/canny/canny3 "${gsl_imgproc_canny3_files}" gsl_imgproc_canny3_files_filepaths)

add_executable(imgproc_canny3
        ${gsl_imgproc_canny3_files_filepaths}
        )

mc_target_link_libraries(imgproc_canny3)
mc_target_link_opencv(imgproc_canny3)
