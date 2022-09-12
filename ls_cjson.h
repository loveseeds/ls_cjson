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

bool cjson_to_bool(const cjson* obj);
int32_t cjson_to_i32(const cjson* obj);
uint32_t cjson_to_u32(const cjson* obj);
double cjson_to_double(const cjson* obj);
char* cjson_to_string(const cjson* obj);
void cjson_to_string_copy(const cjson* obj, char* buffer, int32_t size);

int32_t cjson_array_size(const cjson* array);
cjson* cjson_to_array(const cjson* array, int32_t index);


#ifdef __cplusplus
}
#endif

#endif // !_LS_CJSON_H_
