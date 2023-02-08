#include<sys/time.h>
#include<stack>
#include"rbtree.h"
#include"timer_common.h"

template <typename _User_Data>
struct timer_rbtree_node {
    rbtree_node_t node;
    Timer<_User_Data> timer;
};  

template <typename _UData>
class RBTreeTimerContainer : public ITmerContainer<_UData>
{
public:
    RBTreeTimerContainer();
    ~RBTreeTimerContainer();

public:
    void tick() override;
    Timer<_UData> *addTimer(time_t timeout) override;
    void delTimer(Timer<_UData> *timer)  override;
    void resetTimer(Timer<_UData> *timer, time_t timeout) override;
    int getMinExpire() override;
    Timer<_UData> *top();
    void popTimer();

private:
    rbtree_t rbtree;  /* rbt */
    rbtree_node_t sentinel;  /* rbt's sentinel node */
};

template <typename _UData>
RBTreeTimerContainer<_UData> :: 
RBTreeTimerContainer() {
    /* init rbt */
    rbtree_init(&this->rbtree, &this->sentinel, rbtree_insert_value);
}

template <typename _UData>
RBTreeTimerContainer<_UData> ::
~RBTreeTimerContainer() {
    /* traverse the rbt tree to remove nodes */
    if (rbtree.root == &this->sentinel)     return ;

    /* rbt is not null */
    rbtree_node_t *p = rbtree.root;
    std::stack<rbtree_node_t *> s;

    while (!s.empty() || p != &this->sentinel){
        
        if (p != &this->sentinel) {
            s.push(p);
            p = p->left;
        }
        else {
            p = s.top();
            s.pop();
            /* delete node */
            timer_rbtree_node<_UData> *node = reinterpret_cast< timer_rbtree_node<_UData> *> (p);
            
            if (node) {
                delete node;
            }

            p = p->right;

        }
    }
}

template <typename _UData>
void RBTreeTimerContainer<_UData> ::
tick() {
    /**
     * find the timer with the minimum timeout value, then
     * determine whether it times out, if it times out 
     * execute the callback function and delete the timer.
     * Continue the above ops until there is no timeout timer.
    */

    /* get the current time */
    time_t cur_time = getMSec();
    /* if there is not node in rbt, diretly return */
    if (rbtree.root == rbtree.sentinel) {
        return ;
    }

    auto node = rbtree_min(this->rbtree.root, &this->sentinel);
    timer_rbtree_node<_UData> *timer = reinterpret_cast<timer_rbtree_node<_UData> *>(node);

    while (timer && timer->timer.getExpire() < cur_time){
        /* run cb_func */
        timer->timer.handleTimeOut();

        /* delete timer */
        popTimer();

        node = rbtree_min(this->rbtree.root, &this->sentinel);
        timer = reinterpret_cast<timer_rbtree_node<_UData> *>(node);

    }
}

template <typename _UData>
Timer<_UData> *RBTreeTimerContainer<_UData> ::
addTimer(time_t timeout)
{
    /* create a node */
    timer_rbtree_node<_UData> *node = new timer_rbtree_node<_UData>;
    node->timer.setTimeout(timeout);
    node->node.key = node->timer.getExpire();

    /* insert node */
    rbtree_insert(&this->rbtree, &node->node);

    return &node->timer;

}

template <typename _UData>
void RBTreeTimerContainer<_UData> ::
delTimer(Timer<_UData> *timer)
{
    if (timer == nullptr) {
        return ;
    }

    /* fouce convert type */
    timer_rbtree_node<_UData> *temp = reinterpret_cast< timer_rbtree_node<_UData> *>
                                        (reinterpret_cast<u_char *>(timer) - sizeof(rbtree_node_t) );
    if (temp == nullptr) {
        return ;
    }

    /* delete node from rbt */
    rbtree_delete(&this->rbtree, *temp->node);

    /* delete date */
    delete temp;
}

template <typename _UData>
void RBTreeTimerContainer<_UData> ::
resetTimer(Timer<_UData> * timer, time_t timeout)
{
    if (timer == nullptr) {
        return ;
    }

    /* fouce convert type */
    timer_rbtree_node<_UData> *temp = reinterpret_cast<timer_rbtree_node<_UData> *>
                                        (reinterpret_cast<u_char >(timer) - sizeof(rbtree_node_t) );
    if (temp == nullptr) {
        return ;
    }

    /* delete node from rbt */ 
    rbtree_delete(&this->rbtree, &temp->node);

    /* reset date and insert into rbt */
    temp->timer.setTimeout(timeout);
    rbtree_insert(&this->rbtree, &temp->node);

}

/**
 * gets the absolute time with the minimum timeout 
 * value in timer container
*/
template <typename _UData>
int RBTreeTimerContainer<_UData> ::
getMinExpire()
{
    Timer<_UData> *temp = top();
    if (temp) {
        return temp->getExpire();
    }

    return -1;
}

/* get the timer with minimum timeout value */
template <typename _UData>
Timer<_UData> *RBTreeTimerContainer<_UData> ::
top()
{
    if (rbtree.root == rbtree.sentinel) {
        return nullptr;
    }

    auto res = rbtree_min(this0>rbtree.root, &this->sentinel);

    /* fouce convert type */
    timer_rbtree_node<_UData> *node = reinterpret_cast<timer_rbtree_node <_UData> *>(res);

    return node ? &node->timer : nullptr;
}

template <typename _UData>
void RBTreeTimerContainer<_UData> ::
popTimer()
{
    /* get the timer with minimum timeout value */
    auto min_timer = top();

    /* delete timer */
    delTimer(min_timer);
}