// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
	if (list.head == NULL) {
		return 0;
	}
	NODE *current = list.head;
	int count = 0;
    while (current->next != NULL) {
	count++;
	current = current->next;
    }
	return ++count;
}
// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){
    NODE *newNode = malloc(sizeof(NODE));
    Verify_Malloc(newNode);
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
	return;
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {
	NODE *newNode = malloc(sizeof(NODE));
	Verify_Malloc(newNode);
	newNode->data = data;
	if (list->head == NULL) {
		list->head = newNode;
		return;
	}
	NODE *current = list->head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newNode;
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
	if (list->head == NULL) {
		return 0;
	}
	*data = list->head->data;
	NODE *next = list->head->next;
	free(list->head);
	list->head = next;
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
	if (list->head == NULL) {
		return 0;
	}

	if (list->head->next == NULL) {
		*data = list->head->data;
		free(list->head);
		list->head = NULL;
		return 1;
	}
	NODE *current = list->head;
	while (current->next->next != NULL) {
		current = current->next;
	}
	*data = current->next->data;
	free(current->next);
	current->next = NULL;
   return 1;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
	int count = 0;
	NODE *current = list.head;
	while (current != NULL) {
		if (current->data == data) {
			count++;
		}
		current = current->next;
	}
    return count;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
	NODE *current = list->head;
	NODE *prev = NULL;
	while (current != NULL) {
		if (current->data == data) {
			if (prev != NULL) {
				prev->next = current->next;
			} else {
				list->head = current->next;
			}
			free(current);
			return 1;
		}
		prev = current;
		current = current->next;
	}
    return 0;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    if (list.head == NULL) {
	return 1;
    }
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
	if (list->head == NULL) {
		return;
	}
	NODE *current = list->head->next;
	while (current != NULL) {
		NODE *temp = current->next;
		free(current);
		current = temp;
	}
	free(list->head);
	list->head = NULL;
    return;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
	
	if (list->head == NULL) {
		return;
	}
	int found[Size(*list)];
	int size = 0;
	NODE *current = list->head;
	found[size++] = current->data;
	while (current->next != NULL) {
		int match = 0;
		for (int i = 0; i < size; i++) {
			if (current->next->data == found[i]) {
				match = 1;
				break;
			}
		}
		if (match) {
			NODE *temp = current->next->next;
			free(current->next);
			current->next = temp;
		} else {
			found[size++] = current->next->data;
			current = current->next;
		}
	}
	
	/*
	if (list->head == NULL) {
		return;
	}
	NODE *current = list->head;
	int found[999999];
	found[current->data] = 1;
	while (current->next != NULL) {
		if (found[current->next->data]) {
			NODE *temp = current->next->next;
			free(current->next);
			current->next = temp;
		} else {
			found[current->next->data] = 1;
			current = current->next;
		}
	}
	*/
    return;
}

// modify main to completely test your functions 
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);

    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a beter test for Count_If
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    // write a better test for Clear
    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");

    // write a better test for Remove_Duplicates
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Remove_Duplicates(&list);
    Print_List(stdout, list);
    //Moar tests
    /*
    printf("More tests:\n");
	LINKED_LIST list2 = Create_List();
	printf("size = %d\n", Size(list2));
	printf("Test push front on empty list\n");
	Push_Front(&list2, 0);
	Print_List(stdout, list2);
	
	printf("Test pop front on one element list\n");
	int x = 0;
	int deleted = Pop_Front(&list2, &x);
	if (deleted) {
		Print_List(stdout, list2);
		printf("deleted: %d\n", x);
	} else {
		printf("Node not deleted\n");
	}

	printf("test push back on empty list\n");
	Push_Back(&list2, 1);
	Print_List(stdout, list2);
	printf("Size = %d\n", Size(list2));

	printf("Test pop back on one element list\n");
	deleted = Pop_Back(&list2, &x);
	if (deleted) {
		Print_List(stdout, list2);
		printf("deleted: %d\n", x);
	} else {
		printf("Node not deleted\n");
	}
	printf("size = %d\n", Size(list2));

	printf("Pop front and pop back on empty lists\n");
	deleted = Pop_Front(&list2, &x);
	printf("Pop_Front: %d\n", deleted);
	deleted = Pop_Back(&list2, &x);
	printf("Pop_Back: %d\n", deleted);

	printf("Testing delete on empty list\n");
	deleted = Delete(&list2, 9);
	printf("Should be 0: %d\n", deleted);
	printf("Testing delete on single element list\n");
	Push_Front(&list2, 9);
	deleted = Delete(&list2, 9);
	Print_List(stdout, list2);
	printf("Should be 1: %d\n", deleted);


	printf("Expected: 1->1->2->3->1->2->3\n");
	Push_Front(&list2, 3);
	Push_Back(&list2, 1);
	Push_Front(&list2, 2);
	Push_Back(&list2, 2);
	Push_Front(&list2, 1);
	Push_Back(&list2, 3);
	Push_Front(&list2, 1);
	Print_List(stdout, list2);

	printf("1 Count: %d\n", Count_If(list2, 1));
	printf("2 Count: %d\n", Count_If(list2, 2));
	printf("3 Count: %d\n", Count_If(list2, 3));

	printf("Normal Delete test\n");
	printf("Should be 1: %d\n", Delete(&list2, 1));
	Print_List(stdout, list2);

	printf("Testing remove duplicates. Expected: 1->2->3\n");
	Remove_Duplicates(&list2);
	Print_List(stdout, list2);
	Clear(&list2);
	printf("Testing remove duplicates on list of all same element (cos why not)\n");
	Push_Front(&list2, 5);
	Push_Front(&list2, 5);
	Push_Front(&list2, 5);
	Remove_Duplicates(&list2);
	Print_List(stdout, list2);
	printf("Now on one element list\n");
	Remove_Duplicates(&list2);
	Print_List(stdout, list2);

	printf("5 Count: %d\n", Count_If(list2, 5));
	printf("12 Count: %d\n", Count_If(list2, 12));
	Clear(&list2);
	printf("Now on empty list\n");
	Remove_Duplicates(&list2);
	Print_List(stdout, list2);

	printf("clear on empty list\n");
	Clear(&list2);
	Print_List(stdout, list2);
	printf("1 Count: %d\n", Count_If(list2, 1));
	*/	
    return 0;
}
