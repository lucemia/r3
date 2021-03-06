# CHANGELOG

by Yo-An Lin <yoanlin93@gmail.com>

### 1.2.1  - Tue May 27 21:16:13 2014

- Bug fixes.
- Function declaration improvement.
- pkg-config flags update (r3.pc)

### 1.2    - Fri May 23 23:30:11 2014

- Added simple pattern optimization.
- Clean up.
- Bug fixes.

### 0.9999 - Mon May 19 10:03:41 2014

API changes:

1. Removed the `route` argument from `r3_tree_insert_pathl_`:

        node * r3_tree_insert_pathl_(node *tree, char *path, int path_len, void * data);

    This reduce the interface complexity, e.g.,

        r3_tree_insert_path(n, "/user2/{id:\\d+}", &var2);

2. The original `r3_tree_insert_pathl_` has been moved to `r3_tree_insert_pathl_` as a private API.

3. Moved `r3_tree_matchl` to `r3_tree_matchl` since it require the length of the path string.

        m = r3_tree_matchl( n , "/foo", strlen("/foo"), entry);

4. Added `r3_tree_match` for users to match a path without the length of the path string.

        m = r3_tree_match( n , "/foo", entry);

5. Added `r3_tree_match_entry` for users want to match a `match_entry`, which is just a macro to simplify the use:


        #define r3_tree_match_entry(n, entry) r3_tree_matchl(n, entry->path, entry->path_len, entry)


6. Please note that A path that is inserted by `r3_tree_insert_route` can only be matched by `r3_tree_match_route`.

7. Added `r3_` prefix to `route` related methods.


