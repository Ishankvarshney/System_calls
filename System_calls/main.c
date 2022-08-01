#include <stdio.h> 
#include "files_directory_pipe.h" 

int main(int argc, char *argv[] )  
{  
  
   	printf("Hello: %s\n\n", argv[0]);  
   
   	if(argc < 3)
   	{ //./assgn type operation 
      	printf(" Number of Arguments are less than required .INVALID!!!\n");  
   	}  
   	else
   	{  
   		//FILE
		if(strcmp(argv[1], "file")==0)
		{
			if(strcmp(argv[2], "create")==0)
			{
				create_reg_File(argc,argv);
			}
			else if(strcmp(argv[2],"read")==0)
			{
				read_File(argc,argv);
			}
			else if(strcmp(argv[2],"write")==0)
			{
				write_File(argc,argv);
			}
			else if(strcmp(argv[2],"open")==0)
			{
				open_CloseFile(argc,argv);
			}
			else if(strcmp(argv[2],"info")==0)
			{
				File_info(argc,argv);
			}
			else if(strcmp(argv[2],"chmod")==0)
			{
				change_Mode(argc,argv);
			}
			else
			{
				printf("WRONG CHOICE--------files!!!\n");
			}
		}
		//DIRECTORY
		else if(strcmp(argv[1],"directory")==0)
		{ 
			if(strcmp(argv[2],"create")==0)
			{
				create_Directory(argc,argv);
			}
			else if(strcmp(argv[2],"chmod")==0)
			{
				change_Mode(argc,argv);
			}
			else if(strcmp(argv[2],"info")==0)
			{
				File_info(argc,argv);
			}
			else
			{
				printf("WRONG CHOICE---------directory!!!\n");
			}
		}
		//PIPE
		else if(strcmp(argv[1],"pipe")==0)
		{ 
			if(strcmp(argv[2],"named")==0)
			{
				create_NamedPipe(argc,argv);
			}
			else if(strcmp(argv[2],"unnamed")==0)
			{
				create_UnnamedPipe(argc,argv);
			}
			else
			{
				printf("WRONG CHOICE---------pipes!!!.\n");	
			}
		}
		else
		{
			printf("Please enter valid input....your input can be file,directory or pipes.\n");
		}
	}  
	return 1;
}  