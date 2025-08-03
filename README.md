# Varvulado

**Description:**
12AX7 tube simulation VST

---

## Table of Contents

1. [Overview](#overview)
2. [Prerequisites](#prerequisites)
3. [Project Structure](#project-structure)
4. [Building with JUCE and CMake](#building-with-juce-and-cmake)
5. [Debug Configuration in Visual Studio](#debug-configuration-in-visual-studio)
6. [Using the Plugin in Reaper](#using-the-plugin-in-reaper)
7. [Post-Build Scripts](#post-build-scripts)
8. [Contributing](#contributing)
9. [License](#license)

---

## Overview

Varvulado is a VST3 plugin that emulates the classic 12AX7 tube preamp. It delivers warm analog saturation using polynomial soft-clipping combined with RC filters to closely mimic real tube behavior.

---

## Prerequisites

* Windows 10 or 11 (x64)
* Visual Studio Community 2022
* JUCE 7 (include the `Juce/` folder or reference via CMake)
* CMake (version 3.15 or newer)
* (Optional) Simulink Coder for regenerating the Simulink model

---

## Project Structure

```
Varvulado/
├─ CMakeLists.txt
├─ Simulink/
│   └─ TubePreampModel.slx   # Simulink model
├─ Source/
│   ├─ PluginProcessor.h
│   ├─ PluginProcessor.cpp
│   ├─ PluginEditor.h
│   ├─ PluginEditor.cpp
│   ├─ PluginParameters.h
│   ├─ TubeModel.h
│   └─ TubeModel.cpp
└─ postbuild.bat            # Post-build script (copy + manifest)
```

---

## Building with JUCE and CMake

1. **Clone the repository**:

   ```bash
   git clone https://github.com/YourUser/Varvulado.git
   cd Varvulado
   ```
2. **Configure the build**:

   ```bash
   mkdir build && cd build
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```
3. **Build**:

   * Open `Varvulado.sln` in Visual Studio 2022.
   * Select **Debug** or **Release**, then **Build** the solution.
4. **Post-build step**:

   * The `postbuild.bat` script will copy the plugin DLL into the VST3 bundle and generate the `moduleinfo.json` manifest.

---

## Debug Configuration in Visual Studio

1. Go to **Project → Properties → Debugging**.
2. Set:

   * **Command**: `C:\Program Files\REAPER (x64)\reaper.exe`
   * **Command Arguments** (optional):
     `/start "C:\Users\YourUser\Documents\Reaper Projects\test.rpp"`
   * **Working Directory**: `C:\Program Files\REAPER (x64)\`
3. Press **F5** to build, run post-build, and launch Reaper for debugging.

---

## Using the Plugin in Reaper

1. Open Reaper.
2. Navigate to **Options → Preferences → Plug-ins → VST3** and add:

   ```
   C:\Program Files\Common Files\VST3
   ```
3. Click **Clear cache & rescan**.
4. Insert **Varvulado** via the FX browser in any track.

---

## Post-Build Scripts

* **postbuild.bat**: Copies the compiled `.dll` into the VST3 bundle and runs `juce_vst3_helper.exe` to generate `moduleinfo.json`.
* Integrated in the build via the `.jucer` or CMake configuration.

---

## Contributing

1. Fork the repository.
2. Create a branch: `git checkout -b feature/my-feature`.
3. Commit your changes: `git commit -m "Add my feature"`.
4. Push: `git push origin feature/my-feature`.
5. Open a Pull Request.

---

## License

Licensed under the MIT License. See the `LICENSE` file for details.
