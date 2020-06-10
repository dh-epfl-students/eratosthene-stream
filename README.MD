# Overview
This project responds to a need to adapt an existing graphical engine programmed in OpenGL to Web usage. It explores a solution where graphics rendering is performed on a dedicated server and streamed to a basic Web client,
where this client is only tasked with display and user inputs controlling.

The main project can be found on https://github.com/nils-hamel/eratosthene-suite.

![alt text](doc/screenshot.png)

## Dependencies
This client depends on following libraries:
* Vulkan SDK (1.2+)
* GLFW 3.2

You also need the following tools:
* `clang++`
* `cmake`
* `glslc` to compile GLSL to SPIR-V  (https://github.com/google/shaderc)


## Build
**The project is targeted for Linux servers only, and has been tested on a Ubuntu 18.04 desktop machine.**
 
To build the project, you can use the command 
```
$ make all
```

To clean the project, you can use the command
```
$ make clean
```

To run the project, make sure your current working directory is the project's base directory (`eratosthene-stream`) and run the executable:
```
$ bin/eratosthene-stream
```

You can also pass a .ply file to render this model instead of the default debugging one :
```
$ ./eratosthene−stream "/path/to/file.ply"
```