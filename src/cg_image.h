/*==============================================================================
	cg_image, single-header
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

CG_API struct cg_image* cg_image_load           (char const *filename);
CG_API void             cg_image_free           (struct cg_image *im);
CG_API void             cg_image_rgb_to_gray    (struct cg_image *im);
CG_API struct cg_image* cg_image_clone          (struct cg_image *im);
CG_API void             cg_image_to_ycbcr       (struct cg_image *im);
CG_API void             cg_image_normalise      (struct cg_image *im);
CG_API void             cg_image_blur_gauss_2d  (struct cg_image *im, float sigma, int n);
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
   int   dims; /* number of dimensions, e.g. 2 for 2d*/
	int   comp; /* number of components, e.g. 3 for rgb image */
	int  *size; /* size of each dimension, [w][h][d] */
	void *data; /* TYPE* data, can be allocated  with stretchy_buffer */
};

CG_API struct cg_image* cg_image_load(char const *filename)
{
	struct cg_image *im = (struct cg_image*)malloc(sizeof(struct cg_image));

	im->dims = 2;
	im->size = malloc(im->dims * sizeof(int));
	im->data = stbi_load(filename, &im->size[0], &im->size[1], &im->comp, 0);

	return im;
}

CG_API void cg_image_free(struct cg_image *im)
{
	im->dims = 0;
	im->comp = 0;
	free(im->data);
	free(im->size);
	free(im);
}

CG_API void cg_image_rgb_to_gray(struct cg_image *im)
{
	unsigned int i=0, ptr=0, elms=1;
	unsigned char *data = (unsigned char*)im->data;

	assert(im->comp == 3);

	for (i=0; i<im->dims; ++i)
		elms *= im->size[i];

	for (i=0; i<elms; ++i)
	{
		unsigned char  r = data[ptr++];
		unsigned char  g = data[ptr++];
		unsigned char  b = data[ptr++];

		data[i] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
	}
	im->comp = 1;
	data = realloc(data, sizeof(data)/3);
}

CG_API struct cg_image* cg_image_clone(struct cg_image *im)
{
	unsigned int i=0, elms=1;
	struct cg_image *out = NULL;
   unsigned char* idata = NULL;
   float* odata = NULL;

   out = malloc(sizeof(struct cg_image));
   out->dims = im->dims;
	out->comp = im->comp;
   out->data = malloc(sizeof(float)*elms);
   odata = (float*)out->data;
   idata = (unsigned char*)im->data;

	for (i=0; i<im->dims; ++i)
		elms *= im->size[i];


	/* todo deal with types */
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
