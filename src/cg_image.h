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
CG_API unsigned int      cg_image_elems          (struct cg_image *im);
CG_API struct cg_image*  cg_image_clone          (struct cg_image *im, int bypp);
CG_API void              cg_image_rgb_to_gray    (struct cg_image *im);
CG_API void              cg_image_normalise      (struct cg_image *im);
CG_API void              cg_image_gaussian_blur  (struct cg_image *im, float sigma);
CG_API float*            cg_image_gaussian_kernel(float sigma, unsigned int size);
CG_API unsigned int      cg_image_gaussian_size  (float sigma);
/* END OF API ================================================================*/

#ifdef __cplusplus
}
#endif

#endif
#ifdef CG_IMAGE_IMPLEMENTATION

/* IMPLEMENTATION ============================================================*/
struct cg_image
{
   void *data;          /* can be u_bytes, u_shorts, floats or doubles  */
   unsigned int  *size; /* size of each dimension, [d][h][w][c] */
   unsigned char  dims; /* number of dimensions, e.g. 3 for 2d as channel is a dimension */
   unsigned char  bypp; /* number of bytes per pixel, e.g. 1, 2, 4, or 8 */
};

CG_API unsigned int cg_image_elems(struct cg_image *im)
{
   unsigned int elms = 1, i=0;
   for (i=0; i<im->dims; ++i)
      elms *= im->size[i];
   return elms;
}

CG_API struct cg_image* cg_image_load(char const *filename)
{
   int width=0, height=0, comp=0;
   struct cg_image *im = (struct cg_image*)malloc(sizeof(struct cg_image));

   im->bypp = 1; /* stb supports formats of unsigned char */
   im->dims = 3; /* stb supports 2d image formats */
   im->size = malloc(im->dims * sizeof(unsigned int));
   im->data = stbi_load(filename, &width, &height, &comp, 0);

   im->size[0] = width;
   im->size[1] = height;
   im->size[2] = comp;

   return im;
}

CG_API void cg_image_free(struct cg_image *im)
{
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
   out->bypp = bypp;
	out->size = malloc(im->dims * sizeof(unsigned int));
   memcpy(out->size, im->size, im->dims * sizeof(unsigned int));
   elms = cg_image_elems(im);

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
   assert(im->size[im->dims-1] == 3);
   elms = cg_image_elems(im);

	#define CG_IMAGE_RGB_TO_GRAY(type) type *data = (type*)im->data; \
		for (i=0; i<elms; ++i) \
		{ \
			type r = data[ptr++]; \
			type g = data[ptr++]; \
			type b = data[ptr++]; \
			data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b; \
		} \
		im->data = (type*)realloc(im->data, sizeof(type)*elms);

   if 	  (im->bypp == 1) { CG_IMAGE_RGB_TO_GRAY(unsigned char); }
   else if (im->bypp == 4) { CG_IMAGE_RGB_TO_GRAY(float); }
   else if (im->bypp == 8) { CG_IMAGE_RGB_TO_GRAY(double); }
   else if (im->bypp == 2) { CG_IMAGE_RGB_TO_GRAY(unsigned short); }

	#undef CG_IMAGE_RGB_TO_GRAY
}

CG_API void cg_image_normalise(struct cg_image *im)
{
	unsigned int i=0, elms=1;
	double dmax = DBL_MIN, dmin = DBL_MAX;
	elms = cg_image_elems(im);

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

CG_API float* cg_image_gaussian_kernel(float sigma, unsigned int ksize)
{
   int i, centre; /* must not be unsigned! */
   float sum, *kernel = NULL;

   assert(sigma > 0.0f);
   assert(ksize > 0);

   sum = 0.0f, centre = ksize/2;
   kernel = (float*)malloc(sizeof(float)*ksize);

   for (i=0; i<ksize; ++i) {
      kernel[i] = exp(-(i-centre)*(i-centre) / (2.0 * sigma*sigma));
      sum += kernel[i];
   }

   for (i=0; i<ksize; ++i)
      kernel[i] /= sum;

   return kernel;
}

CG_API unsigned int cg_image_gaussian_size(float sigma)
{
   unsigned int size = (4*sigma+1);
   if (size%2 == 0)
      size++;
   return size;
}

CG_API unsigned int cg_image_sub2ind(unsigned int* zyxc, unsigned int* size, unsigned int dims)
{
   unsigned int pos = zyxc[0], i;
   for (i=1; i<dims; ++i)
      pos = (pos * size[i]) + zyxc[i];
   return pos;
}

CG_API void cg_image_gaussian_blur(struct cg_image *ia, float sigma)
{
   unsigned int ksize = 0, i=0, d;
   float *kernel = NULL;
   struct cg_image *ib = NULL;
   float *a = NULL, *b = NULL;

   ksize = cg_image_gaussian_size(sigma);
   kernel = cg_image_gaussian_kernel(sigma, ksize);
   ib = cg_image_clone(ia, 4);
   a = (float*)ia->data;
   b = (float*)ib->data;

   for (d=1; d<ia->dims; ++d)
   {
      a[i] *= 0.99;
   }

   free(ib);
   free(kernel);
}

/* Alvarez, Mazorra, “Signal and Image Restoration using Shock Filters and Anisotropic Diffusion,” SIAM J. on Numerical Analysis, vol. 31, no. 2, pp. 590–605, 1994.
CG_API void cg_image_blur_gauss_2d(struct cg_image *im, float sigma, int numsteps)
{
   double         lambda, dnu;
   float          nu, boundaryscale, postscale, *ptr, *data;
   unsigned int   i, x, y, elms, width, height;
   int            step;

   assert(sigma>0 && numsteps>0);
   assert(im->dims == 2);
   assert(im->comp == 1);

   width = im->size[0];
   height = im->size[1];
   data = (float*)im->data;

	elms = im->comp;
	for (i=0; i<im->dims; ++i)
		elms *= im->size[i];

   lambda = (sigma*sigma)/(2.0*numsteps);
   dnu = (1.0 + 2.0*lambda - sqrt(1.0 + 4.0*lambda))/(2.0*lambda);
   nu = (float)dnu;
   boundaryscale = (float)(1.0/(1.0 - dnu));
   postscale = (float)(pow(dnu/lambda,2*numsteps));

   for (y=0; y<height; ++y)
   {
      for(step = 0; step<numsteps; ++step)
      {
           ptr = data+width*y;
           ptr[0] *= boundaryscale;


           for(x=1; x<width; x++) {
               ptr[x] += nu*ptr[x-1];
            }

           ptr[x=width-1] *= boundaryscale;


           for(; x>0; x--)
               ptr[x-1] += nu*ptr[x];
      }
   }

   for(x = 0; x < width; ++x)
   {
      for(step = 0; step<numsteps; ++step)
      {
           ptr = data + x;
           ptr[0] *= boundaryscale;


           for(i=width; i<elms; i+=width)
               ptr[i] += nu*ptr[i-width];

           ptr[i=elms-width] *= boundaryscale;


           for(; i>0; i-=width)
               ptr[i - width] += nu*ptr[i];
      }
   }

   for(i = 0; i < elms; ++i)
      data[i] *= postscale;

   return;
}
 */

/* END OF IMPLEMENTATION =====================================================*/

#endif
