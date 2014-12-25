/* Example of a recursive-descent parser of a basic grammar.
 * The grammar can be found at http://usn.pw/blog/cs/2014/12/25/parsing/
 * Written by Thomas Galvin. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum node_type {
	NODE_EXPONENT,
	NODE_PRODUCT,
	NODE_SUM,
	NODE_INTEGER
};

struct node;
struct node {
	enum node_type type;
	union {
		struct {
			struct node * left, * right;
		};
		int value;
	};
};

char lookahead = '\0';

void next() {
	lookahead = getchar();
}

bool accept(char a) {
	if(lookahead == a) {
		next();
		return true;
	} else {
		return false;
	}
}

void expect(char e) {
	if(!accept(e)) {
		printf("Expected %c\n", e);
		exit(1);
	}
}

struct node * create_node(enum node_type type, struct node * left, struct node * right) {
	struct node * node = malloc(sizeof(struct node));
	node->type = type;
	node->left = left;
	node->right = right;
	return node;
}

struct node * create_node_integer(int value) {
	struct node * node = malloc(sizeof(struct node));
	node->type = NODE_INTEGER;
	node->value = value;
	return node;
}

void print_node(struct node * node) {
	if(node->type == NODE_INTEGER) {
		printf("%d", node->value);
	} else {
		if(node->type == NODE_EXPONENT)
			printf("exp(");
		else if(node->type == NODE_PRODUCT)
			printf("mul(");
		else if(node->type == NODE_SUM)
			printf("add(");
		else
			printf("unknown(");
		print_node(node->left);
		printf(",");
		print_node(node->right);
		printf(")");
	}
	free(node);
}

struct node * parse_single();
struct node * parse_exponent();
struct node * parse_product();
struct node * parse_sum();

struct node * parse_single() {
	if(accept('(')) {
		struct node * node = parse_sum();
		expect(')');
		return node;
	} else if(lookahead >= '0' && lookahead <= '9') {
		int value = 0;
		while(lookahead >= '0' && lookahead <= '9') {
			value = (value * 10) + (lookahead - '0');
			next();
		}
		return create_node_integer(value);
	} else {
		printf("Unexpected character %c\n", lookahead);
		exit(1);
	}
}

struct node * parse_exponent() {
	struct node * node = parse_single(), ** head = &node;
	while(accept('^')) {
		struct node * right = parse_single();
		*head = create_node(NODE_EXPONENT, *head, right);
		head = &right;
	}
	return node;
}

struct node * parse_product() {
	struct node * node = parse_exponent();
	while(accept('*')) {
		node = create_node(NODE_PRODUCT, node, parse_exponent());
	}
	return node;
}

struct node * parse_sum() {
	struct node * node = parse_product();
	while(accept('+')) {
		node = create_node(NODE_SUM, node, parse_product());
	}
	return node;
}

int main() {
	next();
	struct node * ast = parse_sum();
	print_node(ast);
	printf("\n");
	return 0;
}
