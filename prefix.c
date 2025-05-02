Node* buildFromPrefix() {
    while (*prefixExpr == ' ') prefixExpr++;  // skip spaces

    if (*prefixExpr == '\0') {
        fprintf(stderr, "Error: Unexpected end of expression.\n");
        return NULL;
    }

    char c = *prefixExpr++;

    if (!isOperator(c) && !isalnum(c)) {
        fprintf(stderr, "Error: Invalid character '%c' in expression.\n", c);
        return NULL;
    }

    Node *node = createNode(c);

    if (isOperator(c)) {
        node->left = buildFromPrefix();
        if (!node->left) {
            fprintf(stderr, "Error: Missing left operand for operator '%c'.\n", c);
            return NULL;
        }

        node->right = buildFromPrefix();
        if (!node->right) {
            fprintf(stderr, "Error: Missing right operand for operator '%c'.\n", c);
            return NULL;
        }
    }

    return node;
}
