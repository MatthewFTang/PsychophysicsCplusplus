# Psychophysics  experiments in C++

### A  project implementing a psychophysics experiment in C++ using the raylib library.

I made this project to determine whether modern c++ graphics libraries can be easily used to program psychophysics
or psychology experiments.

PsychToolbox  (https://psychtoolbox.org/) in MATLAB and PsychoPy  (https://www.psychopy.org/)
in Python are the most-widely used platforms for making experiments for psychophysics. However, with the
advacement of modern graphics
libraries, like raylib and SDL, in C/C++, it brings the possibility of having a much more performant
language with easy development. Furthermore, because the widespread use of C++ in game development, there's a huge
amount of resources available to help make more complex experiments (3D, VR etc). Raylib can also be deployed in the
web for online experiments.

I found making the experiment was comparable with the other platforms and found the timing to be excellent meaning
this could easily be suitable for experiments where timing is critical, e.g. electrophysiology, neuroimaging.

The experiment in the example is a global dot motion task where the participant has to replicate the direction of
motion. I included an ImGui framework where you can modify the experiment parameters and enter participant
information. The results get saved in a csv file.

## Requirements

<ul>
<li>C++ 20
<li> raylib (https://www.raylib.com, https://github.com/raysan5/raylib) 
<li> Dear ImGui (https://github.com/ocornut/imgui)
<li> fmt (https://github.com/fmtlib/fmt)
</ul>


