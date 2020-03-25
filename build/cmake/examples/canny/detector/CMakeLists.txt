
include(./../../../qt.cmake)

###add qt ui
mc_target_define_qt()

###
set(qt_sources
        main.cpp
        )

mc_merge_file_path(${gs_examples_path}/canny/detector_hipersayanx "${qt_sources}" qt_source_paths)

###add ccxx
add_executable(examples_canny_detector_hipersayanx
        ${qt_source_paths}
        )

target_link_libraries(examples_canny_detector_hipersayanx
        ${Qt5Core_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5Gui_LIBRARIES}
        )


