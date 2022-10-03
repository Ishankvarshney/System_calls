# System_calls
Unix System File Calls(Command Line based user Interface program)
One header file:- files_directory_pipe
and One main file to execute the whole program.

File Operation:-

                 Open/close : Open or Close Files.
                 Write : write data to a file.
                 Read: Read data from File.
                 Chmod: Chnange permissions of file.
                 Info : Print Information relate to file.
                 
Pipe Operation :- 
                 Creating a Unnamed/named file

Directory :-

             create : Create New Directory
             chmod  : Change Directory Permissions
             Info   : Print Information Related to directory
             
 System calls : 
 
                Files -> creat,open,close,read,write,chmod,stat,lseek           
                pipes -> pipe,mknod
                Directory -> mkdir,chmod,stat
                Advanced system calls -> dup,dup2,pipe,unlink
