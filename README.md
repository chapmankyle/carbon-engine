<h1 align="center">Carbon Engine</h1>

<p align="center">
  <img src="https://travis-ci.com/chapmankyle/carbon-engine.svg?branch=master" alt="Travis CI"></img>
  <img src="https://ci.appveyor.com/api/projects/status/ja6b1h34y79t2hqk/branch/master?svg=true" alt="Appveyor CI"></img>
  <img src="https://img.shields.io/github/license/chapmankyle/carbon-engine.svg?" alt="License: GPL-3.0"></img>
  <img src="https://img.shields.io/github/v/release/chapmankyle/carbon-engine.svg?" alt="Release"></img>
</p>

A modular graphics engine built using C++17 and Vulkan :rocket:

# Purpose :zap:

The purpose of this graphics engine is to simplify the process of working with Vulkan by abstracting away the 
tedious work needed to setup both on and off-screen rendering. It is also a learning exercise for me to understand 
how graphics engines work and how to make my very own.

# Cloning :alien:

The repository relies on [submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) to work correctly, so 
you can simply type the following to clone the repo and all submodules:
```bash
# clone repo and all submodules
git clone --recursive https://github.com/chapmankyle/carbon-engine.git
```

If you would like to update the repository, it is advised to update the submodules as well by typing
the following:
```bash
# pull recent changes
git pull

# update submodules
git submodule update --init --recursive
```

# Dependencies :gift:

The following dependencies are included as submodules in the `deps` directory:
- :tv: [GLFW](https://www.glfw.org/) - Used for handling window interaction
- :triangular_ruler: [GLM](https://glm.g-truc.net/0.9.9/index.html) - Used for working with vectors and matrices

# Modules :card_index_dividers:

#### carbon [common](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/common)

[![debug](https://img.shields.io/badge/carbon-debug-brightgreen.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/common/debug.hpp)
[![template-types](https://img.shields.io/badge/carbon-template_types-brightgreen.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/common/template_types.hpp)
[![utils](https://img.shields.io/badge/carbon-utils-brightgreen.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/common/utils.hpp)

#### carbon [core](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/core)

[![instance](https://img.shields.io/badge/carbon-instance-orange.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/core/instance.hpp)
[![logical-device](https://img.shields.io/badge/carbon-logical_device-orange.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/core/logical_device.hpp)
[![physical-device](https://img.shields.io/badge/carbon-physical_device-orange.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/core/physical_device.hpp)
[![time](https://img.shields.io/badge/carbon-time-orange.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/core/time.hpp)

#### carbon [display](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/display)

[![input](https://img.shields.io/badge/carbon-input-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/input.hpp)
[![surface](https://img.shields.io/badge/carbon-surface-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/surface.hpp)
[![swapchain](https://img.shields.io/badge/carbon-swapchain-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/swapchain.hpp)
[![window](https://img.shields.io/badge/carbon-window-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/window/window.hpp)

#### carbon [display](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/display) > [window](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/display/window)

[![window](https://img.shields.io/badge/carbon-window-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/window/window.hpp)
[![window-glfw](https://img.shields.io/badge/carbon-window_glfw-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/window/window_glfw.hpp)

#### carbon [engine](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/engine)

[![config](https://img.shields.io/badge/carbon-config-yellow.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/engine/config.hpp)
[![engine](https://img.shields.io/badge/carbon-engine-yellow.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/engine/engine.hpp)

#### carbon [pipeline](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/pipeline)

[![render-pass](https://img.shields.io/badge/carbon-render_pass-red.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/pipeline/render_pass.hpp)

# Contributing :tada:
This engine is in a very early alpha stage, so any criticism or ideas are welcome! Simply open a pull request
with details of the changes and I'll review it!

The `master` branch is for the stable releases and the `dev` branch is for the newest features, which may 
make the engine unstable.
