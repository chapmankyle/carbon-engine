<h1 align="center">Carbon Engine</h1>

<p align="center">
  <img src="https://travis-ci.com/chapmankyle/carbon-engine.svg?branch=master" alt="Travis CI"></img>
  <img src="https://ci.appveyor.com/api/projects/status/ja6b1h34y79t2hqk?svg=true" alt="Appveyor CI"></img>
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

# Contributing :tada:
This engine is in a very early alpha stage, so any criticism or ideas are welcome! Simply open a pull request
with details of the changes and I'll review it!

The `master` branch is for the stable releases and the `dev` branch is for the newest features, which may 
make the engine unstable.
