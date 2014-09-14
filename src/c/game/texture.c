#include "texture.h"

#include <stdlib.h>
#include <assert.h>
#include <png.h>
#include <glload/gl_2_0.h>

static GLenum TEXTURE_FORMAT_MAPPING[NUM_TEXTURE_FORMATS] = { GL_RED, GL_RGB, GL_RGBA };



void
init_texture(Texture *t, ImageFormat format, int width, int height, unsigned char *data) {
	unsigned int handle;
	glGenTextures(1, &handle);
	
	glBindTexture(GL_TEXTURE_2D, handle);

	/* Give the image to OpenGL */
	glTexImage2D(GL_TEXTURE_2D, /*Target to which we bound the texture*/
				 0, /*Mipmap level*/
				 TEXTURE_FORMAT_MAPPING[format], /*Internal format*/
				 width, /*Width*/
				 height, /*Height*/
				 0, /*Border Width*/
				 TEXTURE_FORMAT_MAPPING[format], /*Format*/
				 GL_UNSIGNED_BYTE, /*Data Type*/
				 data);/*Data*/
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	t->handle = handle;
	t->format = format;
	t->width = width;
	t->height = height;
}
void
init_texture_png(Texture *t, const char *filename) {
	int width;
	int height;
	ImageFormat format;
	unsigned char *data;
	
	data = read_png(filename, &width, &height, &format);
	
	init_texture(t, format, width, height, data);

	free(data);
}


void
destroy_texture(Texture *t) {
	glDeleteTextures(1, &(t->handle));
	t->handle = 0;
	t->format = INVALID_TEXTURE_FORMAT;
	t->width = 0;
	t->height = 0;
}

void
bind_texture(Texture *t, int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, t->handle);
}

void
unbind_texture(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*
  Function taken from:
  http://stackoverflow.com/questions/11296644/loading-png-textures-to-opengl-with-libpng-only
  and modified to suit needs
  
  Returns the loaded image width, height, and format in the last few parameters
  Returned value allocated on heap, must call free() when done
*/
unsigned char *
read_png(const char *filename, int *width, int *height, ImageFormat *format) {
	FILE *fp;

    png_byte header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	png_infop end_info;

	int bit_depth, color_type;
	png_uint_32 temp_width, temp_height;
	
	int rowbytes;

	png_byte *image_data;
	png_bytep *row_pointers;

    fp = fopen(filename, "rb");
    if (fp == 0) {
		printf("Error opening file: %s\n", filename);
		assert(0);
    }
    /* read the header */
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
        fprintf(stderr, "Error: %s is not a PNG.\n", filename);
        fclose(fp);
		assert(0);
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "Error: png_create_read_struct returned NULL.\n");
        fclose(fp);
		assert(0);
    }

    // create png info struct
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "error: png_create_info_struct returned NULL.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    /* create png info struct */
    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        printf("Error: png_create_info_struct returned NULL.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
		assert(0);
    }

    /* the code in this if statement gets called if libpng encounters an error */
    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("Error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
		assert(0);
    }

    /* init png reading */
    png_init_io(png_ptr, fp);

    /* let libpng know you already read the first 8 bytes */
    png_set_sig_bytes(png_ptr, 8);

    /* read all the info up to the image data */
    png_read_info(png_ptr, info_ptr);

    /* get info about png */
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
				 NULL, NULL, NULL);

    if (width) { *width = temp_width; }
    if (height){ *height = temp_height; }

	if (bit_depth != 8) {
		printf("Error: unsupported bit depth %d. Must be 8.\n", bit_depth);
	}
	switch(color_type) {
	case PNG_COLOR_TYPE_RGB: *format = TEX_FMT_RGB; break;
	case PNG_COLOR_TYPE_RGBA: *format = TEX_FMT_RGBA; break;
	default: printf("Error: unknown libpng color type %d.\n", color_type); assert(0);
	}

    /* Update the png info struct. */
    png_read_update_info(png_ptr, info_ptr);

    /* Row size in bytes. */
    rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    /* glTexImage2d requires rows to be 4-byte aligned */
    rowbytes += 3 - ((rowbytes-1) % 4);

    /* Allocate the image_data as a big block, to be given to opengl */
    image_data = malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image_data == NULL) {
        printf("Error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
		assert(0);
    }

    /* row_pointers is for pointing to image_data for reading the png with libpng */
    row_pointers = malloc(temp_height * sizeof(png_bytep));
    if (row_pointers == NULL) {
        printf("Error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
		assert(0);
    }

    /* set the individual row_pointers to point at the correct offsets of image_data */
    for (unsigned int i = 0; i < temp_height; i++) {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    /* read the png into image_data through row_pointers */
    png_read_image(png_ptr, row_pointers);
	
	/*clean up*/
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(row_pointers);
	fclose(fp);
	return image_data;
}
