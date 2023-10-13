# Find the lucky monster - Queue and Linked-List
For this assignment you have to write a c program that will use the circular singly linked list and queue data structure 

Problem: Find the lucky monster  A Monster Kingdom has trapped G (G ≤ 10) groups of criminal monsters. They want to execute them. They found out a strategy so that the criminal monsters will kill each other and at the end one  monster  will  be  alive  and  he  will  be  released.  The  kingdom  has  10  execution  grounds  one after  another.  Each  ground  has  a  ground  number.  The  grounds  are  numbered  with  a  sequence number  starting  from  1  to  10.  As  part  of  the  strategy,  each  group  is  placed  to  an  execution ground. The groups are numbered based on the assigned execution ground number. Note that G is assumed to be less than or equal to 10 and as a result some grounds could be empty.  

Each group gi has ni (ni ≥2) number of monsters. As part of the process, they labeled each monster of  a  group  with  a  sequence  number  starting  from  1  and  ending  at  ni.  All  the  ni  number  of monsters  of  group  gi  are  standing  in  a  circle  and  waiting  to  be  executed.  However,  due  to distraction,  it  was  found  out  that  all  monsters  in  all  the  groups  were  standing  in  reverse  order instead of proper order like the following picture (let us say monsters count of a group is 6): 
 
 ```6-> 5-> 4 -> 3 -> 2-> 1```
 (one to six)
 
After  realizing  the  wrong  order  of  sequence,  they  reversed  the  circle  to  the  correct  order  (note that they have not just changed their labels, they have physically changed their order by moving the criminal to the correct place) : 
 
```1 ->2-> 3-> 4 -> 5 -> 6```
 (six to one)
 
The execution process is divided into two phases. 

## Phase1 Execution: 

In  Phase1,  the  execution  happens  within  the  group  and  this  phase  of  execution  for  a  group  gi stops when the total number of monsters for the group reduced to a threshold thi (thi<ni  ). Now, they will start the executing process. The counting out begins from the first monster in the circle of the group and proceeds around the circle in a fixed direction. In each step, a certain number of people  ki  -1  (ki  >  0)  are  skipped  and  the  next  monster  is  executed.  The  elimination  proceeds around the circle, which is becoming smaller and smaller as the executed people are removed. As mentioned,  the  execution  process  for  the  group  gi  will  stop  when  the  group  has  thi  number  of monsters. 

In summary, for a group gi, you have the total number of monsters ni (ni ≥2), and a number ki (ki > 0), which indicates that ki-1 monsters are skipped and kith monster is killed in circle. There is a threshold thi (thi<ni), that indicates to stop killing in phase 1 when the number of monsters of the group reduced to thi. The same process should be applied to all the groups according to their own n, k, and th. The remaining monsters will be transferred to phase 2. 

### Phase 1 Example 

For  example,  if  a  group  has  n  =  5,  k  =  2,  and  th  =  2,  then  the  phase  1  process  will  be  the following:  First, the monster at position 2 is killed, then the monster at position 4 is killed, then monster at position 1 is killed. As there are only two monsters remaining (monsters 3 and 5), the execution process  for  this  phase  for  the  group  will  stop. The  remaining  monsters  will  be  transferred  to Phase 2.

Another example: if a group has n = 7, k = 3, and th = 3, then the phase 1 process will be the following: The monsters at positions 3, 6, 2, and 7 will be executed and the remaining monsters 1, 4, and 5 will be transferred to phase 2. 
 
## Phase2 Execution: 
In phase 2, the execution will happen across the groups with the following strategy: 

- The  highest  monster  sequence  number  across  all  the  fronts  of  the  groups  will  be  executed. 
- If the same highest monster sequence number is standing in the fronts of multiple groups, the  monster  standing  on  the  smallest  execution  ground  number  (same as  group  number) will be executed first to break the tie. 
- Keep following the phase 2 process until there is only one monster remaining among all the groups and that monster will be the winner and will be released! o Your task is to find that monster!  

Please see the example from the sample input/output for better clarification. 

### Input Specification:  
The input has to be read from in.txt file. The first line of the file contains the number of groups G captured by the kingdom. The next G lines contain the information of the groups. 

For each line of a group, the first integer indicates the ground number gi(gi ≤10), the next integer indicates the number of monster ni in the group ( ≤10000), the next integer indicates the value of ki (ni > ki > 0) and then the next integer indicates the value of thi (ni>thi >0) integer. 

### Output Specification: 
The output has to be written to out.txt file as well as to the console with the exact same format specified by the sample output bellow. The output mainly contains the simulation steps and the last line will contain survived monster number with the group number. 

#### Sample input from in.txt file:
```
4 
4 7 3 3 
1 10 3 2  
7 9 2 4  
3 8 2 1 
``` 
#### Sample output:
```
Initial nonempty lists status 
1 10 9 8 7 6 5 4 3 2 1 
3 8 7 6 5 4 3 2 1 
4 7 6 5 4 3 2 1 
7 9 8 7 6 5 4 3 2 1 

After ordering nonempty lists status
1 1 2 3 4 5 6 7 8 9 10 
3 1 2 3 4 5 6 7 8 
4 1 2 3 4 5 6 7 
7 1 2 3 4 5 6 7 8 9 
 
Phase1 execution

Line# 1
Monster# 3 executed 
Monster# 6 executed 
Monster# 9 executed 
Monster# 2 executed 
Monster# 7 executed 
Monster# 1 executed 
Monster# 8 executed 
Monster# 5 executed

Line# 3 
Monster# 2 executed 
Monster# 4 executed 
Monster# 6 executed 
Monster# 8 executed 
Monster# 3 executed 
Monster# 7 executed 
Monster# 5 executed 

Line# 4 
Monster# 3 executed 
Monster# 6 executed 
Monster# 2 executed 
Monster# 7 executed

Line# 7
Monster# 2 executed 
Monster# 4 executed 
Monster# 6 executed 
Monster# 8 executed 
Monster# 1 executed 
 
Phase2 execution
Executed Monster 4 from line 1 
Executed Monster 10 from line 1 
Executed Monster 3 from line 7 
Executed Monster 5 from line 7 
Executed Monster 7 from line 7 
Executed Monster 9 from line 7 
Executed Monster 1 from line 3 
Executed Monster 1 from line 4 
Executed Monster 4 from line 4

Monster 5 from line 4 will survive
```
### Implementation Restrictions:  
a) You must have to use linked list and queue in your implementation.

b) You  must  have  to  use  circular  singly linked  list  for  your  solution  to  get  full  credit. You need  to  declare  appropriate  linked  list  node  structure  to  store  a monster  with  sequence number as the data value.

c) You have to use linked list implementation of queue when applicable.

d) Create a node structure for Monster that has a sequenceNumber and next pointer

e) Create  a  node  structure  for  a  queue  that  has  front  and  back  pointers  to  point  monsters. Also, a good idea would be storing nodeCount, k, and th within the queue structure.
f) You have to implement and use enqueue, dequeue, peek, isEmpty function for this given scenario.

g) In addition to the other functions of a queue like enqueue, dequeue, your code must have to implement the following functions and use them part of the solution:

h)  monster* createMonster(int sequence): It takes an integer, dynamically allocate a monster structure and returns a monster node

i)  void createReverseCircle(queue *q): It takes the reference of a queue, and creates a circular singly linked list for that queue where the nodes contain sequence numbers in reverse order . For example, if n=5 it should produce a circular singly linked list starting from 5 and ending at 1 as sequence number. During this process, use the createMonster function as well as enqueu() function to add the monster to the queue.

j)  void rearrangeCircle(queue* q): This function takes the reference of a queue and reverse the given circular singly linked list where the first node of the linked list is pointed by the front of the queue

k)  void display(queue q): This function displays a given queue

l) It is also encouraged that you create functions for phase1, phase2, and other auxiliary functions to simplify your code

m)  For phase1 execution, you can avoid using dequeue function, however, you must have to use dequeue function in phase2 execution.

n) You also have to use memory leak detector in your code like assignment 1. 
 
Your  code  must  compile  in  Mimir  platform.  If  it  does  not  compile  in  Mimir,  we  conclude  that your code does not compile even if it works in your computer. 

#### Hints: 
- Read the complete instruction first. It is always a good idea to plan it and do some paper work to understand the problem. 
- Just  draw  the  scenario  for  a  single  group  of  monsters  first  to  understand  how  the execution process works. 
- Analyze the sample input/output and draw them in paper to see how they are structured 
- Use  an  array  of  queue.  The  empty  function  of  queue  will  help  you  a  lot  as there can  be  many empty queues. 
- For a queue, generate n numbers (n, ....3, 2, 1) in reverse order and insert into the singly circular  linked  list.  Your  enqueue  function  can  help  you  to  insert  them  if  you  write  the enqueue properly 
- Then test your code by displaying. In this way you will match your output with the first part of the sample output 
- Then  reverse  the  singly  circular  linked  list.  You  had  done  a  lab  on  reversing  a  singly  linked list. Now, you have to do it for circular singly linked list. //if you get stuck in this part, my suggestion would be create the list in normal ascending order first and write and test the other functionalities. When you are satisfied with other functionalities, come back to this part of the code and work on it. 
- Then start processing phase 1. Delete nodes based on the value of k until the list has the number of nodes remaining. Display the data of the killed monster of phase 1 just before freeing up the node  
- Then start phase2. 
- Test your code after each step! 
 
Steps to check your output AUTOMATICALLY in Mimir or repl.it or other command line based compiler: You can run the following commands to check whether your output is exactly matching with the sample output or not. 

#### Step1: Copy the sample output into sample_out.txt file and upload it to the mimir/replit (you can make your own sample_out.txt file)
#### Step2:  compile  and  run  your  code  using  typical  gcc  and  other  commands.  Your  code  should  produce out.txt file.
#### Step3:  Run the following command to compare your out.txt file with the sample output file ```$diff -i out.txt sample_out.txt```

The  command  will  not  produce  any  output  if  the  files  contain  exactly  same  data.  Otherwise,  it  will tell you the lines with mismatches. Incase if your code does not match, you can use the following command to see the result in side by side: ```$diff -y out.txt sample_out.txt```
