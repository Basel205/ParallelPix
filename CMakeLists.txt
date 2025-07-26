# cmake_minimum_required(VERSION 3.20)
# project(ImageProcessingOpenMP)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(OpenMP REQUIRED)

# # Add executable with all components
# add_executable(ImageProcessingOpenMP
#     main.cpp
#     effects/image_processor.cpp
#     effects/gaussian_blur.cpp
#     effects/anime_filter.cpp
#     effects/oil_painting.cpp
#     effects/pencil_sketch.cpp
#     effects/thermal_effect.cpp
#     utils/logger.cpp
#     utils/system_info.cpp
#     utils/timer.cpp
#     benchmarking/benchmark.cpp
# )


# target_include_directories(ImageProcessingOpenMP PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/libs
#     ${CMAKE_CURRENT_SOURCE_DIR}/effects
#     ${CMAKE_CURRENT_SOURCE_DIR}/utils
# )

# # target_link_libraries(ImageProcessingOpenMP PRIVATE OpenMP::OpenMP_CXX)
# target_link_libraries(ImageProcessingOpenMP PRIVATE 
#     OpenMP::OpenMP_CXX
#     stdc++fs  # Required for filesystem operations on some compilers
# )



cmake_minimum_required(VERSION 3.20)
project(ImageProcessingOpenMP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(ImageProcessingOpenMP
    main.cpp
    effects/image_processor.cpp
    effects/gaussian_blur.cpp
    effects/anime_filter.cpp
    effects/oil_painting.cpp
    effects/pencil_sketch.cpp
    effects/thermal_effect.cpp
    utils/cpu_monitor.cpp
    utils/logger.cpp
    utils/system_info.cpp
    utils/timer.cpp
    benchmarking/benchmark.cpp
)

target_include_directories(ImageProcessingOpenMP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
    ${CMAKE_CURRENT_SOURCE_DIR}/effects
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

target_link_libraries(ImageProcessingOpenMP PRIVATE 
    OpenMP::OpenMP_CXX
    psapi  # Required for Windows CPU monitoring
)
