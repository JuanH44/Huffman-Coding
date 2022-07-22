typedef struct nodeL{
  struct nodeL *next;
  char c;
  int n;
} *NodeL,*List;

typedef struct queue{
  NodeL head;
  NodeL tail;
} *Queue;

List newList(){
  return NULL;
}

Queue newQueue(){
  Queue q = (Queue)malloc(sizeof(struct queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

int isNewQueue(Queue q){
  return q->head == NULL && q->tail == NULL;
}

Queue enQueue(Queue q, char c){
  NodeL node = (NodeL)malloc(sizeof(struct nodeL));
  node->next = NULL;
  node->c = c;
  node->n = 1;

  if(isNewQueue(q)){
    q->head = node;
    q->tail = node;
  }else{
    q->tail->next = node;
    q->tail = node;
  }
  return q;
}

List toList(Queue q){
  return q->head;
}

char getChar(NodeL node){
  return node->c;
}

NodeL getNext(NodeL node){
  return node->next;
}

int getCounter(NodeL node){
  return node->n;
}

void setCounter(NodeL node, int n){
  node->n = n;
}

void printList(List lista){
  while (lista) {
    printf("\n\t%d[%c] ", lista->n,lista->c);
    lista = lista->next;
  }
  return;
}
