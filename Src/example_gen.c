#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 *  $1: output file name
 *  $2: length(KB)
 */
int main(int argc, char** argv)
{
  int length = atoi(argv[2]);
  int i, j;
  
  if (3 != argc)
    {
      printf("Usage: %s [filename] [file length in KB]\n", argv[0]);
      return 0;
    }
  FILE *file = fopen(argv[1], "w");
  if (NULL == file)
    {
      printf("File: '%s' cannot be created!\n", argv[1]);
      return 0;
    }

  srand(time(NULL));
  for (i = 0; i < length; i++)
    {
      for (j = 0; j < 1023; j++)
	{
	  char c = rand() % 26 + 'a';
	  fputc(c, file);
	}
      fputc('\n', file);
    }
  fclose(file);

  printf("Done\n");
  return 0;
}
