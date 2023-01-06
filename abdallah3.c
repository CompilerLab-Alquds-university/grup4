#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeration of symbol types  تعداد أنواع الرموز
enum SymbolType {
  SYMBOL_INT,
  SYMBOL_FLOAT
};

// Structure representing a symbol in the symbol table يمثل رمزًا في جدول الرموز
struct Symbol {
  char* name;
  enum SymbolType type;
  union {
    int int_value;
    float float_value;
  } value;
};

// Structure representing a symbol table   يمثل جدول الرموز
struct SymbolTable {
  int size;
  int capacity;
  struct Symbol** symbols;
};

// Global symbol table جدول الرموز العالمية
struct SymbolTable* SymbolTable;

// Initializes the global symbol table يقوم بتهيئة جدول الرموز العام
void init_symbol_table() {
  SymbolTable = (struct SymbolTable*) malloc(sizeof(struct SymbolTable));
  SymbolTable->size = 0;
  SymbolTable->capacity = 16;
  SymbolTable->symbols = (struct Symbol*) malloc(SymbolTable->capacity * sizeof(struct Symbol));
}

// Adds a symbol to the global symbol table يضيف رمزًا إلى جدول الرموز العام
void add_symbol(char* name, enum SymbolType type, union {
  int int_value;
  float float_value;
} value) {
  // Check if the symbol table is full تحقق مما إذا كان جدول الرموز ممتلئًا
  if (SymbolTable->size == SymbolTable->capacity) {
    // Increase the capacity of the symbol table زيادة سعة جدول الرموز
    SymbolTable->capacity *= 2; 
    SymbolTable->symbols = (struct Symbol*) realloc(SymbolTable->symbols, SymbolTable->capacity * sizeof(struct Symbol));
  }

  // Create the new symbol انشاء جدول رموز جديد 
  struct Symbol* symbol = (struct Symbol*) malloc(sizeof(struct Symbol));
  symbol->name = name;
  symbol->type = type;
  symbol->value = value;

  // Add the symbol to the symbol table أضف الرمز إلى جدول الرموز
  SymbolTable->symbols[SymbolTable->size++] = symbol;
}

// Looks up a symbol in the global symbol table يبحث عن رمز في جدول الرموز العام
struct Symbol* lookup_symbol(char* name) {
  for (int i = 0; i < SymbolTable->size; i++) {
    struct Symbol* symbol = SymbolTable->symbols[i];
    if (strcmp(symbol->name, name) == 0) {
      return symbol;
    }
  }
  return NULL;
}

int main() {
  init_symbol_table();

  add_symbol("x", SYMBOL_INT, (union) { .int_value = 10 });
  add_symbol("y", SYMBOL_FLOAT, (union) { .float_value = 3.14 });

  struct Symbol* x = lookup_symbol("x");
  printf("x: type=%d, value=%d\n", x->type, x->value.int_value);

  struct Symbol* y = lookup_symbol("y");
  printf("y: type=%d, value=%f\n", y->type, y->value.float_value);