#include <stdio.h>

using namespace std;

int main()
{
	FILE *file=fopen("input/input_chi_500.txt","r");
	char buffer[512];
	FILE *file2 = NULL;
	int v;
	for(int i=0;i<8000;i++)
	{
		fscanf(file, "%d\n", &v); 
		if(i%400==0)
		{
			sprintf(buffer,"input/input_chi_400_split/%d.txt",i);	
			if(file2!=NULL)
			{
				fclose(file2);
			}
			file2=fopen(buffer,"w");
		}
		fprintf(file2,"%d\n",v);
	}
	fclose(file2);
	fclose(file);
	return 0;
}
