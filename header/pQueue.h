
typedef struct nodeP{
  struct nodeP *prev, *next;
  int priority;
  NodeT node;
} *NodeP;

typedef struct queueP{
  NodeP tail;
  NodeP head;
} *QueueP;

QueueP newQueueP(){
    QueueP t = (QueueP)malloc(sizeof(struct queueP));
    t->tail = NULL; t->head = NULL;
    return t;
}

int isEmpty(QueueP p){
  return p-> tail == NULL && p -> head == NULL;
}

QueueP enQueueP(QueueP p, NodeT node, int priority){
  NodeP t = (NodeP)malloc(sizeof(struct nodeP));
  t->node = node;
  t->priority = priority;

  if(isEmpty(p)){
    p->head = t; p->tail = t;
    t->next = NULL;
    t->prev = NULL;
  }else{
    while (p->head != NULL && p->head->priority <= t->priority ){
      p->head = p->head->next;
    }
    if(p->head == NULL){
      t->next = NULL;
      t->prev = p->tail;
      p->tail->next = t;
      p->tail = t;
      p->head = t;
    }else{
      t->prev = p->head->prev;
      t->next = p->head;
      if(p->head->prev != NULL)
        p->head->prev->next = t;
      p->head->prev = t;
    }
    while (p->head->prev) {
        p->head = p->head->prev;
    }
  }
  return p;
}

NodeT first(QueueP p){
    return p->head->node;
}

NodeT last(QueueP p){
  return p->tail->node;
}

QueueP deQueueP (QueueP p){
    if(p->head == p->tail)
        return newQueueP();
    else{
        p->head = p->head->next;
        p->head->prev = NULL;
      }
    return p;
}

void printpQueue(QueueP p){
  NodeP first = p->head;
  while(first){
    printf("%d[%c] ",first->priority, first->node->c );
    first = first->next;
  }

}

NodeP getHead(QueueP p){
  return p->head;
}
NodeP getTail(QueueP p){
  return p->tail;
}

int getPriority(NodeP node){
  return node->priority;
}

NodeP getNextP(NodeP p){
  return p->next;
}
char getCharP(NodeP p){
  return  p->node->c;
}
