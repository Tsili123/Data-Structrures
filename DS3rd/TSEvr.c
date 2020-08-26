#include "TSEvr.h"
//globals
int counter=0,counter2=0;
//counter is for airports


//NOT USED
int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source)
{
	*target = source; /* basic type assignment */
}
//NOT USED EVEN THOUGH IT WAS GIVEN
/*
int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem)
{
 	int scanresult;
   	scanresult = fscanf( from, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];\n", &Elem->airport_id, Elem->name , Elem->city, Elem->country , Elem->iata , Elem->icao );
    if ( scanresult == 6 ) 
	{
        printf( " ok format ");
        return 1;
    } 
	else 
	{
        printf( "Bad format\n" );
        return 0;
    }
    
}
*/

//NOT USED
int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem)
{
	fprintf(to,"key : %d \n",Elem.airport_id);
}
//fuction that count lines of file
//this is to determine the number of values
int countlines(FILE * fp)
{
	char c;
	int count=0;
	
	 // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
	
	printf("%d\n",count);
	return count;
}
//read file line by line 
void lineByline(FILE * file,TStoixeiouEvr *Elem)
{
	char *s;
	//get one line
	while ((s = readline(file)) != NULL)
	{
		//parse it and get the values
	    parse_line(Elem,s);
	   	counter++;
	   	//then free it so as not to accumulate space
	    free(s);
	}
	//ERROR CHECK
		/*
	s = readline(file);
	parse_line(Elem,s);
	   	counter++;
	    free(s);
	*/
	//error check
	printf("number of airports : %d\n",counter);
}
//read one line of file
char * readline(FILE *fp)
{
    int ch;
    int i = 0;
    int buff_len = 0;
	char *buffer;
	
    buffer = malloc(buff_len + 1);
    if (!buffer) return NULL;  // Out of memory
	//read characters until change of line and put them in buffer
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
    {
        buff_len++;
        void *tmp = realloc(buffer, buff_len + 1);//increase string's size
        if (tmp == NULL)
        {
            free(buffer);
            return NULL; // Out of memory
        }
        buffer = tmp;//copy address of new string

        buffer[i] = (char) ch;//copy character
        i++;//increment index of array
    }
    buffer[i] = '\0';//end of string

    // Detect end
    if (ch == EOF && (i == 0 || ferror(fp)))
    {
    	printf("\n");
        free(buffer);
        return NULL;
    }
    return buffer;//get string
}

void parse_line(TStoixeiouEvr *Elem,char *buffer)
{
	int i=counter;
	int index;
	//allocate space for strings that contain file's data
	Elem[i].name = malloc(strlen(buffer)+1);
	Elem[i].city = malloc(strlen(buffer)+1);
	Elem[i].country= malloc(strlen(buffer)+1);
	Elem[i].iata = malloc(strlen(buffer)+1);
	Elem[i].icao = malloc(strlen(buffer)+1);
	//read the specific given format
	index = sscanf( buffer, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];", &Elem[i].airport_id,  Elem[i].name , Elem[i].city, Elem[i].country , Elem[i].iata , Elem[i].icao);
	//error check
	if(index==0)
		printf("error\n");
	
/*
	printf("\n%d\n",index);
	printf("\nid : %d\n",Elem[i].airport_id);
	printf("%s\n",Elem[i].name);
	printf("%s\n",Elem[i].city);
	printf("%s\n",Elem[i].country );
	printf("%s\n", Elem[i].iata);
	printf("%s\n", Elem[i].icao);
*/
	
}
//read line by line and pass integers at the end
int read_routes_file(FILE * file,int *source_id,int *dest_id)
{
	char *s;
	//*index=0;
	//get one line
	s = readline(file);
	if(s!=NULL)
	{	
		//parse the string that contains the 2 variables
	    parse_line_routes(s,source_id,dest_id);
	    //error check for "\N' values in the route file
	   /*if(counter2==1)
	   {
	    	printf("%s %d\n",s,*index);
	    	counter2=2;
		}
		//free space of each string*/
	    free(s);
	}
	//
	return counter2;
}
//destruct array of copies
void destruct_copies(int max_routes,TStoixeiouEvr *Elem)
{
	int i;
	//free strings
	for(i=0;i<max_routes;i++)
	{
		free(Elem[i].city);
		free(Elem[i].country);
		free(Elem[i].iata);
		free(Elem[i].icao);
		free(Elem[i].name);
	}
}
//free the names of strings
void destruct_data(TStoixeiouEvr *Elem)
{
		free(Elem->city);
		free(Elem->country);
		free(Elem->iata);
		free(Elem->icao);
		free(Elem->name);
}
//parse string to get source and destination id
void parse_line_routes(char *buffer,int *source_id,int *dest_id/*,index*/)
{
	//carefully process the format
	
	/**index =*/ sscanf( buffer, "%*[^;];%*d;%*[^;];%d;%*[^;];%d;%*[^;];%*d;%*s", source_id, dest_id );
	
	//ERROR CHECK
//	printf("%d %d\n",*source_id,*dest_id);
	//if(*index==0)
	//	counter2++;
		//printf("Error\n");
		
}



