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
    int sockfd, ret;
    struct sockaddr_in server_address; // domes gia to xeirismo dieuthinsewn diadiktuou

    int new_socket;
    struct sockaddr_in new_address;

    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;

	// dhmiourgia server socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // dhmiourgia mh desmeumenis dieuthinsis
    if(sockfd < 0)
    {
        printf("Error: connection failed.\n");
        exit(1);
    }
    printf("Server socket created successfully.\n");

    memset(&server_address, '\0', sizeof(server_address)); //vazoume sto mhkos tou server_address \0 gia na ta orisoume emeis katw
    server_address.sin_family = AF_INET; // pou anoikei
    server_address.sin_port = htons(PORT); // metatropi thiras ip se seira byte host se aritmo thiras ip se seira byte network
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // metatrepei sumvoloseira sthn tipiki dekadikh shmeiwsi me teleies ipv4 se akairaia timh katallhlh gia thn xrhsh ws dieuthinsi diadiktuou

	//desmeusi sth thira
    ret = bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)); // sisxetizei ton upodoxea me me stoixeia epikoinwnias wste na mporei na entopistei
    if(ret < 0)
    {
        printf("Error: binding failed\n");
        exit(1);
    }
    printf("Bind to port %d succesful.\n", 4444);

	//anamoni sundesis
    if(listen(sockfd, 10) == 0) // prothesi apodoxis aithsewn apo sundesi
    {
        printf("Listening...\n");
    }
    else
    {
        printf("Error: binding failed\n"); 
    }

    while(1)
    {	
		// apodoxi sundesis apo client
        new_socket = accept(sockfd, (struct sockaddr*)&new_address, &addr_size); // apodoxi sundesis kai epistrofi enos neou ypodoxea kai dieuthinsis, dinei kainourio perigrafea arxiou
        if(new_socket < 0)
        {
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(new_address.sin_addr), ntohs(new_address.sin_port)); // metatrepei to in se tupiki simeiwsh me telies kai ntohs apo network se host

		// dimiourgia neas diergasias
	    childpid = fork();

        if(childpid==0)
        {
            close(sockfd);
        
            while(1)
            {
                float num1, num2, answer;
                int choice;

				// lipsi epilogis praksis
                recv(new_socket, &choice, sizeof(int),0);
                printf("Client- The choice is: %d\n", choice);

				//eksodos apo to programma
                if(choice==5)
                {	
       	            bzero(buffer,1025);
            	    recv(new_socket, buffer,1024,0);
            	    if(strcmp(buffer, "exit")==0)
            	    {
            		    printf("Disconnected from:%s:%d\n", inet_ntoa(new_address.sin_addr), ntohs(new_address.sin_port));	
            		    break;	
            	    }
                }

				// lipsi arithmwn apo ton client
                recv(new_socket, &num1, sizeof(float),0);
                printf("Client- Number 1: %f\n", num1);

                recv(new_socket, &num2, sizeof(float),0);
                printf("Client- Number 2: %f\n", num2);

				//ypologismos praksewn
                switch(choice)
                {
                    case 1: 
                        answer = num1 + num2;
                    break;

                    case 2:
                        answer = num1 - num2;
                    break;

                    case 3:
                        answer = num1*num2;
                    break;

                    case 4:
                         answer = num1/num2;
                    break;
                }
			// apostoli apotelesmatos ston client
            send(new_socket, &answer, sizeof(float),0);

            }
        }
    }
    
    close(sockfd);
    close(new_socket);
    return 0;
 }
 
 
 
