#include "ls_cjson.h"
#include <stdio.h>

void cjson_create_test(void)
{
    cjson_item root = cjson_create_root();

    cjson_add_bool(root, "is_success", true);
    cjson_add_i32(root, "user_id", 123);
    cjson_add_i32(root, "user_type", 2);
    cjson_add_double(root, "money", 10.2);
    cjson_add_string(root, "name", "loveseeds");

    cjson_item data = cjson_create_item();
    cjson_add_u32(data, "timestamp", 1663079164);
    cjson_add_item(root, "data", data);

    cjson_item array = cjson_create_array();
    cjson_item element1 = cjson_create_item();
    cjson_add_string(element1, "sd", "20021/10/2 10:10:02");
    cjson_add_string(element1, "ed", "20021/10/8 10:10:02");

    cjson_item element2 = cjson_create_item();
    cjson_add_string(element2, "sd", "20022/2/2 10:10:02");
    cjson_add_string(element2, "ed", "20022/3/2 10:10:02");

    cjson_add_array(array, element1);
    cjson_add_array(array, element2);

    cjson_add_item_array(root, "rule_list", array);

    const char* verify_type[] = { "qrcode", "card", "password" };
    cjson_add_string_array(root, "verify_type", verify_type, sizeof(verify_type)/sizeof(verify_type[0]));

    int32_t week[] = { 1, 2, 3, 6, 7 };
    cjson_add_i32_array(root, "week", week, sizeof(week) / sizeof(week[0]));

    char* root_string = cjson_print(root);

    printf("root string: %s", root_string);

    cjson_free(root_string);
}

int main()
{
    cjson_create_test();

    return 0;
}
