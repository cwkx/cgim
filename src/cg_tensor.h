/*==============================================================================
	cg_sample single-header for extending
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
struct cg_tensor;
/* END OF API ================================================================*/

#ifdef __cplusplus
}
#endif

#endif
#ifdef CG_TENSOR_IMPLEMENTATION

/* IMPLEMENTATION ============================================================*/
struct cg_tensor_T
{
   T *data;
   unsigned int *size;
   unsigned char n;
};
/* END OF IMPLEMENTATION =====================================================*/

#endif
