#include "../universal_grabber.h"

void universal_grabber_scene_send_main_on_enter(void* context) {
    UniversalGrabber* app = context;
    widget_reset(app->widget);

    if(app->main_code_pos >= MAX_CODES) app->main_code_pos = 0;
    CodeSlot* code = &app->main_codes[app->main_code_pos];
    app->current_code = *code;

    char buf[64];
    snprintf(buf, sizeof(buf), "Main Slot %lu", app->main_code_pos + 1);
    widget_add_string_element(app->widget, 0, 0, AlignLeft, AlignTop, FontPrimary, buf);

    snprintf(buf, sizeof(buf), "Prot:%u Bits:%u", code->protocol, code->bit_length);
    widget_add_string_element(app->widget, 0, 12, AlignLeft, AlignTop, FontSecondary, buf);

    snprintf(buf, sizeof(buf), "Data:%016llX", code->data);
    widget_add_string_element(app->widget, 0, 24, AlignLeft, AlignTop, FontSecondary, buf);

    widget_add_string_element(app->widget, 0, 40, AlignCenter, AlignTop, FontSecondary, "Press OK to Send");

    view_dispatcher_switch_to_view(app->view_dispatcher, WidgetView);
}

bool universal_grabber_scene_send_main_on_event(void* context, SceneManagerEvent event) {
    UniversalGrabber* app = context;
    if(event.type == SceneManagerEventTypeCustom && event.event == 0) {  // OK
        notification_message(app->notifications, &sequence_blink_start_blue);
        if(app->buzzer_enabled) notification_message(app->notifications, &sequence_beep);
        if(app->vibro_enabled) notification_message(app->notifications, &sequence_single_vibro);

        // Real transmit would go here: subghz_transmit_... with current_code

        widget_add_string_element(app->widget, 110, 40, AlignRight, AlignTop, FontPrimary, "*");

        furi_delay_ms(600);

        notification_message(app->notifications, &sequence_blink_stop);
        return true;
    }
    if(event.type == SceneManagerEventTypeBack) {
        return true;
    }
    return false;
}

void universal_grabber_scene_send_main_on_exit(void* context) {
    UNUSED(context);
}
