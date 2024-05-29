# Pitch Shift

![CI](https://github.com/Chowdhury-DSP/JUCEPluginTemplate/workflows/CI/badge.svg)
[![License](https://img.shields.io/badge/License-BSD-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

An audio plugin demonstrating the use of the [Bungee](https://github.com/kupix/bungee)
time-stretching/pitch-shifting library in the context of a real-time
audio plugin.

This repository is still a work-in-progress... not everything might
be working at the moment.

## Building

To build from scratch, you must have CMake installed.

```bash
# Clone the repository
$ git clone https://github.com/Chowdhury-DSP/PitchShift.git
$ cd PitchShift

# build with CMake
$ cmake -Bbuild
$ cmake --build build --config Release
```

## License

PitchShift is open source, and is licensed under the BSD 3-clause license.
Enjoy!
