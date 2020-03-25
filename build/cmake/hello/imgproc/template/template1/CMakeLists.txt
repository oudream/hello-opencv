
set(gsl_imgproc_template1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/template/template1 "${gsl_imgproc_template1_files}" gsl_imgproc_template1_files_filepaths)

add_executable(imgproc_template1
        ${gsl_imgproc_template1_files_filepaths}
        )

mc_target_link_libraries(imgproc_template1)
mc_target_link_opencv(imgproc_template1)
