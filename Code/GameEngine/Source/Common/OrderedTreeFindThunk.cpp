struct OrderedTreeNode
{
    OrderedTreeNode *parent;
    OrderedTreeNode *root;
    OrderedTreeNode *left;
    OrderedTreeNode *right;
    long key;
};

struct OrderedTreeFindThunk
{
    OrderedTreeNode *header;

    OrderedTreeNode *find(const long *key);
};

OrderedTreeNode *OrderedTreeFindThunk::find(const long *key)
{
    OrderedTreeNode *node = header->root;
    OrderedTreeNode *candidate = header;

    while (node != 0) {
        if (!(node->key < *key)) {
            candidate = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (candidate == header || *key < candidate->key) {
        return header;
    }

    return candidate;
}
