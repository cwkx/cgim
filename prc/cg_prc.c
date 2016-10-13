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

		while (ptr != NULL)
		{
			ptr = strstr (ptr, "template");
			if (ptr != NULL)
			{
				printf("found at: %i\n", (int)(ptr-buffer));
				ptr += nlen;

			}
		}

	}

	fclose(fp);
	free(buffer);

	return 0;
}

char* replace_str(char *str, char *orig, char *rep)
{
	static char buffer[4096];
	char *p;
	int i=0;

	while(str[i])
	{
		if (!(p=strstr(str+i,orig)))
			return str;

		strncpy(buffer+strlen(buffer),str+i,(p-str)-i);
		buffer[p-str] = '\0';
		strcat(buffer,rep);
		printf("STR:%s\n",buffer);
		i=(p-str)+strlen(orig);
	}

	return buffer;
}

/*

main(declarations, implementations)
{
  i=0
  while (i<EOF)
    if capital
      i = get_templates(i, template_list)
    if lowercase
      i = get_forward_decclaration(i, template_list)
      i = get_body(i, body)
      expand_replace(template_list, body, declarations, implementations)
    if comment
      i = get_end_of_comment(i)
    else
      i++
}

i get_templates(i, template_list)
{
   t=0
   p0 = 0

   if i>=EOF
      return i
   if lowercase
      return i
   if comma
      t++
      p0 = i
      i++
}

etc, consider stb_c_lexer?

*/
