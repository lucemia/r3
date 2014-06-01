#include <r3.h>

// create a router tree with 10 children capacity (this capacity can grow dynamically)
n = r3_tree_create(10);

int route_data = 3;

// insert the route path into the router tree
r3_tree_insert_path(n, "/bar", &route_data); // ignore the length of path

r3_tree_insert_pathl(n, "/zoo", strlen("/zoo"), &route_data );
r3_tree_insert_pathl(n, "/foo/bar", strlen("/foo/bar"), &route_data );

r3_tree_insert_pathl(n ,"/post/{id}", strlen("/post/{id}") , &route_data );

r3_tree_insert_pathl(n, "/user/{id:\\d+}", strlen("/user/{id:\\d+}"), &route_data );

// let's compile the tree!
r3_tree_compile(n);


// dump the compiled tree
r3_tree_dump(n, 0);

// match a route
node *matched_node = r3_tree_matchl(n, "/foo/bar", strlen("/foo/bar"), NULL);
if (matched_node) {
    int ret = *( (*int) matched_node->data );
}

// release the tree
r3_tree_free(n);
