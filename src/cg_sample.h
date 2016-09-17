/*==============================================================================
	cg_sample single-header for extending
   copyright chris g. willcocks MIT license
==============================================================================*/

#ifndef CG_INCLUDE_SAMPLE_H
#define CG_INCLUDE_SAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CG_PRIVATE
#define CG_API static
#else
#define CG_API extern
#endif

/* START OF API ==============================================================*/
struct cg_sample;
CG_API int                 cg_sample_func_1(int x);
CG_API void                cg_sample_func_3(struct cg_sample *x);
CG_API struct cg_sample*   cg_sample_alloc(int x);
CG_API void                cg_sample_clean(struct cg_sample *x);
/* END OF API ================================================================*/

#ifdef __cplusplus
}
#endif

#endif
#ifdef CG_SAMPLE_IMPLEMENTATION

/* IMPLEMENTATION ============================================================*/
struct cg_sample
{
	unsigned char a,b,c,d;  // example data
	void *x;                /* TYPE data array */
};
CG_API int cg_sample_func_1(int)
{
	return 2*x;
}
CG_API void cg_sample_func_3(struct cg_sample *x)
{
	x->a = 2;
}
CG_API struct cg_sample* cg_sample_alloc(int x)
{
	struct cg_sample *s = malloc(sizeof(struct cg_sample));
	s->a = x;
	return s;
}
CG_API void cg_sample_clean(struct cg_sample *s)
{
	free(s->x);
	free(s);
}
/* END OF IMPLEMENTATION =====================================================*/

#endif
