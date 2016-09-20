/*==============================================================================
	cg_tensor, single-header small tensor class (multi-dimensional array)
   copyright chris g. willcocks MIT license
==============================================================================*/

/* implementation ============================================================*/
struct cg_tensor_T
{
   T *data;
   unsigned int *size;
   unsigned char n;
};

uint32 cg_tensor_T_elems(struct cg_tensor_T *t)
{
   uint32 i;
   uint32 elms=1;

   for (i=0; i < t->n; ++i)
      elms *= t->size[i];

   return elms;
}

void cg_tensor_T_free(struct cg_tensor_T *t)
{
   free(t->data);
   free(t->size);
   free(t);
}

struct cg_tensor_T2* void cg_tensor_T_to_T2(const struct cg_tensor_T *t1)
{
   T2 *t2 = NULL;
   uint32 elms, i;

   t2 = malloc(sizeof(struct cg_tensor_T2));
   t2->n = t1->n;
   t2->s = malloc(t2->n * sizeof(T2));
   memcpy(t2->size, t1->size, t2->n * sizeof(T2));

   /* copy from a source type into a destination type */
   elms = cg_tensor_T2_elems(o);
   t2->data = (T2*)malloc(sizeof(T2)*elms);
   for (i=0; i<elms; ++i)
   {
      t2->data[i] = (T2)t1->data[i];
   }

   return t2;
}

/* end of implementation =====================================================*/
