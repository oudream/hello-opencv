
set(gsl_imgproc_morphology_erode_dilate1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/morphology/erode_dilate1 "${gsl_imgproc_morphology_erode_dilate1_files}" gsl_imgproc_morphology_erode_dilate1_files_filepaths)

add_executable(imgproc_morphology_erode_dilate1
        ${gsl_imgproc_morphology_erode_dilate1_files_filepaths}
        )

mc_target_link_libraries(imgproc_morphology_erode_dilate1)
mc_target_link_opencv(imgproc_morphology_erode_dilate1)
