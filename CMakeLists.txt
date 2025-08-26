// Projeto JUCE & Simulink: Tube Preamp Universal Audio 610 Simulation
// Recriando estrutura de arquivos e código completo

// --------------------
// CMakeLists.txt
// --------------------
cmake_minimum_required(VERSION 3.15)
project(TubePreampPlugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# JUCE setup
find_package(JUCE CONFIG REQUIRED)

juce_add_plugin(TubePreampPlugin
    COMPANY_NAME "MyCompany"
    PLUGIN_MANUFACTURER_CODE TuPr
    PLUGIN_CODE Tp01
    FORMATS VST3
    PRODUCT_NAME "Tube Preamp 610"
)

target_sources(TubePreampPlugin PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginParameters.h
    Source/TubeModel.cpp
    Source/TubeModel.h
)

# Include Projucer-generated BinaryData if present (embedded resources)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/BinaryData.cpp)
    message(STATUS "Including Projucer BinaryData.cpp for embedded resources")
    target_sources(TubePreampPlugin PRIVATE JuceLibraryCode/BinaryData.cpp)
    target_include_directories(TubePreampPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)
endif()

target_compile_definitions(TubePreampPlugin PRIVATE JUCE_WEB_BROWSER=0)

juce_generate_juce_header(TubePreampPlugin)

target_link_libraries(TubePreampPlugin
    PRIVATE
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
)
