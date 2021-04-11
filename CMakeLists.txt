cmake_minimum_required(VERSION 3.17)
project(itoi)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(itoi main.cpp image/Image.cpp image/Image.h image/DoubleImage.cpp image/DoubleImage.h borders/BorderEffectAction.cpp borders/BorderEffectAction.h borders/MirrorBorderEffect.cpp borders/MirrorBorderEffect.h borders/CopyBorderEffect.cpp borders/CopyBorderEffect.h borders/ZeroBorderEffect.cpp borders/ZeroBorderEffect.h filters/KernelFactory.cpp filters/KernelFactory.h filters/FiltersImplementation.cpp filters/FiltersImplementation.h labs/lab1.cpp labs/lab1.h)

target_link_libraries(itoi Qt5::Widgets)