cmake_minimum_required(VERSION 3.5.1)
project(src)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# if(CMAKE_SYSTEM_PROCESSOR MATCHES “BCM28|armv7”)
# add_compile_options(-march=armv8-a+crc -mcpu=cortex-a53 -mfpu=neon-fp-armv8)
# endif()

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    message("---- found openMP ---- ")
endif()

message("---- arch is  ---- " ${CMAKE_SYSTEM_PROCESSOR})

add_executable( src
                FullyConnectedActivation.cpp
                main.cpp
                model31_func.cpp
                model31_func_data.cpp
                model31_func_initialize.cpp
                model31_func_terminate.cpp
                predict.cpp
                rtwtypes.h
                # DeepLearningNetwork.cpp
                # model31_func.cpp
                # model31_func_data.cpp
                # model31_func_initialize.cpp
                # model31_func_terminate.cpp
                # MWACLUtils.cpp
                # MWCNNLayer.cpp
                # MWCNNLayerImpl.cpp
                # MWCNNLayerImpl.hpp
                # MWCustomLayerForARMNEON.cpp
                # MWFCLayer.cpp
                # MWFCLayerImpl.cpp
                # MWInputLayer.cpp
                # MWInputLayerImpl.cpp
                # MWOutputLayer.cpp
                # MWOutputLayerImpl.cpp
                # MWReLULayer.cpp
                # MWReLULayerImpl.cpp
                # MWSoftmaxLayer.cpp
                # MWSoftmaxLayerImpl.cpp
                # MWTargetNetworkImpl.cpp
                # MWTensorBase.cpp
                # predict.cpp
		        # main.cpp
                )



target_link_libraries(src m)
