cmake_minimum_required(VERSION 3.17)
project(itoi)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(itoi main.cpp image/Image.cpp image/Image.h image/DoubleImage.cpp image/DoubleImage.h borders/BorderEffectAction.cpp borders/BorderEffectAction.h borders/MirrorBorderEffect.cpp borders/MirrorBorderEffect.h borders/CopyBorderEffect.cpp borders/CopyBorderEffect.h borders/ZeroBorderEffect.cpp borders/ZeroBorderEffect.h filters/KernelFactory.cpp filters/KernelFactory.h filters/FiltersImplementation.cpp filters/FiltersImplementation.h labs/lab1.cpp labs/lab1.h octaves/OctaveFactory.cpp octaves/OctaveFactory.h octaves/Octave.cpp octaves/Octave.h octaves/OctaveElement.cpp octaves/OctaveElement.h labs/lab2.cpp labs/lab2.h points/InterestingPoint.cpp points/InterestingPoint.h points/Moravec.cpp points/Moravec.h points/Harris.cpp points/Harris.h points/DetectorUtil.cpp points/DetectorUtil.h labs/lab3.cpp labs/lab3.h points/DataSaver.cpp points/DataSaver.h descriptors/DescriptorUtil.cpp descriptors/DescriptorUtil.h descriptors/PatchProcessor.cpp descriptors/PatchProcessor.h descriptors/MatchData.cpp descriptors/MatchData.h descriptors/Descriptor.cpp descriptors/Descriptor.h descriptors/PatchDescriptor.cpp descriptors/PatchDescriptor.h labs/lab4.cpp labs/lab4.h descriptors/HistogramProcessor.cpp descriptors/HistogramProcessor.h descriptors/HistogramDescriptor.cpp descriptors/HistogramDescriptor.h descriptors/Basket.cpp descriptors/Basket.h labs/lab5.cpp labs/lab5.h descriptors/RotationInvariantProcessor.cpp descriptors/RotationInvariantProcessor.h)

target_link_libraries(itoi Qt5::Widgets)