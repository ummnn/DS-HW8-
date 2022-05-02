/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */


/* 필요한 헤더파일 추가 */
#include<stdio.h>
#include<stdlib.h>

/* Node 구조체 */
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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

    printf("[----- [이동현] [2019038027] -----]\n\n");
	char command;
	int key;
	listNode* headnode=NULL; //headnode 초기화

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
		    case 'z': case 'Z': //case가 z나 Z인 경우
			    initialize(&headnode); //initialize함수 실행
			    break;
		    case 'p': case 'P': //case가 p나 P인 경우
			    printList(headnode); //printlist함수 실행
			    break;
		    case 'i': case 'I':  //case가 i나 I인 경우
			    printf("Your Key = ");
			    scanf("%d", &key); //key를 입력받는다
			    insertNode(headnode, key); //insertNode함수 실행
			    break;
		    case 'd': case 'D':  //case가 d나 D인 경우
			    printf("Your Key = ");
			    scanf("%d", &key); //key를 입력받는다
			    deleteNode(headnode, key); //deleteNode함수 실행
			    break;
            case 'n': case 'N':  //case가 n나 N인 경우
                printf("Your Key = ");
                scanf("%d", &key); //key를 입력받는다
                insertLast(headnode, key); //insertLast함수 실행
                break;
            case 'e': case 'E': //case가 e나 E인 경우
                deleteLast(headnode); //deleteLast함수 실행
                break;
            case 'f': case 'F': //case가 f나 F인 경우
                printf("Your Key = ");
                scanf("%d", &key); //key를 입력받는다
                insertFirst(headnode, key); //insertfirst함수 실행
                break;
            case 't': case 'T': //case가 t나 T인 경우
                deleteFirst(headnode); //deleteFirst함수 실행
                break;
            case 'r': case 'R': //case가 r나 R인 경우
                invertList(headnode); //invertList 함수 실행
                break;
            case 'q': case 'Q': //case가 q나 Q인 경우
                freeList(headnode); //freeList함수 실행
                break;
            default: //잘못된 입력이 들어왔을 경우
                printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //concentration메시지 출력
                break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //listNode의 사이즈만큼 메모리 할당
	(*h)->rlink = *h; 
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

//메모리해제 함수
int freeList(listNode* h){

    
	if(h->rlink == h) //h의 rlink가 h와 같다면
	{
		free(h); //h 메모리 해제
		return 1;
	}

	listNode* p = h->rlink; //p에 h의 rlink저장

	listNode* prev = NULL; //prev NULL로 초기화
	while(p != NULL && p != h) { //p가 NULL이거나 p가 h일때까지 반복
		prev = p; //prev에 p 저장
		p = p->rlink; //p에 p의 rlink저장
		free(prev); //prev 메모리 해제
	}
	free(h); //h 메모리 해제
	return 0;
}

//프린트 함수
void printList(listNode* h) {
	int i = 0;
	listNode* p; //p선언

	printf("\n---PRINT\n");

	if(h == NULL) { //헤드노드가 비었다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //p에 h의 rlink저장

	while(p != NULL && p != h) { //p가 NULL이거나 h일떄까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //p에 p의 rlink저장
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; //p에 h의 rlink저장
	while(p != NULL && p != h) { //p가 NULL이거나 h일떄까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //p에 p의 rlink 저장
		i++;
	}

}



/*
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; //헤드노드가 비어있다면 -1반환

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode의 사이즈만큼 메모리 할당
	node->key = key; //node의 key에 key저장
	node->rlink = NULL; //node의 rlink초기화
	node->llink = NULL; //node의 llink초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; //h의 rlink에 node 저장
		h->llink = node; //h의 llink에 node 저장
		node->rlink = h; //node의 rlink에 h저장
		node->llink = h; //node의 llink에 h저장
	} else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h; 
	}

	return 1;
}

/*
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //h의 link가 h거나 h가 비어있을때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //nodetoremove에 h의 llink저장

	/* link 정리 */
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove); //nodetoremove 메모리 해제

	return 1;
}


/*
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key에 key저장
	node->rlink = NULL; //rlink 초기화
	node->llink = NULL; //llink 초기화

    //head다음에 노드 추가
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}

/*
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) //h가 비었거나 h의 rlink가 h일때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //nodetoremove에 h의 rlink저장

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove); //nodetoremove 해제

	return 1;

}


/*
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //h의 rlink가 h를 가리키거나 h가 비었을때
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink; //n에 h의 rlink저장
	listNode *trail = h; //trail에 h저장
	listNode *middle = h; //middle에 h저장

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){ //n이 NULL이거나 n이 h일떄까지 반복
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n저장
		n = n->rlink; //n에 n의 rlink저장
		middle->rlink = trail; //middle의 rlink에 trail 저장
		middle->llink = n; //middle의 llink에 n저장
	}

	h->rlink = middle; //h의 rlink에 middle저장

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //h가 NULL이라면 -1리턴

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key에 key저장
	node->llink = node->rlink = NULL; //node의 llink에 node의 rlink 저장

	if (h->rlink == h) //h의 rlink가 h라면
	{
		insertFirst(h, key); //insertFirst함수 실행
		return 1;
	}

	listNode* n = h->rlink; //n에 h의 rlink저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //insertLast함수 실행
	return 0;
}


/*
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) //h의 rlink가 h거나 h가 NULL일 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //n에 h의 rlink저장

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); //n메모리 해제
			}
			return 0;
		}

		n = n->rlink; //n에 n의rlink 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


