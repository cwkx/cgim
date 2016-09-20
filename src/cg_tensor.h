/*==============================================================================
	cg_tensor, single-header small tensor class (multi-dimensional array)
   copyright chris g. willcocks MIT license
==============================================================================*/

#ifndef CG_INCLUDE_TENSOR_H
#define CG_INCLUDE_TENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CG_PRIVATE
#define CG_API static
#else
#define CG_API extern
#endif

/* START OF API ==============================================================*/
typedef char               int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;
typedef float              real32;
typedef double             real64;

struct cg_tensor_$T;

CG_API unsigned int  cg_tensor_$T_elems   (struct cg_tensor_$T *t);
CG_API void          cg_tensor_$T_free    (struct cg_tensor_$T *t);

/* END OF API ================================================================*/

#ifdef __cplusplus
}
#endif

#endif
#ifdef CG_TENSOR_IMPLEMENTATION

/* IMPLEMENTATION ============================================================*/

struct cg_tensor_int8 {
   int8 *data;
   unsigned int *size;
   unsigned char n;
};

CG_API unsigned int cg_tensor_elems(struct cg_tensor *t)
{
   unsigned int elms=1, i;
   for (i=0; i < t->d; ++i)
      elms *= t->s[i];
   return elms;
}

CG_API void cg_tensor_free(struct cg_tensor *t)
{
   free(t->x);
   free(t->s);
   free(t);
}


CG_API struct cg_image* cg_image_clone(struct cg_tensor *t, int b)
{
   struct cg_tensor *o = NULL; /* output tensor */
   unsigned int i=0, elms;

	assert(t->b == 1 || t->b == 2 || t->b == 4 || t->b == 8);
	assert(   b == 1 ||    b == 2 ||    b == 4 ||    b == 8);

   o = malloc(sizeof(struct cg_tensor));
   o->d = t->d;
   o->b = b
	o->s = malloc(t->d * sizeof(unsigned int));
   memcpy(o->s, t->s, t->d * sizeof(unsigned int));

   elms = cg_tensor_elems(o);

	/* copy from a source type into a destination type */
	#define CG_IMAGE_CLONE(from,to) from *id = (from *)t->data; to *cd = NULL; \
		o->data = malloc(sizeof(to)*elms); cd = (to *)o->data; for (i=0; i<elms; ++i) cd[i] = (to)id[i]

	/* could have a branch if t->bypp == bypp then do memcpy for each */
   if (t->bypp == 1)
   {
      if (bypp == 1) { CG_IMAGE_CLONE(unsigned char, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(unsigned char, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(unsigned char, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(unsigned char, double); }
   }
	else if (t->bypp == 4)
   {
		if (bypp == 1) { CG_IMAGE_CLONE(float, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(float, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(float, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(float, double); }
   }
   else if (t->bypp == 8)
   {
		if (bypp == 1) { CG_IMAGE_CLONE(double, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(double, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(double, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(double, double); }
   }
   else if (t->bypp == 2)
   {
		if (bypp == 1) { CG_IMAGE_CLONE(unsigned short, unsigned char); }
		if (bypp == 2) { CG_IMAGE_CLONE(unsigned short, unsigned short); }
		if (bypp == 4) { CG_IMAGE_CLONE(unsigned short, float); }
		if (bypp == 8) { CG_IMAGE_CLONE(unsigned short, double); }
   }

	#undef CG_IMAGE_CLONE

   return o;
}
/* END OF IMPLEMENTATION =====================================================*/

#endif
