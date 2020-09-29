//This is the tables we use in this project

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<time.h>
#include<string>

using namespace std;
typedef unsigned char BYTE;


void readFile(const char* file_name,char *&bufTemp,unsigned long long buffSize);
void Build_Power_Model(int num_of_key,int num_of_pt,BYTE *power_model,BYTE *ctxt);
void Build_16Byte_Ciphertxt(BYTE *ciphertxt,int num_of_pt,char *bufTemp); 
void BUild_Traces_Matrix(int *trace_mat,int num_of_traces,int tr_length,int sp,int buffSize,char *bufTemp );
void Statistical_Analysies(BYTE *power_model,int num_of_key,int num_of_pt,int *trace_mat,int tr_length,float *R_mat);
void Extract_Key(float *R_mat,int num_of_key,int tr_length);
