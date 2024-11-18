#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444 // thira

int main(int argc, char *argv[])
{
    int clientSocket, ret, sockfd;
    struct sockaddr_in server_address;
    char buffer[1024];

	// dhmiourgia client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0)
    {
        printf("Error: connection failed.\n");
        exit(1);
    }
    printf("Client socket created successfully.\n");

    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	// sundesi ston server
    ret = connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address)); 
	// kathorizei ton perigrafea arxeiou ths upodoxis pou thelei na sundethei, deixnei se mia domh sockaddr pou periexei thn dieythnisi pou tha sundethei sthn upodoxi kai telos kathorizei to mikos ths domhd sockaddr pou deixnei to orisma dieuthinsis
    if(ret < 0)
    {
        printf("Error: connection failed.\n");
        exit(1);
    }
    printf("Connected to server.\n");

     
	 float num1, num2, answer;
     int choice;

   	 while(1)
    {	// epilogi praksis kai apostoli ston server
    	printf("Enter your choice: \n1.Addition \n2.Subtraction \n3.Multiplication \n4.Division\n5.Exit\n");
    	scanf("%d", &choice);
    	send(clientSocket, &choice, sizeof(int),0);
    	
		// eksodos apo to programma
   		 if(choice==5)
		{	
			printf("Type exit if you want to leave the program:\n");
		
			bzero(buffer, 1025);
			scanf("%s", &buffer[0]);
			send(clientSocket,buffer,strlen(buffer),0); 
		
			if(strcmp(buffer,"exit")==0)
			{
				close(clientSocket);
				printf("Disconnected from server.\n");
				exit(1);
			}
		}
		// eisagwgh arithmwn kai apostoli ston server
    	printf("Enter number 1:\n");
    	scanf("%f", &num1);
    	send(clientSocket, &num1, sizeof(float),0);
    	
    	printf("Enter number 2:\n");
    	scanf("%f", &num2);
    	send(clientSocket, &num2, sizeof(float),0);
   
		// lipsi apotelesmatos apo ton server
    	recv(clientSocket, &answer, sizeof(float),0);
    	printf("Server- The answer is: %.2f\n", answer);

    }
	close(sockfd);
	return 0;
}
  
   
