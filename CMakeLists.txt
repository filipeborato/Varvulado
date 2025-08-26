# Projeto JUCE & Simulink: Tube Preamp Universal Audio 610 Simulation
# Recriando estrutura de arquivos e código completo

# --------------------
# CMakeLists.txt
# --------------------
cmake_minimum_required(VERSION 3.15)
project(TubePreampPlugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# JUCE setup: prefer installed JUCE CMake package, but fall back to Projucer-generated JuceLibraryCode
find_package(JUCE CONFIG QUIET)

if(JUCE_FOUND)
    message(STATUS "Found JUCE package via CMake: using juce_add_plugin")

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
            Source/VintageLookAndFeel.cpp
            Source/VintageLookAndFeel.h
    )

else()
    message(STATUS "JUCE CMake package not found. Falling back to embedded JuceLibraryCode for IDE/IntelliSense.")

    # Create a regular target so CMake configures and language servers (IntelliSense) see headers.
    file(GLOB_RECURSE PROJECT_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c"
    )
    file(GLOB_RECURSE JUCE_EMBED_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/*.c"
    )

    list(APPEND PROJECT_SOURCES ${JUCE_EMBED_SOURCES})

    add_library(TubePreampPlugin STATIC ${PROJECT_SOURCES})

    target_include_directories(TubePreampPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)

    # Some basic defines commonly used by JUCE-based projects
    target_compile_definitions(TubePreampPlugin PRIVATE JUCE_WEB_BROWSER=0)

    # If BinaryData exists, ensure it's included as source
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/BinaryData.cpp)
        target_sources(TubePreampPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/BinaryData.cpp)
    endif()

endif()

# Include Projucer-generated BinaryData if present (embedded resources)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/BinaryData.cpp)
    message(STATUS "Including Projucer BinaryData.cpp for embedded resources")
    target_sources(TubePreampPlugin PRIVATE JuceLibraryCode/BinaryData.cpp)
    target_include_directories(TubePreampPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)
endif()

if(JUCE_FOUND)
    target_compile_definitions(TubePreampPlugin PRIVATE JUCE_WEB_BROWSER=0)
    juce_generate_juce_header(TubePreampPlugin)
    target_link_libraries(TubePreampPlugin
            PRIVATE
                    juce::juce_audio_processors
                    juce::juce_audio_utils
                    juce::juce_core
    )
endif()
