all:
##	--maxrregcount=31 -
	nvcc -O3 -arch=sm_35 --maxrregcount=31 --ptxas-options=-v  -Xcompiler -fopenmp corrcoef.cu
	#/usr/local/cuda-6.0/bin/nvcc -O2  -arch=sm_20 --ptxas-options=-v -pg -Xcompiler -fopenmp corrcoef.cu 
