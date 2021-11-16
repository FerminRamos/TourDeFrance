/******************************************************************************
 *Fermin Ramos
 *tdfData.c grabs command line arguments, input file (tdf20.in), and outputs
 * a file depending on what command line argument was passed. tdfData.c has
 * the ability to organize the input file data into 3 formats - format, teams,
 * country. Format prints input file data with left justification and a field
 * width of 20. Teams only prints team, rider number, rider, and time. Country
 * prints country, rider, classification, time. 
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#define S_LENGTH 30
#define LINE_LENGTH 300
#define TOTAL_RIDERS 146

/*Prototypes*/
void getData(void);
void printFormatted(void);
void organizeTeams(void);
void printTeams(int row);
void printCountries(void);

/*Global Variables*/
char strArrays[TOTAL_RIDERS][4][30];
int intArrays[TOTAL_RIDERS][2];

int main(int argc, char *argv[])
{ 
  /*Grabs Data from Textfile*/
  getData();
  
  /*Check which command line argument entered + activate associated function*/
  if(strcmp(argv[1],"format") == 0)
    printFormatted();
  else if(strcmp(argv[1],"team") == 0)
    organizeTeams();
  else if(strcmp(argv[1],"country") == 0)
    printCountries();
  else
    printf("ArgumentNOTfound: %s\n", argv[1]);
  
  return 0;
}


/******************************************************************************
 *Grabs Data from input textfile and organizes it into a 2D arary. Separates
 * data into 2 separate arrays based on data type. intArrays is an array that
 * holds ONLY int data types (classification & rider number). strArrays is
 * an array that holds ONLY strings (rider, country, team, time).
 * 
 *Returns nothing. 
 *****************************************************************************/
void getData()
{
  char name[S_LENGTH], country[S_LENGTH], team[S_LENGTH], time[S_LENGTH];
  char line[LINE_LENGTH];
  int class, number, row;
  row = 0;
  
  /*Grabs info from text file*/
  while(fgets(line,LINE_LENGTH,stdin) != NULL)
  {
    /*Grabs 1 line*/
    sscanf(line,"%d %s %d %s %s %s", &class, name, &number, country, team, time);
    
    /*Insert data into arrays*/
    strcpy(strArrays[row][0], name);
    strcpy(strArrays[row][1], country);
    strcpy(strArrays[row][2], team);
    strcpy(strArrays[row][3], time);    
    intArrays[row][0] = class;
    intArrays[row][1] = number;
    
    row++;
  }
}

/******************************************************************************
 *printFormatted() does NOT sort the data. printFormatted() prints 
 * classification, rider, number, country, team, time. Prints with left 
 * justification and a field width of 20. Uses both intArrays & strArrays to
 * print info.
 *
 *Returns nothing. 
 *****************************************************************************/
void printFormatted()
{
  /*prints top line of formatted.out file*/
  char classification[] = {"Classification"};
  char rider[] = {"Rider"};
  char number[] = {"Rider No."};
  char country[] = {"Country"};
  char team[] = {"Team"};
  char time[] = {"Time (hh:mm:ss)"};
  printf("%-20s%-20s%-20s%-20s%-20s%-20s\n", classification, rider, number,
	                                     country, team, time);
  
  /*prints all lines*/
  int row;
  for(row = 0; row < TOTAL_RIDERS; row++)
  {
    /*prints classification*/
    printf("%-20d", intArrays[row][0]);
    /*prints rider name*/
    printf("%-20s", strArrays[row][0]);
    /*prints rider number*/
    printf("%-20d", intArrays[row][1]);
    /*prints country*/
    printf("%-20s", strArrays[row][1]);
    /*prints team*/
    printf("%-20s", strArrays[row][2]);
    /*prints time*/
    printf("%-20s\n", strArrays[row][3]);
  }
}

/******************************************************************************
 *organizeTeams() sorts through intArray by finding lowest possible rider 
 * number first, and counting upwards until all riders have been counted. Each 
 * rider number found records its row and passes row number into printTeams() 
 * so info can be printed (team, rider number, rider, and time data).
 *
 *Returns nothing.
 *Calls printTeams()
 *****************************************************************************/
void organizeTeams()
{
  char team[] = {"Team"};
  char number[] = {"Rider No."};
  char rider[] = {"Rider"};
  char time[] = {"Time (hh:mm:ss)"};

  /*prints header*/
  printf("%-20s%-20s%-20s%-20s\n", team, number, rider, time);

  int row, riderNum;
  riderNum = 1;
  /*There are 218 rider numbers, iterates until we reach the end*/
  while(riderNum < 219)
  {
    /*Iterates through all possible rider numbers in intArrays*/
    for(row = 0; row < TOTAL_RIDERS; row++)
    {
      /*checks if value = current lowest rider number*/
      if(intArrays[row][1] == riderNum)
	printTeams(row);
    }
    /*Next possible rider number*/
    riderNum++;
  }
}

/******************************************************************************
 *printTeams() takes in row number from organizeTeams(). With row number, 
 * printTeams() grabs data from row to print other info (team, rider number, 
 * rider, time).
 *
 *Returns nothing 
 *****************************************************************************/
void printTeams(int row)
{ 
  /*prints team, rider number, rider, time in order*/
  printf("%-20s%-20d%-20s%-20s\n", strArrays[row][2], intArrays[row][1],
	                           strArrays[row][0], strArrays[row][3]);
}

/******************************************************************************
 *printCountry() iterates through strArrays and sorts each country 
 * alphabetically. Country strings WILL be copied into miscellaneous rows, 
 * but rowOrder keeps track of where it is relocated, so that the rest of
 * the information can be tracked back to that country (rider, classification,
 * time). After all countries have been organized, it prints them.
 * 
 *Returns nothing
 *****************************************************************************/
void printCountries()
{
  /*Prints Header*/
  char country[] = {"Country"};
  char rider[] = {"Rider"};
  char class[] = {"Classification"};
  char time[] = {"Time (hh:mm:ss)"};
  printf("%-20s%-20s%-20s%-20s\n", country, rider, class, time);
  
  int row, s1, s2, rowOrder[TOTAL_RIDERS], intHolder;
  char strHolder[30];

  /*rowOrder holds order of rows to be printed, initializes*/
  for(row = 0; row <= TOTAL_RIDERS; row++)
    rowOrder[row] = row;

  /*Sorts alphabetically, by country.*/
  for(s1 = 0; s1 <= TOTAL_RIDERS; s1++)
  {
    for(s2 = s1+1; s2 <= TOTAL_RIDERS; s2++)
    {
      /*Flips order of strings if activated*/
      if(strcmp(strArrays[s1][1], strArrays[s2][1]) > 0)
      {
	/*Flips rows to print*/
	intHolder = rowOrder[s1];
	rowOrder[s1] = rowOrder[s2];
	rowOrder[s2] = intHolder;
	
	/*Flips strings*/
	strcpy(strHolder, strArrays[s1][1]);
	strcpy(strArrays[s1][1], strArrays[s2][1]);
	strcpy(strArrays[s2][1], strHolder);
      }
    }
  }
  
  /*Prints: country, rider, classification, time*/
  for(row = 0; row <= TOTAL_RIDERS; row++)
  {
    int r;
    /*Remember rowOrder keeps track of data, even when country moved locations*/
    r = rowOrder[row];
    printf("%-20s%-20s%-20d%-20s\n", strArrays[row][1], strArrays[r][0],
	                             intArrays[r][0], strArrays[r][3]);
  }
}
