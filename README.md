# Ray Tracer

A ray tracer written in C++

## Structure

| File | Purpose |
| --- | --- |
| `main.cpp` | Scene setup and render entry point |
| `common.h` | Shared constants and includes |
| `vec3.h` | 3D vector, also used as `point3` and `colour` |
| `ray.h` | Ray class |
| `colour.h` | Colour output |
| `camera.h` | Camera, sampling, and ray colour logic |
| `hittable.h` | Abstract base for hittable geometry |
| `hittable_list.h` | Scene object container |
| `sphere.h` | Sphere geometry |
| `interval.h` | Ray `t` interval helpers |

## Progress

- [x] PPM output, vec3, ray class
- [x] Perspective camera and viewport
- [x] Ray–sphere intersection
- [x] Surface normal shading
- [x] Front/back face detection
- [x] Hittable abstraction and scene list
- [x] Antialiasing
- [x] Diffuse materials
- [ ] Metal and glass materials
- [ ] Positionable camera, FOV, depth of field