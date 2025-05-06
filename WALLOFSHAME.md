# Wall of Shame
This log tracks instances where AI was used to solve development issues. It highlights specific challenges that required AI assistance, providing context on what the issue was and how AI helped resolve it. The goal is to document these cases to better understand when and why AI is a valuable tool in the development process.

## 31/03/2025 - Compilation Error

**Issue:** The CMakeLists.txt file had incorrect syntax, leading to compilation issues.

**Solution:** The problem was solved by modifying the `CMakeLists.txt` to a more appropriate format. Specifically, I replaced the incorrect `-lOpenGL32 -lfreeGLUT` linking syntax with proper usage of `target_link_libraries` to ensure dependencies are correctly linked.

> [!TIP] 
> The initial syntax, `-lOpenGL32 -lfreeGLUT`, is more suited for manual compilation with `g++` rather than for CMake projects. In CMake, it's crucial to use `target_link_libraries` to handle dependencies and ensure they are found correctly by the build system. AI was used to identify the mistake in the linking process and suggest the appropriate solution.
