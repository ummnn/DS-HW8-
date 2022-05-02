/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */


/* �ʿ��� ������� �߰� */
#include<stdio.h>
#include<stdlib.h>

/* Node ����ü */
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{

    printf("[----- [�̵���] [2019038027] -----]\n\n");
	char command;
	int key;
	listNode* headnode=NULL; //headnode �ʱ�ȭ

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		    case 'z': case 'Z': //case�� z�� Z�� ���
			    initialize(&headnode); //initialize�Լ� ����
			    break;
		    case 'p': case 'P': //case�� p�� P�� ���
			    printList(headnode); //printlist�Լ� ����
			    break;
		    case 'i': case 'I':  //case�� i�� I�� ���
			    printf("Your Key = ");
			    scanf("%d", &key); //key�� �Է¹޴´�
			    insertNode(headnode, key); //insertNode�Լ� ����
			    break;
		    case 'd': case 'D':  //case�� d�� D�� ���
			    printf("Your Key = ");
			    scanf("%d", &key); //key�� �Է¹޴´�
			    deleteNode(headnode, key); //deleteNode�Լ� ����
			    break;
            case 'n': case 'N':  //case�� n�� N�� ���
                printf("Your Key = ");
                scanf("%d", &key); //key�� �Է¹޴´�
                insertLast(headnode, key); //insertLast�Լ� ����
                break;
            case 'e': case 'E': //case�� e�� E�� ���
                deleteLast(headnode); //deleteLast�Լ� ����
                break;
            case 'f': case 'F': //case�� f�� F�� ���
                printf("Your Key = ");
                scanf("%d", &key); //key�� �Է¹޴´�
                insertFirst(headnode, key); //insertfirst�Լ� ����
                break;
            case 't': case 'T': //case�� t�� T�� ���
                deleteFirst(headnode); //deleteFirst�Լ� ����
                break;
            case 'r': case 'R': //case�� r�� R�� ���
                invertList(headnode); //invertList �Լ� ����
                break;
            case 'q': case 'Q': //case�� q�� Q�� ���
                freeList(headnode); //freeList�Լ� ����
                break;
            default: //�߸��� �Է��� ������ ���
                printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //concentration�޽��� ���
                break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� �Էµɶ����� �ݺ�

	return 1;
}

int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode)); //listNode�� �����ŭ �޸� �Ҵ�
	(*h)->rlink = *h; 
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

//�޸����� �Լ�
int freeList(listNode* h){

    
	if(h->rlink == h) //h�� rlink�� h�� ���ٸ�
	{
		free(h); //h �޸� ����
		return 1;
	}

	listNode* p = h->rlink; //p�� h�� rlink����

	listNode* prev = NULL; //prev NULL�� �ʱ�ȭ
	while(p != NULL && p != h) { //p�� NULL�̰ų� p�� h�϶����� �ݺ�
		prev = p; //prev�� p ����
		p = p->rlink; //p�� p�� rlink����
		free(prev); //prev �޸� ����
	}
	free(h); //h �޸� ����
	return 0;
}

//����Ʈ �Լ�
void printList(listNode* h) {
	int i = 0;
	listNode* p; //p����

	printf("\n---PRINT\n");

	if(h == NULL) { //����尡 ����ٸ�
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //p�� h�� rlink����

	while(p != NULL && p != h) { //p�� NULL�̰ų� h�ϋ����� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //p�� p�� rlink����
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; //p�� h�� rlink����
	while(p != NULL && p != h) { //p�� NULL�̰ų� h�ϋ����� �ݺ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //p�� p�� rlink ����
		i++;
	}

}



/*
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; //����尡 ����ִٸ� -1��ȯ

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode�� �����ŭ �޸� �Ҵ�
	node->key = key; //node�� key�� key����
	node->rlink = NULL; //node�� rlink�ʱ�ȭ
	node->llink = NULL; //node�� llink�ʱ�ȭ

	if (h->rlink == h) /* ù ���� ���� */
	{
		h->rlink = node; //h�� rlink�� node ����
		h->llink = node; //h�� llink�� node ����
		node->rlink = h; //node�� rlink�� h����
		node->llink = h; //node�� llink�� h����
	} else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h; 
	}

	return 1;
}

/*
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //h�� link�� h�ų� h�� ���������
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //nodetoremove�� h�� llink����

	/* link ���� */
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove); //nodetoremove �޸� ����

	return 1;
}


/*
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸� �Ҵ�
	node->key = key; //node�� key�� key����
	node->rlink = NULL; //rlink �ʱ�ȭ
	node->llink = NULL; //llink �ʱ�ȭ

    //head������ ��� �߰�
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}

/*
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) //h�� ����ų� h�� rlink�� h�϶�
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //nodetoremove�� h�� rlink����

	/* link ���� */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove); //nodetoremove ����

	return 1;

}


/*
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //h�� rlink�� h�� ����Ű�ų� h�� �������
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink; //n�� h�� rlink����
	listNode *trail = h; //trail�� h����
	listNode *middle = h; //middle�� h����

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;

	while(n != NULL && n != h){ //n�� NULL�̰ų� n�� h�ϋ����� �ݺ�
		trail = middle; //trail�� middle ����
		middle = n; //middle�� n����
		n = n->rlink; //n�� n�� rlink����
		middle->rlink = trail; //middle�� rlink�� trail ����
		middle->llink = n; //middle�� llink�� n����
	}

	h->rlink = middle; //h�� rlink�� middle����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //h�� NULL�̶�� -1����

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸� �Ҵ�
	node->key = key; //node�� key�� key����
	node->llink = node->rlink = NULL; //node�� llink�� node�� rlink ����

	if (h->rlink == h) //h�� rlink�� h���
	{
		insertFirst(h, key); //insertFirst�Լ� ����
		return 1;
	}

	listNode* n = h->rlink; //n�� h�� rlink����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key); //insertLast�Լ� ����
	return 0;
}


/*
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) //h�� rlink�� h�ų� h�� NULL�� ��
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //n�� h�� rlink����

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); //n�޸� ����
			}
			return 0;
		}

		n = n->rlink; //n�� n��rlink ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


