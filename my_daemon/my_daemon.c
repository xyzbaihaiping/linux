
void creat_daemon()
{
	pid_t pid;
	struct sigaction sa;
	umask(0);
    
	pid = fork();
	if(pid == 0)//child
	{}
	else
	{
		exit(0);
	}
	set_sid();
	sa.sa_handler=SIG_IGN;
	sigemptyset(&sa.sa_mask); 
	sa.sa_flags = 0; 
	 
     if( sigaction(SIGCHLD, &sa, NULL ) < 0 )
	 { // 注册⼦进程退出忽略信号 
	    return; 
     }    
	 
	 chdir("/");
	 close(0);
	 close(1);
	 close(2);
}
int main()
{
	creat_daemon();
	while(1)
	{
		sleep();
	}

}
