#include <math.h>
#include <string.h>
#include <vector>
#include "Texture.h"

#define DEBUG

using namespace std;

// Texture list
vector<TEX*> _textures(0);

#ifndef __FREEGLUT_EXT_H__
// Draw bitmap text
void glutBitmapString(void *font,char *text)
{
	while (*text)
    	glutBitmapCharacter(font, *text++);
}

// Draw vector text
void glutStrokeString(void *font,char *text)
{
	while (*text)
    	glutStrokeCharacter(font, *text++);
}

#endif

int _seekTex(char *nome)
{
	unsigned int i;
	for(i=0;i<_textures.size();++i)
		if(!strcmp(nome,_textures[i]->name))
			return i;
	return -1;
}

void FreeTextures()
{
	unsigned int i;
#ifdef DEBUG
	printf("Total tex: %lu\n",_textures.size());
#endif
	// for each
	for(i=0;i<_textures.size();++i)
	{
		// Free texture
#ifdef DEBUG
		printf("%s: %d x %d (id: %d)\n", _textures[i]->name, _textures[i]->dimx,
				_textures[i]->dimy, _textures[i]->texid);
#endif
		free(_textures[i]);
	}
	_textures.clear();
}

TEX *LoadTexture(string file, bool mipmap)
{
	GLenum format;

	if(file=="")
		return NULL;

	char* name = (char *)file.c_str();
	int index = _seekTex(name);

	if(index!=-1)
		return _textures[index];

	TEX *pImage = LoadJPG(name);

	if(pImage == NULL)
		exit(0);

	strcpy(pImage->name,name);

	glGenTextures(1, &pImage->texid);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, pImage->texid);
	printf("LoadTexture: %d\n",pImage->texid);
	if(pImage->ncomp==1) format = GL_LUMINANCE;
	else format = GL_RGB;

	if(mipmap)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, pImage->dimx, pImage->dimy,
			format, GL_UNSIGNED_BYTE, pImage->data);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, pImage->dimx, pImage->dimy,
			0, format, GL_UNSIGNED_BYTE, pImage->data);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	free(pImage->data);

	_textures.push_back(pImage);
	return pImage;
}

void SetTextureFilter(GLint tex, GLint minfilter, GLint magfilter)
{
	glEnable(GL_TEXTURE_2D);
	if(tex!=-1)
	{
		glBindTexture(GL_TEXTURE_2D,tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magfilter);
	}
	else
	for(unsigned int i=0;i<_textures.size();++i)
	{
		glBindTexture(GL_TEXTURE_2D,_textures[i]->texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magfilter);
	}
	glDisable(GL_TEXTURE_2D);
}

void DecodeJPG(jpeg_decompress_struct* cinfo, TEX *pImageData, bool invert)
{
	jpeg_read_header(cinfo, TRUE);

	jpeg_start_decompress(cinfo);

	pImageData->ncomp = cinfo->num_components;
	pImageData->dimx  = cinfo->image_width;
	pImageData->dimy  = cinfo->image_height;

	int rowSpan = pImageData->ncomp * pImageData->dimx;
	pImageData->data = new unsigned char[rowSpan * pImageData->dimy];

	int height = pImageData->dimy - 1;
	unsigned char** rowPtr = new unsigned char*[pImageData->dimy];
	if(invert)
		for (int i = 0; i <= height; i++)
			rowPtr[height - i] = &(pImageData->data[i*rowSpan]);
	else
		for (int i = 0; i <= height; i++)
			rowPtr[i] = &(pImageData->data[i*rowSpan]);

	int rowsRead = 0;
	while (cinfo->output_scanline < cinfo->output_height)
	{
		rowsRead += jpeg_read_scanlines(cinfo, &rowPtr[rowsRead], cinfo->output_height - rowsRead);
	}

	delete [] rowPtr;

	jpeg_finish_decompress(cinfo);
}

TEX *LoadJPG(const char *filename, bool invert)
{
	struct jpeg_decompress_struct cinfo;
	TEX *pImageData = NULL;
	FILE *pFile;

	if((pFile = fopen(filename, "rb")) == NULL)
	{
		printf("Unable to load %s\n",filename);
		return NULL;
	}

	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, pFile);

	pImageData = (TEX*)malloc(sizeof(TEX));

	DecodeJPG(&cinfo, pImageData, invert);

	jpeg_destroy_decompress(&cinfo);

	fclose(pFile);

	return pImageData;
}
