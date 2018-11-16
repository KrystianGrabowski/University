

tree(leaf) --> ["*"].
tree(node(A,B)) --> ["("], tree(A), tree(B), [")"].

%phrase(tree(node(node(leaf,leaf),leaf)), ["(", "(", "*", "*", ")", "*",")"]).