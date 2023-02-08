#ifndef _RBTREE_H_
#define _RETREE_H_

#include<stdint.h>
#include<stdio.h>

typedef intptr_t    int_t;
typedef uintptr_t   uint_t;
typedef intptr_t    flag_t;

typedef uint_t      rbtree_key_t;
typedef int_t       rbtree_key_int_t;

typedef unsigned char u_char;

typedef struct rbtree_node_s rbtree_node_t;

/* rbt's node */
struct rbtree_node_s {
    rbtree_key_t    key;
    rbtree_node_t   *left;
    rbtree_node_t   *right;
    rbtree_node_t   *parent;
    u_char          color;
    u_char          data;
};

typedef struct rbtree_s rbtree_t;

/* define node-insert's ptr */
typedef void (*rbtree_insert_pt) (rbtree_node_t *root,
    rbtree_node_t *node, rbtree_node_t *sentinel);

/* rbt's struct */
struct rbtree_s {
    rbtree_node_t       *root;
    rbtree_node_t       *sentinel;
    rbtree_insert_pt    insert; 
};

#define rbtree_init(tree, s, i)     \
    rbtree_sentinel_init(s);        \
    (tree)->root = s;               \
    (tree)->sentinel = s;           \
    (tree)->insert = i

/**
 * insert node to rbt, the method will
 * rotate rbt and change the color of
 * nodes to keep the balance of rbt
*/
void rbtree_insert(rbtree_t *tree, rbtree_node_t *node);

/**
 * delete node from rbt, the method will
 * rotate rbt and change the color of
 * nodes to keep the balance of rbt 
*/
void rbtree_delete(rbtree_t *tree, rbtree_node_t *node);

void rbtree_insert_value(rbtree_node_t *root,
    rbtree_node_t *node, rbtree_node_t *sentinel);
void rbtree_insert_timer_value(rbtree_node_t *root,
    rbtree_node_t *node, rbtree_node_t *sentinel);

rbtree_node_t *rbtree_next(rbtree_t *tree, 
    rbtree_node_t *node);

rbtree_node_t *rbtree_find(rbtree_t *tree, 
    rbtree_node_t *node, rbtree_node_t *sentinel);

#define rbt_red(node)           ((node)->color = 1)
#define rbt_black(node)         ((node)->color = 0)
#define rbt_is_red(node)        ((node)->color)
#define rbt_is_black(node)      (!rbt_is_red(node))
#define rbt_copy_color(n1,n2)   (n1->color = n2->color)

/* sentinel must be black */
#define rbtree_sentinel_init(node) rbt_black(node)

/* get the smallest key in rbt */
static inline rbtree_node_t *
rbtree_min(rbtree_node_t *node, rbtree_node_t *sentinel){
    if(node == NULL || node == sentinel){
        return NULL;
    }

    while (node->left != sentinel)
    {
        node = node->left;
    }

    return node;
    
}

#endif /* _RBTREE_H_ */
