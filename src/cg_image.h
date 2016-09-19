/*==============================================================================
	cg_image, single-header
	multi-dimensional & component, unsigned char, unsigned short, float, or doulbe types
   copyright chris g. willcocks MIT license
==============================================================================*/

#ifndef CG_INCLUDE_IMAGE_H
#define CG_INCLUDE_IMAGE_H

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
CG_API struct cg_image*  cg_image_load           (char const *filename);
CG_API void              cg_image_free           (struct cg_image *im);
CG_API struct cg_image*  cg_image_clone          (struct cg_image *im, int bypp);
CG_API void              cg_image_rgb_to_gray    (struct cg_image *im);
CG_API void              cg_image_normalise      (struct cg_image *im);
CG_API void              cg_image_blur_gauss_2d  (struct cg_image *im, float sigma, int n);
/*CG_API void             cg_image_blur_box_2d   (const struct cg_image *src, struct cg_image *dst, const unsigned int* boxes, const int n);
  CG_API unsigned int*    cg_image_blur_boxes    (const double sigma, const int n);*/
/* END OF API ================================================================*/

#ifdef __cplusplus
}
#endif

#endif
#ifdef CG_IMAGE_IMPLEMENTATION

/* IMPLEMENTATION ============================================================*/
struct cg_image
{
   void *data; /* can be unsigned bytes, shorts, floats or doubles  */
   unsigned int  *size; /* size of each dimension, [w][h][d] */
   unsigned char  dims; /* number of dimensions, e.g. 2 for 2d */
   unsigned char  comp; /* number of components, e.g. 3 for rgb image */
   unsigned char  bypp; /* number of bytes per pixel, e.g. 1, 2, 4, or 8 */
};

CG_API struct cg_image* cg_image_load(char const *filename)
{
   int width=0, height=0, comp=0;
   struct cg_image *im = (struct cg_image*)malloc(sizeof(struct cg_image));

   im->bypp = 1; /* stb supports formats of unsigned char */
   im->dims = 2; /* stb supports 2d image formats */
   im->size = malloc(im->dims * sizeof(unsigned int));
   im->data = stbi_load(filename, &width, &height, &comp, 0);
   im->size[0] = width;
   im->size[1] = height;
   im->comp = comp;

   return im;
}

CG_API void cg_image_free(struct cg_image *im)
{
   im->bypp = 0;
   im->dims = 0;
   im->comp = 0;
   free(im->data);
   free(im->size);
   free(im);
}

CG_API struct cg_image* cg_image_clone(struct cg_image *im, int bypp)
{
   struct cg_image *out = NULL;
   unsigned int i=0, elms=1;

	assert(im->bypp == 1 || im->bypp == 2 || im->bypp == 4 || im->bypp == 8);
	assert(    bypp == 1 ||     bypp == 2 ||     bypp == 4 ||     bypp == 8);

   out = malloc(sizeof(struct cg_image));
   out->dims = im->dims;
   out->comp = im->comp;
   out->bypp = bypp;
	out->size = malloc(im->dims * sizeof(unsigned int));
   memcpy(out->size, im->size, im->dims * sizeof(unsigned int));

	elms = im->comp;
   for (i=0; i<im->dims; ++i)
      elms *= im->size[i];

	/* copy from a source type into a destination type */
	#define CG_IMAGE_CLONE(from,to) from *id = (from *)im->data; to *cd = NULL; \
		out->data = malloc(sizeof(to)*elms); cd = (to *)out->data; for (i=0; i<elms; ++i) cd[i] = (to)id[i]

	/* could have a branch if im->bypp == bypp then do memcpy for each */
   if (im->bypp == 1)
   {
      if (bypp == 1) { CG_IMAGE_CLONE(unsigned char, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(unsigned char, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(unsigned char, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(unsigned char, double); }
   }
	else if (im->bypp == 4)
   {
		if (bypp == 1) { CG_IMAGE_CLONE(float, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(float, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(float, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(float, double); }
   }
   else if (im->bypp == 8)
   {
		if (bypp == 1) { CG_IMAGE_CLONE(double, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(double, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(double, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(double, double); }
   }
   else if (im->bypp == 2)
   {
		if (bypp == 1) { CG_IMAGE_CLONE(unsigned short, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(unsigned short, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(unsigned short, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(unsigned short, double); }
   }

	#undef CG_IMAGE_CLONE

   return out;
}

CG_API void cg_image_rgb_to_gray(struct cg_image *im)
{
   unsigned int i=0, ptr=0, elms=1;
   assert(im->comp == 3);

   for (i=0; i<im->dims; ++i)
      elms *= im->size[i];

	#define CG_IMAGE_RGB_TO_GRAY(type) type *data = (type*)im->data; \
		for (i=0; i<elms; ++i) \
		{ \
			type r = data[ptr++]; \
			type g = data[ptr++]; \
			type b = data[ptr++]; \
			data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b; \
		} \
		data = realloc(im->data, sizeof(type)*elms);

   if 	  (im->bypp == 1) { CG_IMAGE_RGB_TO_GRAY(unsigned char); }
   else if (im->bypp == 4) { CG_IMAGE_RGB_TO_GRAY(float); }
   else if (im->bypp == 8) { CG_IMAGE_RGB_TO_GRAY(double); }
   else if (im->bypp == 2) { CG_IMAGE_RGB_TO_GRAY(unsigned short); }

	#undef CG_IMAGE_RGB_TO_GRAY

   im->comp = 1;
}

CG_API void cg_image_normalise(struct cg_image *im)
{
	unsigned int i=0, elms=1;
	double dmax = DBL_MIN, dmin = DBL_MAX;

	elms = im->comp;
	for (i=0; i<im->dims; ++i)
		elms *= im->size[i];

	#define CG_IMAGE_NORMALISE(type,upper) \
	{ \
		type* data = (type*)im->data; \
		for (i=0; i<elms; ++i) \
		{ \
			if (data[i] > dmax) dmax = data[i]; \
			if (data[i] < dmin) dmin = data[i]; \
		} \
		for (i=0; i<elms; ++i) \
			data[i] = (type)((data[i]-dmin)/(dmax-dmin) * upper); \
	}

	if 	  (im->bypp == 1) { CG_IMAGE_NORMALISE(unsigned char,255); }
   else if (im->bypp == 4) { CG_IMAGE_NORMALISE(float, 1.0); }
   else if (im->bypp == 8) { CG_IMAGE_NORMALISE(double, 1.0); }
   else if (im->bypp == 2) { CG_IMAGE_NORMALISE(unsigned short, 65535); }

	#undef CG_IMAGE_NORMALISE
}

/*
CG_API void cg_image_blur_gauss_2d(const struct cg_image *
src, struct cg_image *dst, c
onst double sigma)
{
  int n = 3;
  unsigned int* boxes = cg_image_blur_boxes(sigma, n);
  cg_image_blur_box_2d(src, dst, boxes, n);
  free(boxes);
}
*/

/* Reference: Alvarez, Mazorra, "Signal and Image Restoration using Shock Filters and Anisotropic Diffusion," SIAM J. on Numerical Analysis, vol. 31, no. 2, pp. 590-605, 1994.*/
CG_API void cg_image_blur_gauss_2d(struct cg_image *im, float sigma, int n)
{

}

CG_API void cg_image_blur_box_2d(const struct cg_image *src, struct cg_image *dst, const unsigned int* boxes, const int n)
{
   /* todo: w */

}

CG_API unsigned int* cg_image_blur_boxes(const double sigma, const int n)
{
   unsigned int wl, wu, m;
   unsigned int* sizes = NULL;
   int i;

   wl = floor(sqrt((12*sigma*sigma/n)+1));
   if(wl%2==0)
      wl--;

   wu = wl+2;
   m  = (int)((12*sigma*sigma - n*wl*wl - 4*n*wl - 3*n)/(-4*wl - 4) + 0.5);
   sizes = malloc(sizeof(unsigned int)*n);

   for (i=0; i<n; ++i)
      if (i<m)
         sizes[i]=wl;
      else
         sizes[i]=wu;

   return sizes;
}
/* END OF IMPLEMENTATION =====================================================*/

#endif
