#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fp;
	long lSize;
	char *buffer;

	fp = fopen ( "../prc/cg_tensor.c" , "rb" );
	if (!fp) perror("../prc/cg_tensor.c"),exit(1);

	fseek( fp , 0L , SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	/* allocate memory for entire content */
	buffer = calloc(1, lSize+1);
	if (!buffer) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	if (1!=fread(buffer, lSize, 1, fp))
		fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

   {
      char   *ptr = buffer;
      size_t nlen = strlen("template");

      while (ptr != NULL) {
        ptr = strstr (ptr, "template");
        if (ptr != NULL) {
          printf("found at: %i\n", (int)(ptr-buffer));
          ptr += nlen;

        }
      }

   }

	fclose(fp);
	free(buffer);

	return 0;
}
