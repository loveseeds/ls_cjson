#include "ls_cjson.h"
#include <stdlib.h>
#include <string.h>

cjson_item cjson_parse(const char* json_string)
{
    if(json_string == NULL) { return NULL; }

    return cJSON_Parse(json_string);
}

void cjson_delete(cjson_item root)
{
    if(root != NULL)
    {
        cJSON_Delete(root);
    }
}

char* cjson_print(const cjson_item root)
{
    if(root == NULL) { return ""; }

    return cJSON_Print(root);
}

char* cjson_print_unformatted(const cjson_item root)
{
    if(root == NULL) { return ""; }

    return cJSON_PrintUnformatted(root);
}

void cjson_free(char* root_string)
{
    if(root_string != NULL)
    {
        cJSON_free((void*)root_string);
    }
}

bool cjson_to_bool(const cjson_item item)
{
    bool result = false;

    if(cJSON_IsBool(item))
    {
        if(cJSON_IsTrue(item)) { result = true; }
    }
    else if(cJSON_IsNumber(item))
    {
        result = item->valueint ? true : false;
    }
    else if(cJSON_IsString(item))
    {
        result = atoi(item->valuestring) ? true : false;
    }

    return result;
}

int32_t cjson_to_i32(const cjson_item item)
{
    int32_t result = 0;

    if(cJSON_IsNumber(item))
    {
        result = item->valueint;
    }
    else if(cJSON_IsString(item))
    {
        result = atoi(item->valuestring);
    }

    return result;
}

uint32_t cjson_to_u32(const cjson_item item)
{
    uint32_t result = 0;

    if(cJSON_IsNumber(item))
    {
        result = (uint32_t)item->valueint;
    }
    else if(cJSON_IsString(item))
    {
        result = (uint32_t)atoi(item->valuestring);
    }

    return result;
}

double cjson_to_double(const cjson_item item)
{
    double result = 0;

    if(cJSON_IsNumber(item))
    {
        result = item->valuedouble;
    }
    else if(cJSON_IsString(item))
    {
        result = atof(item->valuestring);
    }

    return result;
}

// if json root is delete, the string can't be used
char* cjson_to_string(const cjson_item item)
{
    char* result = "";

    if(cJSON_IsString(item))
    {
        result = item->valuestring;
    }

    return result;
}

// copy json string to buffer with max size
void cjson_to_string_copy(const cjson_item item, char* buffer, int32_t size)
{
    int32_t length = 0;

    if(cJSON_IsString(item))
    {
        length = strlen(item->valuestring);
        length = length < (size-1) ? length : (size-1);

        if(length)
        {
            memcpy(buffer, item->valuestring, length);
            buffer[length] = '\0'; // to string
        }
    }
}

int32_t cjson_array_size(const cjson_item array_item)
{
    int32_t result = 0;

    if(cJSON_IsArray(array_item))
    {
        result = cJSON_GetArraySize(array_item);
    }

    return result;
}

// array index begin with 0
cjson_item cjson_to_array(const cjson_item array_item, int32_t index)
{
    cjson_item result = NULL;
    int32_t array_size = cjson_array_size(array_item);

    if( array_size && index <= (array_size - 1) )
    {
        result = cJSON_GetArrayItem(array_item, index);
    }

    return result;
}

cjson_item cjson_parse_item(const cjson_item from_item, const char* item_name)
{
    cjson_item result = NULL;

    result = cJSON_GetObjectItem(from_item, item_name);

    return result;
}

bool cjson_parse_bool(const cjson_item from_item, const char* item_name)
{
    cjson_item item = cjson_parse_item(from_item, item_name);
    return cjson_to_bool(item);
}

int32_t cjson_parse_i32(const cjson_item from_item, const char* item_name)
{
    cjson_item item = cjson_parse_item(from_item, item_name);
    return cjson_to_i32(item);
}

uint32_t cjson_parse_u32(const cjson_item from_item, const char* item_name)
{
    cjson_item item = cjson_parse_item(from_item, item_name);
    return cjson_to_u32(item);
}

double cjson_parse_double(const cjson_item from_item, const char* item_name)
{
    cjson_item item = cjson_parse_item(from_item, item_name);
    return cjson_to_double(item);
}

char* cjson_parse_string(const cjson_item from_item, const char* item_name)
{
    cjson_item item = cjson_parse_item(from_item, item_name);
    return cjson_to_string(item);
}

void cjson_parse_string_copy(const cjson_item from_item, const char* item_name, char* buffer, int32_t buffer_size)
{
    cjson_item item = cjson_parse_item(from_item, item_name);
    cjson_to_string_copy(item, buffer, buffer_size);
}

cjson_array cjson_parse_array(const cjson_item from_item, const char* item_name)
{
    return cjson_parse_item(from_item, item_name);
}

int32_t cjson_parse_array_size(const cjson_array from_item)
{
    return cjson_array_size(from_item);
}

bool cjson_parse_array_bool(const cjson_array from_item, int32_t index)
{
    cjson_item array_item = cjson_to_array(from_item, index);
    return cjson_to_bool(array_item);
}

int32_t cjson_parse_array_i32(const cjson_array from_item, int32_t index)
{
    cjson_item array_item = cjson_to_array(from_item, index);
    return cjson_to_i32(array_item);
}

double cjson_parse_array_double(const cjson_array from_item, int32_t index)
{
    cjson_item array_item = cjson_to_array(from_item, index);
    return cjson_to_double(array_item);
}

char* cjson_parse_array_string(const cjson_array from_item, int32_t index)
{
    cjson_item array_item = cjson_to_array(from_item, index);
    return cjson_to_string(array_item);
}

void cjson_parse_array_string_copy(const cjson_array from_item, int32_t index, char *buffer, int32_t buffer_size)
{
    cjson_item array_item = cjson_to_array(from_item, index);
    cjson_to_string_copy(array_item, buffer, buffer_size);
}

cjson_item cjson_parse_array_item(const cjson_array from_item, int32_t index)
{
    return cjson_to_array(from_item, index);
}


// create json

cjson_item cjson_create_root(void)
{
    return cJSON_CreateObject();
}

cjson_item cjson_create_item(void)
{
    return cJSON_CreateObject();
}

cjson_array cjson_create_array(void)
{
    return cJSON_CreateArray();
}

bool cjson_add_bool(cjson_item to_item, const char* key, bool value)
{
    if(!cJSON_IsObject(to_item)) { return false; }

    return cJSON_AddBoolToObject(to_item, key, value) != NULL ? true : false;
}

bool cjson_add_i32(cjson_item to_item, const char* key, int32_t value)
{
    if(!cJSON_IsObject(to_item)) { return false; }

    return cJSON_AddNumberToObject(to_item, key, value) != NULL ? true : false;
}

bool cjson_add_u32(cjson_item to_item, const char* key, uint32_t value)
{
    if(!cJSON_IsObject(to_item)) { return false; }

    return cJSON_AddNumberToObject(to_item, key, value) != NULL ? true : false;
}

bool cjson_add_double(cjson_item to_item, const char* key, double value)
{
    if(!cJSON_IsObject(to_item)) { return false; }

    return cJSON_AddNumberToObject(to_item, key, value) != NULL ? true : false;
}

bool cjson_add_string(cjson_item to_item, const char* key, const char* value)
{
    if(!cJSON_IsObject(to_item)) { return false; }

    return cJSON_AddStringToObject(to_item, key, value) != NULL ? true : false;
}

bool cjson_add_to_item(cjson_item to_item, const char* key, cjson_item value)
{
    return cJSON_AddItemToObject(to_item, key, value) ? true : false;
}

bool cjson_add_i32_array(cjson_item to_item, const char* key, const int32_t *buffer, int32_t length)
{
    cjson_item array = cJSON_CreateIntArray(buffer, length);

    return cjson_add_to_item(to_item, key, array);
}

bool cjson_add_double_array(cjson_item to_item, const char* key, const double *buffer, int32_t length)
{
    cjson_item array = cJSON_CreateDoubleArray(buffer, length);

    return cjson_add_to_item(to_item, key, array);
}

bool cjson_add_string_array(cjson_item to_item, const char* key, const char* * buffer, int32_t length)
{
    cjson_item array = cJSON_CreateStringArray(buffer, length);

    return cjson_add_to_item(to_item, key, array);
}

bool cjson_add_to_array(cjson_array to_item, const cjson_item item)
{
    if(!cJSON_IsArray(to_item)) { return false; }

    return cJSON_AddItemToArray(to_item, item) ? true : false;
}

bool cjson_add_item_array(cjson_item to_item, const char* key, cjson_array value)
{
    return cjson_add_to_item(to_item, key, value);
}
