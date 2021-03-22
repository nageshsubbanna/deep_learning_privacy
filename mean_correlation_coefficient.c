# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <minc.h>
# include <volume_io/volume_io.h>

double image_mean (Volume);
double image_std_dev (Volume, double);
double mcc (Volume, Volume); /* The two volumes to be compared, the number of slices, the height and the width of the images, in that order */

void main (int argc, char *argv[300])
{
	/* Declarations */ 
	Volume vol1, vol2; 
	double mean_corr_coeff; 

	/* input the images */ 
	input_volume (argv[1],3,NULL,NC_UNSPECIFIED,FALSE,0,0,TRUE,&vol1,NULL); 
	input_volume (argv[2],3,NULL,NC_UNSPECIFIED,FALSE,0,0,TRUE,&vol2,NULL); 
	
	mean_corr_coeff=mcc (vol1, vol2); 
	
	printf ("Mean Correlation Coefficient = %lf", mcc);
}

double image_mean (Volume v)
{
    int i,j,k;
    int size[3];
    double m;
    double val;
    double nvox=0;

    get_volume_sizes (v,size);
    
    for (i=0;i<size[0];i++)
	for (j=0;j<size[1];j++)
	    for (k=0;k<size[2];k++)
	    {
		val=get_volume_real_value (v,i,j,k,0,0);
		if (val>=0.5) 
		{
		    m=m+val;
		    nvox++;
		}
	    }

    m=m/nvox;

    printf ("Mean = %lf\n", m);
    return (m);
}

double image_std_dev (Volume v, double m)
{
    int i,j,k;
    double sd;
    int size[3];
    double val;
    double nvox=0;

    get_volume_sizes (v,size);

    for (i=0;i<size[0];i++)
	for (j=0;j<size[1];j++)
	    for (k=0;k<size[2];k++)
	    {
		val=get_volume_real_value (v,i,j,k,0,0);
		if (val>=0.5) 
		{
		    sd=sd+(val-m)*(val-m);
		    nvox++;
		}
	    }

    sd=sd/(nvox-1);
    sd=sqrt(sd);

    printf ("Standard deviation = %lf\n", sd);
    return (sd);
}

double mcc (Volume v1, Volume v2)
{

	int i,j,k;
	int size[3];
	double val1, val2;
	double m1, m2;
	double s1, s2;
	double sum=0;
	double mean_corr_coeff;

	m1=image_mean (v1);
	m2=image_mean (v2);

	s1=std_dev (v1,m1);
	s2=std_dev (v2,m2);
	
	get_volume_sizes(v1,size);

	for (i=0;i<size[0];i++)
		for (j=0;j<size[1];j++)
			for (k=0;k<size[2];k++)
			{
				val1=get_volume_real_value (v1,i,j,k,0,0);
				val2=get_volume_real_value (v2,i,j,k,0,0);
				sum=sum+(val1-m1)*(val2-m2);
			}

	mean_corr_coeff=sum/(s1*s2);

	return (mean_corr_coeff);
}
