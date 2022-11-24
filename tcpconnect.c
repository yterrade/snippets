int tcp_connect(char *addr,u_short port,int *ret_error)
{
   int fd;
   int error;
   socklen_t namelen;

   int ret;
   struct addrinfo *result;
   struct addrinfo hint;
   struct sockaddr dst_addr;
   int socktype = 0;
   char port_str[6] = {0};

   memset(&hint,0,sizeof(hint));
   hint.ai_family = AF_UNSPEC;
   hint.ai_socktype = SOCK_STREAM;
   hint.ai_flags = AI_NUMERICHOST;
   hint.ai_protocol = 0;


   sprintf(port_str,"%d",port);

   if(getaddrinfo(addr,port_str,&hint,&result) != 0) 
   {
      perror("TCP_assync_connect2 getaddrinfo Failure");   
      return NULL;
   }
   fd = socket (result->ai_family,SOCK_STREAM , 0);

   if (fd == -1)
   {
      *ret_error = errno;
      assert(*ret_error != 0);

      perror("TCP_assync_connect2 (socket)");

      freeaddrinfo(result);
      return NULL;
   }

   error = connect(fd,result->ai_addr,result->ai_addrlen);

   namelen = sizeof(struct sockaddr);
   getsockname(fd,(struct sockaddr *) &comm_id->comm_info.tcp.local,&namelen);

   memcpy((char *) &comm_id->comm_info.tcp.foreign,(char *) &dst_addr,sizeof(dst_addr));

   *ret_error = 0;

   return(error);
}

