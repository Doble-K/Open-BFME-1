struct Rva14AAB0ListNode
{
    Rva14AAB0ListNode *next;
};

struct Rva14AAB0ListHead
{
    Rva14AAB0ListNode *head;

    Rva14AAB0ListHead *advance();
};

Rva14AAB0ListHead *Rva14AAB0ListHead::advance()
{
    head = head->next;
    return this;
}
