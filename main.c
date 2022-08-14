/* COP 3502C Assignment 3 This program is written by: Ricardo Carvalheira */

#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

FILE *inFile, *outFile;


typedef struct monster
{
  int sequenceNumber;
  struct monster *next;
}monster;

typedef struct queue 
{   
    int monsterGroupNumber;  //ID
    int monsterCount;//node count
    int monstersSkipped; //k
    int monsterThreshold; //th
    monster* front;
    monster* back;
}queue;

monster * createMonster(int sequence) 
{ // It takes an integer, dynamically allocate a monster structure and returns a monster node
 
  monster* newMonster;
  newMonster=(monster*) malloc(sizeof(monster));
  newMonster->sequenceNumber=sequence;
  newMonster->next=NULL;
  return newMonster;
}

void enqeue(queue *qPtr, int val)
{
  monster * newMonster=createMonster(val);

  if(qPtr->back!=NULL)
  {
    qPtr->back->next=newMonster;
  }
    
  qPtr->back=newMonster;
  qPtr->back->next=qPtr->front;

  if(qPtr->front==NULL)
  {
    qPtr->front=newMonster;
  }
  return;
}

int dequeue(queue*q)
{
  int deletedMonsterSequenceNumber;

  if(q->front==NULL)
    return -1;

    deletedMonsterSequenceNumber=q->front->sequenceNumber;
    monster* deletedMonsterNode=q->front;
    q->front=q->front->next;

    if(q->front==NULL)
    { 
      q->back=NULL;
    }
    q->monsterCount--; //Decrease the number of monsters within a group

    free(deletedMonsterNode);
  
  return deletedMonsterSequenceNumber;
}

void createReverseCircle(queue *q)
{
	//It takes the reference of a queue, and creates a circular singly linked list for that queue  where the nodes contain sequence numbers in reverse order.
	//  This function calls createMonster as well as enqueue() to add monsters to the queue
  q->front=NULL;
  q->back=NULL;
  int i;
  for(i=q->monsterCount; i>=1;i--)
  {
    enqeue(q, i);
  }

}

void display(queue* q)
{
    monster *t=q->front; //monster pointer to transverse
    int size = q->monsterCount; //how many monsters there are
    if(q->front==NULL||size==0)
    {
      return;
    } 
    while(size>0)
	  {
		  printf(" %d",t->sequenceNumber);
      fprintf(outFile, " %d",t->sequenceNumber);

		  t=t->next; //traverse the array while there are still monsters
      size--;
	  }
    printf("\n");
    fprintf(outFile, "\n");

}
void displayTheOneWhoSurvived(queue* q)
{ //This function displays the monster who survived the lottery and calls dequeue to free their       memory
    monster *t=q->front;
    int size = q->monsterCount;
    if(q->front==NULL||size==0)
    {
      return;
    } 
    while(size>0)
	  {
      int dequeued;
      dequeued=dequeue(q);
		  printf("Monster %d from line %d will survive", dequeued,q->monsterGroupNumber);
      fprintf(outFile,"Monster %d from line %d will survive", dequeued,q->monsterGroupNumber);
		  t=t->next;
      size--;
	  }
}

void rearrangeCircle(queue* q)
{ // This function takes the reference of a queue and reverse the given circular singly linked    list where the first node of the linked list is pointed by the front of the queue

 if(q==NULL||q->front->next==NULL)
    return;

  monster* original=q->front;
  monster* reversed = q->back;
  reversed->next=original;
  monster* temp;
  
  do
  {
    temp=original;
    original=original->next;
    temp->next=reversed;
    reversed=temp;

  }while(original->next!=reversed);

  monster* tempFront;

  tempFront=q->front;
  q->front=temp;
  q->back=tempFront;
  return;
}



int killFrontMonster(queue *q)
{//This function kills the monster for phase1. It is kind of an enqueue
  int saveMonsterVal;

  if(q->front==NULL)
  {
    return 0;
  }
  if(q->front==q->back)
  {//If there is only one monster leftwe define both front and back to null
    saveMonsterVal=q->front->sequenceNumber;
    free(q->front);
    free(q->back);
    q->front = NULL;
    q->back = NULL;
  }
  else
  {
    monster * tempDequeued = q->front;
    saveMonsterVal=tempDequeued->sequenceNumber;
    q->front=q->front->next;
    q->back->next=q->front;
    free(tempDequeued);
  }
  
    return saveMonsterVal;//returns the sequenceNumber of the monster
}

monster* killMonster(monster* prev, monster *temp)
{//kills the monster in phase1
  if(prev==NULL||temp==NULL) return NULL;
  
  monster *die=temp;
  temp=temp->next;
  prev->next=temp;
  
  printf("\nMonster# %d executed", die->sequenceNumber);
  fprintf(outFile,"\nMonster# %d executed", die->sequenceNumber);

  free(die);
  return temp;
}

void phaseOne(queue* q)
{

  monster *prev=NULL;
  monster *temp = q->front;
  int dequeued=0; //stores the number of the monster dequeued

  printf("\nLine# %d", q->monsterGroupNumber);
  fprintf(outFile,"\nLine# %d", q->monsterGroupNumber);
	int i;

  while(q->monsterCount>q->monsterThreshold)
  {//while the number of monsters is larger than the monsterThreshold, keep looping
    for( i=0; i<(q->monstersSkipped-1) ;i++)
    {
      prev=temp;
      temp=temp->next;
    }
    if(temp==q->front)
    {

      temp=temp->next;
      dequeued=killFrontMonster(q);

      printf("\nMonster# %d executed", dequeued);
      fprintf(outFile,"\nMonster# %d executed", dequeued);
    }
      
    else
    {
      temp=killMonster(prev,temp);
    }

    q->monsterCount--;
  }
}


int findMonster(queue* q, int totalGroups)
{ //Peek
  int max=-1;
  int index=0;
  int counter=0;
  int groups=totalGroups;

  monster *t;

	int i;
  if(q->monsterCount==0)
    {
      q++;
    } 
  for( i=0;i<groups;i++)
  {
    t=q[i].front;
    if(t->sequenceNumber>max)
    {
      max=t->sequenceNumber;
      index=q[i].monsterGroupNumber;
    }
  }

  return index;
  }

void phaseTwo(queue* q, int totalGroups)
{
    int realIndex=0;  
    queue * ptr=q;//setting a pointer to the beginning of the queues array to store the address
    int count=0;
  	int index=findMonster(q,totalGroups);//Key found from the Peek function
    while(q->monsterGroupNumber!=index) //while the group number is not equals to that key, keep looping
    {		q++;//advance the aritimethic pointer

	  }
    realIndex =q-ptr; //Using aritimethic pointer to find out the real index. So, we know how many times it advanced. This is used to keep track of the real index for that key
  
    int dequeued=0;
    if(totalGroups>1)
	{
		while(q->monsterCount>0)
	    {
	    	
	      dequeued=dequeue(q);
	
	      printf("Executed Monster %d from line %d\n", dequeued,q->monsterGroupNumber);
	      fprintf(outFile,"Executed Monster %d from line %d\n", dequeued,q->monsterGroupNumber);
	
	     }
	  
	}


     else 
     {
     	while(q[totalGroups].monsterCount>1)
		 {
			  dequeued=dequeue(&q[totalGroups]);
 	    	printf("Executed Monster %d from line %d\n", dequeued,q[totalGroups].monsterGroupNumber);
 			  fprintf(outFile,"Executed Monster %d from line %d\n", dequeued,q[totalGroups].monsterGroupNumber);

		 }
     
	 }
	 

      
}

int main() 
{
	atexit(report_mem_leak); //for memory leak detector.
  inFile = fopen("in.txt", "r");

  if(inFile==NULL)
  {
    printf("Missing in.txt!\n");
    return -1;
  } 

  int totalGroups,i,j;
  fscanf(inFile,"%d", &totalGroups);
  outFile = fopen("out.txt", "w");

  queue* monsterQueue = (queue*) malloc(totalGroups*sizeof(queue));

  for( i=0;i<totalGroups;i++)
  {
    fscanf(inFile,"%d %d %d %d", &monsterQueue[i].monsterGroupNumber, &monsterQueue[i].monsterCount, &monsterQueue[i].monstersSkipped, &monsterQueue[i].monsterThreshold);
  }
  for( i=0;i<totalGroups;i++)
  {
    for( j=i+1;j<totalGroups;j++)
    { 
      if(monsterQueue[i].monsterGroupNumber>monsterQueue[j].monsterGroupNumber)
      {
        queue monsterTemp=monsterQueue[i];     
        monsterQueue[i]=monsterQueue[j];
        monsterQueue[j]=monsterTemp;
      }
    }
  }
 
  for( i=0;i<totalGroups;i++)
  {
  createReverseCircle(&monsterQueue[i]);  
  }
  
  printf("Initial nonempty lists status\n");
  fprintf(outFile,"Initial nonempty lists status\n");

  for( i=0;i<totalGroups;i++)
  {
    printf("%d", monsterQueue[i].monsterGroupNumber);
    fprintf(outFile,"%d", monsterQueue[i].monsterGroupNumber);
    display(&monsterQueue[i]);
  }


  for( i=0;i<totalGroups;i++)
  { //reverse!
    rearrangeCircle(&monsterQueue[i]);  
  }  

    printf("\nAfter ordering nonempty lists status\n");
    fprintf(outFile,"\nAfter ordering nonempty lists status\n");

  for( i=0;i<totalGroups;i++)
  {
    printf("%d", monsterQueue[i].monsterGroupNumber);
    fprintf(outFile,"%d", monsterQueue[i].monsterGroupNumber);
    display(&monsterQueue[i]);
  }
  
  printf("\nPhase1 execution\n");
  fprintf(outFile, "\nPhase1 execution\n");

  for( i=0;i<totalGroups;i++)
  {
    phaseOne(&monsterQueue[i]);
    printf("\n");
    fprintf(outFile,"\n");
  }

  printf("\nPhase2 execution\n");
  fprintf(outFile, "\nPhase2 execution\n");

 
  for( i=totalGroups;i>=1;i--)
  {
    phaseTwo(monsterQueue,i);
  }
    
  printf("\n");
  fprintf(outFile,"\n");

  for( i=0;i<totalGroups;i++)
  {
    displayTheOneWhoSurvived(&monsterQueue[i]);

  }

  free(monsterQueue);
  fclose(inFile);
  fclose(outFile);
  return 0;
}
