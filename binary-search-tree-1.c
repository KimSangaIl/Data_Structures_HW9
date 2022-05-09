/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)
{
	if (ptr) {				//노드에 값이 있는 경우
		inorderTraversal(ptr->left);	//왼쪽 서브 트리로 이동하여 함수 호출
		printf(" [%d] ", ptr->key);	//노드의 키값을 출력
		inorderTraversal(ptr->right);	//오른쪽 서브 트리로 이동하여 함수 호출
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {				//노드에 값이 있는 경우
		printf(" [%d] ", ptr->key);	//노드의 키값을 출력
		preorderTraversal(ptr->left);	//왼쪽 서브 트리로 이동하여 함수 호출
		preorderTraversal(ptr->right);	//오른쪽 서브 트리로 이동하여 함수 호출
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);	//왼쪽 서브 트리로 이동하여 함수 호출
		postorderTraversal(ptr->right);	//오른쪽 서브 트리로 이동하여 함수 호출
		printf(" [%d] ", ptr->key);	//노드의 키값을 출력
	}
}

int insert(Node* head, int key)
{
	Node* new = (Node*)malloc(sizeof(Node));	//삽입할 노드를 저장할 변수 동적 할당
	new->key = key;		//새 노드의 키값을 입력 받은 키값으로 초기화
	new->left = NULL;
	new->right = NULL;	//새 노드의 좌우 서브 트리 링크를 NULL로 초기화

	if (head->left == NULL) {	//헤드 노드의 왼쪽 서브 트리가 비어있는 경우
		head->left = new;	//왼쪽 서브 트리에 새 노드를 추가
		return 1;		//함수 종료
	}

	Node* temp = head->left;	//새 노드를 삽입하기 위해 탐색할 임시 노드 선언 및 헤드 노드의 왼쪽 서브 트리로 초기화
	Node* ptemp = NULL;		//임시 노드의 부모 노드를 지정할 노드 선언 및 NULL로 초기화

	while (temp != NULL) {		//임시 노드가 NULL이 될때까지 반복
		if (temp->key == key) {	//임시 노드의 키값이 입력 받은 키값과 같은 경우
			return 1;	//입력 받은 키값이 이미 존재하기 때문에 함수 종료	
		}
		ptemp = temp;			//ptemp노드를 임시 노드로 초기화
		if (temp->key > key) {		//임시 노드의 키값이 입력 받은 키값보다 큰 경우
			temp = temp->left;	//임시 노드를  왼쪽 서브 트리로 이동
		}
		else temp = temp->right;	//키값이 작은 경우 오른쪽 서브 트리로 이동
	}

	if (ptemp->key > key) {		//ptemp노드의 키값이 입력 받은 키값보다 큰 경우
		ptemp->left = new;	//ptemp노드의 왼쪽 서브 트리에 새 노드 추가
	}
	else ptemp->right = new;	//키값이 작은 경우 오른쪽 서브 트리에 새 노드 추가

	return 1;	//함수 종료
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {			//헤드 노드가 비어있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
		return -1;			//비정상 함수 종료
	}

	if (head->left == NULL) {		//헤드 노드의 왼쪽 서브 트리가 비어있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
		return -1;			//비정상 함수 종료
	}

	Node* temp = head->left;	//노드를 삭제하기 위해 탐색할 임시 노드 선언 및 헤드 노드의 왼쪽 서브 트리로 초기화
	Node* ptemp = NULL;		//임시 노드의 부모 노드를 지정할 노드 선언 및 NULL로 초기화

	while (temp != NULL) {		//임시 노드가 NULL이 될때까지 반복
		if (temp->key == key) {	//임시 노드의 키값이 입력 받은 키값과 같은 경우
			if (temp->left == NULL && temp->right == NULL) {	//임시 노드의 좌우 서브 트리가 비어있는 경우
				if (ptemp == head) {		//ptemp노드가 헤드 노드인 경우
					head->left = NULL;	//헤드 노드의 왼쪽 서브 트리를 NULL로 초기화
				}
				if (ptemp->left == temp) {	//ptemp노드의 왼쪽 서브 트리가 임시 노드인 경우
					ptemp->left = temp;	//ptemp노드의 왼쪽 서브 트리를 임시 노드로 초기화
				}
				else {				//ptemp노드의 오른쪽 서브 트리가 임시 노드인 경우
					ptemp->right = temp;	//ptemp노드의 오른쪽 서브 트리를 임시 노드로 초기화
				}
				free(temp);			//임시 노드의 메모리를 해제
			}
			else {		//임시 노드의 좌우 서브 트리가 비어있지 않은 경우
				printf("Node %d is not a leaf\n", temp->key);	//리프 노드가 아니라는 메시지 출력
			}
			return 1;	//함수 종료
		}
		ptemp = temp;			//ptemp노드를 임시 노드로 초기화
		if (temp->key > key) {		//임시 노드의 키값이 입력 받은 키값보다 큰 경우
			temp = temp->left;	//임시 노드를  왼쪽 서브 트리로 이동
		}
		else temp = temp->right;	//키값이 작은 경우 오른쪽 서브 트리로 이동
	}
	//모든 트리 탐색 후 입력 받은 키값을 찾지 못한 경우
	printf("Can't find the node for key %d", key);	//입력 받은 키값과 일치하는 노드를 찾지 못했다는 메시지 출력
	return 1;	//함수 종료	
}

Node* searchRecursive(Node* ptr, int key)
{
	
}

Node* searchIterative(Node* head, int key)
{
	
}

int freeBST(Node* head)
{

}
