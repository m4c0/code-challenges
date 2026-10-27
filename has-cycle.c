bool has_cycle(SinglyLinkedListNode* head) {
    // Assuming we can destroy the list
    // If we can't, then we need to keep a set of visited nodes
    SinglyLinkedListNode * node = head;
    while (node) {
        if (node->next == node) return true;
        
        SinglyLinkedListNode * next = node->next;
        node->next = node;
        node = next;
    }
    return false;
}

