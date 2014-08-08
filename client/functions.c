#include <json.h>
#include <stdio.h>
#include <string.h>

#include "api.h"
#include "map_lib.h"
#include "utilities.h"

enum json_type type;

json_object * oa_json_get_object(json_object * jobj, char * object_name) {
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);

        if (type == json_type_object)
            if (strcmp(key, object_name) == 0)
                return val;
    }

    return NULL;
}

json_object * oa_json_get_array(json_object * jobj, char * array_name) {
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);

        if (type == json_type_array)
            if (strcmp(key, array_name) == 0)
                return val;
    }

    return NULL;
}

char * oa_json_get_string(json_object * jobj, char * string_name) {
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);

        if (type == json_type_string)
            if (strcmp(key, string_name) == 0)
                return (char *) json_object_get_string(val);
    }

    return NULL;
}

int oa_array_length(json_object * jarray) {
    return json_object_array_length(jarray);
}

char * oa_as_string(json_object * obj) {
    return (char *) json_object_get_string(obj);
}

void lookup_user() {
    // params
    struct map_t * params = map_create();

    char buffer[64];

    printf("\nWhat is the user's username? ");
    fgets(buffer, sizeof(buffer), stdin);

    // check for newline and eat extra data if present
    if (strchr(buffer, '\n') == NULL) {
        int ch;

        while ((ch = getchar()) != '\n');
    }
    
    map_set(params, "username", trim(buffer));

    char * s = docurl(ACTION_LOOKUP_USER, params);

    json_object * jobj = json_tokener_parse(s);   

    printf("%s\n", json_object_to_json_string(jobj));
}