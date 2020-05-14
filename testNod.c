#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noddy.h"
//##include "lineEvnt.h"
#define DEBUG(X)	X
#define NUM_RUNS    20


extern int noddy (DATA_INPUT, DATA_OUTPUT, int, char *, char *,
                  BLOCK_VIEW_OPTIONS *, GEOPHYSICS_OPTIONS *);


const char* getfield(char* line, int num)
{
    char* tok;
    int i = 0;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (i == num) {
            return tok;
	}
	i++;
    }
    return NULL;
}
int main (int argc, char *argv[])
{

   char calc_model[100];
   int mode=0;
   double x,y,z,x2,y2,z2;
   int rockType,index;
   int restauration = 0;/* GL: restauration mode, outputs original position*/
	int orientation=0; /*LG hack for orientations*/
	char exportname[250];
	char orientationname[250];
	char locationname[250];
   if (argc < 4)
   {
      printf ("Arguments <historyfile> <outputfile> <calc_mode>:\nBLOCK\nGEOPHYSICS\nSURFACES\nBLOCK_GEOPHYS\nBLOCK_SURFACES\nRESTORATION\nALL\n");
      return (-1);
   }


   if(!strcmp(argv[3],"BLOCK"))
	   mode=1;
   else if(!strcmp(argv[3],"GEOPHYSICS"))
	   mode=2;
   else if(!strcmp(argv[3],"SURFACES"))
	   mode=8;
   else if(!strcmp(argv[3],"BLOCK_GEOPHYS"))
	   mode=16;
   else if(!strcmp(argv[3],"ALL"))
	   mode=32;
   else if(!strcmp(argv[3],"BLOCK_SURFACES"))
	   mode=64;   /*GL:file for exporting initial locations*/
   else if(!strcmp(argv[3],"RESTORATION")){
	    mode=1;
		restauration=1;
		sprintf((char *) exportname,"%s_rest.csv",argv[2]);
   }   
   /*LG hack for orientations*/
   else if (!strcmp(argv[3],"ORIENTATION")){
		mode=1;
		orientation=1;
		printf("\n Exporting orientation \n");
		sprintf((char *) orientationname,argv[4]);
		sprintf((char *) exportname,"%s_ori.csv",argv[2]);
		sprintf((char *) locationname,argv[4]);
		printf("\n %s \n",locationname);
   }
		else
   {
	   printf("Calculation mode %s not recognised\n", argv[3]);
	   return(-1);
   }

   if (!noddy(INPUT_FILE_HISTORY, OUTPUT_FILE_IMAGE,
              //CALC_MAGNETICS_IMAGE | CALC_GRAVITY_IMAGE | BLOCK_MODEL, //mwj_hack
               mode, //mwj_hack
              (char *) argv[1], (char *) argv[2],
              (BLOCK_VIEW_OPTIONS *) NULL, (GEOPHYSICS_OPTIONS *) NULL))
   {
      printf ("\nNoddy Failed.\nSorry.\n");
	return (FALSE);
   }
   
   /*GL: exporting initial locations */
   if(restauration){
	FILE * pFile;

	/* dimension of the grid*/
	BLOCK_VIEW_OPTIONS *viewOptions = NULL;

	/* opening the file*/
	pFile = fopen(exportname,"w");
	if( pFile == NULL ){
		printf("Error while opening the output file: %s\n",exportname);
		return (FALSE);
	}
	printf("\nWriting to file: %s\n",exportname);

	viewOptions = getViewOptions();
	if( viewOptions == NULL ){
		printf("Error while getting the dimensions.\n");
		return (FALSE);
	}
	printf("Writing grid dimensions...\n");
	printf("%lf\t%lf\t%lf\n",viewOptions->originX,viewOptions->originY,
					(viewOptions->originZ - viewOptions->lengthZ));
	printf("%lf\t%lf\t%lf\n",viewOptions->lengthX,viewOptions->lengthY,
					viewOptions->lengthZ);
	printf("%lf\t%lf\t%lf\n",viewOptions->geologyCubeSize,
					viewOptions->geologyCubeSize,viewOptions->geologyCubeSize);
	fprintf(pFile,"%lf\t%lf\t%lf\n",viewOptions->originX,viewOptions->originY,
					(viewOptions->originZ - viewOptions->lengthZ));
	fprintf(pFile,"%lf\t%lf\t%lf\n",viewOptions->lengthX,viewOptions->lengthY,
					viewOptions->lengthZ);
	fprintf(pFile,"%lf\t%lf\t%lf\n",viewOptions->geologyCubeSize,
					viewOptions->geologyCubeSize,viewOptions->geologyCubeSize);
	printf("Writing grid dimensions... Done.\n");

	printf("Writing original coordinates...\n");
	//for//(z = viewOptions->originZ + viewOptions->lengthZ; z>= viewOptions->originZ; z-= viewOptions->geologyCubeSize ){
	for(z =viewOptions->originZ ; 
					z<= viewOptions->originZ + viewOptions->lengthZ; 
					z+= viewOptions->geologyCubeSize ){
	    for(y= viewOptions->originY;  
						y<= viewOptions->originY + viewOptions->lengthY; 
						y+= viewOptions->geologyCubeSize ){
		    for(x=viewOptions->originX; 
							x<= viewOptions->originX + viewOptions->lengthX; 
							x+= viewOptions->geologyCubeSize ){
			   x2=x;y2=y;z2=z;
			   whereRock(&x2, &y2, &z2,&rockType,&index);
			   fprintf(pFile,"%d\t%d\t%lf\t%lf\t%lf\n",index,rockType,x2,y2,z2);
		    }
	    }      
    }
	printf("Writing original coordinates... Done.\n");
	
	fclose(pFile);
    }
   if (orientation){
    printf("\nWriting orientations\n");
	int ne = 0;
	FILE * pFile;
	pFile = fopen(exportname,"w");
	printf("%s",exportname);
	printf("\n %s \n",locationname);
	if( pFile == NULL ){
		printf("Error while opening the output file: %s\n",exportname);
		return (FALSE);
	}

	double dip, dipdir;
	dip = 0.;
	dipdir = 0.;
    WINDOW win = (WINDOW) getEventDrawingWindow ();
   	int numEvents;
   	numEvents = (int) totalObjects(win);

	BLOCK_VIEW_OPTIONS *viewOptions = NULL;
//	
    printf("events %i \n",numEvents);
	viewOptions = getViewOptions();
	if( viewOptions == NULL ){
		printf("Error while getting the dimensions.\n");
		return (FALSE);
	}
	//z = 5000;
	fprintf(pFile,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n","x","y","z","dip","strike","event","x2","y2","z2","index","rocktype");
	FILE * lFile;
	lFile = fopen(locationname,"r");
	if( lFile == NULL ) {
			printf("No locations specified using a regular grid \n");
		    for(y= viewOptions->originY;  
						y<= viewOptions->originY + viewOptions->lengthY; 
						y+= viewOptions->geologyCubeSize*10 ){
		    for(x=viewOptions->originX;
						   	
							x<= viewOptions->originX + viewOptions->lengthX; 
							x+= viewOptions->geologyCubeSize*10 ){
					for (z=viewOptions->originZ;
									z<=viewOptions->originZ + viewOptions->lengthZ;
									z+=viewOptions->geologyCubeSize*10) {
				//export ori of all events
				for (ne = 0; ne<numEvents; ne++){
					calcOrientation(x,y,z,4,ne,&dip,&dipdir);
					x2=x; y2=y; z2=z;
					whereRock(&x2, &y2, &z2,&rockType,&index);
			   		// fprintf(pFile,"%d\t%d\t%lf\t%lf\t%lf\n",index,rockType,x2,y2,z2);
					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t%f\t%f\t%f\t%f\t%f\t\n",	
									x,y,z,dip,dipdir+90,ne,x2,y2,z2,index,rockType);
					
					
				}			
				//export bedding 
				calcOrientation(x,y,z,3,4,&dip,&dipdir);
				whereRock(&x2, &y2, &z2,&rockType,&index);

				fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t%f\t%f\t%f\t%f\t%f\t\n",	
									x,y,z,dip,dipdir+90,numEvents,x2,y2,z2,index,rockType);
				

			}
			}
		}
	}
	if (lFile != NULL) {
	char line[1024];
	int linen = 0;
	while (fgets(line,1024,lFile)) {
		if (linen == 0){

			linen++;
			continue;
		}
		char* tmp = strdup(line);
		//printf("%s\n",tmp);
		tmp = strdup(line);
		double x = atof(getfield(tmp,0));// = sscanf("%f",getfield(tmp,0));
		tmp = strdup(line);
		double y = atof(getfield(tmp,1));// = sscanf("%f",getfield(tmp,0));
		tmp = strdup(line);
		double z = atof(getfield(tmp,2));// = sscanf("%f",getfield(tmp,0));

		for (ne = 0; ne<numEvents; ne++){
			calcOrientation(x,y,z,4,ne,&dip,&dipdir);
			x2=x; y2=y; z2=z;
			whereRock(&x2, &y2, &z2,&rockType,&index);
			fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t%f\t%f\t%f\t%f\t%f\t\n",	
				x,y,z,dip,dipdir+90,ne,x2,y2,z2,index,rockType);
			}			
				//export bedding 
		calcOrientation(x,y,z,3,4,&dip,&dipdir);
		x2=x; y2=y; z2=z;
		whereRock(&x2, &y2, &z2,&rockType,&index);
		fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t%f\t%f\t%f\t%f\t%f\t\n",	
		x,y,z,dip,dipdir+90,numEvents,x2,y2,z2,index,rockType);
		free(tmp);
	}
   	}
	fclose(pFile);

   }


   return (TRUE);
}


