#pragma once

namespace samurai {
  template<typename T>
  class ringnode {
  private:
    ringnode<T>& previous;
    T val;
    ringnode<T>& next;
  public:
    ringnode(T val) {
      val = val;
      previous = NULL;
      next = NULL;
    }
    void set_previous(ringnode<T>& p) {previous = p;}
    void set_next(ringnode<T>& n) {next = n;}
    ringnode<T>& get_previous() {return previous;}
    ringnode<T>& get_next() {return next;}
    T get_val() {return val;}
  };
  template<typename T>
  class ring {
  private:
    ringnode<T>& node;
    ringnode<T>& head;
  public:
    ring() {
      node = NULL;
      head = NULL;
    }
    void add(T newval) {
      ringnode<T>& newnode = new ringnode<T>(newval);
      if (node == NULL) {
        newnode->set_previous(newnode);
        newnode->set_next(newnode);
        node = newnode;
      } else {
        newnode->set_next(node->get_next());
        newnode->set_previous(node);
        node->get_next()->set_previous(newnode);
        node->set_next(newnode);
      }
      head = node; //renew head when ring has been changed
    }
    bool remove() {
      if (node->get_next() == node) return false;
      ringnode<T>& newnode = node->get_next();
      node->get_next()->set_previous(node->get_previous());
      node->get_previous()->set_next(node->get_next());
      delete node;
      node = newnode;
      head = node; //renew head when ring has been changed
      return true;
    }
    T get_value() {return node->get_value();}
    bool proceed() {
      if (node->get_next()) return false;
      node = node->get_next();
      return true;
    }
    ringnode<T>& get_node() {return node;}
    ringnode<T>& get_next() {return node->get_next();}
  };
}
