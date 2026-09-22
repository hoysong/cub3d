# cub3D

English | [한국어](./README.md)

![cub3D demo](./video.gif)

<code>cub3D</code> is a 42 project inspired by the classic first-person shooter
**Wolfenstein 3D**. It parses a two-dimensional map and renders a real-time
three-dimensional view with ray casting, using C and MiniLibX.

## 1. Features

- Ray casting with perspective wall rendering
- Far-to-near wall rendering based on the [Painter's algorithm](https://en.wikipedia.org/wiki/Painter%27s_algorithm)
- Direction-specific XPM wall textures for north, south, east, and west faces
- Configurable RGB colors for the floor and ceiling
- Keyboard movement and rotation
- Mouse-controlled camera rotation
- Minimap showing the player position and field of view
- Validation of <code>.cub</code> elements, map structure, and enclosure

## 2. Development environment

- C
- Make
- MiniLibX (Linux)
- X11

The Linux version of MiniLibX is included in the
<code>minilibx-linux</code> directory. X11 development packages are required
to build the project.

On Ubuntu or Debian-based systems, install the dependencies with:

~~~bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
~~~

## 3. Build and run

~~~bash
git clone <repository-url>
cd cub3d
make
./cub3D test_map/good.cub
~~~

Other example maps are also available:

~~~bash
./cub3D test_map/pacman.cub
./cub3D test_map/circle.cub
~~~

Available Make targets:

| Command | Description |
| --- | --- |
| <code>make</code> | Build the <code>cub3D</code> executable |
| <code>make clean</code> | Remove object files |
| <code>make fclean</code> | Remove object files and the executable |
| <code>make re</code> | Rebuild the project from scratch |

### 3.1. <code>cannot find -lbsd</code>

If the linker reports the following error, the BSD compatibility development
library is missing:

~~~text
gcc -o mlx-test main.o -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd
/usr/bin/ld: cannot find -lbsd: No such file or directory
~~~

Install <code>libbsd-dev</code> and rebuild:

~~~bash
sudo apt update
sudo apt install libbsd-dev
make re
~~~

## 4. Controls

| Key | Action |
| --- | --- |
| <code>W</code> / <code>S</code> | Move forward / backward |
| <code>A</code> / <code>D</code> | Strafe left / right |
| <code>←</code> / <code>→</code> | Rotate the view |
| <code>P</code> | Toggle mouse-controlled view |
| <code>M</code> | Toggle the minimap |
| <code>ESC</code> | Exit the program |

The window close button also exits the program.

## 5. <code>.cub</code> map format

A map file contains texture paths, floor and ceiling colors, and the map
itself. Configuration elements may appear in any order, but the map must come
after them.

~~~text
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F 30,30,30
C 120,180,255

1111111
1000001
10N0001
1000001
1111111
~~~

### 5.1. Identifiers

| Identifier | Meaning |
| --- | --- |
| <code>NO</code> | North wall texture |
| <code>SO</code> | South wall texture |
| <code>WE</code> | West wall texture |
| <code>EA</code> | East wall texture |
| <code>F</code> | Floor RGB color |
| <code>C</code> | Ceiling RGB color |

Each RGB channel accepts a value from 0 to 255.

### 5.2. Map characters

| Character | Meaning |
| --- | --- |
| <code>0</code> | Walkable space |
| <code>1</code> | Wall |
| <code>N</code>, <code>S</code>, <code>E</code>, <code>W</code> | Player start position and direction |
| Space | Empty area outside the map |

The map must contain exactly one player start position, and every walkable
area must be completely enclosed by walls.

## 6. Project structure

~~~text
.
├── main.c                  # Program entry point
├── parser/                 # .cub parsing and validation
├── mlx_stuff/
│   ├── algorithm/          # Ray and wall intersection calculations
│   ├── raycasting/         # Ray casting and screen rendering
│   └── ...                 # Window, input, player, and minimap handling
├── my_libft/               # Custom C utility library
├── minilibx-linux/         # MiniLibX for Linux
├── test_map/               # Valid and invalid maps plus XPM textures
└── Makefile
~~~

## 7. Rendering overview

The field of view is sampled with rays to identify the first wall hit for each
direction. Consecutive hits on the same wall and texture are grouped into
visible wall segments, which are projected into screen coordinates.

Before drawing, the wall segments are sorted from farthest to nearest and
rendered in that order. This follows the
[Painter's algorithm](https://en.wikipedia.org/wiki/Painter%27s_algorithm):
nearer walls overwrite farther walls where their screen regions overlap.
Each segment is then filled with the corresponding vertical slice of its XPM
texture.
