#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef 
	struct _node_t {
		char* data ;
		struct _node_t * child ; // left
		struct _node_t * sibling ; // right
	} 
	node_t ;

typedef struct _node_t tree_t ;

node_t * 
tree_create_node (char* data) 
{
	node_t * root ;
	root = (node_t *) malloc(sizeof(node_t)) ;
	root->data = (char*) malloc(sizeof(char)*64);
	strcpy(root->data, data);
	root->child = 0x0 ;
	root->sibling = 0x0 ; 
	return root ;
}

node_t *
tree_add_child (node_t * parent, node_t * child)
{
	if (parent->child == 0x0) {
		parent->child = child ;
	}
	else {
		node_t * curr ;
		for (curr = parent->child ; curr->sibling != 0x0 ; curr = curr->sibling) ;
		// curr->sibling == 0x0  
		curr->sibling = child ;

	}
	return parent ;
}

int
tree_height(tree_t * t) 
{
	int max = 0 ; 
	node_t * c ;
	for (c = t->child ; c != 0x0 ; c = c->sibling) {
		int h = tree_height(c) ;
		max = (max < h) ? h : max ;
	}
	return max + 1 ;
}

node_t *
tree_search (node_t * t, char* key)
{
	if (strcmp(t->data,key))
		return t ;

	for (node_t * i = t->child ; i != 0x0 ; i = i->sibling) {
		node_t * r ;
		r = tree_search(i, key) ;
		if (r != 0x0) 
			return r ;		
	}

	return 0x0 ;
}

void
_tree_print (node_t * t, int level)
{
	for (int i = 0 ; i < level ; i++)
		printf("  ") ;

	if(level>0)
		printf("+--");

	printf("%s\n", t->data) ;
	
	node_t * curr ;
	for (curr = t->child ; curr != 0x0 ; curr = curr->sibling) 
		_tree_print(curr, level + 1) ;
}

void
tree_print (tree_t * t)
{
	_tree_print(t, 0) ;
}


tree_t *
read_a_tree(char *s)
{
	char * begin, * end, * sub ;
	int n ;
	int data ;	

	data = atoi(s) ;
	node_t * t = tree_create_node(data) ;

	for (begin = s + 1 ; *begin != '(' && *begin != ')' && *begin != ',' ; begin++) ;
	if (*begin == ')' || *begin == ',') 
		return t ;

	// *begin == '('
	sub = begin + 1 ;
	for (end = begin + 1, n = 0 ; n > 0 || *end != ')' ; end++) {
		if (*end == '(') {
			n++ ;
		}
		if (*end == ')') {
			n-- ;
		}
		if (n == 0 && *end == ',') {
			tree_add_child(t, read_a_tree(sub)) ;
			sub = end + 1 ;
		}
	}
	tree_add_child(t, read_a_tree(sub)) ;

	return t ;
}

int
main ()
{
    tree_t *t[100] = {0};
    char store[100][64];

    int man, rel;
    char s1[64];
    char s2[64];
    int n=0;

    int child[100] = {0};

//    printf("사람 수, 관계 수: ");
    scanf("%d %d", &man, &rel);
//    printf("DEBUG: man: %d rel: %d\n", man, rel);

    for (int i = 0; i < rel; i++){
//	printf("스승, 제자:");
        scanf("%s %s", s1, s2);
        int a = 0, b = 0;
        tree_t *t1;
        tree_t *t2;
        for (a = 0; a < n; a++) {
            if (strcmp(store[a], s1) == 0)
                break;
        }
        
	if (a >= n){
            t1 = tree_create_node(s1);
            strcpy(store[a], s1);
            t[a] = t1;
            n++;
        }
        else{
            t1 = t[a];
        }

	for (b = 0; b < n; b++){
            if (strcmp(store[b], s2) == 0)
                break;
        }
        
	if (b >= n){
            t2 = tree_create_node(s2);
            strcpy(store[b], s2);
            t[b] = t2;
            n++;
        }
        else{
            t2 = t[b];
	}

    	    child[b] = 1;
            tree_add_child(t1, t2);
   
    }


    for (int i = 0; i < man; i++){
        if (!child[i])
            tree_print(t[i]);
    }

return 0 ;
}
/*
	tree_t * t ;
	t = tree_create_node("mj");


		printf("입력: ");
		scanf("%s", s);
		printf("DEBUG: %s\n", s);
		node_t* e = tree_create_node(s); 
		tree_add_child(t,e);	

		printf("입력: ");
		scanf("%s", s2);
		printf("DEBUG: %s\n", s2);
		node_t* d = tree_create_node(s2); 
		tree_add_child(e,d);	
*/

