#include <stdio.h>
//enum and variant 'layering' each element of Variant.data union
typedef enum {//enum is size of char, but intraconvertible with int
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
} VariantType;
//having the enum 'VariantType' as member in Variant struct allows members to be categorised and accessed according to .data(int str or fl) or .typ(INT, FLOAT, or STRING)
struct Variant {
    VariantType type;
    union {
        int as_integer;
        float as_float;
        char *as_string;
    } data;
};

typedef struct Variant Variant;

void Variant_print(Variant *var)//id an input according to its .type, then print its .data element
{
    switch(var->type) {
        case TYPE_INT:
            printf("INT: %d\n", var->data.as_integer);
            break;
        case TYPE_FLOAT:
            printf("FLOAT: %f\n", var->data.as_float);
            break;
        case TYPE_STRING:
            printf("STRING: %s\n", var->data.as_string);
            break;
        default:
            printf("UNKNOWN TYPE: %d", var->type);
    }
}

int C_union_main(int argc, char *argv[])
{
    Variant a_int = {.type = TYPE_INT, .data.as_integer = 100};//assigns a_int values in .type and .data* in a Variant struct
    Variant a_float = {.type = TYPE_FLOAT, .data.as_float = 100.34};
    Variant a_string = {.type = TYPE_STRING, .data.as_string = "YO DUDE"};

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_string);

    //here's how you access them
    //reassigned new values to be printed again in next code block to demonstrate the change
    a_int.data.as_integer = 200;
    a_float.data.as_float = 2.345;
    a_string.data.as_string = "Hi there.";

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_string);

    return 0;
}
