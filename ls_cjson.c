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

bool cjson_to_bool(const cjson* obj)
{
    bool result = false;

    if(cJSON_IsBool(obj))
    {
        if(cJSON_IsTrue(obj)) { result = true; }
    }
    else if(cJSON_IsNumber(obj))
    {
        result = obj->valueint ? true : false;
    }
    else if(cJSON_IsString(obj))
    {
        result = atoi(obj->valuestring) ? true : false;
    }

    return result;
}

int32_t cjson_to_i32(const cjson* obj)
{
    int32_t result = 0;

    if(cJSON_IsNumber(obj))
    {
        result = obj->valueint;
    }
    else if(cJSON_IsString(obj))
    {
        result = atoi(obj->valuestring);
    }

    return result;
}

uint32_t cjson_to_u32(const cjson* obj)
{
    uint32_t result = 0;

    if(cJSON_IsNumber(obj))
    {
        result = (uint32_t)obj->valueint;
    }
    else if(cJSON_IsString(obj))
    {
        result = (uint32_t)atoi(obj->valuestring);
    }

    return result;
}

double cjson_to_double(const cjson* obj)
{
    double result = 0;

    if(cJSON_IsNumber(obj))
    {
        result = obj->valuedouble;
    }
    else if(cJSON_IsString(obj))
    {
        result = atof(obj->valuestring);
    }

    return result;
}

// if json root is delete, the string can't be used
char* cjson_to_string(const cjson* obj)
{
    char* result = "";

    if(cJSON_IsString(obj))
    {
        result = obj->valuestring;
    }

    return result;
}

// copy json string to buffer with max size
void cjson_to_string_copy(const cjson* obj, char* buffer, int32_t size)
{
    int32_t length = 0;

    if(cJSON_IsString(obj))
    {
        length = strlen(obj->valuestring);
        length = length < (size-1) ? length : (size-1);

        if(length)
        {
            memcpy(buffer, obj->valuestring, length);
            buffer[length] = '\0'; // to string
        }
    }
}

int32_t cjson_array_size(const cjson* array)
{
    int32_t result = 0;

    if(cJSON_IsArray(array))
    {
        result = cJSON_GetArraySize(array);
    }

    return result;
}

// array index begin with 0
cjson* cjson_to_array(const cjson* array, int32_t index)
{
    cjson* result = NULL;
    int32_t array_size = cjson_array_size(array);

    if( array_size && index <= (array_size - 1) )
    {
        result = cJSON_GetArrayItem(array, index);
    }

    return result;
}

