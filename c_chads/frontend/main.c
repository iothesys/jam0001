#include <stdio.h>
#include "../lang/parser/parser.h"

void print_ast(struct Parser_Node *node, usize depth) {
    const string source = parser_get_state()->lexer.src;
    for (usize i = 0; i < depth; i += 1) 
        printf("    ");
    switch (node->kind) {
        case PN_DECL:
            printf("Decl(name = %.*s)\n", (int)node->data.decl.name.size, source+node->data.decl.name.from);
            break;
        case PN_PROC:
            printf("Proc\n");
            break;
    }
    for (usize i = 0; i < node->children.size; i += 1) {
        print_ast(vec_get(&node->children, i), depth + 1);
    }
    // just temp
    vec_drop(&node->children);
}

int main() {
    parser_init(
        "main = proc {}"
    );
    struct Parser_Node result = parser_parse_toplevel();
    print_ast(&result, 0);
    parser_deinit();
    return 0;
}
