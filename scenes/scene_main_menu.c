#include "../universal_grabber.h"

void universal_grabber_scene_main_menu_on_enter(void* context) {
    UniversalGrabber* app = context;
    Submenu* submenu = app->submenu;
    submenu_reset(submenu);

    submenu_add_item(submenu, "Send main code  ", 0, NULL, app);
    submenu_add_item(submenu, "Send saved code ", 1, NULL, app);
    submenu_add_item(submenu, "Grabbing radio  ", 2, NULL, app);
    submenu_add_item(submenu, "Bruting code    ", 3, NULL, app);
    submenu_add_item(submenu, "Noice Maker     ", 4, NULL, app);
    submenu_add_item(submenu, "Copy saved->main", 5, NULL, app);
    submenu_add_item(submenu, "Algo code sender", 6, NULL, app);
    submenu_add_item(submenu, "Settings        ", 7, NULL, app);
    submenu_add_item(submenu, "Utilites        ", 8, NULL, app);

    submenu_set_selected_item(submenu, 2);  // Default to Grabbing
    view_dispatcher_switch_to_view(app->view_dispatcher, SubmenuView);
}

bool universal_grabber_scene_main_menu_on_event(void* context, SceneManagerEvent event) {
    UniversalGrabber* app = context;
    if (event.type == SceneManagerEventTypeCustom) {
        switch (event.event) {
            case 0: scene_manager_next_scene(app->scene_manager, SceneSendMain); return true;
            case 1: scene_manager_next_scene(app->scene_manager, SceneSendSaved); return true;
            case 2: scene_manager_next_scene(app->scene_manager, SceneGrabbing); return true;
            case 3: scene_manager_next_scene(app->scene_manager, SceneBruting); return true;
            case 4: scene_manager_next_scene(app->scene_manager, SceneJammer); return true;
            case 5: scene_manager_next_scene(app->scene_manager, SceneCopy); return true;
            case 6: scene_manager_next_scene(app->scene_manager, SceneAlgoSender); return true;
            case 7: scene_manager_next_scene(app->scene_manager, SceneSettings); return true;
            case 8: scene_manager_next_scene(app->scene_manager, SceneUtilities); return true;
        }
    }
    return false;
}

void universal_grabber_scene_main_menu_on_exit(void* context) {
    UNUSED(context);
}
