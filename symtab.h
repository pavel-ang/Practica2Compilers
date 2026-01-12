#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_STRUCT   
} VarType;

typedef union {
    int i;
    double f;
    char s[256];
    int b;
} ValueData;

typedef struct {
    VarType type;
    ValueData v;
} Value;

typedef struct {
    VarType type;
    Value v;
} ExprVal;

typedef struct {
    VarType type;
    char place[128];
} CVal;

#define MAX_FIELDS 16
#define MAX_STRUCTS 32

typedef struct {
    char name[64];
    VarType type;
} Field;

typedef struct {
    char name[64];
    int field_count;
    Field fields[MAX_FIELDS];
} StructType;

typedef struct {
    char name[64];
    VarType type;
    /* Optional constant value (used for constant folding in backend).
       If not used, leave as-is. */
    Value const_value;
    int has_const; /* 0 = no constant, 1 = has constant */

    /* Temporary/name/address used by backend (C3A temporaries or offsets) */
    int address; /* numeric address/offset for backend */
    char temp_name[32]; /* name like "$t1" (zero-terminated) */

    /* Array support */
    int is_array;    /* 0 = scalar, 1 = array */
    int array_size;  /* number of elements when is_array==1 */
    int base_address; /* default base address/offset for arrays (25 by default) */

    StructType *struct_def;   
} Symbol;

void symtab_init();
Symbol* symtab_get(const char *name);
void symtab_add(const char *name, VarType type);
void symtab_add_array(const char *name, VarType type, int size);
void symtab_set_value(Symbol *sym, Value v);
void symtab_print_all();

/* Create and return a fresh temporary name. Caller should free the returned string. */
char* new_temp();

StructType* struct_add(const char *name);
void struct_add_field(StructType *s, const char *fname, VarType t);
StructType* struct_get(const char *name);

#endif
