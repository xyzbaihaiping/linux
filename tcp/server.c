/*************************************************************************
    > File Name: server.c
    > Author: bhp
    > Mail: bhp16333177100@sina.com 
    > Created Time: 2016年07月27日 星期三 02时11分34秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<pthread.h>

static void usage(const char *proc)
{
	printf("usage: %s [ip] [port]\n",proc);
}

void *thread_run(void *arg)
{
	printf("creat a new thread\n");
	int fd = (int)arg;
	char buf[1024];
	while(1)
	{
		memset(buf, '\0', sizeof(buf));
		ssize_t _s = read(fd, buf, sizeof(buf) - 1);
		if(_s > 0)
		{
			buf[_s] = '\0';
			printf("client# %s\n",buf);
			write(fd, buf, strlen(buf));
		}else if(_s == 0)
		{
			printf("client close...\n");
			break;
		}else
		{
			printf("read error ...\n");
			break;
		}
	}
	return (void *)0;
}


int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(0);
	}

	//1.creat sock
	int listen_sock = socket(AF_INET, SOCK_STREAM,0);
	if(listen_sock < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);

	//2.bind
	if( bind(listen_sock, (struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		return 2;
	}

	//3.listen
	listen(listen_sock, 5);

	//4.accept
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
	while(1)
	{
		int fd = accept(listen_sock, (struct sockaddr*)&peer,&len);
		if(fd < 0)
		{
			perror("accept");
			return 3;
		}
	
//pthread
	printf("get a new link, sock -> %s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
	pthread_t id;
	pthread_create(&id,NULL,thread_run,(void *)fd);

	pthread_detach(id);
	
//proc
	//pid_t id = fock();
	//if(id == 0)
	//{//child
	//char buf[1024];
	//while(1)
	//{
	//	memset(buf, '\0', sizeof(buf));
	//	ssize_t _s = read(fd, buf, sizeof(buf) - 1);
	//	if(_s > 0)
	//	{
	//		buf[_s] = '\0';
	//		printf("client# %s\n",buf);
	//		write(fd, buf, strlen(buf));
	//	}else if(_s == 0)
	//	{
	//		printf("client close...\n");
	//		break;
	//	}else
	//	{
	//		printf("read error ...\n");
	//		break;
	//	}
	//	exit(0);
	//}
	//else
	//{//father
	//	waitpid(-1,NULL,WNOHAGE);
	//}
	//
	//
	//}
	}
	return 0;
}































