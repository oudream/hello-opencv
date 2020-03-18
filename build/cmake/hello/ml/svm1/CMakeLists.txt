
set(gsl_ml_svm1_files
    main.cpp
        )

mc_merge_file_path(${gs_hello_path}/ml/svm1 "${gsl_ml_svm1_files}" gsl_ml_svm1_files_filepaths)

add_executable(ml_svm1
        ${gsl_ml_svm1_files_filepaths}
        )

mc_target_link_libraries(ml_svm1)
mc_target_link_opencv(ml_svm1)
