#ifndef _LS_CJSON_H_
#define _LS_CJSON_H_

#include <stdint.h>
#include <stdbool.h>
#include "cJSON/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef cJSON cjon;

cjon* cjson_parse(const char* json_string);
void  cjson_delete(cjon* root);

char* cjson_prirnt(const cjon* root);
char* cjson_prirnt_unformatted(const cjon* root);
void  cjson_free(const char* root_string);

bool cjson_to_bool(const cjon* obj);
int32_t cjson_to_i32(const cjon* obj);
uint32_t cjson_to_u32(const cjon* obj);
double cjson_to_double(const cjon* obj);
char* cjson_to_string(const cjon* obj);
void cjson_to_string_copy(const cjon* obj, char* buffer, int32_t size);

#ifdef __cplusplus
}
#endif

#endif // !_LS_CJSON_H_
