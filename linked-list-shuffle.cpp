typedef struct node_s {
    int number;
    node_s * next;
} node_t;

constexpr node_t * linked_list_shuffle(int (*rand)(), node_t * head) {
    int size = 0;
    for (node_t * n = head; n; n = n->next) size++;
    
    if (size == 0) return nullptr;
    
    node_t * head2 = head;
    for (int i = 1; i < size / 2; i++, head2 = head2->next) {
    }
    
    node_t * result = nullptr;
    node_t * last_result = nullptr;
    // list 1: head until head2
    // list 2: head2 until nullptr
    
    node_t * l1 = head;
    node_t * l2 = head2;
    
    auto add_l = [&](auto & l) {
        if (result == nullptr) {
            result = last_result = l;
            l = l->next;
        } else {
            last_result->next = l;
            last_result = l;
            l = l->next;
        }
    };
    
    for (int i = 0; i < size; i++) {
        if (l1 == head2) {
            add_l(l2);
            continue;
        }
        if (l2 == nullptr) {
            add_l(l1);
            continue;
        }
        if (rand() % 2 == 0) {
            add_l(l1);
        } else {
            add_l(l2);
        }
    }
    
    last_result->next = nullptr;
    return result;
}

#include <stdio.h>
int main() {
  node_t n[6];
  for (int i = 0; i < 6; i++) {
    n[i].number = i;
    n[i].next = i == 5 ? nullptr : &n[i + 1];
  }

  for (int i = 0; i < 6; i++) {
    printf("%d %p\n", n[i].number, n[i].next);
  }
  printf("=======\n");

  auto rand = [] {
    static int v = 0;
    v ^= 1;
    return v;
  };
  node_t * res = linked_list_shuffle(rand, &n[0]);
  for (; res; res = res->next) {
    printf("%d\n", res->number);
  }
}
