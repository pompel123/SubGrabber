#include "../universal_grabber.h"

void universal_grabber_scene_bruting_on_enter(void* context) {
    UniversalGrabber* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 0, AlignCenter, AlignTop, FontPrimary, "Bruting 12-bit codes");
    widget_add_string_element(app->widget, 0, 20, AlignCenter, AlignTop, FontSecondary, "Press OK to start");
    view_dispatcher_switch_to_view(app->view_dispatcher, WidgetView);
}

bool universal_grabber_scene_bruting_on_event(void* context, SceneManagerEvent event) {
    // TODO: implement brute loop sending 000 to FFF with delay
    return false;
}

void universal_grabber_scene_bruting_on_exit(void* context) {
    UNUSED(context);
}
