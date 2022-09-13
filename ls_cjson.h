#ifndef _LS_CJSON_H_
#define _LS_CJSON_H_

#include <stdint.h>
#include <stdbool.h>
#include "cJSON/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef cJSON  cjson;
typedef cJSON* cjson_item;

cjson_item cjson_parse(const char* json_string);
void  cjson_delete(cjson_item root);

char* cjson_print(const cjson_item root);
char* cjson_print_unformatted(const cjson_item root);
void  cjson_free(const char* root_string);

cjson_item cjson_parse_item(const cjson_item from_item, const char* item_name);
bool cjson_parse_bool(const cjson_item from_item, const char* item_name);
int32_t cjson_parse_i32(const cjson_item from_item, const char* item_name);
uint32_t cjson_parse_u32(const cjson_item from_item, const char* item_name);
double cjson_parse_double(const cjson_item from_item, const char* item_name);
char* cjson_parse_string(const cjson_item from_item, const char* item_name);
void cjson_parse_string_copy(const cjson_item from_item, const char* item_name, char* buffer, int32_t size);
cjson_item cjson_parse_array(const cjson_item from_item, const char* item_name);
int32_t cjson_parse_array_size(const cjson_item from_item);
cjson_item cjson_parse_array_item(const cjson_item from_item, int32_t index);

cjson_item cjson_create_root(void);
cjson_item cjson_create_item(void);
cjson_item cjson_create_array(void);
bool cjson_add_bool(cjson_item to_item, const char* key, bool value);
bool cjson_add_i32(cjson_item to_item, const char* key, int32_t value);
bool cjson_add_u32(cjson_item to_item, const char* key, uint32_t value);
bool cjson_add_double(cjson_item to_item, const char* key, double value);
bool cjson_add_string(cjson_item to_item, const char* key, const char* value);
bool cjson_add_item(cjson_item to_item, const char* key, cjson_item value);
bool cjson_add_i32_array(cjson_item to_item, const char* key, const int32_t *buffer, int32_t length);
bool cjson_add_double_array(cjson_item to_item, const char* key, const double *buffer, int32_t length);
bool cjson_add_string_array(cjson_item to_item, const char* key, const char* * buffer, int32_t length);
bool cjson_add_array(cjson_item to_item, const cjson_item item);
bool cjson_add_item_array(cjson_item to_item, const char* key, cjson_item value);

#ifdef __cplusplus
}
#endif

#endif // !_LS_CJSON_H_
