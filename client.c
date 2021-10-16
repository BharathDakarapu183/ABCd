#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
     perror(msg);
     exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd , newsockfd , portno , n;
     struct sockaddr_in serv_addr;
     struct hostent *server;

     char buffer[256];
     if(argc <3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
      }
    portno = atoi(argv[2]);
     sockfd = socket(AF_INET , SOCK_STREAM , 0);
     if(sockfd < 0)
     {
         error("Error opening Socket.");
      }

      server = gethostbyname(argv[1]);
      if(server == NULL)
      {
       fprintf(stderr, "Error , no such host");
}
     
       bzero((char *) &serv_addr , sizeof(serv_addr));
       serv_addr.sin_family = AF_INET;
       bcopy((char *) server->h_addr , (char *) &serv_addr.sin_addr.s_addr , server->h_length);
       serv_addr.sin_port = htons(portno);
       if(connect(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr))<0)
              error("Connection Failed");

        while(1)
        {
          printf("Main-Prompt> ");
         int s;
         char str[255];
         bzero(str,255);
         fgets(str,255,stdin);
        //  printf("%s\n",str);
         if(strcmp(str,"Listusers\n") == 0)
         { 
           bzero(buffer,255);
           strcpy(buffer,"LSTU");
          s = write(sockfd , buffer , 255);
         if(s<0)
            error("Error on writing");
          bzero(buffer , 255);
         s= read(sockfd , buffer , 255);
         printf("Server:%s\n",buffer);
         }
         else if(strncmp(str,"Adduser",7) == 0)
         { 
          //  char *temp = strtok(str," ");
         // printf("IN ADDUSER\n");
          char a[255],b[255] ;
          bzero(a,255);
          bzero(b,255);
          strcpy(a,"ADDU");
          strncpy(b,str+7,strlen(str+7)-1);
          strcat(a,b);
          // printf("%s\n",str);
          bzero(buffer,255);
          strcpy(buffer,a);
           s = write(sockfd , buffer , 255);
         if(s<0)
            error("Error on writing");
          bzero(buffer , 255);
         s= read(sockfd , buffer , 255);
         if(strcmp(buffer,"0")==0)
                  { printf("Server:Userid already present\n");}
                  else{printf("Server:Registered\n");}
         }
         else if(strncmp(str,"SetUser",7)==0)
         {
        // printf("IN Setuser\n");
          char c[255],d[255] ;
          bzero(c,255);
          bzero(d,255);
          strcpy(c,"USER ");
          strncpy(d,str+7,strlen(str+7)-1);
          strcat(c,d);
         // printf("%s\n",c);
          bzero(buffer,255);
          strcpy(buffer,c);
          s = write(sockfd , buffer , 255);
          if(s<0)
            error("Error on writing");
          bzero(buffer , 255);
          s= read(sockfd , buffer , 255);
         // printf("%s\n",buffer);
          if(strcmp(buffer,"1")==0)
          {
            printf("Server:Userid is invalid\n");
            bzero(buffer , 255);
            s= read(sockfd , buffer , 255);
            continue;
          }
          else
          {
              printf("Server:Userid is valid\n");
              bzero(buffer , 255);
              s= read(sockfd , buffer , 255);
              if(s < 0)
              {
                printf("ERROR ON READING");
                exit(1);
              }
              // int val;
              // val= atoi(buffer);
              printf("Server:User has %s messages\n",buffer);
              while(1)
              {
                printf("Sub-Prompt-%s>",d);
                char str1[255];
                bzero(str1,255);
                fgets(str1,255,stdin);
                // printf("%s\n",str1);
                if(strncmp(str1,"Send",4) == 0)
                 {
                  // printf("Insend\n");
                  char touser[255];
                  char p[255];
                  bzero(p,255); 
                  bzero(touser,255);
                  strncpy(touser,str1+4,strlen(str1+4)-1);
                  strcat(p,"SEND ");
                  strcat(p,touser);
                  s = write(sockfd,p,255);
                   if(s<0)
                       error("Error on writing");
                  bzero(buffer,255);
                  read(sockfd,buffer,255);
                   if(strcmp(buffer,"1")==0)
                   {
                      printf("Server:Receiverid is invalid\n");
                   }
                   else
                   { 
                    printf("Server:Receiverid is valid\n");
                    printf("Type Message:");
                    char msg[255];
                    bzero(msg,255);
                    fgets(msg,255,stdin);
                    s = write(sockfd,msg,255);
                    if(s<0)
                      error("Error on writing");
                    while(1)
                     {
                     if(strlen(msg)<=3) 
                        {
                           bzero(msg,255);
                           fgets(msg,255,stdin);
                           s = write(sockfd,msg,255);
                         }
                        else
                        {
                        if(strcmp((msg+strlen(msg)-4),"###\n")!=0)
                           {
                            bzero(msg,255);
                           fgets(msg,255,stdin);
                           s = write(sockfd,msg,255);
                           }
                           else 
                            break;
                        }
                     }
                  }
                 }else if(strncmp(str1,"Read",4) == 0)
                           {
                            bzero(buffer,255);
                           // int leno=0;
                           // printf("inread\n");
                            strcpy(buffer,"READM");
                            s = write(sockfd , buffer , 255);
                            if(s<0)
                            error("Error on writing");
                            bzero(buffer,255);
                            read(sockfd,buffer,255);
                            int len = strlen(buffer);
                            if(strncmp("No",buffer,2)==0){printf("Server:No More Mail\n");continue;}
                                 while(1)
                                      {
                                      bzero(buffer,255);
                                      // printf("%s\n",buffer);
                                      read(sockfd,buffer,255); 
                                      // printf("starting READ\n");
                                      if(strlen(buffer)<=3) 
                                        {
                                         printf("%s",buffer);
                                        }
                                      else
                                         {
                                         if(strcmp((buffer+strlen(buffer)-4),"###\n")!=0)
                                            {
                                             printf("%s",buffer);
                                            }
                                         else
                                            { 
                                             char msgo[255];
                                             bzero(msgo,255);
                                             strncpy(msgo,buffer,strlen(buffer)-4);
                                             printf("%s",msgo);
                                             printf("###\n");
                                            //  printf("DONE READ\n");
                                             break;
                                            }
                                         }
                                      }
                                
                            
                           }

                else if(strcmp(str1,"Delete\n")==0)
                            {
                             bzero(buffer,255);
                              //printf("indelete\n");
                            strcpy(buffer,"DELM");
                            s = write(sockfd , buffer , 255);
                            if(s<0)
                            error("Error on writing");
                            bzero (buffer,255);
                            s= read(sockfd,buffer,255);
                            printf("Server:%s\n",buffer);
                            }
                else if(strcmp(str1,"Done\n")==0)
                  {
                            bzero(buffer,255);
                                // printf("indone\n");
                            strcpy(buffer,"DONEU");
                            s = write(sockfd , buffer , 255);
                            if(s<0)
                            error("Error on writing");
                            break;
                  }
             }
         
         }
        }
         // else  break;
        
       else if(strcmp(str,"Quit\n")==0)
                 {
                  bzero(buffer,255);
                  strcpy(buffer,"QUIT");
                  s = write(sockfd , buffer , 255);
                  if(s<0)
                     error("Error on writing");
                  bzero(buffer,255);
                  s=read(sockfd,buffer,255);
                  printf("Server:%s\n",buffer);
                  break;
                 }
      else
        {
        printf("Wrong Instruction\n");
        }
        }
      close(sockfd);
          return 0;

}
