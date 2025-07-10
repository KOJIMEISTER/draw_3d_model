# Draw 3D Model

![3D Model Showcase](https://github.com/KOJIMEISTER/DRAW_3D_MODEL/blob/main/model/Snowman.gif)

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Demo](#demo)
- [Controls](#controls)
- [Installation](#installation)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)

## Overview

**Draw 3D Model** is a C++ application that loads and displays 3D objects in a real-time 3D environment. Leveraging OpenGL for rendering, this program offers interactive camera controls, realistic lighting, and texture mapping to bring 3D models to life. Whether you're showcasing your 3D creations or exploring graphics programming, this project serves as a robust foundation.

## Features

- **Real-Time Rendering:** Utilizes OpenGL for high-performance 3D rendering.
- **Model Loading:** Supports hierarchical mesh loading with texture mapping using Assimp.
- **Interactive Camera:** Navigate the 3D space with intuitive keyboard and mouse controls.
- **Dynamic Lighting:** Implements directional lighting with ambient, diffuse, and specular components.
- **Shadow Mapping:** Renders realistic shadows to enhance depth and realism.
- **Texture Management:** Handles multiple texture types including diffuse, specular, normals, and height maps.

## Demo

![3D Model Showcase](https://github.com/KOJIMEISTER/DRAW_3D_MODEL/blob/main/model/Snowman.gif)

*Visual demonstration of the 3D Snowman model with interactive controls.*

## Controls

- **Move Forward:** `W`
- **Move Backward:** `S`
- **Move Left:** `A`
- **Move Right:** `D`
- **Toggle Wireframe Mode:** `F`
- **Exit Application:** `ESC`
- **Camera Rotation:** Move the mouse to look around.

## Installation

### Prerequisites

- **C++ Compiler:** Ensure you have a modern C++ compiler that supports C++11 or later.
- **CMake:** Version 3.10 or higher.
- **Git:** For cloning the repository.

### Steps

1. **Clone the Repository**
    ```bash
    git clone https://github.com/KOJIMEISTER/draw_3d_model.git
    ```
2. **Navigate to the Project Directory**
    ```bash
    cd draw_3d_model
    ```
3. **Create a Build Directory**
    ```bash
    mkdir build && cd build
    ```
4. **Run CMake**
    ```bash
    cmake ..
    ```
5. **Build the Project**
    ```bash
    cmake --build .
    ```
6. **Run the Application**
    ```bash
    ./Draw3DModel
    ```

*Note: Ensure that all dependencies are properly installed and linked.*

## Dependencies

The project relies on the following libraries:

- **[GLFW](https://www.glfw.org/):** Windowing and input.
- **[GLAD](https://glad.dav1d.de/):** OpenGL function loader.
- **[GLM](https://glm.g-truc.net/0.9.9/index.html):** Mathematics library for graphics software.
- **[Assimp](https://www.assimp.org/):** Asset Import Library for model loading.
- **[stb_image](https://github.com/nothings/stb):** Image loading.

Ensure that these dependencies are installed and properly configured in your development environment.

## Usage

Upon launching the application, a window will display the loaded 3D model. Use the keyboard and mouse to navigate and interact with the model:

- **Navigate:** Use `W`, `A`, `S`, `D` keys to move the camera forward, left, backward, and right respectively.
- **Rotate Camera:** Move the mouse to change the viewing direction.
- **Toggle Wireframe:** Press `F` to switch between wireframe and solid rendering modes.
- **Exit:** Press `ESC` to close the application.

## Project Structure

```
draw_3d_model/
├── src/
│   ├── main.cpp
│   ├── init.hpp
│   ├── camera.hpp
│   ├── shader.hpp
│   ├── mesh.hpp
│   └── model.hpp
├── shaders/
│   ├── scene.vert
│   └── scene.frag
├── model/
│   ├── untitled.obj
│   └── Snowman.gif
├── include/
│   └── [External Libraries]
├── LICENSE
├── README.md
└── CMakeLists.txt
```

- **src/**: Contains all the source code files.
- **shaders/**: Vertex and fragment shader programs.
- **model/**: 3D model files and related assets.
- **include/**: External library headers.
- **LICENSE**: MIT License.
- **README.md**: Project documentation.
- **CMakeLists.txt**: Build configuration.

## License

This project is licensed under the [MIT License](LICENSE).

---

```
MIT License

Copyright (c) 2024 Nikita

Permission is hereby granted, free of charge, to any person obtaining a copy...
```

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork the Repository**
2. **Create a Feature Branch**
    ```bash
    git checkout -b feature/YourFeature
    ```
3. **Commit Your Changes**
    ```bash
    git commit -m "Add your feature"
    ```
4. **Push to the Branch**
    ```bash
    git push origin feature/YourFeature
    ```
5. **Open a Pull Request**

Please ensure that your contributions adhere to the project's coding standards and include appropriate documentation.

## Acknowledgements

- **[LearnOpenGL](https://learnopengl.com/):** Comprehensive tutorials on OpenGL.
- **[Assimp](https://www.assimp.org/):** For simplifying model loading.
- **[stb](https://github.com/nothings/stb):** Easy-to-use image loading library.

---

Feel free to reach out for any questions or support!
