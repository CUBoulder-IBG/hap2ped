/***************************************************************************************************************************************************
*
*                                 
****************************************************************************************************************************************************/

#include <time.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "readinteger.h"

#define MAXINT INT32_MAX
#define MAXSNP 27500
#define MAXPEOPLE 400000


int32_t genomes[MAXSNP][MAXPEOPLE];

int32_t nbperson=0;

int32_t nbSNP=0;

char allele[MAXSNP][2];
//
// 
//	

int32_t readhap(int32_t chr,char pathped[])
{	FILE *fp; 
    char filename[200]; 
    strcpy(filename,pathped);
	char number[100];
    sprintf(number, "%d", chr);
	strcat(filename,number);
	strcat(filename,".hap");
	printf("The file to read the data is %s\n", filename); 
	fp = fopen(filename, "r"); 
    if (fp == NULL) 
    {   printf("Could not open file %s", filename); 
        return (0); 
    };
	char c;
	int32_t indiceperson;
	do
	{	indiceperson=0;
		char c1;
		do 
		{	c=getc(fp);
			if (c!= EOF && c!='\n')
			{	c1=getc(fp);
				c1=getc(fp);
				genomes[nbSNP][indiceperson]=(c1-48)*2+c-48;
				indiceperson++;
				if (indiceperson>nbperson) nbperson=indiceperson;
				c1=getc(fp);
			};
		} while (c!=EOF && c!='\n' && c1!=EOF && c1!='\n');
		nbSNP++;
	} while (c!=EOF);
	nbSNP--;
	printf("There are %d people and %d SNPs\n", nbperson, nbSNP);
	fclose (fp);
	return (0);
};
//
// READ MAP
//
int32_t readlegend(char pathlegendfile[])
{	FILE *fp; 
    char filename[200]; 
    strcpy(filename,pathlegendfile);
	fp = fopen(filename, "r"); 
    if (fp == NULL) 
    {   printf("Could not open file %s", filename); 
        return (0); 
    };
	char c;
	do {c=getc(fp);} while (c!='\n');
	int32_t SNP=0;
	do 
	{	do {c=getc(fp);} while (c!=' ' && c!=EOF);	
		if (c!=EOF)
		{	do {c=getc(fp);} while (c!=' ');	
			allele[SNP][0]=getc(fp);
			getc(fp);
			allele[SNP][1]=getc(fp);
			getc(fp);
			SNP++;
		};
	} while (c!=EOF);
	if (SNP!=nbSNP) printf("PROBLEM PROBLEM PROBLEM PROBLEM PROBLEM PROBLEM PROBLEM PROBLEM PROBLEM  %d!=%d",nbSNP,SNP);	
	return (0);
}
//
// CREATE PED 
//
int32_t writeped(int32_t chr,int32_t gen,char pathped[], char output,char pathoutput[], char typeoutput )
{	FILE *fp; 
    char filename[200]; 
    strcpy(filename,pathoutput);
	char number[100];
    sprintf(number, "%d", chr);
	strcat(filename,number);
	if (output=='U') 	strcat(filename,".unphased");
	strcat(filename,".ped");
	printf("The file to write the data is %s\n", filename); 
	fp = fopen(filename, "w"); 
    if (fp == NULL) 
    {   printf("Could not open file %s\n", filename); 
        return (0); 
    };
	INT person;
	for(person=0;person<nbperson;person++)
	{	fprintf(fp,	"g%d %d 0 0 0 -9",gen,person+1);
		INT SNP;
		for(SNP=0;SNP<nbSNP;SNP++)
		{	int32_t random= rand()%2;  
			if (output=='U' && random) 
			{	if ( typeoutput=='0')
				{	fprintf(fp, " %d %d", genomes[SNP][person]/2, genomes[SNP][person]%2);
				} else
				{	fprintf(fp, " %c %c", allele[SNP][genomes[SNP][person]/2], allele[SNP][genomes[SNP][person]%2]);
				}
			}
			else 
			{	if ( typeoutput=='0')
				{	fprintf(fp, " %d %d", genomes[SNP][person]%2, genomes[SNP][person]/2);
				} else
				{	fprintf(fp, " %c %c", allele[SNP][genomes[SNP][person]%2], allele[SNP][genomes[SNP][person]/2]);
				}
			}
		};
		fprintf(fp,"\n");
	};
	fclose (fp);
	return (0);
}
//
// 
//

//
//  main program
//	
int32_t main(int32_t argc, char *argv[])
{	 clock_t begin = clock();
	printf("start..\n");
	//
	printf("Reading arguments...\n");
	//
	int32_t chr;
	if (argc<3)
    {   printf("argument chr missing. To run the program the arguments --set set need to be added. Default is 1\n");
		chr=1;
	} else 
	{	chr = atoi (argv[2]);
	};
	printf("chr is %d\n",chr);
	int32_t gen;
    if (argc<5)
	{   printf("argument path origin is missing. To run the program the arguments --pathorigin pathorigin\n");
		gen=4;
	} else 
	{	gen = atoi (argv[4]);
	};
	printf("gen is %d\n",gen);
	char pathped[500];
	if (argc<7)
	{   printf("The path of the run is missing. No default.\n");
		return 0;
	} else 
	{	strcpy(pathped,argv[6]);
	};
	printf("The path of the hap file is %s\n",pathped);
	char output;
	if (argc<9)
	{   printf("The type of output is missing, Default phased\n");
		output='P';
	} else 
	{	output=argv[8][0]; 
	};
	printf("The type of output is %s\n",output=='U'?"Unphased":"Phased");
	char pathoutput[200];
	if (argc<11)
	{   printf("The path output is missing. No default.\n");
		return 0;
	} else 
	{	strcpy(pathoutput,argv[10]);
	};
	printf("The path of the sample to take from the last generation is %s\n",pathoutput);
	char outputtype;
	if (argc<13)
	{   printf("The parameter outputtype is missing. Default is 01.\n");
	} else 
	{	outputtype=argv[12][0]; 
	};
	printf("The format des ped files est %s\n",outputtype=='0'?"0 and 1":(outputtype=='1'?"1 and 2":"A, C, G, and T"));
	char pathlegendfile[200];
	if (argc<15)
	{   printf("The path of the map file is missing. No default.\n");
	} else 
	{	strcpy(pathlegendfile,argv[14]);
	};
	printf("The path of the output is %s\n",pathlegendfile);
	/*int32_t gen;
	if (argc<13)
	{   printf("gen is missing. Default is 5.\n");
		gen=5;
	} else 
	{	gen = atoi (argv[12]);
	};
	printf("gen is %d\n",gen);
	/*int32_t chr;
	if (argc<15)
	{   printf("chr is missing. Default is 5.\n");
		chr=5;
	} else 
	{	chr = atoi (argv[14]);
	};
	printf("chr is %d\n",chr);
	char arm='q';
	if (argc<17)
	{   printf("arm is missing. Default is p.\n");
	} else 
	{	arm = argv[16][0];
	};
	printf("arm is %c\n",arm);*/
	INT person;
	INT SNP;
	for (person=0;person<MAXPEOPLE;person++)
	{	for(SNP=0;SNP<MAXSNP;SNP++)
		{	genomes[SNP][person]=0;
		};
	};
	readhap(chr,pathped);
	if (outputtype=='A') readlegend(pathlegendfile);
	writeped(chr,gen,pathped,output,pathoutput,outputtype);
	clock_t end = clock();
	float elapsed_secs = (float)(end - begin) ;
    printf("\nTotal time:%f cpu click so %f seconds\n",elapsed_secs,elapsed_secs/CLOCKS_PER_SEC );
	return (0);
} 