#### Build Guide
```bash
make
./myscene
```

#### Keyboard Control
- camera
    - movement
        - leftkey: move left
        - rightkey: move right
        - upkey: move up
        - donekey: move down
    - rotation
        - a: turn left
        - d: turn right
        - w: turn up
        - s: turn down
- cube
    - cubeCenter position
        - j: move left
        - l: move right
        - i: move up
        - k: move down
    - cube Scale
        - ,: scale up
        - .: scale down

#### Extra Library
- glm: vector, mat 
- SOIL: texture
- assimp: model
- openGL, glew, glut

#### Scene Capture
<img src=".\screenshot\myscene.png" width="50%">

#### Used Features
- Light
    - pointLight with attenuation
    - directLight 
    - diffuse, ambient, specular
- Texture
    - 2D texture for cube
    - 2D texture for skybox
- Mirror reflection
 
  Let cube relect color of skybox
    
  <img src=".\screenshot\reflection.png" width="50%">


#### Reference
[OpenGl Tutorial](https://learnopengl-cn.readthedocs.io/zh/latest/05%20Advanced%20Lighting/08%20Deferred%20Shading/)

[Skybox Resource](http://www.custommapmakers.org/skyboxes.php)


#### Tricks
##### SOIL
homepage: http://www.lonesock.net/soil.html

download the latest version
```bash
# in soil/Simple OpenGL Image Library/projects/makefile
# if make directly
$ make
gcc -O2 -s -Wall -o obj/image_helper.o -c ../../src/image_helper.c
Assembler messages:
Fatal error: cant create obj/image_helper.o: No such file or directory
makefile:38: recipe for target 'obj/image_helper.o' failed
make: *** [obj/image_helper.o] Error 1
# we shoud
$ mkdir obj
$ cd obj
$ make
# Then we have 
$ ls
image_DXT.o  image_helper.o  SOIL.o  stb_image_aug.o
$ ar rcs libSOIL.a *.o
$ ls
image_DXT.o  image_helper.o  libSOIL.a  SOIL.o  stb_image_aug.o
```
##### Assimp
homepage: http://assimp.sourceforge.net/

After cmake. Have libassimp.so, libassimp.so.4, libassimp.so.4.1.0. 

Add -Wl,-rpath,pathToLib/ to Makefile

##### Shader
Link shader must done after glewinit().

Otherwise, glCreateShader() can cause segmentation fault.