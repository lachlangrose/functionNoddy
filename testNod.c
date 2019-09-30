#include <stdio.h>
#include <stdlib.h>
#include "noddy.h"
//##include "lineEvnt.h"
#define DEBUG(X)	X
#define NUM_RUNS    20


extern int noddy (DATA_INPUT, DATA_OUTPUT, int, char *, char *,
                  BLOCK_VIEW_OPTIONS *, GEOPHYSICS_OPTIONS *);


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
		printf("exporting orientation");
		sprintf((char *) orientationname,argv[4]);
		sprintf((char *) exportname,"%s_ori.csv",argv[2]);
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
	if( pFile == NULL ){
		printf("Error while opening the output file: %s\n",exportname);
		return (FALSE);
	}
	///FILE * inFile;
	///char c[1000]; 
	///char buffer[256];
	///int i, j,k;
	///double coords[3];
	///int event, type;
	///event = 0;
	///type = 3;
	double dip, dipdir;
	dip = 0.;
	dipdir = 0.;
    WINDOW win = (WINDOW) getEventDrawingWindow ();
   	int numEvents;
   	numEvents = (int) totalObjects(win);

	///inFile= fopen(orientationname, "r");
	///while (fgets(c, sizeof(c),inFile)) {
	///j = 0;
	///k=0;
	///for (i = 0; i<strlen(c); i++){
	///	if (c[i] == ','){
	///		j=0;
	///		coords[k] = atof(buffer);
	///		k++;
	///		continue;
	///		if (k == 3){
	///			type = atoi(buffer);
	///			k++;
	///		continue;}
	///	   if (k == 4){
	///		   event = atoi(buffer);	   
	///		   k++;}
	///	}
	///	buffer[j]=c[i];
	///	j+=1;
	///}
	//
	BLOCK_VIEW_OPTIONS *viewOptions = NULL;
//	
    printf("events %i",numEvents);
	viewOptions = getViewOptions();
	if( viewOptions == NULL ){
		printf("Error while getting the dimensions.\n");
		return (FALSE);
	}
	//z = 5000;
	fprintf(pFile,"%s\t%s\t%s\t%s\t%s\t%s\t\n","x","y","z","dip","strike","event");
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
					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t\n",	
									x,y,z,dip,dipdir+90,ne);
					
					//calcOrientation(x,y,z,4,1,&dip,&dipdir);
					//					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t\n",	
					//									x,y,z,dip,dipdir,1);
					//calcOrientation(x,y,z,4,2,&dip,&dipdir);
					//					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t\n",	
					//									x,y,z,dip,dipdir,2);
					//					
					//calcOrientation(x,y,x,4,3,&dip,&dipdir);
					//					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t\n",	
					//									x,y,z,dip,dipdir,3);
					//calcOrientation(x,y,z,3,4,&dip,&dipdir);
					//					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t\n",	
					//									x,y,z,dip,dipdir,4);		
				}			
				//export bedding 
				calcOrientation(x,y,z,3,4,&dip,&dipdir);
					fprintf(pFile,"%f\t%f\t%f\t%f\t%f\t%i\t\n",	
									x,y,z,dip,dipdir+90,numEvents);
				

			}
			}
		}
	
	fclose(pFile);
	//fclose(inFile);
	

   }


   return (TRUE);
}


