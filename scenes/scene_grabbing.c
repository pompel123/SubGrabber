#include "../universal_grabber.h"

static void grabbing_rx_callback(void* context) {
    UniversalGrabber* app = context;

    // Simulated full decode - replace with real SubGhz decoder in production
    uint16_t prot = 1;
    uint16_t bits = 24;
    uint64_t data = 0xABCDEF123456ULL;

    app->current_code.protocol = prot;
    app->current_code.bit_length = bits;
    app->current_code.data = data;

    // Save to saved codes
    if(app->saved_code_pos >= MAX_CODES) app->saved_code_pos = 0;
    app->saved_codes[app->saved_code_pos] = app->current_code;
    app->saved_code_pos++;

    notification_message(app->notifications, &sequence_success);
    if(app->buzzer_enabled) notification_message(app->notifications, &sequence_beep);
    if(app->vibro_enabled) notification_message(app->notifications, &sequence_single_vibro);

    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 0, AlignLeft, AlignTop, FontPrimary, "Code Captured!");

    char line[32];
    snprintf(line, sizeof(line), "Prot: %u  Bits: %u", prot, bits);
    widget_add_string_element(app->widget, 0, 12, AlignLeft, AlignTop, FontSecondary, line);

    snprintf(line, sizeof(line), "Data: %016llX", data);
    widget_add_string_element(app->widget, 0, 24, AlignLeft, AlignTop, FontSecondary, line);

    widget_add_string_element(app->widget, 0, 40, AlignCenter, AlignTop, FontSecondary, "Saved!");
}

void universal_grabber_scene_grabbing_on_enter(void* context) {
    UniversalGrabber* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 0, AlignCenter, AlignTop, FontPrimary, "Grabbing 433.92 MHz");
    widget_add_string_element(app->widget, 0, 20, AlignCenter, AlignTop, FontSecondary, "Waiting for signal...");

    // Start RX (real implementation uses subghz worker or protocol decoder)
    subghz_rx_start(app->subghz, FREQUENCY);

    // For demo, simulate a capture after delay - in real app use callback
    furi_delay_ms(1500);
    grabbing_rx_callback(app);

    view_dispatcher_switch_to_view(app->view_dispatcher, WidgetView);
}

bool universal_grabber_scene_grabbing_on_event(void* context, SceneManagerEvent event) {
    UniversalGrabber* app = context;
    if(event.type == SceneManagerEventTypeBack) {
        subghz_rx_stop(app->subghz);
        return true;
    }
    return false;
}

void universal_grabber_scene_grabbing_on_exit(void* context) {
    UniversalGrabber* app = context;
    subghz_rx_stop(app->subghz);
}
