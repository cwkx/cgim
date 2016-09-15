/*==============================================================================
	cg_image_gl, single-header
	binds cg_image to opengl texture
   copyright chris g. willcocks MIT license
==============================================================================*/

#ifndef CG_INCLUDE_IMAGE_GL_H
#define CG_INCLUDE_IMAGE_GL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CG_PRIVATE
#define CG_API static
#else
#define CG_API extern
#endif

/* START OF API ==============================================================*/
struct cg_image;
CG_API unsigned int cg_image_bind(struct cg_image *im);
/* END OF API ================================================================*/

#ifdef __cplusplus
}
#endif

#endif
#ifdef CG_IMAGE_IMPLEMENTATION

/* IMPLEMENTATION ============================================================*/
CG_API unsigned int cg_image_bind(struct cg_image *im)
{
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im->size[0], im->size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, im->data);
	return tex;
}
/* END OF IMPLEMENTATION =====================================================*/

#endif
