#include "jerryscript-port.h"
#include <stdarg.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h" 

#define LOGTAG "jerryscript"

void jerry_port_log (jerry_log_level_t level,  const char *format, ...)  
{
    va_list args;
    va_start (args, format);
#ifdef JERRY_DEBUGGER
    char buffer[256];
    int length = 0;
    length = vsnprintf (buffer, 255, format, args);
    buffer[length] = '\0';

    switch(level) {
        case JERRY_LOG_LEVEL_ERROR:     { ESP_LOGE(LOGTAG, "%s", buffer); break; }
        case JERRY_LOG_LEVEL_WARNING:   { ESP_LOGW(LOGTAG, "%s", buffer); break; }
        case JERRY_LOG_LEVEL_DEBUG:     { ESP_LOGD(LOGTAG, "%s", buffer); break; }
        case JERRY_LOG_LEVEL_TRACE:     { ESP_LOGV(LOGTAG, "%s", buffer); break; }
    }

    jerry_char_t *jbuffer = (jerry_char_t *) buffer;
    jerry_debugger_send_output (jbuffer, (jerry_size_t) length, (uint8_t) (level + 2));
#else /* If jerry-debugger isn't defined, libc is turned on */
    vfprintf (stderr, format, args);
#endif /* JERRY_DEBUGGER */
    va_end (args);
}


void jerry_port_fatal (jerry_fatal_code_t code)
{
    ESP_LOGE(LOGTAG, "Fatal Code: %d", code);
    esp_restart();
}

bool jerry_port_get_time_zone(jerry_time_zone_t *tz_p) {
    tz_p->offset = 0;
    tz_p->daylight_saving_time = false;
    return true;
}

double jerry_port_get_current_time (void) {
    return (double)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}


void jerry_port_sleep (uint32_t sleep_time) {
    vTaskDelay(sleep_time / portTICK_RATE_MS);
}

void jerryx_port_handler_print_char(char c) {
    ets_printf("%c", c);    
}