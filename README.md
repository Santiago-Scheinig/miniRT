# miniRT

_This project has been created as part of the 42 curriculum by alraro, sscheini._

## Description

miniRT is a raytracing engine written in C that renders 3D scenes from scene description files (.rt format). It supports spheres, planes, and cylinders with ambient and diffuse lighting, hard shadows, and multiple colored spotlights (bonus).

## Instructions

### Compilation

```bash
make        # Compiles the mandatory version (miniRT)
make bonus  # Compiles the bonus version (miniRT_bonus)
make clean  # Removes object files
make fclean # Removes object files and binaries
make re     # Full rebuild
```

### Execution

```bash
./miniRT scene.rt            # Mandatory version
./miniRT_bonus scene.rt      # Bonus version (threads, phong, checker, textures, cone, hyperboloid, paraboloid)
```

The program takes a single argument: a scene description file with the `.rt` extension.

### Controls

- **ESC** or click the red cross on the window frame to close the program.

## Resources

- [Ray Tracing in One Weekend](https://raytracing.github.io/) — Reference for ray tracing fundamentals
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — 42's graphics library
- [Scratchapixel](https://www.scratchapixel.com/) — Ray tracing math and algorithms
- AI tools were used for debugging assistance and understanding matrix transformations for object rotation.