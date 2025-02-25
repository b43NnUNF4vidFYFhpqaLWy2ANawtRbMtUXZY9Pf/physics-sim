# Physics simulation

Constraint-based rigid body physics engine (2D).

## Table of contents

- [Physics simulation](#physics-simulation)
  - [Table of contents](#table-of-contents)
  - [Features](#features)
  - [Build](#build)
    - [Demo](#demo)

## Features

- Rigid body dynamics
- Dynamic AABB tree for broadphase collision detection
- GJK + EPA for narrowphase collision detection
- Constraints:
  - Contact constraint
  - Plane constraint
- Sequential impulse constraint solver

## Build

```sh
mkdir build
cd build
cmake ..
make
```

### Demo

```sh
cmake -DBUILD_DEMO=ON ..
make
./demo/demo
```
