# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <minc.h>
# include <volume_io/volume_io.h>

double image_mean (Volume);
double image_std_dev (Volume, double);
double ssim (Volume, Volume);
double image_cross_std_dev (Volume, Volume, double, double);

void main (int argc, char *argv[300])
{
    Volume vol1, vol2;
    double str_sim; 

    input_volume (argv[1],3,NULL,NC_UNSPECIFIED,FALSE,0,0,TRUE,&vol1,NULL);
    input_volume (argv[2],3,NULL,NC_UNSPECIFIED,FALSE,0,0,TRUE,&vol2,NULL);

    str_sim=ssim (vol1, vol2);

    printf ("Structural similarity = %lf", str_sim);
}

double ssim (Volume v1, Volume v2)
{
    double m1, m2; /* means of the images */
    double s1, s2, s12; /* standard deviations of the images */
    double cons1=0, cons2=0; /* constants */
    double s; /* structural similarity index */

    m1=image_mean (v1);
    m2=image_mean (v2);

    s1=image_std_dev (v1, m1);
    s2=image_std_dev (v2, m2);
    s12=image_cross_std_dev(v1, v2, m1, m2); 

    s=(2*m1*m2+cons1)*(2*s12+cons2)/((m1*m1+m2*m2+cons1)*(s1*s1+s2*s2+cons2));

    return (s); 
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

double image_cross_std_dev (Volume v1, Volume v2, double m1, double m2)
{
    int i,j,k;
    double csd=0;
    int size[3];
    double val1, val2;
    double nvox=0;

    get_volume_sizes (v1,size);

    for (i=0;i<size[0];i++)
	for (j=0;j<size[1];j++)
	    for (k=0;k<size[2];k++)
	    {
		val1=get_volume_real_value (v1,i,j,k,0,0);
		val2=get_volume_real_value (v2,i,j,k,0,0);
		if ((val1>=0.5) && (val2>=0.5))
		{ 
		    csd=csd+(val1-m1)*(val2-m2);
		    nvox++;
		}
	    }

    csd=csd/(nvox-1);

    printf ("Cross standard deviation = %lf\n", csd);
    return (csd);
}
