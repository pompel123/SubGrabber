#include "universal_grabber.h"
#include "scenes/scene_main_menu.h"
#include "scenes/scene_send_main.h"
#include "scenes/scene_send_saved.h"
#include "scenes/scene_grabbing.h"
#include "scenes/scene_bruting.h"
#include "scenes/scene_jammer.h"
#include "scenes/scene_copy.h"
#include "scenes/scene_algo_sender.h"
#include "scenes/scene_settings.h"
#include "scenes/scene_utilities.h"

const SceneManagerHandlers universal_grabber_scene_handlers = {
    .on_enter_handlers = {
        [SceneMainMenu] = universal_grabber_scene_main_menu_on_enter,
        [SceneSendMain] = universal_grabber_scene_send_main_on_enter,
        [SceneSendSaved] = universal_grabber_scene_send_saved_on_enter,
        [SceneGrabbing] = universal_grabber_scene_grabbing_on_enter,
        [SceneBruting] = universal_grabber_scene_bruting_on_enter,
        [SceneJammer] = universal_grabber_scene_jammer_on_enter,
        [SceneCopy] = universal_grabber_scene_copy_on_enter,
        [SceneAlgoSender] = universal_grabber_scene_algo_sender_on_enter,
        [SceneSettings] = universal_grabber_scene_settings_on_enter,
        [SceneUtilities] = universal_grabber_scene_utilities_on_enter,
    },
    .on_event_handlers = {
        [SceneMainMenu] = universal_grabber_scene_main_menu_on_event,
        [SceneSendMain] = universal_grabber_scene_send_main_on_event,
        [SceneSendSaved] = universal_grabber_scene_send_saved_on_event,
        [SceneGrabbing] = universal_grabber_scene_grabbing_on_event,
        [SceneBruting] = universal_grabber_scene_bruting_on_event,
        [SceneJammer] = universal_grabber_scene_jammer_on_event,
        [SceneCopy] = universal_grabber_scene_copy_on_event,
        [SceneAlgoSender] = universal_grabber_scene_algo_sender_on_event,
        [SceneSettings] = universal_grabber_scene_settings_on_event,
        [SceneUtilities] = universal_grabber_scene_utilities_on_event,
    },
    .on_exit_handlers = {
        [SceneMainMenu] = universal_grabber_scene_main_menu_on_exit,
        [SceneSendMain] = universal_grabber_scene_send_main_on_exit,
        [SceneSendSaved] = universal_grabber_scene_send_saved_on_exit,
        [SceneGrabbing] = universal_grabber_scene_grabbing_on_exit,
        [SceneBruting] = universal_grabber_scene_bruting_on_exit,
        [SceneJammer] = universal_grabber_scene_jammer_on_exit,
        [SceneCopy] = universal_grabber_scene_copy_on_exit,
        [SceneAlgoSender] = universal_grabber_scene_algo_sender_on_exit,
        [SceneSettings] = universal_grabber_scene_settings_on_exit,
        [SceneUtilities] = universal_grabber_scene_utilities_on_exit,
    },
};

static bool universal_grabber_custom_event_callback(void* context, uint32_t event) {
    UniversalGrabber* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, event);
}

static bool universal_grabber_back_event_callback(void* context) {
    UniversalGrabber* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

static void ensure_storage_dir(UniversalGrabber* app) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    storage_common_mkdir(storage, STORAGE_PATH);
    furi_record_close(RECORD_STORAGE);
}

static void load_codes(UniversalGrabber* app) {
    ensure_storage_dir(app);
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    if(storage_file_open(file, MAIN_CODES_FILE, FSAM_READ, FSOM_OPEN_EXISTING)) {
        storage_file_read(file, app->main_codes, sizeof(app->main_codes));
        storage_file_close(file);
    } else {
        memset(app->main_codes, 0, sizeof(app->main_codes));
    }

    if(storage_file_open(file, SAVED_CODES_FILE, FSAM_READ, FSOM_OPEN_EXISTING)) {
        storage_file_read(file, app->saved_codes, sizeof(app->saved_codes));
        storage_file_close(file);
    } else {
        memset(app->saved_codes, 0, sizeof(app->saved_codes));
    }

    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
}

static void save_codes(UniversalGrabber* app) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    storage_file_open(file, MAIN_CODES_FILE, FSAM_WRITE, FSOM_CREATE_ALWAYS);
    storage_file_write(file, app->main_codes, sizeof(app->main_codes));
    storage_file_close(file);

    storage_file_open(file, SAVED_CODES_FILE, FSAM_WRITE, FSOM_CREATE_ALWAYS);
    storage_file_write(file, app->saved_codes, sizeof(app->saved_codes));
    storage_file_close(file);

    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
}

int32_t universal_grabber_app(void* p) {
    UNUSED(p);
    UniversalGrabber* app = malloc(sizeof(UniversalGrabber));
    memset(app, 0, sizeof(UniversalGrabber));

    app->subghz = furi_record_open(RECORD_SUBGHZ);
    app->notifications = furi_record_open(RECORD_NOTIFICATION);

    app->view_dispatcher = view_dispatcher_alloc();
    app->scene_manager = scene_manager_alloc(&universal_grabber_scene_handlers, app);
    app->submenu = submenu_alloc();
    app->var_item_list = variable_item_list_alloc();
    app->widget = widget_alloc();

    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, universal_grabber_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, universal_grabber_back_event_callback);

    view_dispatcher_attach_to_gui(app->view_dispatcher, furi_record_open(RECORD_GUI), ViewDispatcherTypeFullscreen);

    // Default settings
    app->buzzer_enabled = true;
    app->vibro_enabled = true;
    app->grab_multi = 3;
    app->min_grab_len = 10;
    app->main_code_pos = 0;
    app->saved_code_pos = 0;

    load_codes(app);

    scene_manager_next_scene(app->scene_manager, SceneMainMenu);

    view_dispatcher_run(app->view_dispatcher);

    save_codes(app);  // save on exit

    // Cleanup
    view_dispatcher_free(app->view_dispatcher);
    scene_manager_free(app->scene_manager);
    submenu_free(app->submenu);
    variable_item_list_free(app->var_item_list);
    widget_free(app->widget);
    furi_record_close(RECORD_SUBGHZ);
    furi_record_close(RECORD_NOTIFICATION);
    free(app);

    return 0;
}
