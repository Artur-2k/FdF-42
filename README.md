# FdF 42

A 3D wireframe renderer for height maps, built with mathematical transformations and 42's MiniLibX, a lightweight graphics API built on top of Xlib.

![Demo](assets/demo.gif)

## Description

This project is designed to introduce the basics of computer graphics and how images are rendered onto the screen. Through the development of a wireframe model viewer, the project explores fundamental concepts such as 2D to 3D transformations, projection techniques, and image rendering using mathematical principles.

By processing height maps, the program creates a dynamic 3D visualization where users can manipulate the view by applying scaling, rotations, and translations. The project uses MiniLibX, a lightweight graphics library provided by 42, which abstracts the complexities of low-level graphics programming to focus on essential rendering and display tasks.

Additionally, this project delves into:

- **Matrix transformations** for projecting 3D points onto a 2D plane.
- **Rasterization techniques** for drawing lines between points.

This project is both a challenge and an opportunity to dive deeper into graphics programming, combining math, logic, and visual creativity.


## Getting Started

### Dependencies

- **Operating System**: Unix-based OS (Linux or macOS).
- **Library**: libX11, libXext, and libm for rendering and mathematical computations.

#### Installation on Linux:
Ensure you have the readline library installed. You can install it using the package manager for your distribution:
- **Debian/Ubuntu**: `sudo apt install libx11-dev libxext-dev libbsd-dev libm-dev`
- **Fedora**: `sudo dnf install libX11-devel libXext-devel libbsd-devel`
- **Arch Linux**: `sudo pacman -S libx11 libxext`

#### Installation on macOS:
Ensure the following dependencies are installed on your system. You can use Homebrew to install them:

`brew install libx11 libxext`

### Installing

1. **Clone the Repository**

	Download the project by running:

        git clone https://github.com/Artur-2k/FdF-42.git


2. **Navigate to the Project Directory**


        cd FdF-42/


3. **Compile the Program**

    Build the project by running:

        make all

### Executing program

### Using a Map

In order to visualize the 3D wireframe model, you need a height map. The map is a file where each number represents the height of a specific point on the grid.

#### Example of a simple map:
```
0 0 0 0 0 0 0 0 0
0 1 2 3 4,0xff 3 2 1 0
0 1 2 3 4,0xff 3 2 1 0
0 1 2 3 4,0xff 3 2 1 0
0 1 2 3 4,0xff 3 2 1 0
0 1 2 3 4,0xff 3 2 1 0
0 1 2 3 4,0xff 3 2 1 0
0 0 0 0 0 0 0 0 0
```

You can create your own height map using any text editor, or you can find various sample maps on the folder **/test_maps** and online. The map file should be passed as an argument when executing the program:

```
./fdf /path/to/your/map
```

For a quick test, you can use any of the sample maps provided in the repository (located at /test_maps/\*.fdf), or you can generate your own maps with different sizes and heights for more dynamic results.

## Author

Author name and contact info:

Github: [Artur-2k](https://github.com/Artur-2k)