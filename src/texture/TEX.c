
#include "TEX.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

int TEX_load(const char * file)
{
	SDL_Surface * img = IMG_Load(file);
	if (!img) return -1;

	if ((img->w & (img->w-1)) || (img->h & (img->h-1))) {
		printf(">>> %s (%dx%d):\n", file, img->w, img->h);
		printf("\tTexture Size Error: not power of 2.\n");
		return -1;
	}

	int clr_cnt = img->format->BytesPerPixel;
	int tex_fmt;
	if (clr_cnt == 4) {
		if (img->format->Rmask == 0x000000FF)
			 tex_fmt = GL_RGBA;
		else tex_fmt =
#ifdef _WIN32
						 GL_RGBA;
#else
						 GL_BGRA;
#endif
	}
	else if (clr_cnt == 3) {
		if (img->format->Rmask == 0x000000FF)
			 tex_fmt = GL_RGB;
		else tex_fmt = 
#ifdef _WIN32
						 GL_RGB;
#else
						 GL_BGR;
#endif
	}
	else return -1;


	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexImage2D(GL_TEXTURE_2D, 0, clr_cnt, img->w, img->h,
			0, tex_fmt, GL_UNSIGNED_BYTE, img->pixels);
	SDL_FreeSurface(img);

	int err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		printf(">>> %s (%dx%dx%d):\n", file, img->w, img->h, 8*clr_cnt);
		printf("\tOpenGL Error: %s\n", gluErrorString(err));
		return -1;
	}

	return tex;
}

void TEX_free(int tex)
{
	glDeleteTextures(1, (const GLuint *)&tex);
}

