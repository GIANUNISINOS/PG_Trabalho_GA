//
// Created by Gian Boschetti on 2019-04-04.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

#include <stdlib.h>
//#include <stdio.h>

// to usleep
#ifdef __APPLE__
	#include <unistd.h> //N�o Existe no Windows, e n�o est� sendo utilizado
#endif


//To GLEW
#include <GL/glew.h>

//To GLFW
#include <GLFW/glfw3.h>

//To GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load image Libraries
#define STB_IMAGE_IMPLEMENTATION
#ifdef __APPLE__
    #include "./header/stb_image.h"
#elif _WIN64
    #include "./stb_image.h"
#endif //APPLE




using namespace std;
