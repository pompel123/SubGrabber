#include "../universal_grabber.h"

void universal_grabber_scene_jammer_on_enter(void* context) {
    UniversalGrabber* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 0, AlignCenter, AlignTop, FontPrimary, "Noise Maker");
    widget_add_string_element(app->widget, 0, 20, AlignCenter, AlignTop, FontSecondary, "Jamming 433.92 MHz");
    widget_add_string_element(app->widget, 0, 40, AlignCenter, AlignTop, FontSecondary, "Back to stop");
    // Start continuous noise (real: subghz tx raw or carrier)
    view_dispatcher_switch_to_view(app->view_dispatcher, WidgetView);
}

bool universal_grabber_scene_jammer_on_event(void* context, SceneManagerEvent event) {
    if(event.type == SceneManagerEventTypeBack) {
        // stop jamming
        return true;
    }
    return false;
}

void universal_grabber_scene_jammer_on_exit(void* context) {
    UNUSED(context);
}
