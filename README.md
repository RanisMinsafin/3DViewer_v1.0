# 3DViewer v1.0

## Introduction

3DViewer v1.0 is a program developed for visualizing 3D wireframe models. This versatile tool allows users to load 3D models, apply various transformations, customize visualization settings, and even save images and screencasts. The program is developed in the C language following the C11 standard and can be built with a Makefile.

## Features

### Basic Functionality

- The program enables users to load 3D wireframe models from obj files (vertices and surfaces list support only).
- Users can translate, rotate, and scale the loaded model in relation to the X, Y, and Z axes.
- The graphical user interface provides an intuitive way to interact with the 3D model and adjust its position, rotation, and scale.
- Users can view information about the uploaded model, including the file name, number of vertices, and edges.

### GUI Framework

- 3DViewer v1.0 features a GUI implementation based on a GUI library with API support for C89/C99/C11.
- For Linux, supported libraries include GTK+, CEF, and Qt.
- For macOS, supported libraries include GTK+, Nuklear, raygui, microui, libagar, libui, IUP, LCUI, CEF, and Qt.

### Advanced Features

- Users can customize the type of projection (parallel and central) to adjust how the 3D model is displayed.
- The program allows users to set the type (solid, dashed), color, and thickness of the edges, as well as the display method (none, circle, square), color, and size of the vertices.
- Background color settings are available to tailor the visualization environment to user preferences.
- Custom settings are saved between program restarts, providing a seamless user experience.

### Performance

- 3DViewer v1.0 ensures smooth performance even when working with models containing up to 1,000,000 vertices.
- The program efficiently handles large models without interface freezes, ensuring user interactivity.

### Image and Screencast Capture

- Users have the option to capture and save rendered images as bmp and jpeg files, allowing them to preserve their work.
- A special button enables users to record small screencasts, creating gif animations of the loaded object's custom affine transformations (640x480, 10fps, 5s).

## Building and Running

- 3DViewer v1.0 is built using the C11 standard with the gcc compiler.
- The code is organized in the 'src' folder.
- A Makefile is provided with standard targets for GNU programs: all, install, uninstall, clean, dvi, dist, tests, and gcov_report.
- Users can build and run the program with the provided Makefile.

## Conclusion

3DViewer v1.0 is a powerful tool for visualizing 3D wireframe models with ease and flexibility. Its user-friendly interface, customizable settings, and performance optimizations make it suitable for a wide range of 3D modeling and visualization tasks. Whether you're working on a small project or handling large 3D models, 3DViewer v1.0 has you covered.