//First Name:Alec Bickler 7/21/2023
//Then includes:
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Command to print the required values for project
//void giveVal();

//struct blocks { int flags, long long tag; };
typedef struct {
int out; // Marks for if valid
long long add; //gives block tag value
} Take;

void main(int argc, char** argv){

int m = strtol(argv[1], NULL, 10);
int n = strtol(argv[2], NULL, 10); 
char* file = argv[3];

  
//printf("M:%d \n", m);
//printf("N:%d \n", n);
//printf("File:%s \n", file);
//necesarry vars
char outs;
long long addr;
int hits = 0;
int misses = 0;
int PC, Outc, index;


//counter vars
int i, j;

//size for table
int size = pow(2, m);
  //printf("size:%d\n", size);

//Take* table = (Take*) malloc(size * sizeof(Take*));
//allocates table memory
Take* table = (Take*) malloc(size * sizeof(Take));
//Block** cache = (Block**)malloc(sets * sizeof(Block*))

//Initializes to weakly taken
for(i=0; i<size;i++) 
{
  table[i].out = 2;
}
int GHB = 0;

/*Test for table creation

for(i=0; i<size;i++) 
{
  int valTest = table[i].out;
  printf("value test %d: %d\n", i, valTest);
}

*/

//int pred3 = table[5].out;
//printf("pred3: %d\n", pred3);

//Opens file and scans for addresses and outcomes
FILE* filename = fopen(file, "r");
while(fscanf(filename, " %llx %c", &addr, &outs) == 2) {

  //pred3 = table[5].out;
//printf("pred3: %d\n", pred3);
//gets address
PC = addr;
    ////printf("outcomes character: %c\n", outs);
  
if(outs == 't')
{
  //Outc = 3;
  Outc = 2;
}
else
  Outc = 1;

    //test outC
    ////printf("outcome %d\n\n", Outc);

  
    //test pc
    //printf("PC %d\n", PC);

//Remove leasts sig bits from PC
PC = PC/4;

  //test pc
//Take index for M
int mIndex = ( PC % (int) (pow(2, m)));

    //test PC
    //printf("PC %d\n", PC);

    //test mIndex
    //printf("mIndex: %d\n", mIndex);


  if(n>0){
    int nIndex = GHB << (m-n);
    index = mIndex ^ nIndex;
  }
  else
    index = mIndex;

////printf("Index: %d\n", index);

//Takes prediction of value at table index
int pred = table[index].out;
////printf("pred: %d\n", pred);

  //test
  /*
  if(index==5){
 pred3 = table[5].out;
printf("pred3: %d\n", pred3);
  
  pred3 = table[index].out;
printf("pred3: %d\n", pred3);
    
  }
  */

  
  
if (outs == 't')
{
  //Represents if outcome is T
  //updates GHB
  GHB = GHB>>1; 
  GHB = GHB + pow(2, n-1);

  //tests if pred is T, pred>=2
  if(pred>=Outc)
  {
    ////printf("reached pred >= outc(2) Hit\n");

    /*
    //if pred is not 3, increment table value
    if(table[index].out < 3)
    {
    table[index].out++;
    ////printf("reached indec.out < 3\n");
    }

    */
    //this is a hit as pred. is >= 2 and outcome is >= 2
    hits++;
  }
  //test if pred is N, pred < 2
  else
  {
   ////printf("reached pred < outc(2) Miss\n");
   /*
   //if pred is not 0, decrement table value
   if(table[index].out>0) 
   {
    table[index].out--;
    ////printf("reached indec.out > 0\n");
   }
   */
    
   //this is a miss
    misses++;
    
   
  }

  //if pred is not 3, increment table value
    if(table[index].out < 3)
    {
    table[index].out++;
    ////printf("reached indec.out < 3\n");
    }
}

  
else
{
  //Represents if outcome is N
  
  //updates GHB
  GHB = GHB>>1;
  
  //Tests for if predicted value is more than 
  if(pred > Outc)
  {
    ////printf("reached pred > outc(1) Miss\n");
    /*
    //if pred is not 3, increment table value
    if(table[index].out<3)
    {
    table[index].out++;
    ////printf("reached indec.out < 3\n");
    }
    */
    
    //this is a miss
    misses++;
  }
  //test if pred is N, pred < 2
  else
  {
   ////printf("reached pred <= outc(1) Hit\n");
    /*
   //if pred is not 0, decrement table value
   if(table[index].out>0) 
   {
    table[index].out--;
    ////printf("reached indec.out > 0\n");
   }
   */
   //this is a hit as pred. is < 2 and outcome is < 2
    hits++;
    
   
  }

  //if pred is not 0, decrement table value
   if(table[index].out>0) 
   {
    table[index].out--;
    ////printf("reached indec.out > 0\n");
   }
   
}
/*
//tests ghb
printf("GHB: %d\n", GHB);
printf("Hits: %d\n", hits);
printf("Misses: %d\n", misses);
*/


}




  

//printf("\n\n\n\nHits: %d\n", hits);
//printf("Misses: %d\n", misses);
//printf("M: %d\n", m);
//printf("N: %d\n", n);

double missratio = (double) misses / (hits + misses);
//double mr = missratio * 100;
//printf("miss-predict ratio: %0.6f\n", missratio);
  //printf("%d %d %0.2f", m, n, mr);
printf("%d %d %0.4f", m, n, missratio);

/*
  for(i=0; i<size;i++) 
{
  int valTest = table[i].out;
  printf("value test %d: %d\n", i, valTest);
}
  */
  
  //printf("Index: %d\n", index);
free(table);
}
