#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char user[10000][1000],str[10000];
int arr[10000] = {};
void error(const char *msg)
{
     perror(msg);
     exit(1);
}
int nouser =0;
int main(int argc, char *argv[])
{
    if(argc<2)
    {
         fprintf(stderr , "Port No not provided. Program terminated\n");
         exit(1);
     }
     int sockfd , newsockfd , portno , n;
     char buffer[255];

     struct sockaddr_in serv_addr , cli_addr;
     socklen_t clilen;

     sockfd = socket(AF_INET , SOCK_STREAM , 0);
     if(sockfd < 0)
     {
         error("Error opening Socket.");
     }
  
     bzero((char *) &serv_addr , sizeof(serv_addr));
     portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port =htons(portno);

     if(bind(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0)
             error("Binding Failed.");
 
     listen(sockfd , 5);
     clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd , (struct sockaddr *) &cli_addr , &clilen);
   
    if(newsockfd < 0)
     error("Error on Accept");
    // for(int i=0;i<10000;i++){arr[i]=0;}
    while(1)
    { 
      int s;
       bzero(buffer , 255);
      s = read(newsockfd ,buffer,255);

      // printf("Server:\n");
      
       if(strcmp(buffer,"LSTU") == 0)
        {
         // printf("present in lstu\n"); 
          char temp[256000];
          bzero(temp,256000);
          if(nouser == 0)
          {
            write(newsockfd,"NO USERS",255);
            continue ;
          }
            strcpy(temp,user[0]);
            for(int i=1;i<nouser;i++)
            {
              strcat(temp," ");
              strcat(temp,user[i]);
              // printf("%s\n",temp);     
            }

         s = write(newsockfd,temp,255);
      }
      else if(strncmp(buffer,"ADDU",4) == 0)
         { 
          //  char *temp;
           //bzero(buffer , 255);
          //s = read(newsockfd,buffer,strlen(buffer));
          char temp1[255];
          bzero(temp1,255);
          strcpy(temp1,buffer+4);
          // printf
          // printf("present in addu \n");
           int flag =0;
          for(int i=0;i<nouser;i++){
                if(strcmp(user[i],temp1)==0)
                 {
                   bzero(buffer,255);
                  strcpy(buffer,"0");
                   s = write(newsockfd,buffer,255);
                  flag =1;
                  break;
                 }
               }
           if(flag ==0){
               FILE *fp;
              strcpy(user[nouser],temp1);
               strcat(temp1,".txt");
               fp = fopen(temp1,"w");
               fclose(fp);
               nouser++;
               write(newsockfd,"1",255);
            }
         }
         else if(strncmp(buffer,"USER",4)==0)
            {
            int pos[1000];
            int ps;
            for(int i=0;i<1000;i++)
            {
              pos[i]=1;
            }
           // printf("present in user\n");
            char temp1[255];
            bzero(temp1,255);
            char userid[255];
            bzero(userid,255);
            strcpy(temp1,buffer+5);
            strcpy(userid,temp1);
            bzero(buffer , 255);
int flag =0;
int temp8;
//printf("%s\n",temp1);
             for(int i=0;i<nouser;i++){
                              if(strcmp(user[i],temp1)==0)
                              { 
                                bzero(buffer,255);
                                strcpy(buffer,"0");
                                //s = write(newsockfd,buffer,strlen(buffer));
                                flag =1;
                                 temp8=arr[i];
                                break;
                              }
                        }
            if(flag==0){
                       write(newsockfd,"1",255);
                       write(newsockfd,"0",255);
                       continue;
             }
            else{
                     write(newsockfd,"0",255);
                     char temp9[255];
                     bzero(temp9,255);
                     sprintf(temp9,"%d",temp8);
                    // printf("%s \n",temp9);
                     write(newsockfd,temp9,255);
                   // printf("%s\n",temp9);
            while(1){
            bzero(buffer,255);
            s = read(newsockfd ,buffer,255);
            if(strncmp(buffer,"SEND",4)==0)
            {
             // printf("present in SEND\n");
                          char temp2[255];
                          bzero(temp2,255);
                    int flag = 0;
                   // printf("present in SNED\n");
                      char touser[255];
                      bzero(touser,255);
                      strcpy(touser,buffer+5);
                     // printf("%s\n",touser);
                      for(int i=0;i<nouser;i++){
                              if(strcmp(user[i],touser)==0)
                              { 
                                bzero(buffer,255);
                                strcpy(buffer,"0");
                                //s = write(newsockfd,buffer,strlen(buffer));
                                flag =1;
                                ps=i;
                                break;
                              }
                        }
                 if(flag==0){
                       write(newsockfd,"1",255);
                       continue;
                 }
                 else{
                     write(newsockfd,"0",255);
                      }
                      int i = 0;
                      for(i=0;i<nouser;i++){
                         if(strcmp(user[i],touser)==0) break;
                        }
                        arr[i]++;
                      char msg[255];
                      bzero(msg,255);
                      bzero(buffer, 255);
                      strcpy(temp2,touser);
                      strcat(touser,".txt");
                      // s = read(newsockfd ,buffer,255);
                      // strcpy(msg,buffer);
                      FILE *fp;
                      fp = fopen(touser,"a");
                      fprintf(fp,"From:%s \nTo:%s \n",temp1,temp2);
                      while(1)
                     {
                        bzero(buffer,255);
                          s = read(newsockfd ,buffer,255);
                     if(strlen(buffer)<=3) 
                        {
                           fprintf(fp,"%s",buffer);
                         }
                        else
                        {
                        if(strcmp((buffer+strlen(buffer)-4),"###\n")!=0)
                           {
                             fprintf(fp,"%s",buffer);
                           }
                           else {
                            bzero(msg,255);
                            strncpy(msg,buffer,strlen(buffer)-4);
                            // printf("%s %s\n",buffer,msg);
                            fprintf(fp,"%s\n",msg);
                            fprintf(fp,"###\n");
                           break;
                               }
                        }
                     }
                      fclose(fp);
                 
            }else if(strncmp(buffer,"READM",5)==0)
                     {
                     //  printf("present in readm\n");
                      int k,p;
                      char fna[255];
                      for(k=0;k<nouser;k++)
                        {
                         if(strcmp(user[k],temp1)==0) break;
                        }
                        bzero(fna,255);
                        strcpy(fna,temp1);
                        strcat(fna,".txt");
                        p=1;
                        //r= arr[k];
                       // printf("%d %d %d\n",k,pos[k],arr[k]);
                        //printf("%s\n",fna);
                          if(arr[k] != 0)
                          {
                            if(pos[k] >= arr[k] + 1)
                                  pos[k] = 1;
                            bzero(buffer,255);
                            strcpy(buffer,"Mails present");
                            s = write(newsockfd,buffer,255);
                            char c[255];
                            FILE *fp;
                            fp = fopen(fna,"r");
                               while(pos[k]>p)
                              {
                                bzero(c,255);
                                fgets(c,255,fp);
                                // printf("%s",c);
                                if(strlen(c)<=3) 
                                  {
                                    
                                  }
                                else
                                  {
                                if(strcmp((c+strlen(c)-4),"###\n")!=0)
                                      {
                                      
                                      }
                                else {
                                      p++;
                                      }
                                  }
                                   
                              }
                              // printf("starting READ\n");
                              while(1)
                              {
                                bzero(c,255);
                               fgets(c,255,fp);
                               // printf("%s",c);
                                if(strlen(c)<=3)
                                {
                                  s = write(newsockfd,c,255);
                                }
                                else
                                {
                                    if(strcmp((c+strlen(c)-4),"###\n")!=0)
                                    {
                                      s = write(newsockfd,c,255);
                                    }
                                    else
                                    {
                                        s = write(newsockfd,c,255);
                                        pos[k]++;
                                        // printf("DONE READ\n");
                                        fclose(fp);
                                        break;
                                    }
                                }
                              }

                                }
                              else
                                 {
                                   bzero(buffer,255);
                                  strcpy(buffer,"No More Mail");
                                   s = write(newsockfd,buffer,255);
                                  }
                     }
             else if(strncmp(buffer,"DELM",4)==0)
                    {
                     //printf("present in delete\n");
                     if(arr[ps]==0)
                       { bzero(buffer,255);
                        strcpy(buffer,"No More Mail");
                        write(newsockfd,buffer,255);
                       }
                      else 
                       {
                       int p=1;
                       if(pos[ps] >= arr[ps] + 1)
                                  pos[ps] = 1;
                       char newf[255];
                       char fna[255];
                       bzero(newf,255);
                       strcat(newf,"temp.txt");
                       char c[255];
                       FILE *fp;
                       FILE *newfp;
                       bzero(fna,255);
                       strcpy(fna,userid);
                       strcat(fna,".txt");
                       fp = fopen(fna,"r");
                       newfp = fopen(newf,"a");
                       //printf("%d %d %d",ps,arr[ps],pos[ps]);
                      //  int n =10;
                       while(p<arr[ps]+1)
                         {  
                          bzero(c,255);
                          fgets(c,255,fp);
                          // printf("%d %s",p,c);
                          //  printf("YESS\n");
                           if(strlen(c)<=3) 
                              { 
                                if(pos[ps]!=p)
                                  fprintf(newfp,"%s",c);                             
                              }
                           else
                              {
                               if(strcmp((c+strlen(c)-4),"###\n")!=0)
                                  {
                                    if(pos[ps]!=p)
                                      fprintf(newfp,"%s",c);  
                                  }
                                else 
                                  {
                                   char msg[255];
                                   bzero(msg,255);
                                   strncpy(msg,c,strlen(c)-4);
                                   // printf("%s %s\n",buffer,msg);
                                   if(pos[ps]!=p)
                                   {fprintf(newfp,"%s\n",msg);
                                   fprintf(newfp,"###\n");}
                                   p++;
                                   //printf("YESS %d\n",p);
                                  }
                               }     
                          }
                         fclose(fp);
                         fclose(newfp);
                         arr[ps]--;
                         remove(fna);
                         rename(newf,fna);
                         bzero(buffer,255);
                         strcpy(buffer,"Message Deleted");

                         write(newsockfd,buffer,255);
                       
                       }
                    }
             else if(strncmp(buffer,"DONEU",5)==0){break;}
           }
             }
     }
     //else break;
        else if(strcmp(buffer,"QUIT")==0)
        {
        for(int i=0;i<nouser;i++)
            {
            char temp5[255];
            bzero(temp5,255);
            strcat(temp5,user[i]);
            strcat(temp5,".txt");
            remove(temp5);
            
            }
          bzero(buffer,255);
        strcpy(buffer,"TCP session closed");
            s = write(newsockfd,buffer,255);
            if(s<0)
                error("Error on writing");
            break;
        }
          
      }
      close(newsockfd);
      close(sockfd);

      return 0;
}
