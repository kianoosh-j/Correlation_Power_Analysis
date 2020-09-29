#include"functionsbody.h"

typedef unsigned char BYTE;
typedef unsigned long long uint64;


int main(int argc,char *argv[]){

	int num_of_pt = 20000,num_of_key = 256,num_of_traces = 20000;
	int tr_length = 200,sp = 2299;
	const char* file_name = argv[1];
	uint64 buffSize = (1 << 29);
	char *bufTemp = (char*)malloc(sizeof(char)*buffSize);


	//we use fastread file function to read the cipher file
	readFile(file_name,bufTemp,buffSize);
	cout<<"ciphertxt file has been successfuly red"<<endl;

	//We Build The 16 Byte Ciphertxt Matrix
	BYTE *ciphertxt = new BYTE[num_of_pt*16];
	Build_16Byte_Ciphertxt(ciphertxt,num_of_pt,bufTemp);
	cout<<"ciphertxt matrix has been successfuly built"<<endl;
	
	//we build power model by using haming weight power_model[b*k*n];
	BYTE *power_model = new BYTE[16*num_of_pt*num_of_key];
	Build_Power_Model(num_of_key,num_of_pt,power_model,ciphertxt);
	delete ciphertxt;
	cout<<"THe power model has been successfuly built"<<endl;

	//In this part we build the matrix of measured traces
	int *trace_mat= new int[num_of_traces*tr_length];
	BUild_Traces_Matrix(trace_mat,num_of_traces,tr_length,sp,buffSize,bufTemp);
	//free(bufTemp);
	cout<<"The matrix of traces has been successfuly built"<<endl;

	//In this part we compute the correlation coefficent between traces and power model
	float *R_mat = new float[16*num_of_key*tr_length];
	Statistical_Analysies(power_model,num_of_key,num_of_pt,trace_mat,tr_length,R_mat);

	//edited by armin: In this part we obtain the key.	
	Extract_Key(R_mat,num_of_key,tr_length);
	
	return 0;
}

