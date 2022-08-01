#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void read_File(int argc, char *argv[])
{//assign file read file.txt start bytes
	if(argc!=6)
	{
		// when argument are not enough or more than required
		printf("Number of Arguments are less than required .INVALID!!! \n");
	}
	else
	{
		//read only mode .....file open
		int fd=open(argv[3],O_RDONLY);
		if(fd==-1)
		{// if fd i.e. file discriptor is neg then errror
			printf("Opening the file----------ERROR. \n");
		}
		else
		{
			//Convert string to integer for start,bytes
			int start=atoi(argv[4]);
			int nbytes=atoi(argv[5]);
			//Move pointer for random read
			if(start!=0)
			{
				lseek(fd,start,SEEK_SET);
			}
			int n,bytes_read=0;
			char buff[1]; 
			printf("\nThe bytes read are: ");
			//Keep reading till end of file or max bytes to be read is reached 
			while(((n=read(fd,buff,1))>0) && (bytes_read<nbytes))
		    {
		        printf("%s", buff); 
		        bytes_read+=n;
		    }
		    		    //print total bytes  that is read by process
		    printf("\n\nTotal bytes read: %d \n",bytes_read);
			if((close(fd))<0)
			{
				//if fd close return neg than error
				printf(" Closing file----------ERROR. \n");
			}
		}
	}
}


void File_info(int argc, char *argv[])
{
	if(argc!=4)
	{
		// when argument are not enough or more than required
		printf("Number of Arguments are less than required .INVALID!!!");
	}
	else
	{
		struct stat sfile;
	
		if(stat(argv[3],&sfile)==-1)
		{// error during execution of info of file
			printf("Error Occurred in FIle info\n");
		}
		//else Accessing data members of stat struct and printing them all
		printf("\nInformation for file: %s \n",argv[3]);
		printf("\nUser ID of owner: %d",sfile.st_uid);
		printf("\nBlocksize for system I/O: %ld",sfile.st_blksize);
		printf("\nGroup ID of owner: %d",sfile.st_gid);
		printf("\nNumber of blocks allocated: %ld",sfile.st_blocks);
		printf("\nTotal size, in bytes: %ld",sfile.st_size);
		printf("\nNumber of hard links: %u",(unsigned int)sfile.st_nlink);
		printf("\nTime of last access: %s", ctime(&sfile.st_atim.tv_sec));
		printf("\nTime of last modification: %s", ctime(&sfile.st_mtim.tv_sec));
		printf("\nTime of last status change: %s", ctime(&sfile.st_ctim.tv_sec));
		printf("\nFile Permissions for User: ");
		printf((sfile.st_mode & S_IRUSR)? "r":"-");// file permission for user,group,other
		printf((sfile.st_mode & S_IWUSR)? "w":"-");
		printf((sfile.st_mode & S_IXUSR)? "x":"-");
		printf("\nFile Permissions for Group: ");
		printf((sfile.st_mode & S_IRGRP)? "r":"-");
		printf((sfile.st_mode & S_IWGRP)? "w":"-");
		printf((sfile.st_mode & S_IXGRP)? "x":"-");
		printf("\nFile Permissions for Other: ");
		printf((sfile.st_mode & S_IROTH)? "r":"-");
		printf((sfile.st_mode & S_IWOTH)? "w":"-");
		printf((sfile.st_mode & S_IXOTH)? "x":"-");
		printf("\n");	
	}	
}


mode_t toMode(char *perm)
{
	//Converts string type to mode_t type
	mode_t mode = 0;
	if (perm[0] == 'r')
	    mode |= 0400;
	if (perm[1] == 'w')
	    mode |= 0200;
	if (perm[2] == 'x')
	    mode |= 0100;
	if (perm[3] == 'r')
	    mode |= 0040;
	if (perm[4] == 'w')
	    mode |= 0020;
	if (perm[5] == 'x')
	    mode |= 0010;
	if (perm[6] == 'r')
	    mode |= 0004;
	if (perm[7] == 'w')
	    mode |= 0002;
	if (perm[8] == 'x')
		mode |= 0001;
	return mode;
}

void create_reg_File(int argc, char *argv[])
{
	//assign file create file.txt permission rwxrwxrwx
	mode_t prev_mask = umask(0); // //providing write permission to others and putting in old_mask
	if(argc!=5)
	{
		printf("Number of Arguments are less than required .INVALID!!!");
	}
	else
	{
		//trying to open it first ...if it do then ok otherwise truncate
		int op=open(argv[3],O_RDONLY);
		if(op!=-1)
		{
			close(op);
			printf("File is already in directory .Should I truncate it");
			printf("press Y for Yes");
			printf("press N for NO");
			char ch;
			scanf("%c", &ch);
			if(ch=='n')
			{
				return;
			}
		}
		mode_t mode=toMode(argv[4]);
		//Create file or truncate it
		int fd=creat(argv[3],mode);
		if(fd==-1)
		{
			printf("Error in creating a file. \n");
		}
		else
		{
			if(op!=-1)
			{
				printf("truncation done. \n");
			}
			else
			{
				printf("File created . \n");	
			}
		}
	}
	umask(prev_mask);
}

int findOpenMode(char *m)
{
	int x;
	if(strcmp(m, "read")==0)
	{
		x=O_RDONLY;
	}
	else if(strcmp(m, "write")==0)
	{
		x=O_WRONLY;
	}
	else if(strcmp(m, "readwrite")==0)
	{
		x=O_RDWR;
	}
	else
	{
		x=-1;
	}
	return x;
}


void open_CloseFile(int argc, char *argv[])
{
	if(argc!=5)
	{
		printf(" Number of Arguments are less than required .INVALID!!!\n");
	}
	else
	{
		int mode=findOpenMode(argv[4]);
		if(mode==-1)
		{
			printf("/nopening mode can't be done");
			return;
		}
		int fd=open(argv[3],mode);
		if(fd==-1)
		{
			printf("Error in opening file. \n");
		}
		else
		{
			printf("File opened successfully in %s mode. \n",argv[4]);
			//Close a file
			if((close(fd))<0)
			{
				printf("closing file.-------ERROR \n");
			}
			else
			{
				printf("File closed \n");
			}
		}
	}
}

void write_File(int argc, char *argv[])
{
	if(argc!=7 && argc!=6)
	{
		printf("Number of Arguments are less than required .INVALID!!!\n");
	}
	else
	{//Open a file in write mode if not present than Create it 
		int fd=open(argv[3],O_WRONLY|O_CREAT);
		if(fd==-1)
		{
			printf("opening file.---------ERROR \n");
		}
		else
		{
			char data[512];
			if(argc==6)
			{
				printf("Enter the data to be written(press ';' to end input)\n");
   				scanf("%[^;]s", data);//Multi-line input allowed
			}
			else
			{
				strncpy(data, argv[6], sizeof(argv[6]));
			}
			int size=0;
			while(data[size]!='\0')
			{
				size++;
			}
			printf(" totsl size is%d\n",size);
			int start=atoi(argv[4]);
			int bytes=atoi(argv[5]);
			if(bytes>size)
			{
				bytes=size;
			}
			//For random access 
			lseek(fd,start,SEEK_SET);
			int bytes_written=write(fd,data,bytes);
			printf("\n\nTotal bytes written: %d \n",bytes_written);
			if((close(fd))<0)
			{
				printf("Error in closing file. \n");
			}
		}
	}
}


void change_Mode(int argc, char *argv[])
{
	if(argc!=5)
	{
		printf("Number of Arguments are not equal to 5 .INVALID!!!");
	}
	else
	{
		struct stat sfile;
		if(stat(argv[3],&sfile)==-1)
		{
			printf("Error Occurred\n");
		}
		else
		{			
			printf("\n Old Permissions  ");
				
//Print string permission from integer mode
			printf((sfile.st_mode & S_IRUSR)? "r":"-");
			printf((sfile.st_mode & S_IWUSR)? "w":"-");
			printf((sfile.st_mode & S_IXUSR)? "x":"-");
			printf((sfile.st_mode & S_IRGRP)? "r":"-");
			printf((sfile.st_mode & S_IWGRP)? "w":"-");
			printf((sfile.st_mode & S_IXGRP)? "x":"-");
			printf((sfile.st_mode & S_IROTH)? "r":"-");
			printf((sfile.st_mode & S_IWOTH)? "w":"-");
			printf((sfile.st_mode & S_IXOTH)? "x":"-");
					
			mode_t mode=toMode(argv[4]);
			chmod(argv[3],mode);

			printf("\n\n New Permissions ");
//Print string permission from integer mode
			stat(argv[3],&sfile);
			printf((sfile.st_mode & S_IRUSR)? "r":"-");
			printf((sfile.st_mode & S_IWUSR)? "w":"-");
			printf((sfile.st_mode & S_IXUSR)? "x":"-");
			printf((sfile.st_mode & S_IRGRP)? "r":"-");
			printf((sfile.st_mode & S_IWGRP)? "w":"-");
			printf((sfile.st_mode & S_IXGRP)? "x":"-");
			printf((sfile.st_mode & S_IROTH)? "r":"-");
			printf((sfile.st_mode & S_IWOTH)? "w":"-");
			printf((sfile.st_mode & S_IXOTH)? "x":"-");
			printf("\n");		
		}
	}
}


mode_t to_Mode(char *perm)
{
	mode_t mode = 0;
	if (perm[0] == 'r')
	    mode |= 0400;
	if (perm[1] == 'w')
	    mode |= 0200;
	if (perm[2] == 'x')
	    mode |= 0100;
	if (perm[3] == 'r')
	    mode |= 0040;
	if (perm[4] == 'w')
	    mode |= 0020;
	if (perm[5] == 'x')
	    mode |= 0010;
	if (perm[6] == 'r')
	    mode |= 0004;
	if (perm[7] == 'w')
	    mode |= 0002;
	if (perm[8] == 'x')
		mode |= 0001;
	return mode;
}


void create_Directory(int argc, char *argv[])
{
	//creating new directory
	mode_t old_mask = umask(0);
	if(argc!=5)
	{
		printf("Number of Arguments are not equal to 5 .INVALID!!!");
	}
	else
	{
		struct stat st;
		if (stat(argv[3], &st)!=-1)
		{
		    printf("Directory already exists");
		    return;
		}
		mode_t mode=to_Mode(argv[4]);
		int dir=mkdir(argv[3],mode);
		if(dir==-1)
		{
			printf("Creating directory---------error. \n");
		}
		else
		{
			printf("Directory created. \n");	
		}
	}
	umask(old_mask);
}

void create_UnnamedPipe(int argc, char *argv[])
{
	//creating unnamed pipe
	if(argc!=4)
	{
		// when argument are not enough or more than required
		printf("\nNot enough arguments.");
		return;
	}
	int fd[2], nbytes;
	pid_t childpid;
	char buffer[128];
	int p=pipe(fd);// creating unnamed pipe
	if(p<0)
	{
		printf("\nCreating named pipe--------- ERROR.");
		return;
	}
	if((childpid = fork()) == -1) 
	{
		perror("fork");
		exit(1);
	} 
	if(childpid == 0) 
	{
		
		close(fd[0]);
		nbytes = write(fd[1], argv[3], (strlen(argv[3]) + 1));
		printf("\nNUMBER of Bytes written by child process into pipe is: %d \n",nbytes);
		exit(0);
	}
	else 
	{
		
		close(fd[1]);
		nbytes = read(fd[0], buffer, sizeof(buffer));
		printf("\nBytes read by parent process from pipe: %d \n",nbytes);
		printf("\n\nData read by parent process: %s",buffer);
	}
}

void create_NamedPipe(int argc, char *argv[])
{
	//creating named pipe
	if(argc!=4)
	{// when argument are not enough or more than required
		printf("\nInvalid number of arguments.");
		return;
	}
	//creating pipe/fifo
    int result = mknod (argv[3], S_IRUSR| S_IWUSR|S_IFIFO, 0);
	if (result < 0) 
	{
		//if result is in negative than error
	    printf("\nError in creating named pipe.");
	    exit(2);
	}
	else
	{
		//else result is positive than success
		printf("\n Created Named pipe.");
	}
}