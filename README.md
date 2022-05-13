# BattleSub
Will eventually become a two player 2D submarine game with some fluid dynamics.
BattleSub is using Magnum Graphics, Box2D, EnTT, and ImGUI:

[![Build Status](https://travis-ci.com/bfeldpw/battlesub.svg?branch=master)](https://travis-ci.com/bfeldpw/battlesub)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5aa2f9b18121497cbe9ec07c610a08bd)](https://www.codacy.com/gh/bfeldpw/battlesub/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=bfeldpw/battlesub&amp;utm_campaign=Badge_Grade)
[![Last commit](https://img.shields.io/github/last-commit/bfeldpw/battlesub)

## What happened
Well, I wanted to use Lua for scripting and configuration purposes, which I did in other projects before. But then TravisCI errored, because of missing Lua. So I added Lua, changed its version for CI, changed Ubuntu version in CI, added missing headers and everything was fine, eventually, apart from - git.

Ofcourse, there is a backup, but given BattleSubs current state and popularity, I do not see any reason to further fiddle around with git, trying to merge the backup including history with current changes.

So now, since the history is gone, lets just add a little changelog here, beginning today (2022-05-13):

2022-05-13: Add lua to enable configuration via scripts

## Installation and Dependencies

To build and install after cloning run
```bash
cd scripts
./build_dependencies && ./build
```
from BattleSub directory.

If successful, run BattleSub using `./run` or `/<path>/<to>/scripts/run` if in another directory.

### Dependencies

You can always have a look at .travis.yml for a configuration that should work. In general, dependencies are:
* SDL2
* Lua

Other dependencies will be installed and compiled when running "build_dependencies" (see above).

### Platforms

While I tried to stay portable with all code and libraries, BattleSub currently only supports Linux, since I don't exactly know, how to develop for Windows. Every support is welcome, ofcourse.

## Credits

Since other libraries are what drives a great part of this project, I think they should go first. I appreciate all the hard work done by publicy available libraries, such as [Magnum Graphics](https://github.com/mosra/magnum),  [Box2D](https://github.com/erincatto/box2d), [EnTT](https://github.com/skypjack/entt), and [Dear ImGUI](https://github.com/ocornut/imgui), as well as other contributions I maybe forgot. 

Special thanks go to [Vladimír Vondruš](https://github.com/mosra) and supporters, not only for the aforementioned Magnum Graphics middleware, but also the fast response time on gitter.im on my questions. Not only have the dev(s) been answering my API-related questions, but have also been giving valuable hints on concepts for implementation of different aspects. 

## Screenshots

Final buffer composition with debug GUI:
![alt text](screenshots/Screenshot_20210219_172850.png?raw=true)
### Velocity field
The velocity field a vector field. Here, direction is color coded while intensity displays the velocity magnitude. The velocity field is used to move itsself (self advection), to move the density field (advection), and to move the physical objects. Since physical objects are calculated on the CPU, the velocity field is subsampled and read back to CPU. A double buffered, threaded pixelbuffer is used via DMA to avoid blocking. Sub-sampling is done spatially as well as temporally. In each frame, a lower resolution stripe of the velocity field is read back. There are no visible artifacts on physics objects, since sudden changes do only appear for force/acceleration. Influence on objects velocities and positions is implicitely smoothened by integration of accelerations.
![alt text](screenshots/Screenshot_20210219_172911.png?raw=true)
### Pressure field
The pressure field is calculated with a numeric optimisation, i.e. iteratively. It originates from divergence and ensures, that grid cells are mass preserving. This finally leads to vortices.
![alt text](screenshots/Screenshot_20210219_173001.png?raw=true)
### Heightmap (Background)
The heightmap is a background image that is procedurally generated by mainly using several octaves of different noise functions.
![alt text](screenshots/Screenshot_20210219_173152.png?raw=true)
### Heightmap distorted by velocity field
The velocity field distorts the heightmap based on velocity direction and magnitude to simulate a visual waterflow. This is pure cosmetics, kind of the "rule of cool".
![alt text](screenshots/Screenshot_20210219_173212.png?raw=true)
### Velocity vectors (sub-sampled)
The velocity field may also be displayed by vectors. It is based on the subsampled field that was read back to CPU. It is further subsampled for reduced density and thus, better visualisation.
![alt text](screenshots/Screenshot_20210219_173237.png?raw=true)
### Velocity probes
Physical objects are influenced by the subsampled velocity field that was read back to CPU. Velocity probes measure the field in several points and include normal vectors of the objects edges to finally calculate the velocities/forces acting on objects. The probes show the current relative velocity (radius) and field direction (radial line).
![alt text](screenshots/Screenshot_20210219_173255.png?raw=true)

