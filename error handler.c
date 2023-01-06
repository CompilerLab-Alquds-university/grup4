#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// تعداد أنواع الخطأ
enum ErrorType {
  ERROR_UNDECLARED_IDENTIFIER,
  ERROR_REDECLARED_IDENTIFIER
};

// هيكل يمثل خطأ
struct Error {
  int line_number;
  enum ErrorType type;
  char* message;
};

// Array of errors
struct Error** Errors;
//عدد الأخطاء
int NumErrors = 0;
// Capacity of the errors array قدرة مصفوفة الأخطاء
int ErrorsCapacity = 16;

// Initializes the errors array  تهيئة مجموعة الأخطاء
void init_errors() {
  Errors = (struct Error*) malloc(ErrorsCapacity * sizeof(struct Error));
}

// Adds an error to the errors array يضيف خطأ إلى مصفوفة الأخطاء
void add_error(int line_number, enum ErrorType type, char* message) {
  // Check if the errors array is full تحقق مما إذا كانت مصفوفة الأخطاء ممتلئة
  if (NumErrors == ErrorsCapacity) {
    // Increase the capacity of the errors array زيادة سعة مصفوفة الأخطاء
    ErrorsCapacity *= 2;
    Errors = (struct Error*) realloc(Errors, ErrorsCapacity * sizeof(struct Error));
  }

  // Create the new error قم بإنشاء الخطأ الجديد
  struct Error* error = (struct Error*) malloc(sizeof(struct Error));
  error->line_number = line_number;
  error->type = type;
  error->message = message;

  // Add the error to the errors array أضف الخطأ إلى مصفوفة الأخطاء
  Errors[NumErrors++] = error;
}

// Prints all of the errors in the errors array يطبع كافة الأخطاء في مصفوفة الأخطاء
void print_errors() {
  for (int i = 0; i < NumErrors; i++) {
    struct Error* error = Errors[i];
    printf("Error on line %d: %s\n", error->line_number, error->message);
  }
}

int main() {
  init_errors();

  add_error(10, ERROR_UNDECLARED_IDENTIFIER, "Undeclared identifier 'x'");