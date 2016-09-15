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
CG_API struct cg_image* cg_image_load          (char const *filename);
CG_API void             cg_image_free          (struct cg_image *im);

CG_API void             cg_image_blur_gauss_2d (const struct cg_image *src, struct cg_image *dst, const double sigma);
CG_API void             cg_image_blur_box_2d   (const struct cg_image *src, struct cg_image *dst, const unsigned int* boxes);
CG_API unsigned int*    cg_image_blur_boxes    (const double sigma, const int n);
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
   struct cg_image *im = malloc(sizeof(struct cg_image));

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

CG_API void cg_image_blur_gauss_2d(const struct cg_image *src, struct cg_image *dst, const double sigma)
{
   unsigned int* boxes = cg_image_blur_boxes(sigma, 3);
   cg_image_blur_box_2d(src, dst, boxes);
   free(boxes);
}

CG_API void cg_image_blur_box_2d(const struct cg_image *src, struct cg_image *dst, const unsigned int* boxes)
{
   /* todo: http://blog.ivank.net/fastest-gaussian-blur.html */
}

CG_API unsigned int* cg_image_blur_boxes(const double sigma, const int n)
{
         unsigned int   wl = floor(sqrt((12*sigma*sigma/n)+1)); if(wl%2==0) wl--;
   const unsigned int   wu = wl+2;
   const unsigned int   m  = (int)((12*sigma*sigma - n*wl*wl - 4*n*wl - 3*n)/(-4*wl - 4) + 0.5);

   unsigned int* sizes = malloc(sizeof(unsigned int)*n);

   int i;
   for (i=0; i<n; ++i)
      if (i<m)
         sizes[i]=wl;
      else
         sizes[i]=wu;

   return sizes;
}

/* END OF IMPLEMENTATION =====================================================*/

#endif
