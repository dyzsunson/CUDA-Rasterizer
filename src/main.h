// CIS565 CUDA Rasterizer: A simple rasterization pipeline for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania

#ifndef MAIN_H
#define MAIN_H

#ifdef __APPLE__
	#include <GL/glfw.h>
#else
	#include <GL/glew.h>
	#include <GL/glut.h>
#endif

#include "glm/gtc/quaternion.hpp"
#include "colorReader.h"
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "glslUtility.h"
#include "glm/glm.hpp"
#include "rasterizeKernels.h"
#include "utilities.h"
#include "ObjCore/objloader.h"

#if CUDA_VERSION >= 5000
    #include <helper_cuda.h>
    #include <helper_cuda_gl.h>
    #define compat_getMaxGflopsDeviceId() gpuGetMaxGflopsDeviceId() 
#else
    #include <cutil_inline.h>
    #include <cutil_gl_inline.h>
    #define compat_getMaxGflopsDeviceId() cutGetMaxGflopsDeviceId()
#endif

using namespace std;

//-------------------------------
//------------GL STUFF-----------
//-------------------------------
//colorReader* myColorReader;

bool nineteen_eighty_four = false;
bool backfaceCull = true;
bool checkWriteCount = false; //draw yellow if we write twice
bool useLargeStep = false;
bool interpColors = true; //else use avg. of colors per-face
bool useShading = true;
bool normalsAsColors = false;
bool rotateModel = false;
bool drawLines = false;
glm::vec3 camPos;
int frame;
int fpstracker;
double seconds;
int fps = 0;
GLuint positionLocation = 0;
GLuint texcoordsLocation = 1;
const char *attributeLocations[] = { "Position", "Tex" };
GLuint pbo = (GLuint)NULL;
GLuint displayImage;
uchar4 *dptr;

obj* mesh;

float *nbo; //nbo has same size as vbo
float* vbo;
int vbosize;
float* cbo;
int cbosize;
int* ibo;
int ibosize;

glm::vec3 position; 
glm::vec3 currView(0, 0, -1); 
glm::vec3 currUp(0,1,0); 
glm::vec3 startView;
glm::vec3 startUp;

//P0 and P1 are for Arcball camera
glm::vec3 startP0;
glm::vec3 endP1;
glm::quat qstart; //starting rotation for camera 
glm::quat currRot;

bool arcballRotOn = false;
bool firstRun = true;
bool interactiveCamera = true; //false for multi-frame animation rendering

//-------------------------------
//----------CUDA STUFF-----------
//-------------------------------

int width=800; int height=800;

//-------------------------------
//-------------MAIN--------------
//-------------------------------

int main(int argc, char** argv);

//-------------------------------
//---------RUNTIME STUFF---------
//-------------------------------

void runCuda();

#ifdef __APPLE__
	void display();
#else
	void display();
	void keyboard(unsigned char key, int x, int y);
#endif

//-------------------------------
//----------SETUP STUFF----------
//-------------------------------

#ifdef __APPLE__
	void init();
#else
	void init(int argc, char* argv[]);
#endif

void initPBO(GLuint* pbo);
void initCuda();
void initTextures();
void initVAO();
GLuint initShader(const char *vertexShaderPath, const char *fragmentShaderPath);

//-------------------------------
//---------CLEANUP STUFF---------
//-------------------------------

void cleanupCuda();
void deletePBO(GLuint* pbo);
void deleteTexture(GLuint* tex);
void shut_down(int return_code);

#endif