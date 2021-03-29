CC=gcc
CFLAGS=I/home/nagesh/include
LDFLAGS=L/home/nagesh/lib

structural_similarity: structural_similarity.c
	$(CC) -o structural_similarity structural_similarity.c -lvolume_io -lminc -lnetcdf -lm -(CFLAGS) -(LDFLAGS) 

mean_correlation_coefficient: mean_correlation_coefficient.c
	$(CC) -o mean_correlation_coefficient mean_correlation_coefficient.c -lvolume_io -lminc -lnetcdf -lm -(CFLAGS) -(LDFLAGS) 
