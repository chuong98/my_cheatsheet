# MODERN CMake

## 1. **CMake Project Structure**
- The structure is that each folder/subfolder has its own CMakeLists.txt file, just like `__init__.py` in Python projects.
- The top-level CMakeLists.txt file is used to set the project name and version, and to include subdirectories for building libraries and executables, using the `add_subdirectory` command.
For example, the top-level CMakeLists.txt file might look like this:       
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set library and executable names
set(LIBRARY_NAME MyLibrary)
set(EXECUTABLE_NAME MyExecutable)

# Find required packages
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

# Include subdirectories for building libraries and executables
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)
``` 

- In each subdirectory, the CMakeLists.txt file is used to define the specific targets (libraries or executables) that are built from the source files in that directory. For example, a minimal CMakeLists.txt file in a subdirectory need at least 4 followingcommands:
```cmake
add_subdirectory(sub_sub_library) # include the sub_directory of the current library subdirectory
add_library(${LIBRARY_NAME} my_library.cc) # define a library target
target_include_directories(${LIBRARY_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} # include the current source directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../another_folder/include  # include the headers from another subdirectory     
    ) #must be defined after the add_library command and before the target_link_libraries command 
add_executable(${EXECUTABLE_NAME} main.cc) # define an executable target
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME}) # link the executable to the library
```

- This allows us to build complex C++ projects with multiple libraries and executables, while keeping the build configuration organized and modular.

## 2. Cmake Features:
### 2.1 add_executable and add_library
1. `add_library`: This command is used to define a library target, like a package in Python.
```cmake
add_library(MyLibrary my_library.cc) # Define a library target named MyLibrary with the source file my_library.cc
```
- you can specify multiple source files for the library using `target_sources`:
```cmake
add_library(MyLibrary) # Define a library target named MyLibrary first
target_sources(MyLibrary PRIVATE my_library.cc utils.cc) # Then add source files to the library target later
``` 
- After defining the library, you need to specify include directories (so that they can find the headers)
```cmake
target_include_directories(MyLibrary PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                           $<INSTALL_INTERFACE:include>
                                           ${ANY_PATH_TO_HEADERS}) # Include directories are visible to consumers of the library
```
- If the library depends on other libraries, you need to link them using `target_link_libraries`:
```cmake
target_link_libraries(MyLibrary PRIVATE AnotherLibrary) # Link AnotherLibrary to MyLibrary, making it available to consumers of MyLibrary
```
2. `add_executable`: This command is used to define an executable target in CMake.
```cmake
add_executable(MyExecutable main.cc) # Define an executable target named MyExecutable with the source file main.cc
```
- you can also specify multiple source files for the executable by using `target_sources`:
```cmake
add_executable(MyExecutable) # Define an executable target named MyExecutable
target_sources(MyExecutable PRIVATE main.cc utils.cc) # Add source files to the executable target
```
this allows you to add source files incrementally, which can be useful for larger projects where you want to keep the `add_executable` command clean and focused on the target name. Then, in each subdirectory, you can define the sources for the executable using `target_sources`. 
- After defining library and executable, you need to link the library to the target:
```cmake
target_link_libraries(MyExecutable PRIVATE MyLibrary) # Link the library to the executable, making it available to consumers of the executable
``` 



### 2.2 Variables and Options
- Variables: CMake allows you to define variables that can be used throughout your CMake files. You can set variables using the `set` command, and use them in other commands.
```cmake
set(MY_VARIABLE "Hello, World!")
message(STATUS "MY_VARIABLE: ${MY_VARIABLE}")
```
- Options: CMake supports options that can be set by the user when configuring the project. You can define options using the `option` command, which allows users to enable or disable features.
The difference between `set` and `option` is that `set` defines a variable that can be changed, while `option` defines a boolean variable that can be toggled.
```cmake
option(MY_OPTION "Enable my option" ON)
if(MY_OPTION)
    message(STATUS "MY_OPTION is enabled")
    add_subdirectory(my_feature) # include a subdirectory if the option is enabled
else()
    message(STATUS "MY_OPTION is disabled")
endif()
``` 

### 2.3. Libraries and Executables
- CMake supports different types of libraries, including static libraries, shared libraries, and object libraries.  
```cmake
add_library(MyStaticLibrary STATIC my_static_library.cc) # Static library, linked at compile time, bigger binary size but faster execution.
add_library(MySharedLibrary SHARED my_shared_library.cc) # Shared library, linked at runtime, smaller binary size but slower execution.
add_library(MyObjectLibrary OBJECT my_object_library.cc) # Object library, not linked directly, but can be used to create other libraries or executables.
```
- `PUBLIC`, `PRIVATE`, and `INTERFACE` keywords are used to specify the visibility of include directories and linked libraries.
```cmake
target_include_directories(MyLibrary PUBLIC include) # Include directories are visible to consumers of the library
target_include_directories(MyLibrary PRIVATE src) # Include directories are only visible to the library itself
target_link_libraries(MyExecutable PUBLIC MyLibrary) # Link the library to the executable, making it available to consumers of the executable
```

## 3. Cmake Command line:
- To configure a CMake project, you typically run the following commands in the terminal:
```bash
mkdir build
cd build
cmake .. # Configure the project
make # Build the project
```
- The `cmake ..` command tells CMake to look for the CMakeLists.txt file in the parent directory (the root of the project).
- The `make` command builds the project based on the configuration specified in the CMakeLists.txt files.
- You can also specify build types (e.g., Debug, Release) using the `-DCMAKE_BUILD_TYPE` option, or other options specified in the CMakeLists.txt files.
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DMY_OPTION=ON ..
```     
- To clean the build directory, you can use:
```bash
make clean
``` 


