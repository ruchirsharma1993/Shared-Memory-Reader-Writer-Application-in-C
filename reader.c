#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<string.h>
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
int main()
{
	int in,i ;

	key_t key = 6000;
	//Obtaining Access to shared memory
	int shmid =  shmget(key, 27, 0666);
	if(shmid<0)
	{
		perror("Reader Error: Access Problem");
		return 0;
	}
 
	//Attaching the shared memory
	 char *shm = (shm = shmat(shmid, NULL, 0)); 
        
	if(shm=="-1")
	{
		perror("Reader Error: Problem in attaching");
	        return 0;
	}

	//Reading what writer inserted into the shared memory...!!
	printf("\nReader Read: ");	
	char *s = shm;
	char buff[100];
	int count=0;
	for (s = shm; *s!='\0'; s++)
        {	
		char c = *s;
		putchar(c);
		buff[count]=c;	
		count++;
	}    	
	putchar('\n');
	
	
	char *revs = strrev(buff);
	printf("\nReader Wrote: %s\n",buff);
	
	 s = shm;
	*s++;
	for (i=0;i<strlen(buff);i++)
	{
		char c = buff[i];		
		*s++ = c;
	
    	}
	
	*s = '\0';
	*shm ='*';
	
	return 0;
}
	
