#include "../universal_grabber.h"

void universal_grabber_scene_settings_on_enter(void* context) {
    UniversalGrabber* app = context;
    VariableItemList* list = app->var_item_list;
    variable_item_list_reset(list);

    variable_item_list_add(list, "Buzzer", 2, NULL, app);  // on/off
    variable_item_list_add(list, "Vibration", 2, NULL, app);
    // add more items for grab_multi, min_grab_len etc.

    view_dispatcher_switch_to_view(app->view_dispatcher, VariableItemListView);
}

bool universal_grabber_scene_settings_on_event(void* context, SceneManagerEvent event) {
    return false;
}

void universal_grabber_scene_settings_on_exit(void* context) {
    UNUSED(context);
}
