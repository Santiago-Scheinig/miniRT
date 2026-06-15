_This project has been created as part of the 42 curriculum by aramos-r, sscheini._

# miniRT

## Description

miniRT is a ray tracing engine written in C that renders 3D scenes described in `.rt` scene files. The project implements the core principles of ray tracing from scratch: casting rays from a camera through each pixel, detecting intersections with geometric objects, and computing the final color using lighting models.

The mandatory version supports spheres, planes, and cylinders with ambient lighting, diffuse shading, hard shadows, and a single point light. The bonus version extends this with multithreaded tile-based rendering (16 worker threads via `pthreads`), multiple colored point lights, Phong specular reflection, checker pattern textures, XPM texture mapping, normal maps, and additional geometric primitives — cone, hyperboloid, and paraboloid.

The renderer uses a matrix-based transform system: each object carries a local-to-world transform, its inverse, and its inverse-transpose, allowing ray intersection tests to be performed in local object space for simplicity while still producing correct world-space normals.

## Instructions

### Dependencies

- A Unix-like system with X11 (Linux) — the project uses **MiniLibX**, 42's X11 windowing wrapper.
- `gcc`, `make`, `norminette` (for style checks).
- The bonus version requires `pthread` support (standard on Linux/macOS).

### Compilation

```bash
make           # Mandatory and bonus version → ./miniRT && ./miniRT_bonus
make bonus     # Bonus version     → ./miniRT_bonus
make clean     # Remove object files
make fclean    # Remove object files and binaries
make re        # Full rebuild (mandatory)
```

> The bonus build compiles a separate binary and does **not** alter the mandatory sources. All bonus-only code is gated behind the `BONUS` preprocessor flag.

### Execution

```bash
./miniRT scene.rt            # Mandatory version
./miniRT_bonus scene.rt      # Bonus version
```

The program takes exactly one argument: a `.rt` scene description file.

### Scene file format

Each line in a `.rt` file defines one element. Identifiers and their fields:

| Identifier | Element | Required fields |
|---|---|---|
| `A` | Ambient light | ratio `[0,1]`, color `R,G,B` |
| `C` | Camera | position, orientation vector, FOV `[0,180]` |
| `L` | Point light | position, brightness `[0,1]`, color `R,G,B` |
| `sp` | Sphere | center, diameter, color |
| `pl` | Plane | point, normal vector, color |
| `cy` | Cylinder | center, axis, diameter, height, color |

Bonus elements additionally support: `cn` (cone), `hb` (hyperboloid), `pb` (paraboloid), plus per-object Phong coefficients, checker patterns, and XPM texture paths.

### Controls

- **ESC** or close the window to exit.

### Developer / CI script

`rtapp.sh` and `rtapp_bonus.sh` are helper scripts that combine norminette style checks with configurable resolution builds:

```bash
./rtapp.sh -norm DK      # Run norminette then build at 1920×1080
./rtapp.sh 2K            # Build at 2560×1440
./rtapp_bonus.sh 4K      # Bonus build at 3840×2160
```

## Resources

The following references were used during development.

### Ray tracing theory

- [_Ray Tracing in One Weekend_](https://raytracing.github.io/) — Peter Shirley's free series; fundamental concepts of ray casting, BVH, and materials.
- [Scratchapixel](https://www.scratchapixel.com/) — In-depth articles on ray-sphere/plane/cylinder intersection math, the Phong model, and coordinate transforms.
- [_The Ray Tracer Challenge_](http://www.raytracerchallenge.com/) — Jamis Buck; test-driven approach to building a ray tracer, especially useful for matrix transform pipelines.

### Math & graphics

- [3Blue1Brown — Essence of Linear Algebra](https://www.3blue1brown.com/topics/linear-algebra) — Intuition behind matrix transforms, inverses, and transpose normals.
- [Inigo Quilez — Articles](https://iquilezles.org/articles/) — Compact intersection formulas for quadric surfaces (cone, paraboloid, hyperboloid).

### 42-specific

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — Hook system, image buffer access, and event loop.
- [42 Norminette](https://github.com/42School/norminette) — Code style enforcer used throughout the project.

### AI usage

AI tools (Claude) were used for:
- **Debugging** — diagnosing incorrect normal transform behavior (missing inverse-transpose pass) and shadow-acne epsilon tuning.
- **Matrix math explanations** — clarifying why normals must be transformed by the inverse-transpose of the object matrix rather than the forward transform.
- **Code review** — checking Norminette compliance and spotting missing edge cases in the intersection routines for capped quadrics.
- **Documentation** — drafting and structuring this README.

No AI-generated code was submitted directly; all suggestions were reviewed, adapted, and integrated manually.
