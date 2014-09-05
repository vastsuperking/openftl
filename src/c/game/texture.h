#ifndef TEXTURE_H
#define TEXtURE_H

typedef enum {
	TEX_FMT_RED = 0,
	TEX_FMT_RGB,
	TEX_FMT_RGBA,
	NUM_TEXTURE_FORMATS,
	INVALID_TEXTURE_FORMAT
} ImageFormat;

typedef struct {
	unsigned int handle;
	ImageFormat format;
	int width;
	int height;
} Texture;

void init_texture(Texture *t, ImageFormat format, int width, int height, unsigned char *data);
void init_texture_png(Texture *t, const char *filename);
void destroy_texture(Texture *t);
void bind_texture(Texture *t, int unit);
void unbind_texture(int unit);
unsigned char *read_png(const char *filename, int *width, int *height, ImageFormat *format);
#endif
