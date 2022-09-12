#include "ls_cjson.h"
#include <stdlib.h>
#include <string.h>

cjon* cjson_parse(const char* json_string)
{
    if(json_string == NULL) { return NULL; }

    return cJSON_Parse(json_string);
}

void cjson_delete(cjon* root)
{
    if(root != NULL)
    {
        cJSON_Delete(root);
    }
}

char* cjson_prirnt(const cjon* root)
{
    if(root == NULL) { return ""; }

    return cJSON_Print(root);
}

char* cjson_prirnt_unformatted(const cjon* root)
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

bool cjson_to_bool(const cjon* obj)
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

int32_t cjson_to_i32(const cjon* obj)
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

uint32_t cjson_to_u32(const cjon* obj)
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

double cjson_to_double(const cjon* obj)
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
char* cjson_to_string(const cjon* obj)
{
    char* result = "";

    if(cJSON_IsString(obj))
    {
        result = obj->valuestring;
    }

    return result;
}

// copy json string to buffer with max size
void cjson_to_string_copy(const cjon* obj, char* buffer, int32_t size)
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



