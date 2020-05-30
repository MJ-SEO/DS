#include <stdlib.h>
#include <stdio.h>

typedef 
	struct _node_t {
		int data ;
		struct _node_t * child ; // left
		struct _node_t * sibling ; // right
	} 
	node_t ;

typedef struct _node_t tree_t ;

node_t * 
tree_create_node (int data) 
{
	node_t * root ;
	root = (node_t *) malloc(sizeof(node_t)) ;
	root->data = data ;
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
tree_search (node_t * t, int key)
{
	if (t->data == key)
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
	printf("%d\n", t->data) ;
	
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
	char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;
	char newline ;
	//scanf("%255[^\n]", s, &newline) ;

	tree_t * t ;
	t = read_a_tree(s) ;
	tree_print(t) ;

	printf("height: %d\n", tree_height(t)) ;

	tree_print(tree_search(t, 3)) ;

	return 0 ;
}
