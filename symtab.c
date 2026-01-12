#include "symtab.h"
#include <stdlib.h>

#define MAX_SYMBOLS 256
static Symbol table[MAX_SYMBOLS];
static int sym_count = 0;

static StructType struct_table[MAX_STRUCTS];
static int struct_count = 0;

void symtab_init() {
    sym_count = 0;
    struct_count = 0;
}

Symbol* symtab_get(const char *name) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(table[i].name, name) == 0)
            return &table[i];
    }
    return NULL;
}

void symtab_add(const char *name, VarType type) {
    if (symtab_get(name)) return;

    strcpy(table[sym_count].name, name);
    table[sym_count].type = type;
    /* No constant value by default */
    table[sym_count].has_const = 0;
    table[sym_count].const_value.v.i = 0;

    /* backend-related defaults */
    table[sym_count].address = -1;
    table[sym_count].temp_name[0] = '\0';

    /* array defaults */
    table[sym_count].is_array = 0;
    table[sym_count].array_size = 0;
    table[sym_count].base_address = 25; /* default base */

    table[sym_count].struct_def = NULL;
    sym_count++;
}

void symtab_add_array(const char *name, VarType type, int size) {
    if (symtab_get(name)) return;

    strcpy(table[sym_count].name, name);
    table[sym_count].type = type;
    table[sym_count].has_const = 0;
    table[sym_count].const_value.v.i = 0;
    table[sym_count].address = -1;
    table[sym_count].temp_name[0] = '\0';
    table[sym_count].is_array = 1;
    table[sym_count].array_size = size;
    table[sym_count].base_address = 25;
    table[sym_count].struct_def = NULL;
    sym_count++;
}

void symtab_set_value(Symbol *sym, Value v) {
    /* store as constant value for constant-folding/backends */
    sym->const_value = v;
    sym->has_const = 1;
}

void symtab_print_all() {
    printf("---- Symbol Table ----\n");
    for (int i = 0; i < sym_count; i++) {
        printf("%s : ", table[i].name);
        switch (table[i].type) {
            case TYPE_INT:
                if (table[i].has_const)
                    printf("int (const) = %d\n", table[i].const_value.v.i);
                else
                    printf("int\n");
                break;

            case TYPE_FLOAT:
                if (table[i].has_const)
                    printf("float (const) = %lf\n", table[i].const_value.v.f);
                else
                    printf("float\n");
                break;

            case TYPE_STRING:
                if (table[i].has_const)
                    printf("string (const) = \"%s\"\n", table[i].const_value.v.s);
                else
                    printf("string\n");
                break;

            case TYPE_BOOL:
                if (table[i].has_const)
                    printf("bool (const) = %s\n", table[i].const_value.v.b ? "true" : "false");
                else
                    printf("bool\n");
                break;

            case TYPE_STRUCT:
                printf("struct %s\n", table[i].struct_def ? table[i].struct_def->name : "unknown");
                break;
        }

        if (table[i].is_array) {
            printf("    [array] size=%d base=%d\n", table[i].array_size, table[i].base_address);
        }
        if (table[i].temp_name[0] != '\0') {
            printf("    [temp name] %s\n", table[i].temp_name);
        } else if (table[i].address != -1) {
            printf("    [address] %d\n", table[i].address);
        }
    }
}

char* new_temp() {
    static int counter = 0;
    counter++;
    char buf[32];
    snprintf(buf, sizeof(buf), "$t%d", counter);
    char *r = (char*)malloc(strlen(buf) + 1);
    if (!r) return NULL;
    strcpy(r, buf);
    return r;
}

StructType* struct_add(const char *name) {
    StructType *s = &struct_table[struct_count++];
    strcpy(s->name, name);
    s->field_count = 0;
    return s;
}

void struct_add_field(StructType *s, const char *fname, VarType t) {
    Field *f = &s->fields[s->field_count++];
    strcpy(f->name, fname);
    f->type = t;
}

StructType* struct_get(const char *name) {
    for (int i = 0; i < struct_count; i++) {
        if (strcmp(struct_table[i].name, name) == 0)
            return &struct_table[i];
    }
    return NULL;
}
