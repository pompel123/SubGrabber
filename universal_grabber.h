#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/widget.h>
#include <subghz/subghz.h>
#include <subghz/subghz_tx_rx_worker.h>
#include <notification/notification.h>
#include <storage/storage.h>

#define MAX_CODES 30
#define FREQUENCY 433920000  // 433.92 MHz

// Storage paths
#define STORAGE_PATH "/ext/apps_data/universal_grabber"
#define MAIN_CODES_FILE STORAGE_PATH "/main_codes.bin"
#define SAVED_CODES_FILE STORAGE_PATH "/saved_codes.bin"

// Code slot structure (12 bytes, exactly like your Arduino EEPROM)
typedef struct {
    uint16_t protocol;
    uint16_t bit_length;
    uint64_t data;
} CodeSlot;

typedef struct {
    SubGhz* subghz;
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;
    Submenu* submenu;
    VariableItemList* var_item_list;
    Widget* widget;

    NotificationApp* notifications;

    // Code positions
    uint32_t main_code_pos;
    uint32_t saved_code_pos;

    // Current code data
    CodeSlot current_code;

    // All stored codes
    CodeSlot main_codes[MAX_CODES];
    CodeSlot saved_codes[MAX_CODES];

    // Settings
    bool buzzer_enabled;
    bool vibro_enabled;
    uint8_t grab_multi;
    uint8_t min_grab_len;
    bool brute_direction;  // false = forward
} UniversalGrabber;

extern const SceneManagerHandlers universal_grabber_scene_handlers;
