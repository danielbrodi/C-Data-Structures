#include <stdio.h>
#include <unistd.h>

int main(int argc, char **arv, char **envp)
{
	int i = 7;
	int j = 12;
	int k = 15;
	int *p = &j;
	
	FILE *fp;
	
	if(0 == (fp = fopen("stoodpid", "w")))
	{
		printf("well, that didn\'t work!\n");
		return -1;
	}	
	
	fprintf(fp, "%p\n", p);
	
	if(fclose(fp))
	{
		printf("oh well.");
		return -1;
	}
	
	return 0;
	
}


