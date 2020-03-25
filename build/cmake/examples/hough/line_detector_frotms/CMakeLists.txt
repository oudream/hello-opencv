
set(gsl_example_hough_line_detector_frotms_files
        edlines/edlines.cpp
        edlines/edlines.h
        houghlines/houghlines.cpp
        houghlines/houghlines.h
        lsdlines/lsdlines.cpp
        lsdlines/lsdlines.h
        main.cpp
        )


mc_merge_file_path(${gs_examples_path}/hough/line_detector_frotms "${gsl_example_hough_line_detector_frotms_files}" gsl_example_hough_line_detector_frotms_files_filepaths)

add_executable(example_hough_line_detector_frotms
        ${gsl_example_hough_line_detector_frotms_files_filepaths}
        )

mc_target_link_libraries(example_hough_line_detector_frotms)
mc_target_link_opencv(example_hough_line_detector_frotms)
