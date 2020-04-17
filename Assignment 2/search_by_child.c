/*
 * This program is a very bad and complex and funny looking but working program.  
 * Modify the program to make it simple and elegant as well. Next, there is only 
 * one child working to find the out if the given data is present int the integer 
 * array now include one more child to do the same thing, but let the parent 
 * distribute the work-load: may be halve the array and let each child search 
 * the data in different half of the array.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFSIZE 80

struct data {
	void *search_data;
	void *array;
	int start_indx;
	int stop_indx;
};

int search(const struct data *);


int main()
{
	int search_data;
	int found_indx;
	int arr_start, arr_stop;

	pid_t pid[2];

	int iArray[] = {10, 34, 56, 1, 100, 93, 23, 46, 13, 66};
	
	int fd[2];
	char buffer[BUFSIZE];
	pipe(fd);
	
	arr_start	= 0;
	arr_stop	 	= 9;

	printf("\nPlease enter integer to be searched : ");
	scanf("%d", &search_data);

	

	pid[0] = fork();
	
	if (pid[0] == 0) // child process
	{

		close(fd[0]); /* The child will not read and
				         hence we close fd[0] */
		struct data newData;
	

		newData.search_data	= (void *) &search_data;
		newData.array			= (void *) iArray;
		newData.start_indx	= arr_start;
		newData.stop_indx		= arr_stop;

		// start searching
		found_indx = search(&newData);

		sprintf(buffer,"%d",found_indx);   /* Since write() accepts only
						               arrays of bytes, we
						               first write the integer n
						               into the char array "buffer"
                                    */

		write(fd[1], buffer, BUFSIZE);
		exit(0);
	}
	close(fd[1]); /* The parent will not write and
				     hence we close fd[1]
			        */
	read(fd[0], buffer, BUFSIZE);
	sscanf(buffer,"%d",&found_indx); /* Read the integer from the
						       line of characters read
						       from the pipe
					          */
	if (found_indx == -1)
		printf("\nThe integer data does not exist in the array\n");
	else
		printf("\nInteger data found at position : %d \n", found_indx + 1);

	printf("\n");	
	return 0;
}


int search(const struct data *newData)
{
	
	int indx;
	int *arr, *data;
	

	data	= (int *) newData->search_data;
	arr 	= (int *) newData->array;

	for (indx = newData->start_indx; 
				indx <=  newData->stop_indx; 
					indx++)
	{
		if (arr[indx] != *data) continue;
		else return indx;
	}
	return (-1);
}
	
	
