typedef SinglyLinkedListNode node_t;

SinglyLinkedListNode* extractAndAppendSponsoredNodes(SinglyLinkedListNode* head) {
    node_t * odd_head = NULL;
    node_t * odd_tail = NULL;
    node_t * even = NULL;
    
    int n = 0;
    while (head) {
        node_t * next = head->next;
        if (n % 2) {
            if (odd_tail == NULL) {
                odd_head = odd_tail = head;
                head->next = NULL;
            } else {
                odd_tail->next = head;
                odd_tail = head;
                head->next = NULL;
            }
        } else {
            if (even == NULL) {
                even = head;
                head->next = NULL;
            } else {
                head->next = even;
                even = head;
            }
        }
        head = next;
        n++;
    }
    
    if (odd_head) {
        odd_tail->next = even;
        return odd_head;
    } else {
        return even;
    }
}

