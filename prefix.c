// Build expression tree from prefix
Node* buildFromPrefix() {
    while (*prefixExpr == ' ') prefixExpr++;  // skip spaces

    char c = *prefixExpr++;
    if (c == '\0') return NULL;

    Node *node = createNode(c);

    if (isOperator(c)) {
        node->left = buildFromPrefix();
        node->right = buildFromPrefix();
    }

    return node;
}
