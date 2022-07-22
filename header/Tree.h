typedef struct nodo{
  struct nodo *right, *left;
  char c;
  int n;
} *Tree, *NodeT;

Tree newTree(){
  return NULL;
}

int isLeaf(NodeT node){
  return node->left==NULL && node->right==NULL;
}

int getValue(NodeT node){
  return node->n;
}

char getCharT(NodeT node){
  return node->c;
}

NodeT newNodeT(NodeT izq, NodeT der, int n, char c){
  NodeT node = (NodeT)malloc(sizeof(struct nodo));
  node->right = der;
  node->left = izq;
  node->c = c;
  node->n = n;
  return node;
}

Tree rightT(Tree t){
  return t->right;
}
Tree leftT(Tree t){
  return t->left;
}
