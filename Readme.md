# JerryScript for ESP32 IDF

The basis for this component comes from https://github.com/jerryscript-project/jerryscript with an addition of port functions for ESP32

Place the content of this repository in a folder jerryscript-esp32 inside of the components folder of your project.

# Example code


## Neccessary includes
```c++
#include <jerryscript.h>
#include <jerryscript-ext/handler.h>
```

## Print something with a self defined function
```c++
const jerry_char_t script[] = "print('Jerrys World');";
size_t script_size = strlen ((const char *) script);
jerry_init(JERRY_INIT_EMPTY);
jerryx_handler_register_global((const jerry_char_t *) "print", jerryx_handler_print);
jerry_value_t parsed_code = jerry_parse(script, script_size, false);
if (!jerry_value_has_error_flag(parsed_code))
{
    jerry_value_t ret_value = jerry_run(parsed_code);
    jerry_release_value(ret_value);
}
jerry_release_value(parsed_code);
jerry_cleanup ();
```