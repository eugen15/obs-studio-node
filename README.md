[Reasons](#reasons) |
[Getting Started](#quick-start) |
[Environment Variables](#environment-variables) |
[Issues](#issues)

__Reasons__
===========

__What happened to node-obs?__
------------------------------
node-obs proved to be difficult to work with. The following are just a few reasons why a new set of bindings were warranted:

- Lack of objects altogether making context harder to control
- What objects we do use, v8 cannot control their lifetimes
- Difficult to use over the Electron IPC (or any IPC)

~~__Why nbind?__~~
----------------
~~I don't think the node object wrapper is bad but in exchange for complete control over how your object maps to V8, you gain a large amount of complexity and verbosity. nbind has a few advantages:~~

~~- Automatic type checking~~
~~- Automatic type conversion of arguments~~
~~- Simple, straight-forward binding API~~

~~It also allows me to use obspp (a C++ wrapper for OBS) as a base for the binding.~~

__What happened to nbind?__
---------------------------
Unfortunately, nbind doesn't currently support passing JS objects. I felt that this was too big of a problem to ignore or work around. There are unfortunately no other significant wrappers that are worth the effort of integrating. Someone mentioned v8pp of which I wasn't impressed. It's more of a v8 wrapper that has overlapping functionality with Node.js Nan. I also would prefer not using v8 directly (where possible anyways) in the case of future changes which v8 is notorious for. 

There are other reasons as well such as not being able to control prototyping from a class, not having a decent C++ object wrapper (though their method did work hence why I didn't think it was a deal breaker). They didn't unsigned integers even though v8 does. Passing them as signed integers and using them as unsigned is possible but potentially buggy. 

All in all, I like the nbind syntax but it removes a lot of freedom for the sake of simplicity. In this case, it's just far too much freedom lost to justify using it. 

__Why cmake?__
--------------
Because the alternative is gyp which is deprecated. Frankly, node-gyp shouldn't be used anymore since it's incredibly difficult to use outside of simple use-cases.

__Getting Started__
===================
I've tried to simplify the build system as much as possible to streamline going from nothing to a working library.

### __Requirements__ ###
- Currently only Windows is supported
  - Note that it shouldn't take much to add other platforms.
- VC++ 15 (2017), 14 (2015), or 12 (2013)
- CMake 3.0 or higher - [Website](https://cmake.org)
- obs-studio source - [Github](https://github.com/jp9000/obs-studio)
- obs-studio dependencies - [VS2015](https://obsproject.com/downloads/dependencies2015.zip) or [VS2013](https://obsproject.com/downloads/dependencies2013.zip)
- yarn - [Website](https://yarnpkg.com)

The rest are handled through package management.

### __Building__ ###
The build assumes a few things about location (see [Environment Variables](#enviroment-variables)). To build out of the box, clone the obs-studio-node repository within the obs-studio directory. Build 64-bit obs-studio in "build64" within the root directory of obs-studio. We use an environment variable "OBS_BUILD_TYPE" to determine which binaries to copy. Place the obs-studio dependencies (see [Requirements](#requirements)) inside a directory called "obs-studio-deps" next to the obs-studio directory. Only one command is required: `yarn`
#### __Warning__ ####
For now, it automatically generates VC++ files for version 14 (2015). Ye be warned. To change this, modify package.json for now until I can figure out a cleaner way to manage it.

__Environment Variables__
=========================

- __ENABLE_DISTRIBUTION__ - \[ Default: "false" \]
- __OSN_DIST_DIR__ - \[ Default: "node-obs" \]
- __OSN_NODE_NAME__ - \[ Default: "obs-node" \]
- __OBS_BUILD_TYPE__ - \[ Default: Release \]
- __OBS_STUDIO_PATH__ - \[ Default: ${CMAKE_SOURCE_DIR}/.. \]
- __OBS_STUDIO_BUILD64__ - \[ Default: ${CMAKE_SOURCE_DIR}/../build64 \]
- __OBS_STUDIO_DEPS64__ - \[ Default: ${CMAKE_SOURCE_DIR}/../../obs-studio-deps/win64 \]

__Issues__
==========
- We don't quite have a complete distribution folder.
- Need to add support for other platforms.
- Obviously any bindings that are missing (most of them for right now).
- Some more detail on how to build obs-studio for our use case would be fitting.
  - How to disable Qt dependencies (which heavily speeds up build time).
  - Eventually, perhaps building from obs-studio instead of internally would better.