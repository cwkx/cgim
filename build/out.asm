Dump of assembler code for function cg_image_gaussian_blur:
../src/cg_image.h:
211	{
   0x000000000043e480 <+0>:	push   rax
   0x000000000043e481 <+1>:	lea    rsi,[rsp+0x4]

212	   unsigned int ksize, i=0, d=0, elms=1;
213	   float *kernel;
214	
215		elms = im->comp;
216		for (i=0; i<im->dims; ++i)
217			elms *= im->size[i];
218	
219	   /* for each dimension */
220	   for (d=0; d<im->dims; ++d)
221	   {
222	
223	   }
224	
225	   cg_image_gaussian_kernel(sigma, kernel, &ksize);
   0x000000000043e486 <+6>:	call   0x43e250 <cg_image_gaussian_kernel>

226	
227	   free(kernel);
228	}
   0x000000000043e48b <+11>:	pop    rax
   0x000000000043e48c <+12>:	ret    
End of assembler dump.
