SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    SinglyLinkedListNode * ins = malloc(sizeof(SinglyLinkedListNode));
    ins->data = data;

    if (position == 0) {
        ins->next = llist;
        return ins;
    }
    
    SinglyLinkedListNode * node = llist;
    for (int i = 0; i < position - 1; i++) {
        node = node->next;
    }
    
    ins->next = node->next;
    node->next = ins;
    
    return llist;
}

