#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <GL/glew.h>

class Texture2d {
	public:
		Texture2d();

		unsigned int ID;				// ID to reference the texture
		unsigned int width, height;		// dimensions of loaded image in pixels
		unsigned int internalFormat;	// format of texture object
		unsigned int imageFormat;		// format of loaded image
		unsigned int wrapS;				// wrapping mode on S axis
		unsigned int wrapT;				// wrapping mode on T axis
		unsigned int filterMin;			// filtering mode if texture pixels < screen pixels
		unsigned int filterMax;			// filtering mode if texture pixels > screen pixels

		void load(const char* file, bool alpha);
		void bind() const;
	private:
		void generate(unsigned int width, unsigned int height, unsigned char* data);
};

#endif