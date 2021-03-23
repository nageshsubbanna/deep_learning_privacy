# deep_learning_privacy
The project contains files needed for evaluating the privacy in U-Net and SegNet based segmentations
The files mean_correlation_coefficient.c and structural_similarity.c are used to compute the mean correlation coefficient and structural similarity between two
images respectively.  They need to be compiled with the makefiles provided in the set. They are invoked by

structural_similarity/mean_correlation_coefficient <image 1> <image 2>

The code requires minc 1.5 and netcdf 3.5 which can be found here http://www.bic.mni.mcgill.ca/software/minc/ and https://www.unidata.ucar.edu/software/netcdf/release-notes-3.5.1.html respectively.  Please follow the instructions there to install the them.  Then run the make file to compile the codes necessary. 

