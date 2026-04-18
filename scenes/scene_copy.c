#include "../universal_grabber.h"

void universal_grabber_scene_copy_on_enter(void* context) {
    UniversalGrabber* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 0, AlignCenter, AlignTop, FontPrimary, "Copy Saved -> Main");
    widget_add_string_element(app->widget, 0, 20, AlignCenter, AlignTop, FontSecondary, "OK to copy current");
    view_dispatcher_switch_to_view(app->view_dispatcher, WidgetView);
}

bool universal_grabber_scene_copy_on_event(void* context, SceneManagerEvent event) {
    UniversalGrabber* app = context;
    if(event.type == SceneManagerEventTypeCustom && event.event == 0) {
        if(app->saved_code_pos < MAX_CODES && app->main_code_pos < MAX_CODES) {
            app->main_codes[app->main_code_pos] = app->saved_codes[app->saved_code_pos];
            widget_add_string_element(app->widget, 0, 40, AlignCenter, AlignTop, FontSecondary, "Copied!");
        }
        return true;
    }
    return false;
}

void universal_grabber_scene_copy_on_exit(void* context) {
    UNUSED(context);
}
