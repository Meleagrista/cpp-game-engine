## Prerequisites
This project is built using OpenGL, so you need to have the FreeGLUT library installed on your system.

### Installing FreeGLUT on Windows
The installation process depends on whether you're using **Visual Studio** or **MinGW**. Since this guide follows the **MinGW** setup, refer to [this tutorial](https://www.youtube.com/watch?v=AUFZnA3lW_Q&list=PLmXuiVQyhgd9ZwaF5aWwZblLx9wTBJDAE&index=5) for detailed instructions.

#### Steps:
1. **Install MinGW** (if not already installed):
    - Download it from the official website: [MinGW on SourceForge](https://sourceforge.net/projects/mingw/)
    - Follow the installation instructions.

2. **Download FreeGLUT:**
    - Visit the official FreeGLUT website: [https://freeglut.sourceforge.net](https://freeglut.sourceforge.net)
    - Download a **precompiled package** for Windows.

3. **Install FreeGLUT:**
    - Extract the downloaded package.
    - Copy the necessary files into your MinGW directory.

### Additional Requirements
Ensure that **CMake** is installed on your system. You can download it from the official website: [https://cmake.org/download/](https://cmake.org/download/)  

# Wall of Shame
## 31/03/2025
- Compilation error solved by changing the `CMakeLists.txt` to a more suitable format.
> Your CMakeLists.txt has a few issues with linking. The -lOpenGL32 -lfreeGLUT syntax is more suited for manual g++ compilation rather than CMake. You should use target_link_libraries properly and ensure that your dependencies are found correctly.