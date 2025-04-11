# Psychophysics Experiments in C++

### A project implementing a psychophysics experiment in C++ using the Raylib library.

This project explores the feasibility of using modern C++ graphics libraries, such as Raylib and Dear ImGui, for psychophysics or psychology experiments. It demonstrates how easily such libraries can be used to create performant and flexible experiments with precise timing.

### Motivation
Traditionally, psychophysics experiments have been developed using platforms like:
- **[PsychToolbox](https://psychtoolbox.org/)** (MATLAB)
- **[PsychoPy](https://www.psychopy.org/)** (Python)

While these platforms are widely used, C++ brings several advantages:
- **Performance:** C++ is generally faster than interpreted languages like Python or MATLAB, which is beneficial for experiments requiring real-time performance.
- **Graphics Flexibility:** With the availability of libraries like Raylib and SDL, as well as the ability to integrate external tools (e.g., Dear ImGui), C++ provides a highly customizable environment.
- **Game Development Resources:** C++ is the backbone of game engines, offering many resources for advanced experiments, such as 3D simulations or virtual reality environments.
- **Cross-Platform Support:** Raylib makes deployment to multiple platforms (including web via emscripten) straightforward, making it well-suited for online experiments.

### About the Experiment
The example in this project is a **global dot motion task**:
- A participant replicates the perceived direction of motion of a group of dots.
- An integrated Dear ImGui interface allows:
    - Modification of experiment parameters.
    - Entry of participant information.
- Results are saved in a CSV file for easy analysis.
- The project ensures precise timing, making it suitable for critical experiments like:
    - **Electrophysiology**
    - **Neuroimaging**
    - Experiments requiring sub-millisecond accuracy.

### Features
- **Raylib Integration:** Simple and lightweight library for rendering and handling input.
- **Dear ImGui Interface:** Provides an easy-to-use interface for configuring experiments and viewing real-time results.
- **Automatic Dependency Management:** Leveraging CMake's `FetchContent` feature, all required dependencies are fetched and built automatically if not found locally.
- **C++ 20 Modern Features:** Uses modern C++ standards for performance, safety, and readability.
- **CSV Data Export:** Results are automatically saved in a CSV file for seamless downstream analysis.
- **Customizable Framework:** The project can be extended to implement more complex tasks like:
    - 3D visualizations.
    - Virtual reality experiments.
    - Online deployment using web technologies.

### Requirements
This project automatically fetches its dependencies via CMake. However, make sure the following base requirements are installed on your system:
- **C++ 20** Compiler (e.g., GCC 10+, Clang 10+, or MSVC 2019+).
- **CMake 3.15+**


### Automatic Dependency Management
The project uses `CMake FetchContent` to fetch the following libraries automatically if they are not found on the system:
- **Raylib** (https://www.raylib.com, https://github.com/raysan5/raylib)
- **Dear ImGui** (https://github.com/ocornut/imgui)
- **fmt Library** (https://github.com/fmtlib/fmt)

This ensures that you don't need to manually download or install these libraries.

### How to Build & Run
Follow these steps to build and run the project:

1. **Install Base Prerequisites:**
   Make sure you have a C++ 20 compiler and any system libraries (GLFW, Freetype) required by Raylib installed.

   Example installation for Ubuntu/Debian:
   ```bash
   sudo apt install cmake g++ git
   ```

2. **Clone the Repository:**
   Clone the repository. There is no need to handle submodules since the dependencies are fetched automatically:
   ```bash
   git clone <repository-url>
   cd PsychophysicsCplusplus
   ```

3. **Configure the CMake Build:**
   Create a build directory and configure the project with CMake. During this step, CMake will automatically fetch all required dependencies (Raylib, fmt, ImGui) if they are not already available on your system:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

4. **Build the Project:**
   Compile the project using `make` or your selected build tool:
   ```bash
   make
   ```

5. **Run the Experiment:**
   After building, run the experiment executable:
   ```bash
   ./motion_judgements
   ```

6. **Modify Experiment Settings:**
   Use the ImGui interface to configure experiment parameters at runtime.

### Potential Extensions
This project can be easily extended to support other types of experiments. Examples include:
- **Motion Perception Tasks:** Experiments with varying levels of coherence or speed.
- **Virtual Reality Experiments:** Combine Raylib with VR libraries.
- **Auditory or Multisensory Experiments:** Utilize Raylib's audio module for tasks involving sound stimuli.
- **Online Experiments:** Deploy the project as a web-based experiment using emscripten (Raylib supports this out-of-the-box).

### Benefits of C++ for Psychophysics
- **Precise Timing:** Ideal for experiments requiring precise control over timing (e.g., ±1 ms accuracy).
- **High Performance:** Leverages the power of C++ for computationally intensive tasks.
- **Customizability:** Modify or extend the framework to suit your specific research needs.

### Contributions
If you have suggestions, find bugs, or wish to contribute to the project, feel free to submit an issue or pull request.

Enjoy exploring the potential of C++ and modern graphics libraries in psychophysics research!