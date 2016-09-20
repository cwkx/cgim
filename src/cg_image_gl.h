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
   GLuint tex, tex_dim, tex_form_1, tex_form_2, tex_type;
   glGenTextures(1, &tex);

   assert(im->dims == 1 || im->dims == 2 || im->dims == 3);
   assert(im->bypp == 1 || im->bypp == 4);

   if 	  (im->dims == 2) tex_dim = GL_TEXTURE_2D;
   else if (im->dims == 3) tex_dim = GL_TEXTURE_3D;
   else 							tex_dim = GL_TEXTURE_1D;
   if      (im->size[im->dims-1] == 1) { tex_form_1 = GL_RED;  tex_form_2 = GL_RED;  }
   else if (im->size[im->dims-1] == 3) { tex_form_1 = GL_RGB;  tex_form_2 = GL_RGB;  }
   else 							            { tex_form_1 = GL_RGBA; tex_form_2 = GL_RGBA; }
   if      (im->bypp == 1) tex_type = GL_UNSIGNED_BYTE;
   else if (im->bypp == 4) tex_type = GL_FLOAT;

   glBindTexture(tex_dim, tex);
   glTexParameterf(tex_dim, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(tex_dim, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(tex_dim, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameterf(tex_dim, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glTexImage2D(tex_dim, 0, tex_form_1, im->size[1], im->size[0], 0, tex_form_2, tex_type, im->data);
   glBindTexture(tex_dim, 0);
   
   return tex;
}
/* END OF IMPLEMENTATION =====================================================*/

#endif
