<h1 align="center">Carbon Engine</h1>

<p align="center">
  <img src="https://travis-ci.com/chapmankyle/carbon-engine.svg?branch=master" alt="Travis CI"></img>
  <img src="https://ci.appveyor.com/api/projects/status/ja6b1h34y79t2hqk/branch/master?svg=true" alt="Appveyor CI"></img>
  <a href="https://www.codacy.com/gh/chapmankyle/carbon-engine/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=chapmankyle/carbon-engine&amp;utm_campaign=Badge_Grade">
    <img src="https://app.codacy.com/project/badge/Grade/be5c937e1dfd4df5856979bc967eeab9"/>
  </a>
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

# Installation :hammer:

The engine is packaged as a header-only library, making installation easy.

Simply copy the [source folder](https://github.com/chapmankyle/carbon-engine/tree/master/carbon) to your build tree and use a C++17 compiler.

That's it, enjoy! :tada:

# Usage :cd:

To create the most basic window, all you need is the following:
```c++
#include "carbon/carbon.hpp"

int main() {
    // create default engine
    carbon::Engine engine();

    // main loop when window is open
    while (engine.isRunning()) {
        engine.update();
    }
    
    return 0;
}
```
The above code will create a resizable `800 x 600` window with the title *"Application"*.

---

To create a window with a title, width, height, etc., you need the following:
```c++
#include "carbon/carbon.hpp"

int main() {
    // setup properties for the engine window
    carbon::window::Props properties;
    properties.title = "Game Title Goes Here";
    properties.width = 1280;
    properties.height = 720;
    properties.resizable = true;
    
    // create engine with specified properties
    carbon::Engine engine(properties);

    // main loop when window is open
    while (engine.isRunning()) {
        engine.update();
    }
    
    return 0;
}
```
The above code will create a resizable `1280 x 720` window with the title *"Game Title Goes Here"*.

---

To disable debug messages, make sure to define the following flag:
```c++
#define CARBON_DISABLE_DEBUG
#include "carbon/carbon.hpp"
```
The macro needs to be before the include of `carbon`, otherwise the debug messages will be present.

# Dependencies :gift:

The following dependencies are included as submodules in the `deps` directory:
- :tv: [glfw](https://www.glfw.org/) - Used for handling window interaction
- :triangular_ruler: [glm](https://glm.g-truc.net/0.9.9/index.html) - Used for working with vectors and matrices
- :page_facing_up: [spdlog](https://github.com/gabime/spdlog) - Used for logging engine information

# Modules :card_index_dividers:

#### carbon [common](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/common)

[![debug](https://img.shields.io/badge/carbon-debug-brightgreen.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/common/debug.hpp)
[![logger](https://img.shields.io/badge/carbon-logger-brightgreen.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/common/logger.hpp)
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

#### carbon [display](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/display) > [window](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/display/window)

[![window](https://img.shields.io/badge/carbon-window-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/window/window.hpp)
[![window-glfw](https://img.shields.io/badge/carbon-window_glfw-blue.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/display/window/window_glfw.hpp)

#### carbon [engine](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/engine)

[![config](https://img.shields.io/badge/carbon-config-yellow.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/engine/config.hpp)
[![engine](https://img.shields.io/badge/carbon-engine-yellow.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/engine/engine.hpp)

#### carbon [pipeline](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/pipeline)

[![render-pass](https://img.shields.io/badge/carbon-render_pass-red.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/pipeline/render_pass.hpp)

#### carbon [resources](https://github.com/chapmankyle/carbon-engine/tree/master/carbon/resources)

[![buffer](https://img.shields.io/badge/carbon-buffer-9b59b6.svg)](https://github.com/chapmankyle/carbon-engine/blob/master/carbon/resources/buffer.hpp)

# Contributing :tada:
This engine is in a very early alpha stage, so any criticism or ideas are welcome! Simply open a pull request
with details of the changes and I'll review it!

The `master` branch is for the stable releases and the `dev` branch is for the newest features, which may 
make the engine unstable.
