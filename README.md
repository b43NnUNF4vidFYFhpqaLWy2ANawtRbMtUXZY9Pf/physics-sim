# Physics simulation

Constraint-based rigid body physics engine (2D).

https://github.com/user-attachments/assets/c0fa2477-c555-4f0d-9b9e-b1e99aa777ea

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
