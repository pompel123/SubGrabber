#include "../universal_grabber.h"

void universal_grabber_scene_algo_sender_on_enter(void* context) {
    UniversalGrabber* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 0, AlignCenter, AlignTop, FontPrimary, "Algo Code Sender");
    widget_add_string_element(app->widget, 0, 20, AlignCenter, AlignTop, FontSecondary, "Manufacturer learning");
    widget_add_string_element(app->widget, 0, 40, AlignCenter, AlignTop, FontSecondary, "Not fully implemented yet");
    view_dispatcher_switch_to_view(app->view_dispatcher, WidgetView);
}

bool universal_grabber_scene_algo_sender_on_event(void* context, SceneManagerEvent event) {
    return false;
}

void universal_grabber_scene_algo_sender_on_exit(void* context) {
    UNUSED(context);
}
