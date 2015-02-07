/*This is RSA algorithm implementation having only 64 bit-length security.*/

#include <stdio.h>
#include "../headers/my_modular_arith.h"

void decryption(long int PRIVATE_EXPO,long int MOD,char *encrypted_str,int n,char *filename)
{
    long int encrypted_values[5000],decrypted_values[5000],i,j,value;
    long long int decrypted_value;
    char decrypted_msg[5000],value_str[20]={'\0'}, *endptr;
	FILE *fp=fopen(filename,"w+");
    //printf("\n\nEncrypted str:%s",encrypted_str);
    for(i=0,j=0;i<n;i++,j++){
	if(encrypted_str[i]!='\n'){
		value_str[j] = encrypted_str[i];
	}
	else{
		value_str[j]='\0';
		j=-1;
		value = strtol(value_str,&endptr,10);
		decrypted_value = modular_expo(value,PRIVATE_EXPO,MOD);
		fprintf(fp,"%c",(char)decrypted_value);
		}
	}
	fclose(fp);
}
