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
CG_API void 				 cg_image_to_float		 (struct cg_image *im);
CG_API void 				 cg_image_to_bytes 		 (struct cg_image *im);
CG_API void              cg_image_to_ycbcr       (struct cg_image *im);
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
	unsigned char *data; /* data: warning may also be floating point */
	unsigned int  *size; /* size of each dimension, [w][h][d] */
	unsigned char  dims; /* number of dimensions, e.g. 2 for 2d */
	unsigned char  comp; /* number of components, e.g. 3 for rgb image */
	unsigned char  bypp; /* number of bytes per pixel, e.g. 1, 2, 4, or 8 */
};

CG_API struct cg_image* cg_image_load(char const *filename)
{
	int width=0, height=0, comp=0;
	struct cg_image *im = (struct cg_image*)malloc(sizeof(struct cg_image));

	im->bypp = 1;
	im->dims = 2;
	im->size = malloc(im->dims * sizeof(unsigned char));
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

CG_API void cg_image_rgb_to_gray(struct cg_image *im)
{
	unsigned int i=0, ptr=0, elms=1;
	assert(im->comp == 3);

	for (i=0; i<im->dims; ++i)
		elms *= im->size[i];

	if (im->bypp == 1)
	{
		unsigned char *data = im->data;
		for (i=0; i<elms; ++i)
		{
			unsigned char r = data[ptr++];
			unsigned char g = data[ptr++];
			unsigned char b = data[ptr++];

			data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		}
		data = realloc(im->data, sizeof(unsigned char)*elms);
	}
	else if (im->bypp == 4)
	{
		float *data = (float*)im->data;
		for (i=0; i<elms; ++i)
		{
			float r = data[ptr++];
			float g = data[ptr++];
			float b = data[ptr++];

			data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		}
		data = realloc(im->data, sizeof(float)*elms);
	}
	else if (im->bypp == 8)
	{
		double *data = (double*)im->data;
		for (i=0; i<elms; ++i)
		{
			double r = data[ptr++];
			double g = data[ptr++];
			double b = data[ptr++];

			data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		}
		data = realloc(im->data, sizeof(double)*elms);
	}
	else if (im->bypp == 2)
	{
		unsigned short *data = (unsigned short*)im->data;
		for (i=0; i<elms; ++i)
		{
			unsigned short r = data[ptr++];
			unsigned short g = data[ptr++];
			unsigned short b = data[ptr++];

			data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		}
		data = realloc(im->data, sizeof(unsigned short)*elms);
	}
	im->comp = 1;
}

CG_API struct cg_image* cg_image_clone(struct cg_image *im, int bypp)
{
	struct cg_image *out = NULL;
	unsigned int i=0, elms=1;
	out = malloc(sizeof(struct cg_image));
	out->dims = im->dims;
	out->comp = im->comp;
	out->bypp = bypp;

	for (i=0; i<im->dims; ++i)
		elms *= im->size[i];

	/* todo: replace same size arrays with memcpy calls */
	if (im->bypp == 1)
	{
		if 	  (bypp == 1) { unsigned char *id = (unsigned char*)im->data; unsigned char  *cd = (unsigned char *)out->data; cd = malloc(sizeof(unsigned char	)*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned char	)id[i]; } }
		else if (bypp == 2) { unsigned char *id = (unsigned char*)im->data; unsigned short *cd = (unsigned short*)out->data; cd = malloc(sizeof(unsigned short)*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned short)id[i]; } }
		else if (bypp == 4) { unsigned char *id = (unsigned char*)im->data; float 			  *cd = (float		  	  *)out->data; cd = malloc(sizeof(float			)*elms); for (i=0; i<elms; ++i) { cd[i] = (float			)id[i]; } }
		else if (bypp == 8) { unsigned char *id = (unsigned char*)im->data; double 		  *cd = (double		  *)out->data; cd = malloc(sizeof(double			)*elms); for (i=0; i<elms; ++i) { cd[i] = (double			)id[i]; } }
	}
	else if (im->bypp == 2)
	{
		if 	  (bypp == 1) { unsigned short *id = (unsigned short*)im->data; unsigned char  *cd = (unsigned char *)out->data; cd = malloc(sizeof(unsigned char	)*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned char	)id[i]; } }
		else if (bypp == 2) { unsigned short *id = (unsigned short*)im->data; unsigned short *cd = (unsigned short*)out->data; cd = malloc(sizeof(unsigned short	)*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned short)id[i]; } }
		else if (bypp == 4) { unsigned short *id = (unsigned short*)im->data; float 			 *cd = (float		  	 *)out->data; cd = malloc(sizeof(float				)*elms); for (i=0; i<elms; ++i) { cd[i] = (float			)id[i]; } }
		else if (bypp == 8) { unsigned short *id = (unsigned short*)im->data; double 		  	 *cd = (double		  	 *)out->data; cd = malloc(sizeof(double			)*elms); for (i=0; i<elms; ++i) { cd[i] = (double			)id[i]; } }
	}
	else if (im->bypp == 4)
	{
		if 	  (bypp == 1) { float *id = (float*)im->data; unsigned char  *cd = (unsigned char *)out->data; cd = malloc(sizeof(unsigned char )*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned char )id[i]; } }
		else if (bypp == 2) { float *id = (float*)im->data; unsigned short *cd = (unsigned short*)out->data; cd = malloc(sizeof(unsigned short)*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned short)id[i]; } }
		else if (bypp == 4) { float *id = (float*)im->data; float 			 *cd = (float		  	 *)out->data; cd = malloc(sizeof(float			  )*elms); for (i=0; i<elms; ++i) { cd[i] = (float			  )id[i]; } }
		else if (bypp == 8) { float *id = (float*)im->data; double 		    *cd = (double		    *)out->data; cd = malloc(sizeof(double		  )*elms); for (i=0; i<elms; ++i) { cd[i] = (double		  )id[i]; } }
	}
	else if (im->bypp == 8)
	{
		if 	  (bypp == 1) { double *id = (double*)im->data; unsigned char  *cd = (unsigned char *)out->data; cd = malloc(sizeof(unsigned char )*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned char )id[i]; } }
		else if (bypp == 2) { double *id = (double*)im->data; unsigned short *cd = (unsigned short*)out->data; cd = malloc(sizeof(unsigned short)*elms); for (i=0; i<elms; ++i) { cd[i] = (unsigned short)id[i]; } }
		else if (bypp == 4) { double *id = (double*)im->data; float 			*cd = (float		  	*)out->data; cd = malloc(sizeof(float			 )*elms); for (i=0; i<elms; ++i) { cd[i] = (float			 )id[i]; } }
		else if (bypp == 8) { double *id = (double*)im->data; double 		   *cd = (double		   *)out->data; cd = malloc(sizeof(double			 )*elms); for (i=0; i<elms; ++i) { cd[i] = (double			 )id[i]; } }
	}

	return out;
}

/*
CG_API void cg_image_blur_gauss_2d(const struct cg_image *src, struct cg_image *dst, const double sigma)
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
