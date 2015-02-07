#include <stdio.h>
#include <string.h>
#include "../headers/encryption.h"
char * encrypt(long int PUBLIC_EXPO,long int MOD,char *filename)
{
    long int unencrypted_msg[50000],encrypted_msg[50000],i;
    char str[50000]={'\0'},str_len=0, encrypted_file[]="encrypt.txt";

    //Reading Public Key
    FILE *fp;
    fp=fopen(filename,"r");
    printf("pub_expo:%ld\n",PUBLIC_EXPO);   //Reading Public Key.
    printf("mod:%ld\n",MOD);
    if(!fp)
        printf("Error opening file!\n");    

    //fscanf(fp,"%s",str);
    fgets(str,5000,fp);
    str_len=strlen(str);
    printf("File content:");
	
    for(i=0;i<str_len;i++)
        unencrypted_msg[i]=(long int)str[i];

    printf("\n\nEncrypted Message:\n");
    for(i=0;i<str_len;i++)
        encrypted_msg[i]=modular_expo(unencrypted_msg[i],PUBLIC_EXPO,MOD);
    fclose(fp);
    //Writing Encypted Message on screen as well as on file to be sent.
    FILE *encrypt_fp;
    encrypt_fp=fopen(encrypted_file,"w+");
    for(i=0;i<str_len;i++)
        {
            printf("%ld:",encrypted_msg[i]);
            fprintf(encrypt_fp,"%ld\n",encrypted_msg[i]);
        }
    fclose(encrypt_fp);
    filename = encrypted_file;
}

long int modular_expo(long int b,long int e,long int m)
{
    long long int r=1,base=b;
    base %= m;
    while(e)
        {
            if( e%2 ==1 )
                r = (r*base) % m;
            e = e >> 1;
            base = (base * base) % m;
        }
    return r;
}
