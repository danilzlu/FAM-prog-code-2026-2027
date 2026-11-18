#include "floyd.h"

/* Возвращает точку встречи либо NULL, если цикл отсутствует. */
static const LinkNode *meeting_point(const LinkNode *head) {
    const LinkNode *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return slow;
    }
    return NULL;
}

bool has_cycle(const LinkNode *head) {
    return meeting_point(head) != NULL;
}

size_t cycle_length(const LinkNode *head) {
    const LinkNode *meet = meeting_point(head);
    if (meet == NULL)
        return 0;
    size_t length = 1;
    for (const LinkNode *p = meet->next; p != meet; p = p->next)
        ++length;
    return length;
}

const LinkNode *cycle_start(const LinkNode *head) {
    const LinkNode *meet = meeting_point(head);
    if (meet == NULL)
        return NULL;
    /* Первая встреча случилась после t шагов, t кратно длине цикла. */
    const LinkNode *p = head;
    while (p != meet) {
        p = p->next;
        meet = meet->next;
    }
    return p;
}
