struct Rva14AAC0ListNode
{
    Rva14AAC0ListNode *next;
};

struct Rva14AAC0ListHead
{
    Rva14AAC0ListNode *head;

    Rva14AAC0ListHead *advance();
};

Rva14AAC0ListHead *Rva14AAC0ListHead::advance()
{
    head = head->next;
    return this;
}
