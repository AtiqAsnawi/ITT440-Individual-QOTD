//QOTD Server code
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<time.h>
#include<pthread.h>
#include<stdbool.h>

//handle the error
#define handle_error_en(en, msg)\
        do(errno=en);perror(msg);exit (EXIT.FAILURE);) while (0)
#define handle _error(msg)\
        do(perror(msg);exit (EXIT, FAILURE);) while (0)
        int day, port;
        char *QOTD;
        const char *goToQOTD;
        pthread_mutex_t quoteLock=PTHREAD_MUTEX_INITIALIZER;
        pthread_t checkForNewDayThread,connectiontandlerThread;

//link to quotes.txt file
int line_no(const char* file)
{
        int count=0;
        int currentChar;
        FILE* fds=fopen(file,"r");
        if(fds==NULL){
                perror("ERROR opening quote file");
                exit(EXIT_FAILURE);
                }

        while(true){
                currentChar=fgetc(fds);
                switch(currentChar){
        case'\n':{
                count++;
                break;
        }

        case EOF:{
                fclose(fds);
                return count;
        }
        default:
        continue;
        }
        }
}
        //find one random quote in file and send to buffer address
        char* quote_read(const char* filepath){
                int quotes_no=line_no(filepath);
                int LineNumberOfQOTD=rand()%quotes_no;
                int lineCounter=0;
                char* lineptr=NULL;
                size_t n=0;
                FILE* fds=fopen(filepath,"r");

 if(fds==NULL){
                perror("quotes file opening ERROR");
                exit(EXIT_FAILURE);
        }

        while(lineCounter<LineNumberOfQOTD){
                if(fgetc(fds)=='\n') lineCounter++;
        }
        getline(&lineptr,&n,fds);
        fclose(fds);
        return lineptr;
        }


        //code to handle comection with client
        void * connection(void* port_ptr){
        struct sockaddr_in address;
        int server_fds,new_socket,opt=1,addrlen=sizeof(address),port=*((int*)port_ptr);
        free(port_ptr);

   //creating socket file
    if((server_fds=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                perror("creating socket is failed");
                exit(EXIT_FAILURE);
        }

      //assign ip address and port 1769
        if(setsockopt(server_fds,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt))==-1)
        {
         perror("setsockopt");
         exit(EXIT_FAILURE);
        }

        address.sin_family=AF_INET;
        address.sin_addr.s_addr=INADDR_ANY;
        address.sin_port=htons(port);

  // bind the socket to the port 1769
    if(bind(server_fds,(struct sockaddr *)&address,sizeof(address))<0)
        {
       perror("bind failed");
       exit(EXIT_FAILURE);
        }
    if (listen(server_fds,100)<0)
        {
                perror("listen");
                exit(EXIT_FAILURE);
        }
        printf("listening on port %i\n",port);

        while(1){
                if((new_socket=accept(server_fds,(struct sockaddr *) &address,(socklen_t *) &addrlen))<0)
                {
                        perror("accept");
                        exit(EXIT_FAILURE);
                }
                pthread_mutex_lock(&quoteLock);
                send(new_socket,QOTD,strlen(QOTD),0);
                pthread_mutex_unlock(&quoteLock);
                close(new_socket);
                }
        }
        int main(int argc,char const *argv[])
        {
        int thread1,thread2,join;
        int* port=valloc(sizeof(int));

        if(port==NULL){
        perror("Cannot locate memory to listen port");
        exit(EXIT_FAILURE);
        }

        time_t time1=time(NULL);
        struct tm tm = *localtime(&time1);
        day=tm.tm_mday;

        switch(argc){
        case 1:{
        *port=1769;
        goToQOTD=strdup("quotelist.txt");
        break;
        }

        case 2:{
                *port=atoi(argv[2]);
                goToQOTD=argv[1];
                break;
                }

        default:{
                fprintf(stderr,"Not Valid Arguments\n");
                fprintf(stderr,"Usage:\n &s [path_to_quotes_file] [port]\nServer will read quotes from file \"quoteslist\" and listen to port 1769 \n");
                exit(EXIT_FAILURE);
                }
        }

        printf("Username :  %s ",getlogin());
        printf("\n");
        printf("Quote file have %i number of quotes\n", line_no(goToQOTD));
        //choose random quote
        srand(time1);

        QOTD = quote_read(goToQOTD);
        connection(port);

}
