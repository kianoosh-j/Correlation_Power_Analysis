//this file contains the body of most of the function we use in our main code
#include"functionsbody.h"
typedef unsigned char BYTE;


//In this part we define our tables.

BYTE Shift_Byte_Pos[16] = {0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11};

BYTE HW[256] = {
0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};


BYTE Inv_SByte[256] = {
0x52,0x09,0x6A,0xD5,0x30,0x36,0xA5,0x38,0xBF,0x40,0xA3,0x9E,0x81,0xF3,0xD7,0xFB,
0x7C,0xE3,0x39,0x82,0x9B,0x2F,0xFF,0x87,0x34,0x8E,0x43,0x44,0xC4,0xDE,0xE9,0xCB,
0x54,0x7B,0x94,0x32,0xA6,0xC2,0x23,0x3D,0xEE,0x4C,0x95,0x0B,0x42,0xFA,0xC3,0x4E,
0x08,0x2E,0xA1,0x66,0x28,0xD9,0x24,0xB2,0x76,0x5B,0xA2,0x49,0x6D,0x8B,0xD1,0x25,
0x72,0xF8,0xF6,0x64,0x86,0x68,0x98,0x16,0xD4,0xA4,0x5C,0xCC,0x5D,0x65,0xB6,0x92,
0x6C,0x70,0x48,0x50,0xFD,0xED,0xB9,0xDA,0x5E,0x15,0x46,0x57,0xA7,0x8D,0x9D,0x84,
0x90,0xD8,0xAB,0x00,0x8C,0xBC,0xD3,0x0A,0xF7,0xE4,0x58,0x05,0xB8,0xB3,0x45,0x06,
0xD0,0x2C,0x1E,0x8F,0xCA,0x3F,0x0F,0x02,0xC1,0xAF,0xBD,0x03,0x01,0x13,0x8A,0x6B,
0x3A,0x91,0x11,0x41,0x4F,0x67,0xDC,0xEA,0x97,0xF2,0xCF,0xCE,0xF0,0xB4,0xE6,0x73,
0x96,0xAC,0x74,0x22,0xE7,0xAD,0x35,0x85,0xE2,0xF9,0x37,0xE8,0x1C,0x75,0xDF,0x6E,
0x47,0xF1,0x1A,0x71,0x1D,0x29,0xC5,0x89,0x6F,0xB7,0x62,0x0E,0xAA,0x18,0xBE,0x1B,
0xFC,0x56,0x3E,0x4B,0xC6,0xD2,0x79,0x20,0x9A,0xDB,0xC0,0xFE,0x78,0xCD,0x5A,0xF4,
0x1F,0xDD,0xA8,0x33,0x88,0x07,0xC7,0x31,0xB1,0x12,0x10,0x59,0x27,0x80,0xEC,0x5F,
0x60,0x51,0x7F,0xA9,0x19,0xB5,0x4A,0x0D,0x2D,0xE5,0x7A,0x9F,0x93,0xC9,0x9C,0xEF,
0xA0,0xE0,0x3B,0x4D,0xAE,0x2A,0xF5,0xB0,0xC8,0xEB,0xBB,0x3C,0x83,0x53,0x99,0x61,
0x17,0x2B,0x04,0x7E,0xBA,0x77,0xD6,0x26,0xE1,0x69,0x14,0x63,0x55,0x21,0x0C,0x7D};






//reinforcment functions including statistical functions


float corrcoef(BYTE *x,int *y,int length){
	float ex = 0,ey = 0,exy = 0,ex2 = 0,ey2 = 0;
	for(int i = 0 ; i < length ; i++){
		ex = ex + (float)x[i];
		ey = ey + (float)y[i];
		exy = exy + ((float)x[i]*(float)y[i]);
		ex2 = ex2 + ((float)x[i]*(float)x[i]);
		ey2 = ey2 + ((float)y[i]*(float)y[i]);
	}
	ex = (float)(ex/length);
	ey = (float)(ey/length);
	exy = (float)(exy/length);
	ex2 = (float)(ex2/length);
	ey2 = (float)(ey2/length);
	
	float cov = exy-(ex*ey);
	float var_x = ex2-(ex*ex);
	float var_y = ey2-(ey*ey);
	float temp_var = var_x*var_y;
	float res = cov/sqrt(temp_var);
//	cout<<"res == "<<res<<" var_x == "<<var_x<<endl; 

	if(res < 0)
		res = res*(-1);

	return res;
}	


int key_statistical_analysis(BYTE *key,int *tr_mat,int tr_width,int tr_height,float *res_mat){
	int *temp = new int[tr_height];
	for(int j = 0 ; j < tr_width;j++){
		for(int i = 0; i < tr_height ;i++)
			temp[i] = tr_mat[i*tr_width + j];
		res_mat[j] = corrcoef(key,temp,tr_height);
}
	return 0;				
	
}



int convert_to_int(char *bufTemp,int &index){
	int sign = 1,value = 0;
	
	if(bufTemp[index] =='-'){
		sign = -1;
		index++;
}
	while((unsigned char)bufTemp[index]!=10/*bufTemp[index] != 0xa*/){
		value =((unsigned char)bufTemp[index]-48) + value*10;
		index++;
		}
		
	index++;
	return value*sign;			
}


//The major functions that builds the main code


void Build_16Byte_Ciphertxt(BYTE *ciphertxt,int num_of_pt,char* bufTemp){

	BYTE temp1,temp2;
	for(int i=0;i < num_of_pt*32;i+=2){
		if(97<=(int)bufTemp[i])
			temp1 = (BYTE)((int)bufTemp[i]-87);
		else
			temp1 = (BYTE)(bufTemp[i]-'0');
		if(97<=int(bufTemp[i+1]))
			temp2 = (BYTE)((int)bufTemp[i+1]-87);
		else
			temp2 = (BYTE)(bufTemp[i+1]-'0');

		temp1 = temp1<<4;
		ciphertxt[i/2] = temp1 + temp2;
	}

}


void Build_Power_Model(int num_of_key,int num_of_pt,BYTE *power_model,BYTE *ctxt){
	int err = 0;
	BYTE temp;
	int shifted_byte;
	for(int b = 0 ; b < 16 ; b++){
		shifted_byte = Shift_Byte_Pos[b];
		for(int k = 0 ; k < num_of_key ; k++)
		       for(int n = 0 ; n < num_of_pt ; n++){
				temp = ctxt[16*n + b] ^ (BYTE)k;
			//	if(Inv_SByte[temp] == 255)
			//		err++;
				temp = Inv_SByte[temp] ^ ctxt[16*n + shifted_byte];
				power_model[b*(num_of_key*num_of_pt) + k*(num_of_pt) + n] = HW[temp];
		       }	       
	}

	cout<<"the error rate == "<<err<<endl;
	
}

void BUild_Traces_Matrix(int *trace_mat,int num_of_traces,int tr_length,int sp,int buffSize,char *bufTemp ){
	

	fstream trace_list("../files/list.txt");
	string line;
	int count = 0,index = 0,trace_index = 0,temp_traces = 0;
	const char *file_name;
	
	while(trace_index!=num_of_traces){
		index = 0;
		getline(trace_list,line);
		line = "tracesfiles/" + line;
		file_name = line.c_str();
		
		readFile(file_name,bufTemp,buffSize);
		for(;count!=24+sp;index++)
			if((unsigned char)bufTemp[index] == 10)
				count++;
		count = 0;
		for(int i = 0 ; i < tr_length; i++){
			//if(trace_index == 0)
			//	cout<<" "<<convert_to_int(bufTemp,index)<<endl;
			trace_mat[trace_index*tr_length + i] = convert_to_int(bufTemp,index); 
		}

	trace_index++;	
	}

	trace_list.close();
}

void Statistical_Analysies(BYTE *power_model,int num_of_key,int num_of_pt,int *trace_mat,int tr_length,float *R_mat){

	int num_of_traces = num_of_pt;
	#pragma omp parallel for
	for(int b = 0 ; b < 16 ; b++){
			for(int k = 0 ; k < num_of_key ; k++){
				BYTE *M = power_model + (b*num_of_key*num_of_pt) + (k*num_of_pt);
				float *R = R_mat + (b*num_of_key*tr_length )+(k*tr_length);
				if(key_statistical_analysis(M,trace_mat,tr_length,num_of_traces,R)!=0){
					cerr<<"An error has occured in key_statistical_analysis function "<<endl;
				}
			}
		
		}
		cout<<"the corrcoef part is over"<<endl;

}


void Extract_Key(float *R_mat,int num_of_key,int tr_length){

	BYTE Keys [16]={0};
	float *max_result = new float[16];
	float maximum = 0,tmp;

	for(int b = 0; b < 16 ; b++){
		float maximum = 0;
		for(int k = 0 ; k < num_of_key;k++){
			//add by armin
			for(int t = 1; t < tr_length ; t++){//remove incr +=2 by armin
				tmp =  R_mat[(b*num_of_key*tr_length) + (k*tr_length)+t];
				if (tmp > maximum){
					maximum = tmp;
					Keys[b] = k;
				//	cout <<"B = "<<b<<" , k = "<<k<<"tmp = "<< tmp <<endl;
				}
			}
		}
		max_result[b] = maximum;
	}

	cout<<"the max result is here "<<endl;
	for(int i = 0 ; i < 16 ; i++)
			cout<<dec<<"Key ["<<i<< "]= "<<hex<<(int)Keys[i]<<" by "<<dec<<max_result[i]<<"%"<<endl;
		
}

			//	if( max(R_mat[(b*num_of_key*tr_length) + (k*tr_length)+t],R_mat[(b*num_of_key*tr_length)+ (k*tr_length) + t-1]) > maximum){
