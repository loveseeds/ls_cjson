#include "ls_cjson.h"
#include <stdlib.h>
#include <string.h>

cjson* cjson_parse(const char* json_string)
{
    if(json_string == NULL) { return NULL; }

    return cJSON_Parse(json_string);
}

void cjson_delete(cjson* root)
{
    if(root != NULL)
    {
        cJSON_Delete(root);
    }
}

char* cjson_prirnt(const cjson* root)
{
    if(root == NULL) { return ""; }

    return cJSON_Print(root);
}

char* cjson_prirnt_unformatted(const cjson* root)
{
    if(root == NULL) { return ""; }

    return cJSON_PrintUnformatted(root);
}

void cjson_free(const char* root_string)
{
    if(root_string != NULL)
    {
        cJSON_free((void*)root_string);
    }
}

bool cjson_to_bool(const cjson* item)
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

int32_t cjson_to_i32(const cjson* item)
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

uint32_t cjson_to_u32(const cjson* item)
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

double cjson_to_double(const cjson* item)
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
char* cjson_to_string(const cjson* item)
{
    char* result = "";

    if(cJSON_IsString(item))
    {
        result = item->valuestring;
    }

    return result;
}

// copy json string to buffer with max size
void cjson_to_string_copy(const cjson* item, char* buffer, int32_t size)
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

int32_t cjson_array_size(const cjson* array_item)
{
    int32_t result = 0;

    if(cJSON_IsArray(array_item))
    {
        result = cJSON_GetArraySize(array_item);
    }

    return result;
}

// array index begin with 0
cjson* cjson_to_array(const cjson* array_item, int32_t index)
{
    cjson* result = NULL;
    int32_t array_size = cjson_array_size(array_item);

    if( array_size && index <= (array_size - 1) )
    {
        result = cJSON_GetArrayItem(array_item, index);
    }

    return result;
}

cjson* cjson_parse_item(const cjson* from_item, const char* item_name)
{
    cjson* result = NULL;

    result = cJSON_GetObjectItem(from_item, item_name);

    return result;
}

bool cjson_parse_bool(const cjson* from_item, const char* item_name)
{
    cjson* item = cjson_parse_item(from_item, item_name);
    return cjson_to_bool(item);
}

int32_t cjson_parse_i32(const cjson* from_item, const char* item_name)
{
    cjson* item = cjson_parse_item(from_item, item_name);
    return cjson_to_i32(item);
}

uint32_t cjson_parse_u32(const cjson* from_item, const char* item_name)
{
    cjson* item = cjson_parse_item(from_item, item_name);
    return cjson_to_u32(item);
}

double cjson_parse_double(const cjson* from_item, const char* item_name)
{
    cjson* item = cjson_parse_item(from_item, item_name);
    return cjson_to_double(item);
}

char* cjson_parse_string(const cjson* from_item, const char* item_name)
{
    cjson* item = cjson_parse_item(from_item, item_name);
    return cjson_to_string(item);
}

void cjson_parse_string_copy(const cjson* from_item, const char* item_name, char* buffer, int32_t size)
{
    cjson* item = cjson_parse_item(from_item, item_name);
    cjson_to_string_copy(item, buffer, size);
}

cjson* cjson_parse_array(const cjson* from_item, const char* item_name)
{
    return cjson_parse_item(from_item, item_name);
}

int32_t cjson_parse_array_size(const cjson* from_item)
{
    return cjson_array_size(from_item);
}

cjson* cjson_parse_array_item(const cjson* from_item, int32_t index)
{
    return cjson_to_array(from_item, index);
}


// create json

cjson* cjson_create_root(void)
{
    return cJSON_CreateObject();
}

cjson* cjson_create_item(void)
{
    return cJSON_CreateObject();
}

bool cjson_create_bool(cjson* to_item, const char* key, bool value)
{
    return cJSON_AddBoolToObject(to_item, key, value) != NULL ? true : false;
}



