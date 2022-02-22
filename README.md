# DSA_Cool
My DSA projects

Following are the questions answered above:-

## A-1: Create three database using header linked 
 	Student (Roll No, Name, Branch ID, CGPA)
	University (University ID, University Name, University Location, Year of start)
	Branch (Branch ID, University ID, Branch Name)

1)Implement the following modules/ sub-modules using menu driven approach:
2)Keep the Roll No, University ID and Branch ID Unique (Duplicated entry should not be allowed and prompted)
3)Student can take a University ID/ Branch ID only if it is available in the University/ Branch database.
4)Student Name, University Name and Branch Name should all be in Capital Letters. (If user has not entered accordingly, then the program must convert it into Capital Letters and store.)
5)Display the entire  student list/ University list/  Branch List
6)Delete all students whose CGPA<6.0 and store them in another list. They will come back to original student list if their CGPA>=6.0(Update function)
7)Display the list of students reading in KIIT University
8)ADD/ MODIFY/DELETE/UPDATE using key value in any of the database as per requirement.
9)Display the student details who are reading at KIIT University with branch CSE.
10)Display the list of Branches available in any given University
11)Display the University details in ascending order of their year of starting
12)Display the all Student name/ all University name for a given name substring entered by the user.

## A-2: Create one database using header linked list and file system to store the details of a shopping card given by the Shopping Mall.
 Shopping Card( Card_ID, Customer_Name, Points, Date_of_Birth, Last_date_of_trasaction, address)
Item (Item_ID, Item_Name, Price, Quantity)
1)Implement the following modules/ sub-modules using menu driven approach:
2)Keep the Card_ID and Item_ID Unique (Duplicated entry should not be allowed and prompted)
3)Update function to update the address only (if required).  Other fields can’t be updated by the customer.
4)A customer can buy different products listed and accordingly points will be assigned as follows:
5)When the manager of the shopping mall decides (decides a date), a discount of 10% can be given to 10 customers those who have first accumulated 1000 points. The customer may immediately redeem the points and get 10% discount and its points will be reset to zero, else keep it for later use.  The next 10 customer will get the discount in the next month same date. This process continues.
6)When the manager of the shopping mall decides (decides a date), a discount of 15% can be given to 5 customers those who have first accumulated 1000 points and are senior citizens (age>60). The customer may immediately redeem the points and get 10% discount and its points will be reset to zero, else keep it for later use.  This process is repeated in every month.
7)Display the customer details and item details as per requirements.
8)Add new customer as well as new items.
9)Delete existing customer if the last transaction date is before one year.
10)The system should show the items out of stock during the purchase.

## A-3 In a vaccination centre people make queue. But due to unavailability of space in the same queue, people make a parallel queue (second queue following the first one), then people make a parallel queue (third queue following the second one) and further no queues can be made due to unavailability of space. The case can be shown diagrammatically as follows. The arrow shows the direction in which people can be added. The box shows the space available for waiting. The size of the three boxes is equal where the size will be decided by the user.
  
1)Implement the queues (Insertion and deletion) operations. Whenever the first people get into the centre, all peoples will move one step forward. 
2)Write functions to handle when no one is present to get the vaccine and when no further people can be added to the queue due to unavailability of space.

## A-4 Write a program to implement four numbers of D-queues in an array.
## A-5 Write a program to implement round robin scheduling concept using a linked list. Each node will represent a process with attributes as <PID, CPU_time>. A quantum time T will be input by the user. A process will be executed (when user wants) for quantum time T and the CPU_time will be updated with CPU_time T, and the current process node is deleted from the beginning and added to the end of the list. If the updated CPU_time is <=0, then the process is deleted from the list. After a process is executed for T time, the the next process in the queue is executed upon user choice. The entire process gets completed when all process nodes are deleted.
## A-6 Write a program to construct a binary tree from given sequence of preorder and inorder traversal of the tree.
## A-7 Write a program to check that the left sub-tree of an binary tree is  mirror image of its right sub-tree.
## A-8 Write a program to implement a graph ADT and traverse the graph in bread first search and depth first search for a given node.
	
