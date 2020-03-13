#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>  
#include <string.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <wait.h>

int findStat(const char *path)
{
  struct stat pathDir; 
  stat(path, &pathDir);
  return S_ISDIR(pathDir.st_mode); //Melakukan cek apakah directory?
}

int main()
{
	pid_t child1 = fork();
	pid_t child2 = fork();
	pid_t child  = fork(); 	
	int status; //status akhir 
	if (child1 > 0 && child2 > 0)
		{ 
			while ((wait(&status)) > 0);
			DIR *directory; 
			struct dirent *folder;
			chdir("/home/donny/modul2/jpg/"); 
			directory = opendir(".");
			if (directory)
			{
	      	while ((folder = readdir(directory)) != NULL)
			{
			  	if(strcmp(folder->d_name,"..")==0 || strcmp(folder->d_name,".")==0)
					continue;
			  	if(findStat(folder->d_name))
				{
			  		if(fork() == 0)
					{
			        	char folder_pindah[1000];
			        	sprintf(folder_pindah,"/home/donny/modul2/jpg/%s",folder->d_name);
			        	char* argv[] = {"mv", folder_pindah,"/home/donny/modul2/indomie/", NULL};
			        	execv("/bin/mv", argv);
		      		}
		      		else
					{
		        		while ((wait(&status)) > 0);
		          		if(fork() == 0)
						{
		          			if(fork() == 0)
							{
				  	    		char coba1[1000];
				  	    		FILE *file;
				    	    	sprintf(coba1,"/home/donny/modul2/indomie/%s/coba1.txt",folder->d_name);
				    	    	file = fopen(coba1, "w");
				    	    	fclose(file);
		      	  			}
		            		else
							{
				        		while ((wait(&status)) > 0);
				        		sleep(3);
				        		char coba2[1000];
				        		FILE *file;
				        		sprintf(coba2,"/home/donny/modul2/indomie/%s/coba2.txt",folder->d_name);
				        		file = fopen(coba2, "w");
				        		fclose(file);
				        		exit(0);
				      		}
		        		}
		        		else
						{
				      		while ((wait(&status)) > 0);
			    			exit(0);
					    }
					}
		    	}
		      	else
				{
		      		while ((wait(&status)) > 0);
		      		if(fork() == 0)
					{
			      		while ((wait(&status)) > 0);
			      		char file_pindah[1000];
				      	sprintf(file_pindah,"/home/donny/modul2/jpg/%s",folder->d_name);
				      	char* argv[] = {"mv", file_pindah,"/home/donny/modul2/sedaap/", NULL};
				      	execv("/bin/mv", argv);
					}
			  	}        
			}
		}
	}	 
	else if (child1== 0 && child2 > 0)
	{ 
	    while ((wait(&status)) > 0);
	    if (child == 0)
		{
			char *argv[] = {"mkdir", "-p","/home/donny/modul2/indomie", NULL};
		    execv("/bin/mkdir", argv);
    	}
    	else
		{
			while ((wait(&status)) > 0);
      		sleep(5);
      		char *argv[] = {"mkdir", "-p","/home/donny/modul2/sedaap", NULL};
      		execv("/bin/mkdir", argv);
    	}	
  	} 
	else if (child1 > 0 && child2 == 0)
	{ 
	    char* argv[] = {"unzip", "-q","/home/donny/modul2/jpg.zip", NULL};
	    execv("/usr/bin/unzip", argv);
	}
	return 0; 
} 

