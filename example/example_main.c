#include "../ls_cjson.h"
#include <stdio.h>

char* test_cjson_create(void)
{
    cjson_item root = cjson_create_root();

    cjson_add_bool(root, "is_success", true);
    cjson_add_i32(root, "user_id", 123);
    cjson_add_u32(root, "user_type", 2);
    cjson_add_double(root, "money", 10.2);
    cjson_add_string(root, "name", "loveseeds");

    cjson_item data = cjson_create_item();
    cjson_add_u32(data, "timestamp", 1663079164);
    cjson_add_to_item(root, "data", data);

    cjson_array array = cjson_create_array();
    cjson_item element1 = cjson_create_item();
    cjson_add_string(element1, "sd", "20021/10/2 10:10:02");
    cjson_add_string(element1, "ed", "20021/10/8 10:10:02");

    cjson_item element2 = cjson_create_item();
    cjson_add_string(element2, "sd", "20022/2/2 10:10:02");
    cjson_add_string(element2, "ed", "20022/3/2 10:10:02");

    cjson_add_to_array(array, element1);
    cjson_add_to_array(array, element2);

    cjson_add_item_array(root, "rule_list", array);

    const char* verify_type[] = { "qrcode", "card", "password" };
    cjson_add_string_array(root, "verify_type", verify_type, sizeof(verify_type)/sizeof(verify_type[0]));

    int32_t week[] = { 1, 2, 3, 6, 7 };
    cjson_add_i32_array(root, "week", week, sizeof(week) / sizeof(week[0]));

    char* root_string = cjson_print_unformatted(root);

    printf("root string: %s\n", root_string);

    return root_string;
}

void test_cjson_parse(const char* json_string)
{
    cjson_item root = cjson_parse(json_string);

    printf("=== cjson parse string! ===\n");
    
    printf("is_success : %d\n", cjson_parse_bool(root, "is_success"));
    printf("user_id : %d\n", cjson_parse_i32(root, "user_id"));
    printf("user_type : %d\n", cjson_parse_u32(root, "user_type"));
    printf("money : %d\n", cjson_parse_double(root, "money"));
    printf("name :  %s\n", cjson_parse_string(root, "name"));

    cjson_item data = cjson_parse_item(root, "data");
    printf("timestamp : %u\n", cjson_parse_u32(data, "timestamp"));

    cjson_array array = cjson_parse_array(root, "rule_list");
    printf("array size : %d\n", cjson_parse_array_size(array));

    cjson_item array_item0 = cjson_parse_array_item(array, 0);
    printf("array_item0, sd :  %s\n", cjson_parse_string(array_item0, "sd"));
    printf("array_item0, ed :  %s\n", cjson_parse_string(array_item0, "ed"));

    cjson_item array_item1 = cjson_parse_array_item(array, 0);
    printf("array_item1, sd :  %s\n", cjson_parse_string(array_item1, "sd"));
    printf("array_item1, ed :  %s\n", cjson_parse_string(array_item1, "ed"));

    cjson_array verify_type_array = cjson_parse_array(root, "verify_type");
    printf("verify_type size : %d\n", cjson_parse_array_size(verify_type_array));
    printf("verify_type :  %s\n", cjson_parse_array_string(verify_type_array, 0));
    printf("verify_type :  %s\n", cjson_parse_array_string(verify_type_array, 1));
    printf("verify_type :  %s\n", cjson_parse_array_string(verify_type_array, 2));
    printf("verify_type :  %s\n", cjson_parse_array_string(verify_type_array, 3)); // out range

    cjson_array week_array = cjson_parse_array(root, "week");
    printf("week_array size : %d\n", cjson_parse_array_size(week_array));
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 0));
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 1));
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 2));
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 3));
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 4));
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 5)); // out range
    printf("week_array :  %d\n", cjson_parse_array_i32(week_array, 6)); // out range

    cjson_delete(root);
}

int main()
{
    char* json_string = test_cjson_create();

    test_cjson_parse(json_string);
    
    cjson_free(json_string);

    return 0;
}
