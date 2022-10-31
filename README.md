# vk-voxel-raytracer

Attempt to write a Voxel Raytracer using Vulkan

## Project Structure

The code base is split up into two parts: The runner and raytracer itself.

The runner is used as a pipeline to build, test and/or run the raytracer.
The raytracer is the main application.


## Quickstart

Run the quickstart.sh script like the following:
```
sh quickstart.sh <mode>
```

`<mode>` can be one of the following: debug, release


## Code Style

I want to abstract away as many details as possible, including the Vulkan interface,
allocations etc.

This is possible using an Entity Component System.


## First Goals/Steps

- [x] Runner
- [ ] Entity Component System Base
- [ ] SDL2 + Vulkan integration
- [ ] Vulkan Window

These steps are my primary focus for now, more will be added in the future.
