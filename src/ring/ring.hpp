#pragma once

#include <list>
#include <vector>

namespace samurai {
    template<typename T>
    class ringnode {
    private:
        ringnode<T> *previous;
        T val;
        ringnode<T> *next;
    public:
        ringnode(T value) : val(value) {
            //this->val = value;
            this->previous = NULL;
            this->next = NULL;
        }

        void set_previous(ringnode<T> *p) { previous = p; }

        void set_next(ringnode<T> *n) { next = n; }

        ringnode<T> *get_previous() { return previous; }

        ringnode<T> *get_next() { return next; }

        T get_val() { return val; }
    };

    template<typename T>
    class ring {
    private:
        ringnode<T> *node;
        ringnode<T> *head;
    public:
        ring() {
            node = NULL;
            head = NULL;
        }
        ring(std::vector<T> data) {
            node = NULL;
            head = NULL;
            for (T d : data) {
                push(d);
            }
        }
        ring(std::list<T> data) {
            node = NULL;
            head = NULL;
            for (auto it = data.begin(); it != data.end(); ++it) {
                push(*it);
            }
        }
        ~ring() {
            while (this->pop() != NULL); //delete all nodes before destroying ring
        }

        ringnode<T> *push(T newval) {
            ringnode<T> *newnode = new ringnode<T>(newval);
            //inserting first node
            if (node == NULL) {
                newnode->set_previous(newnode);
                newnode->set_next(newnode); //node == previousnode == nextnode if only one node
                node = newnode;
                head = node;
            } else { //inserting subsequent nodes
                newnode->set_next(node->get_next());
                newnode->set_previous(node);
                node->get_next()->set_previous(newnode);
                node->set_next(newnode);
                node = newnode;
            }
            return node;
        }

        ringnode<T> *pop() { //returns pointer to next node or NULL if empty
            if (node == NULL) return NULL;
            ringnode<T> *newnode = node->get_next();

            //last node case
            if (node == newnode) {
                node->set_next(NULL);
                node->set_previous(NULL);
                delete node;
                node  = NULL;
                head = NULL;
                return NULL;
            }

            //more than 1 node in ring
            node->get_next()->set_previous(node->get_previous());
            node->get_previous()->set_next(node->get_next());
            delete node;
            node = newnode;
            return node;
        }

        ringnode<T> *get_node() { return node; }
        ringnode<T> *get_next_node() { return node->get_next(); }
        ringnode<T> *get_previous_node() { return node->get_previous(); }
        ringnode<T> *reset() { return node = head;}
        ringnode<T> *set_head() { head = node; return node; }
        ringnode<T> *set_node(ringnode<T> *n) {
            //TODO add test
            ringnode<T> *origin = node;
            while(true) {
                ringnode<T> *newnode = proceed();
                if (newnode == n) {
                    return newnode;
                }
                else if (newnode == origin) {
                    //made full loop: node isn't in ring
                    //bonus: back in original position
                    return NULL;
                }
            }

        }

        ringnode<T> *proceed() {
            if (node == NULL) {
                return NULL;
            }
            return node = node->get_next();
        }
        ringnode<T> *get_head() {
            return head;
        }

    };

}
