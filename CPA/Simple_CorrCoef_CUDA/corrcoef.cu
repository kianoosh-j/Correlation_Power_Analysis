#include<stdio.h>
#include <iostream>
#include<time.h>
#include<omp.h>
//#include "Dtools.h"
#include <time.h>
#include <sys/time.h>


typedef unsigned char BYTE;

#define length 40000
#define step 32
#define width 192
#define height 256
#define depth 16

#define test_byte 8

using namespace std;


__global__ void LargeScale_CorrCoef(int *a_dev, int *b_dev, float *c_dev){

		int tx = threadIdx.x, ty = threadIdx.y;
		int bx = blockIdx.x, by = blockIdx.y;

		int row = by*blockDim.y + ty;
		int col = bx*blockDim.x + tx;

		int exy = 0, ex = 0, ex2 = 0, ey = 0, ey2 = 0;
		float fexy = 0, fex = 0, fex2 = 0, fey = 0, fey2 = 0;

		//shared variables 
		__shared__ int a_shared[32][step];
		__shared__ int b_shared[step][16];
	//	__shared__ long long int btmp_shared[step][16];


		for (int it = 0 ; it < depth ; it++){
			for (int iter = 0 ; iter < length ; iter+=step){

				a_shared[ty][tx]    		  	  = a_dev[it*height*length + row*length + (tx+iter)];
				a_shared[ty][tx+blockDim.x]       = a_dev[it*height*length + row*length + (tx+blockDim.x+iter)];
				b_shared[ty][tx] 		  		  = b_dev[col + (ty+iter)*width];
				__syncthreads();


				for (int iter2 = 0 ; iter2 < step ; iter2++){
					ey  += b_shared[iter2][tx];
					ey2 += b_shared[iter2][tx]*b_shared[iter2][tx];
					ex  += a_shared[ty][iter2];
					ex2 += a_shared[ty][iter2]*a_shared[ty][iter2];
					exy += a_shared[ty][iter2]*b_shared[iter2][tx];
				}	
				__syncthreads();	

			}

			__syncthreads();

			
			fexy =  (float)((double)exy / (double)length);
			fex  =  (float)((double)ex  / (double)length);
			fex2 =  (float)((double)ex2 / (double)length);
			fey  =  (float)((double)ey  / (double)length);
			fey2 =  (float)((double)ey2 / (double)length);

			float cov  = fexy - fex*fey;
			float varx = fex2 - fex*fex;
			float vary = fey2 - fey*fey;
/*
		long long int cov  = length*exy - ex*ey;
		long long int varx = length*length*ex2 - length*ex*ex;
		long long int vary = length*length*ey2 - length*ey*ey;

*/		__syncthreads();


			c_dev[it*height*width + row*width + col] = (float)(cov/sqrt((float)(varx*vary)));
			ex = 0, ey = 0, ex2 = 0, ey2 = 0, exy = 0;
		}
}


void kernelCall(int *a, int *b, float *c){

struct timeval time1,time2,diff;
float sumOfTime = 0.0;
float sumTime=0.0;
for (int i = 0 ; i < 5 ; i++){
	dim3 Grid(12,8);
	dim3 Block(16,32);

	int *a_dev, *b_dev;
	float *c_dev;

	cudaMalloc((void**)&a_dev, depth*height*length*sizeof(int) );
	cudaMalloc((void**)&b_dev, width*length*sizeof(int) );
	cudaMalloc((void**)&c_dev, depth*height*width*sizeof(float) );
	//cudaMemset((void**)&c_dev, 0, depth*height*width*sizeof(float) );

	cudaMemcpy(a_dev, a, depth*height*length*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(b_dev, b, length*width*sizeof(int), cudaMemcpyHostToDevice);
    cout<<"lunch"<<endl;
    gettimeofday(&time1,NULL);
    
	LargeScale_CorrCoef<<<Grid, Block>>>(a_dev, b_dev, c_dev);
	cudaThreadSynchronize();
	
	gettimeofday(&time2,NULL);
    timersub(&time2,&time1,&diff);
    cudaMemcpy(c, c_dev, depth*height*width*sizeof(float), cudaMemcpyDeviceToHost);
    
    sumOfTime = ((time2.tv_sec - time1.tv_sec)*1000.0)+((time2.tv_usec - time1.tv_usec)/1000.0);
    sumTime += sumOfTime;
    cout << "Elapsed time = " << (sumOfTime) << " ms" <<", Sec = "<< diff.tv_sec << ", ms = "<<diff.tv_usec/1000.0<<endl;
    
    //cout << "Elapsed Time = " << ((sumOfTime)) << " ms" <<endl;
    
	cudaFree(a_dev);
	cudaFree(b_dev);
	cudaFree(c_dev);
	//cudaDeviceReset();
}
	cout << "Avg. of total elapsed time = " << (sumTime)/5 << " ms" <<endl;
    //cout << "Elapsed Time = " << (double)((t2-t1)/1000.0) << " ms" <<endl;
    
}


void checkResult(int *a, int *b, float *c){
	long long int sum_b = 0, sum_a = 0.0, sum_b2 = 0.0, sum_a2 = 0.0, sum_ab = 0.0;
	int count = 0;
	float fsum_ab = 0.0, fsum_a = 0.0, fsum_a2 = 0.0, fsum_b = 0.0, fsum_b2 = 0.0;

	for (int iter = 0 ; iter < height ; iter++)
		for (int iter2 = 0 ; iter2 < width ; iter2++){
			for (int iter3 = 0 ; iter3 < length ; iter3++){
				sum_a  += a[test_byte*height*length + iter*length + iter3];
				sum_b  += b[iter3*width + iter2];
				sum_a2 += a[test_byte*height*length + iter*length + iter3]*a[test_byte*height*length + iter*length + iter3];
				sum_b2 += b[iter3*width + iter2]*b[iter3*width + iter2];
				sum_ab += a[test_byte*height*length + iter*length + iter3]*b[iter3*width + iter2];
			}


			fsum_ab = (float)((float)sum_ab / (float)length); //(float)
			fsum_a  = (float)((float)sum_a  / (float)length); //(float)
			fsum_a2 = (float)((float)sum_a2 / (float)length); //(float)
			fsum_b  = (float)((float)sum_b  / (float)length); //(float)
			fsum_b2 = (float)((float)sum_b2 / (float)length); //(float)

			float cov  = fsum_ab - fsum_a*fsum_b;
			float vara = fsum_a2 -fsum_a*fsum_a;
			float varb = fsum_b2 -fsum_b*fsum_b;

			float val_gpu = c[test_byte*height*width + iter*width + iter2];
			float val_cpu = /*cov/sqrt(vara*varb);*/(float)cov/sqrt(vara*varb);

			//if (val_cpu - val_gpu > 0.0000001910001 || val_gpu - val_cpu > 0.0000001910001)
			{
							count++;
//							if(iter == 0 && iter2 == 0)
							printf("c_dev[%d][%d] = %f, val_cpu = %f \n", iter, iter2, val_gpu, val_cpu);

			//	if ( iter == 255 && iter2 == 190)
			//		printf("c_dev[%d][%d] = %f, val_cpu = %f \n", iter, iter2, val_gpu, val_cpu);
//				if (count < height*width)
//					printf("c_dev[%d][%d] = %f, val_cpu = %f \n", iter, iter2, val_gpu, val_cpu);
			}
				
			sum_a  = 0.0;
			sum_a2 = 0.0;
			sum_b  = 0.0;
			sum_b2 = 0.0;
			sum_ab = 0.0;
		}

		printf(" error rate == %d \n", count);
		//printf("c[0] = %f\n", c[0]);
}

int main(){

        int   *a  = new int[depth*height*length];
		int   *b  = new int[length*width];
        float *c  = new float[depth*width*height];

    int temp;
    srand(time(NULL));

    for (int it = 0 ; it < depth ; it++){
    	for (int iter = 0 ; iter < height ; iter++)
			for (int iter2 = 0 ; iter2 < length ; iter2++){
				temp = rand()%10;
				a[it*height*length + iter*length + iter2] = (int)temp;
			}		
    }
	
	for (int iter = 0 ; iter < length ; iter++)		
		for (int iter2 = 0 ; iter2 < width ; iter2++){
			temp = rand()%10;	
			b[iter*width + iter2] = (int)temp;	
		}

	kernelCall(a,b,c);
	cout<<"Checking Result"<<endl;
	checkResult(a,b,c);	

	return 0;
}
