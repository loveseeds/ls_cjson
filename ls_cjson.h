#ifndef _LS_CJSON_H_
#define _LS_CJSON_H_

#include <stdint.h>
#include <stdbool.h>
#include "cJSON/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef cJSON cjson;

cjson* cjson_parse(const char* json_string);
void  cjson_delete(cjson* root);

char* cjson_prirnt(const cjson* root);
char* cjson_prirnt_unformatted(const cjson* root);
void  cjson_free(const char* root_string);

cjson* cjson_parse_item(const cjson* from_item, const char* item_name);

bool cjson_parse_bool(const cjson* from_item, const char* item_name);
int32_t cjson_parse_i32(const cjson* from_item, const char* item_name);
uint32_t cjson_parse_u32(const cjson* from_item, const char* item_name);
double cjson_parse_double(const cjson* from_item, const char* item_name);
char* cjson_parse_string(const cjson* from_item, const char* item_name);
void cjson_parse_string_copy(const cjson* from_item, const char* item_name, char* buffer, int32_t size);

cjson* cjson_parse_array(const cjson* from_item, const char* item_name);
int32_t cjson_parse_array_size(const cjson* from_item);
cjson* cjson_parse_array_item(const cjson* from_item, int32_t index);



#ifdef __cplusplus
}
#endif

#endif // !_LS_CJSON_H_
