#include "tstree.h" //uses tree for fast URL search and route
#include "bstrlib.h"
//urlor is a cmd line tool reads file of routes prompts user to enter them for look up
TSTree *add_route_data(TSTree *routes, bstring line)
{
    struct bstrList *data = bsplit(line, ' ');
    check(data->qty == 2, "Line '%s' does not have 2 columns", bdata(line));

    routes = TSTree_insert(routes, bdata(data->entry[0]), blength(data->entry[0]), bstrcpy(data->entry[1]));

    bstrListDestroy(data);

    return routes;//sends routes to caller fn load_routes

error:
    return NULL;
}

TSTree *load_routes(const char *file)
{//reads URLs from file returns list as routes
    TSTree *routes = NULL;
    bstring line = NULL;
    FILE *routes_map = NULL;//FILE is a typedef struct holding file info lets you perform functions on the pointer data

    routes_map = fopen(file, "r");
    check(routes_map != NULL, "Failed to open routes: %s", file);

    while((line = bgets((bNgetc)fgetc, routes_map, '\n')) != NULL) {
        check(btrimws(line) == BSTR_OK, "Failed to trim line.");//takes lines from routes_map feeds it to add_route_data then destroys the line
        routes = add_route_data(routes, line);
        check(routes != NULL, "Failed to add route.");
        bdestroy(line);
    }

    fclose(routes_map);
    return routes;

error:
    if(routes_map) fclose(routes_map);
    if(line) bdestroy(line);

    return NULL;
}

bstring match_url(TSTree *routes, bstring url)
{//searches through tree to match URL
    bstring route = TSTree_search(routes, bdata(url), blength(url));

    if(route == NULL) {//searches by prefix if main search fails
        printf("No exact match found, trying prefix.\n");
        route = TSTree_search_prefix(routes, bdata(url), blength(url));
    }

    return route;//route used in main
}

bstring read_line(const char *prompt)
{//as named
    printf("%s", prompt);

    bstring result = bgets((bNgetc)fgetc, stdin, '\n');
    check_debug(result != NULL, "stdin closed.");

    check(btrimws(result) == BSTR_OK, "Failed to trim.");

    return result;

error:
    return NULL;
}

void bdestroy_cb(void *value, void *ignored)
{//fn for destroy to call to traverse routes to be destroyed
    (void)ignored;
    bdestroy((bstring)value);
}

void destroy_routes(TSTree *routes)//as named
{
    TSTree_traverse(routes, bdestroy_cb, NULL);
    TSTree_destroy(routes);
}

int main(int argc, char *argv[])
{//takes URL as arg in argv[1]
    bstring url = NULL;
    bstring route = NULL;
    check(argc == 2, "USAGE: urlor <urlfile>");//confirm only 2 args used: run urlor and the url as 2nd arg

    TSTree *routes = load_routes(argv[1]);
    check(routes != NULL, "Your route file has an error.");

    while(1) {//will run until found
        url = read_line("URL> ");
        check_debug(url != NULL, "goodbye.");

        route = match_url(routes, url);

        if(route) {
            printf("MATCH: %s == %s\n", bdata(url), bdata(route));
        } else {
            printf("FAIL: %s\n", bdata(url));
        }

        bdestroy(url);
    }

    destroy_routes(routes);
    return 0;//when found return 0 prevents while loop from running

error:
    destroy_routes(routes);
    return 1;
}