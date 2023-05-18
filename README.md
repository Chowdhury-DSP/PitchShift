# JUCE Plugin Template

![CI](https://github.com/Chowdhury-DSP/JUCEPluginTemplate/workflows/CI/badge.svg)
[![License](https://img.shields.io/badge/License-BSD-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

This repository contains template code for building a Chowdhury DSP
audio plugin.

## Building

To build from scratch, you must have CMake installed.

```bash
# Clone the repository
$ git clone https://github.com/Chowdhury-DSP/JUCEPluginTemplate.git
$ cd JUCEPluginTemplate

# set up plugin
$ ./setup.sh MyPluginName MyPluginID

# build with CMake
$ cmake -Bbuild
$ cmake --build build --config Release
```

## License

JUCEPluginTemplate is open source, and is licensed under the BSD 3-clause license.
Enjoy!
