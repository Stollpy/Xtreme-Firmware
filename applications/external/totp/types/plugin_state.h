#pragma once

#include <notification/notification.h>
#include <gui/gui.h>
#include <dialogs/dialogs.h>
#include "../features_config.h"
#include "../ui/totp_scenes_enum.h"
#include "../services/config/config_file_context.h"
#include "../services/idle_timeout/idle_timeout.h"
#include "notification_method.h"
#include "automation_method.h"
#ifdef TOTP_BADBT_TYPE_ENABLED
#include "../workers/bt_type_code/bt_type_code.h"
#endif

#define TOTP_IV_SIZE (16)

/**
 * @brief Application state structure
 */
typedef struct {
    /**
     * @brief Application current scene
     */
    Scene current_scene;

    /**
     * @brief Application current scene state
     */
    void* current_scene_state;

    /**
     * @brief Reference to the firmware notification subsystem
     */
    NotificationApp* notification_app;

    /**
     * @brief Reference to the firmware dialogs subsystem 
     */
    DialogsApp* dialogs_app;

    /**
     * @brief Reference to the firmware GUI subsystem
     */
    Gui* gui;

    /**
     * @brief Timezone UTC offset in hours 
     */
    float timezone_offset;

    /**
     * @brief Config file context
     */
    ConfigFileContext* config_file_context;

    /**
     * @brief Encrypted well-known string data
     */
    uint8_t* crypto_verify_data;

    /**
     * @brief Encrypted well-known string data length
     */
    size_t crypto_verify_data_length;

    /**
     * @brief Whether PIN is set by user or not 
     */
    bool pin_set;

    /**
     * @brief Initialization vector (IV) to be used for encryption\decryption 
     */
    uint8_t iv[TOTP_IV_SIZE];

    /**
     * @brief Basic randomly-generated initialization vector (IV)
     */
    uint8_t base_iv[TOTP_IV_SIZE];

    /**
     * @brief Notification method
     */
    NotificationMethod notification_method;

    /**
     * @brief Main rendering loop mutex
     */
    FuriMutex* mutex;

    /**
     * @brief Automation method
     */
    AutomationMethod automation_method;

#ifdef TOTP_BADBT_TYPE_ENABLED
    /**
     * @brief Bad-Bluetooth worker context
     */
    TotpBtTypeCodeWorkerContext* bt_type_code_worker_context;
#endif

    /**
     * @brief IDLE timeout context
     */
    IdleTimeoutContext* idle_timeout_context;

    /**
     * @brief Font index to be used to draw TOTP token
     */
    uint8_t active_font_index;
} PluginState;
