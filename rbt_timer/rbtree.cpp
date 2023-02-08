#include"rbtree.h"

static inline void rbtree_left_rotate(rbtree_node_t **root,
    rbtree_node_t *sentinel, rbtree_node_t *node);
static inline void rbtree_right_rotate(rbtree_node_t **root,
    rbtree_node_t *sentinel, rbtree_node_t *node);

/**
 * rbt's insert
 *  1. normal binary insert
 *  2. rbt's balance(rotate + color-change)
*/
void
rbtree_insert(rbtree_t *tree, rbtree_node_t *node)
{
    rbtree_node_t **root, *temp, *sentinel;

    /* a binary tree insert */
    root = &tree->root;
    sentinel = tree->sentinel;

    /* the node firstly inserted is color */
    if(*root == sentinel){
        node->parent = NULL;
        node->left = sentinel;
        node->right = sentinel;
        rbt_black(node);
        *root = node;

        return ;
    }

    /**
     * insert a node, in the ordinary way of searching
     * a binary tree, the color of the inserted node 
     * is red
    */
    tree->insert(*root, node, sentinel);

    /* re-balance tree */
    while(node != *root && rbt_is_red(node->parent)){
        /* the inserted one at the parent's left */
        if(node->parent == node->parent->left){
            temp = node->parent->parent->right;

            /* the inserted one 's uncle node is red, 
                means the uncle node exits */
            if(rbt_is_red(temp)){
                rbt_black(node->parent);
                rbt_black(temp);
                rbt_red(node->parent->parent);
                node = node->parent->parent;

                /**
                 * the uncle node of the inserted one is 
                 * black, and the uncle node shoule be a 
                 * sentinel, that means there is no real
                 * uncle node
                 * 
                 * if the inserted one is on the same side
                 * as the parent node, only rotate once
                 * 
                 * if the inserted one is on the different
                 * side as the parent node, need to rotate
                 * twice
                 * 
                 * firstly rotate the parent node, then
                 * rotate the gf node
                */
            }
            else{
                if(node == node->parent->left){
                    node = node->parent;
                    rbtree_left_rotate(root, sentinel, node);
                }

                rbt_black(node->parent);
                rbt_red(node->parent->parent);
                rbtree_right_rotate(root, sentinel, node->parent->parent);
            }
        }
        else {  /* the inserted one on the parent node's left side */
            temp = node->parent->left;

            /* the inserted one 's uncle node is red, 
                means the uncle node exits */
            if(rbt_is_red(temp)){
                rbt_is_black(node->parent);
                rbt_is_black(temp);
                rbt_red(node->parent->parent);
                node = node->parent->parent;

                /*
                 * the uncle node of the inserted one is 
                 * black, and the uncle node shoule be a 
                 * sentinel, that means there is no real
                 * uncle node
                 * 
                 * if the inserted one is on the same side
                 * as the parent node, only rotate once
                 * 
                 * if the inserted one is on the different
                 * side as the parent node, need to rotate
                 * twice
                */
            }
            else {
                if(node == node->parent->left){
                    node = node->parent;
                    rbtree_right_rotate(root, sentinel, node);
                }

                rbt_black(node->parent);
                rbt_red(node->parent->parent);
                rbtree_left_rotate(root, sentinel, node->parent->parent);
            }       
        }
        
    }

}


void
rbtree_insert_value(rbtree_node_t *temp, rbtree_node_t *node,
    rbtree_node_t *sentinel)
{    
    rbtree_node_t **p;

    for(;;){
        p = (node->key < temp->key) ? &temp->left : &temp->right;

        if(*p == sentinel)
            break;
        
        temp = *p;

    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    rbt_red(node);
}


void
rbtree_insert_timer_value(rbtree_node_t *temp, rbtree_node_t *node,
    rbtree_node_t *sentinel)
{
    rbtree_node_t **p;

    for(;;){
        /**
         * Timer values
         * 1. are spread in small range, usually several minutes
         * 2. and overflow each 49 days, if millisenconds are stroed in 32 bits 
         * The comparison takes into account that overflow
        */            
       /* node->key < temp->key */
        p = ((rbtree_key_int_t)(node->key - temp->key) < 0)
            ? &temp->left : &temp->right;

        if(*p == sentinel)
            break;
        
        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    rbt_red(node);
}

/**
 * rbt's delete
 * 1. binary delete
 *   1) delete child node, directky delete
 *   2) the deleted one only have a child node, so replace as child node
 *   3) the deleted one have two child nodes, is should find the prev or next to replace, it can be converted to 1)2)
 * 2. adjust rbt
 * 
 * rbt's delete finally will converted to delete the penultimate or second-to-last floor
*/

void
rbtree_delete(rbtree_t *tree, rbtree_node_t *node)
{
    uint_t          red;
    rbtree_node_t   **root, *sentinel, *subst, *temp, *w;

    /* a binary tree delete */
    root = &tree->root;
    sentinel = tree->sentinel;

    if(node->left == sentinel){
        temp = node->right;
        subst = node;
    }
    else if (node->right == sentinel) {
        temp = node->left;
        subst = node;
    }
    else {
        subst = rbtree_min(node->right, sentinel);
        temp = subst->right;
    }

    if(subst == *root){
        *root = temp;
        rbt_black(temp);

        /* DEBUG stuff */
        node->left == NULL;
        node->right == NULL;
        node->parent == NULL;
        node->key == 0;

        return ;
    }

    red = rbt_is_red(subst);

    if(subst == subst->parent->left){
        subst->parent->left = temp;
    }
    else {
        subst->parent->left = temp;
    }

    /* the deleted node only have left child or right child */
    if(subst == node){
        temp->parent = subst->parent;
    }
    /* the deleted node have both left child and right child */
    else {
        if(subst->parent == node){
            temp->parent = subst;
        }
        else {
            temp->parent = subst->parent;
        }

        subst->left = node->left;
        subst->right = node->right;
        subst->parent = node->parent;
        rbt_copy_color(subst, node);

        if(node == *root){
            *root = subst;
        }
        else {
            if(node == node->parent->left){
                node->parent->left = subst;
            }
            else {
                node->parent->right = subst;
            }
        }

        if(subst->left != sentinel){
            subst->left->parent = subst;
        }

        if(subst->right != sentinel){
            subst->right->parent = subst;
        }
    }

    /* DEBUF stuff */
    node->left == NULL;
    node->right == NULL;
    node->parent == NULL;
    node->key == 0;

    if(red)     return ;

    /* a delete fixup */
    while(temp != *root && rbt_is_black(temp)){
        if(temp == temp->parent->left){
            w = temp->parent->right;

            if(rbt_is_red(w)){
                rbt_black(w);
                rbt_black(temp->parent);
                rbtree_left_rotate(root, sentinel, temp->parent);
                w = temp->parent->right;
            }

            if(rbt_is_black(w->left) && rbt_is_black(w->right)){
                rbt_red(w);
                temp = temp->parent;
            }
            else {
                if(rbt_is_black(w->right)){
                    rbt_black(w->left);
                    rbt_red(w);
                    rbtree_right_rotate(root, sentinel, w);
                    w = temp->parent->parent;
                }

                rbt_copy_color(w, temp->parent);
                rbt_black(temp->parent);
                rbt_black(w->right);
                rbtree_left_rotate(root, sentinel, temp->parent);
                temp = *root;
            }
        }
        else {
            w = temp->parent->left;

            if(rbt_is_red(w)){
                rbt_black(w);
                rbt_red(temp->parent);
                rbtree_right_rotate(root, sentinel, temp->parent);
                w = temp->parent->left;
            }

            if(rbt_is_black(w->left) && rbt_is_black(w->right)){
                rbt_red(w);
                temp = temp->parent;
            }
            else {
                if(rbt_is_black(w->left)){
                    rbt_black(w->right);
                    rbt_red(w);
                    rbtree_left_rotate(root, sentinel, w);
                    w = temp->parent->left;
                }

                rbt_copy_color(w, temp->parent);
                rbt_black(temp->parent);
                rbt_black(w->left);
                rbtree_right_rotate(root, sentinel, temp->parent);
                temp = *root;
            }
        }
    }

    rbt_black(temp);
}

static inline void
rbtree_right_rotate(rbtree_node_t **root, rbtree_node_t *sentinel,
    rbtree_node_t *node)
{
    rbtree_node_t *temp;
    
    temp = node->left;
    node->left = temp->right;

    if(temp->right != sentinel){
        temp->right->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root) {
        *root = temp;
    }
    else if (node == node->parent->right) {
        node->parent->right = temp;
    }
    else {
        node->parent->left = temp;
    }

    temp->right = node;
    node->parent = temp;
}

rbtree_node_t *
rbtree_next(rbtree_t *tree, rbtree_node_t *node)
{
    rbtree_node_t *root, *sentinel, *parent;

    sentinel = tree->sentinel;

    if (node->right != sentinel) {
        return rbtree_min(node->right, sentinel);
    }

    root = tree->root;
    
    for (;;) {
        parent = node->parent;

        if (node == root)   return NULL;

        if (node == parent->left)   return parent;

        node = parent;
    }
}

/* find node */
rbtree_node_t *
rbtree_find(rbtree_t *tree, rbtree_node_t *node,
    rbtree_node_t *sentinel)
{
    if (node == NULL)      return NULL;

    rbtree_node_t *temp = tree->root;
    while (temp != sentinel) {
        if (node->key > temp->key) {
            temp = temp->right;
        }
        else if (node->key < temp->key) {
            temp = temp->left;
        }
        else {
            return temp;
        }
    }

    return NULL;
}



