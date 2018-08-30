#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

extern "C" {
	#include <jpeglib.h>
}

#ifndef M_PI
#define M_PI 3.1415926
#endif

// Define a estrutura de uma imagem
typedef struct
{
    char name[50];
	int ncomp;
	GLint dimx;
	GLint dimy;
    GLuint texid;
	unsigned char* data;
} TEX;

// Texture handling functions
TEX *LoadTexture(std::string, bool mipmap);
void SetTextureFilter(GLint tex, GLint minfilter, GLint magfilter);
TEX *LoadJPG(const char *filename, bool invert=true);
void FreeTextures();

#endif
