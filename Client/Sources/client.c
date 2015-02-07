/* A simple client using TCP
   The server_ip, file_name and port_number are passed as an argument 
   It requests one file at a time.   
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include "../headers/key_generate.h"
#include "../headers/decryption.h"
int main(int argc, char *argv[])
{
	int sockfd, portno,n;
	long int pub_expo,pri_expo,mod;
	struct sockaddr_in serv_addr;
	char buffer[256], *servip,pub_expo_str[256]={'\0'},mod_str[256]={'\0'},filename[256]={'\0'},content[50000]={'\0'};
	if(argc<4)
	   {
		printf("Not enough parameters.");
		exit(0);
	   }
	servip=argv[1] ;   //server ip is being delievered
	portno=atoi(argv[3]); //port number is being delievered
	strcpy(filename,argv[2]);	//requested file name is being kept and stored
	
	//Key generation is being done here
	key_generate(&pri_expo,&pub_expo,&mod);
	
	//Converting long integer public key into string to append it after the filename
	sprintf(pub_expo_str,"%ld",pub_expo);   
	sprintf(mod_str,"%ld",mod);

	strcat(argv[2],"#");	strcat(argv[2],pub_expo_str);  //argv[2] = filename + pub_expo_str, now
	strcat(argv[2],"#");	strcat(argv[2],mod_str);   //argv[2] = filename + pub_expo_str + mod_str, now

	sockfd=socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0)
		perror("error opening socket");
	printf("client online\n");
	bzero((char *)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(servip);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
		perror("error connecting");

	//to request file 'filename' we must write its name in buffer, So	
	//write argv[2](filename + pub_expo_str + mod_str) in the buffer
	write(sockfd,argv[2],strlen(argv[2])+1);	
	
	//file received by this point, So we need to read data
	n=read(sockfd,content,50000);	//moves content from sockfd --> 'content[]'
	
	printf("Content Received:\n");	
	write(1,content,n);     //write content of n length from 'content[]' to the terminal
	if(n<=0)
	  { 
		perror("file not found");
	 	exit(0);
	   }

/***********************************************
Decryption function goes here   
************************************************/

decryption(pri_expo,mod,content,n,filename);

/*************************************************/	

printf("File Received.\n");		
return 0;
}
