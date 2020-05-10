#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Linkedlist */

struct node {
        void * element ;
        struct node * left ;
        struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

linkedlist_t *
linkedlist_alloc (int unit)
{
        linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
        l->left = l  ;
        l->right = l ;
        l->element = malloc(sizeof(int)) ;
        int * u = (int *) l->element ;
        *u = unit ;

        return l ;
}

void
linkedlist_free (linkedlist_t * l)
{
        node_t * curr ;
        node_t * next ;

        curr = l->right ;
        while (curr != l) {
                next = curr->right ;
                free(curr->element) ;
                free(curr) ;
                curr = next ;
        }
        free(l->element) ;
        free(l) ;
}

int
linkedlist_length (linkedlist_t * l)
{
        int len = 0 ;

        node_t * curr = l->right ;
        while (curr != l) {
                len += 1 ;
                curr = curr->right ;
        }
        return len ;
}

void
linkedlist_insert (node_t * left, void * e, int unit)
{
        node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
        _new->element = malloc(unit) ;
        memcpy(_new->element, e, unit) ;

        node_t * right = left->right ;

        _new->left = left ;
        _new->right = right ;

        left->right = _new ;
        right->left = _new ;
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
        linkedlist_insert(l, e, *((int *)(l->element))) ;
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
        linkedlist_insert(l->left, e, *((int *)(l->element))) ;
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
        if (l->left == l)
                return 1 ;

        n->left->right = n->right ;
        n->right->left = n->left ;

        free(n->element) ;
        free(n) ;
        return 0 ;
}

int
linkedlist_remove_first (linkedlist_t * l, void * e)
{
        if (l->right == l)
                return 1 ;

        memcpy(e, l->right->element, *((int *)(l->element))) ;
        linkedlist_remove(l, l->right) ;
        return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
        if (l->left == l)
                return 1 ;

        memcpy(e, l->left->element, *((int *)(l->element))) ;
        linkedlist_remove(l, l->left) ;
        return 0 ;
}

int
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
        if (pos < 0)
                return 1 ;

        int unit = *((int *) l->element) ;
        int i = 0 ;
        node_t * curr = l->right ;
        while (i < pos && curr != l) {
                curr = curr->right ;
                i += 1 ;
        }
        if (i != pos)
                return 1 ;

        memcpy(e, curr->element, unit) ;
        return 0 ;
}


linkedlist_t *
linkedlist_clone (linkedlist_t * orig)
{
 linkedlist_t *clone = linkedlist_alloc(*((int *)orig->element));

    node_t *curr = orig->right;
    while (curr != orig)
    {
        linkedlist_insert_last(clone, curr->element);
        curr = curr->right;
    }

  return clone;
}


/* Polynomial */

typedef struct term {
        int coef ;
        int expo ;
} term_t ;


typedef linkedlist_t polynomial ;

polynomial *
polynomial_alloc()
{
        return linkedlist_alloc(sizeof(term_t)) ;
}

void
polynomial_add_term(polynomial * p, term_t * n)
{
        if (n->coef == 0)
                return ;

        node_t * curr = p->right ;
        while (curr != p) {
                term_t * t = (term_t *) curr->element ;
                if (n->expo > t->expo) {
                        break ;
                }
                else if (n->expo == t->expo) {
                        t->coef += n->coef ;
                        return ;
                }
                curr = curr->right ;
        }
        linkedlist_insert(curr->left, n, sizeof(term_t)) ;
}

polynomial *
polynomial_create (char * s)
{
  polynomial * c = linkedlist_alloc(sizeof(term_t)) ;

  char* ptr = strtok(s,"+");

  while (ptr != NULL)
  {
    term_t t;
    t.coef = *(strchr(ptr, '(')+1)-48;
    t.expo = *(strchr(ptr, '^')+1)-48;
    polynomial_add_term(c, &t);
  //  printf("DEBUG %d, %d\n", t.coef, t.expo);
  //  printf("%s\n", ptr);
    ptr = strtok(NULL, "+");
  }
  return c;
}

void
polynomial_print(polynomial * p)
{
        node_t * curr ;

        curr = p->right ;
        while (curr != p) {
                term_t * t ;
                t = (term_t *) curr->element ;
                printf("(%d) x^%d", t->coef, t->expo) ;

                curr = curr->right ;
                if (curr != p)
                        printf(" + ") ;
        }
        printf("\n") ;
}

polynomial *
polynomial_add (polynomial * p1, polynomial * p2)
{
        polynomial * r = linkedlist_alloc(sizeof(term_t)) ;

        term_t t1, t2 ;
        int i1 = 0 , i2 = 0 ;

        while (i1 < linkedlist_length(p1) && i2 < linkedlist_length(p2)) {
                linkedlist_get(p1, i1, &t1) ;
                linkedlist_get(p2, i2, &t2) ;

                if (t1.expo > t2.expo) {
                        polynomial_add_term(r, &t1) ;
                        i1 += 1 ;
                }
                else if (t2.expo > t1.expo) {
                        polynomial_add_term(r, &t2) ;
                        i2 += 1 ;
                }
                else /* t1->expo == t2->expo */ {
                        term_t t ;
                        t.coef = t1.coef + t2.coef ;
                        t.expo = t1.expo ;
                        polynomial_add_term(r, &t) ;
                        i1 += 1 ;
                        i2 += 1 ;
                }
        }
        while (i1 < linkedlist_length(p1)) {
                linkedlist_get(p1, i1, &t1) ;
                polynomial_add_term(r, &t1) ;
                i1 += 1 ;
        }
        while (i2 < linkedlist_length(p2)) {
                linkedlist_get(p2, i2, &t2) ;
                polynomial_add_term(r, &t2) ;
                i2 += 1 ;
        }
        return r ;
}

polynomial *
polynomial_subt (polynomial * p1, polynomial * p2)
{
        polynomial * s = linkedlist_alloc(sizeof(term_t));

  term_t t1, t2;
  int i1 =0, i2 =0;

   while (i1 < linkedlist_length(p1) && i2 < linkedlist_length(p2)) {
                linkedlist_get(p1, i1, &t1) ;
                  linkedlist_get(p2, i2, &t2) ;

                  if (t1.expo > t2.expo) {
                          polynomial_add_term(s, &t1) ;
                          i1 += 1 ;
                  }
                  else if (t2.expo > t1.expo) {
        t2.coef = t2.coef * -1;
                        polynomial_add_term(s, &t2) ;
                          i2 += 1 ;
                  }
                  else /* t1->expo == t2->expo */ {
                        term_t t ;
                        t.coef = t1.coef - t2.coef ;
                        t.expo = t1.expo ;
                        polynomial_add_term(s, &t) ;
                        i1 += 1 ;
                        i2 += 1 ;
                }
          }
          while (i1 < linkedlist_length(p1)) {
                  linkedlist_get(p1, i1, &t1) ;
                  polynomial_add_term(s, &t1) ;
                  i1 += 1 ;
          }
          while (i2 < linkedlist_length(p2)) {
                linkedlist_get(p2, i2, &t2) ;
                polynomial_add_term(s, &t2) ;
                i2 += 1 ;
          }
          return s ;
}

polynomial *
polynomial_mult (polynomial * p1, polynomial * p2)
{
        node_t * n1, * n2 ;
        term_t * t1, * t2 ;
        polynomial * pr = linkedlist_alloc(sizeof(term_t)) ;

        for (n1 = p1->right ; n1 != p1 ; n1 = n1->right) {
                t1 = n1->element ;
                for (n2 = p2->right ; n2 != p2 ; n2 = n2->right) {
                        t2 = n2->element ;

                        term_t tr ;
                        tr.coef = t1->coef * t2->coef ;
                        tr.expo = t1->expo + t2->expo ;
                        polynomial_add_term(pr, &tr) ;
                }
        }
        return pr ;
}

void mult(term_t a, polynomial * p){

}


void
polynomial_div (polynomial * dividend, polynomial * divisor,
                            polynomial ** quotient, polynomial ** remainder)
{
        
  int dividend_coef, dividend_expo, divisor_coef, divisor_expo;
  term_t dummy;

  polynomial * for_m = linkedlist_alloc(sizeof(term_t));
  polynomial * object = linkedlist_alloc(sizeof(term_t)); 
  linkedlist_t * clone;

  object = linkedlist_clone(dividend);
  // TODO 반복문
  while(1){
    term_t compare_object;
    linkedlist_get(object, 0, &compare_object);
    dividend_coef = compare_object.coef;
    dividend_expo = compare_object.expo;
    
    term_t compare_divisor;
    linkedlist_get(divisor,0, &compare_divisor);
    divisor_coef = compare_divisor.coef;
    divisor_expo = compare_divisor.expo;

    term_t quo;
    quo.coef = divisor_coef*dividend_coef;
    quo.expo = dividend_expo-divisor_expo;
    polynomial_add_term(*quotient, &quo);

    polynomial_add_term(for_m, &quo);
    if(linkedlist_length(for_m)>1){
      linkedlist_remove_first(for_m, &dummy);
    }
    clone = polynomial_mult(for_m, divisor);
    object = polynomial_subt(dividend, clone);
    
    term_t out;
    linkedlist_get(object, 0, &out);

    if(divisor_expo>out.expo){
      break;
    }
  }

  *remainder = linkedlist_clone(object);
  // 반복문 끝나고 남은 new_ploynomial을 remainder에 넣기.
}

int
main ()
{
        polynomial * clone;
        polynomial * sub;
        polynomial * dividend;
        polynomial * m;
        term_t dummy;

        char buf[256];
        char newline;
        printf("----------입력받기----------\n");
        scanf("%255[^\n]", buf);
        scanf("%c", &newline);
        dividend = polynomial_create(buf);
        polynomial_print(dividend);

        clone = linkedlist_clone(dividend);
        printf("first clone:");
        polynomial_print(clone);

        term_t t;
        linkedlist_get(dividend,0,&t);

        printf("%d, %d", t.coef, t.expo);
        printf("\n");

        polynomial * c;
        c = linkedlist_alloc(sizeof(term_t)) ;

        polynomial_add_term(c, &t);

        m = polynomial_mult(c, dividend);
        printf("Multi 1: ");
        polynomial_print(m);
        printf("c의 길이는: %d \n", linkedlist_length(c));

        linkedlist_get(dividend,1,&t);
        polynomial_add_term(c, &t);
        printf("c의 길이는: %d \n", linkedlist_length(c));

        linkedlist_remove_first(c, &dummy);
        
         printf("c의 길이는: %d \n", linkedlist_length(c));
        m = polynomial_mult(c, dividend);
        printf("Multi 2: ");
        polynomial_print(m);
        
        clone = linkedlist_clone(m);
        printf("second clone:");
        polynomial_print(clone);


  /*      linkedlist_t * c;
  
        c = linkedlist_clone(dividend);

        polynomial_print(c);
*/


}

