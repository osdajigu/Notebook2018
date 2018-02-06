int evaluate (state &node, int alpha, int beta, int node_type) {
    if (is_leaf(node))
        return utility(node);
    vector<state> children = successor(node);
    if (node_type == MIN) {
        for (auto child : children) {
            beta = min(beta, evaluate(child, alpha, beta, MAX));
            if (beta <= alpha)
                break;
        }
        return beta;
    } else {
        for (auto child : children) {
            alpha = max(alpha, evaluate(child, alpha, beta, MIN));
            if (beta <= alpha)
                break;
        }
        return alpha;
    }
}
