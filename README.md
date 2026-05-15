# C++ Ray Tracer

A physically-based CPU path tracer written from scratch in C++17. Renders photorealistic scenes via recursive Monte Carlo path tracing, with a polymorphic scene graph, BVH spatial acceleration, procedural and image-based textures, volumetric media, and instance transforms.

![Final scene render](images/renders/final_scene.png)
*Final scene — ~1,000+ objects, volumetric fog, procedural noise, image textures, area lighting*

---

## Technical Highlights

### BVH Acceleration

Ray–scene intersection is accelerated with a bounding volume hierarchy (BVH) — a binary tree of axis-aligned bounding boxes (AABBs) built over all scene geometry. At each node, rays are tested against the bounding box using the slab method before descending into children, pruning entire subtrees on a miss.

Construction selects a random axis, sorts primitives by their AABB min along that axis, and splits at the midpoint — giving O(log n) average traversal depth. On scenes with 500+ objects this yields a **~6.5× speedup** over linear traversal.

### Polymorphic Architecture

Three abstract base classes form the core:

| Base class | Implementors |
| --- | --- |
| `hittable` | `sphere`, `quad`, `bvh_node`, `hittable_list`, `constant_medium`, `translate`, `rotate_y` |
| `material` | `lambertian`, `metal`, `dielectric`, `diffuse_light`, `isotropic` |
| `texture` | `solid_colour`, `checker_texture`, `image_texture`, `noise_texture` |

Any `hittable` can carry any `material`; any `material` can sample any `texture`. Instance transforms (`translate`, `rotate_y`) wrap any `hittable` without duplicating geometry — the ray is transformed into object space, tested, and the hit record is transformed back.

### Volumetric Rendering

`constant_medium` wraps any convex `hittable` and simulates participating media (fog, smoke) using exponential density sampling. Given a density parameter, it computes a random scatter distance — if that distance falls inside the volume boundary, the ray scatters via an `isotropic` material (uniform random direction). Otherwise it exits the volume unchanged.

### Perlin Noise

Procedural textures use a Perlin noise implementation built on a hash lattice of random gradient vectors. Interpolation uses trilinear weighting with Hermitian smoothing (6t⁵ − 15t⁴ + 10t³) to eliminate grid artefacts. Turbulence layers multiple octaves (fBm) and feeds the result into a sine function to produce a marble-like pattern.

---

## Scene Catalogue

<details>
<summary>All 9 scenes</summary>

| # | Scene | Key features |
| --- | --- | --- |
| 1 | **Bouncing Spheres** | 500+ randomly placed spheres, depth of field, motion blur |
| 2 | **Checkered Spheres** | 3D spatial checker texture, two large spheres |
| 3 | **Earth** | Spherical UV mapping, image texture (earthmap.jpg) |
| 4 | **Perlin Spheres** | Procedural marble texture, noise layering |
| 5 | **Quads** | Five coloured quadrilateral primitives |
| 6 | **Simple Light** | Rectangular and spherical area lights, dark background |
| 7 | **Cornell Box** | Classic test scene — two rotated boxes, area ceiling light |
| 8 | **Cornell Smoke** | Cornell box with volumetric fog via `constant_medium` |
| 9 | **Final Scene** | All features combined — 1,000+ objects, 800×800 @ 1000 spp |

</details>

---

## Render Gallery

| Bouncing Spheres | Cornell Box |
| --- | --- |
| ![Bouncing Spheres](images/renders/bouncing_spheres.png) | ![Cornell Smoke](images/renders/cornell_smoke.png) |

| Cornell Smoke | Final Scene |
| --- | --- |
| ![Simple Light](images/renders/simple_light.png) | ![Final Scene](images/renders/final_scene.png) |

---

## Build & Run

**Prerequisites:** C++17 compiler, CMake 3.23+

```bash
cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/myScene > output.ppm
```

On PowerShell:

```powershell
.\build\myScene.exe | Out-File -Encoding ascii output.ppm
```

The renderer writes a PPM image to `stdout`. Scene selection and render parameters (resolution, samples per pixel, max bounce depth) are set via a `switch` statement in `src/main.cpp`.

---

## Project Structure

```text
src/
├── main.cpp            — Scene definitions and render entry point
├── common.h            — Shared constants, RNG utilities, common includes
├── vec3.h              — 3D vector math (aliased as point3, colour)
├── ray.h               — Ray primitive with time parameter
├── interval.h          — Numeric range for ray parameter bounds
├── colour.h            — Gamma correction and PPM output
├── camera.h            — Viewport, multi-sample integrator, ray_colour recursion
├── hittable.h          — Abstract base class and hit_record
├── hittable_list.h     — Linear scene container
├── sphere.h            — Ray–sphere intersection, moving spheres
├── quad.h              — Quadrilateral primitive and box() helper
├── aabb.h              — Axis-aligned bounding box, slab-method intersection
├── bvh.h               — BVH construction and traversal
├── material.h          — Five material types
├── texture.h           — Four texture types
├── perlin.h            — Perlin noise with trilinear interpolation
├── constant_medium.h   — Volumetric fog/smoke wrapper
├── stb_implement.h     — stb_image implementation unit
└── external/
    └── stb_image.h     — Image loading & pixel converter (from https://github.com/nothings/stb)
```

---

## Implementation Notes

- **Motion blur** — rays carry a time parameter t ∈ [0,1]; moving spheres interpolate their centre at ray time; BVH bounding boxes span the full motion envelope
- **Front/back face detection** — dot product of ray direction vs outward normal determines surface side at intersection time, enabling correct refraction and two-sided shading
- **Gamma correction** — linear-to-sRGB conversion via square root (γ = 2.0)
- **Instance transforms** — rays are inverse-transformed into object space rather than transforming geometry, keeping `bvh_node` construction simple and memory-efficient
