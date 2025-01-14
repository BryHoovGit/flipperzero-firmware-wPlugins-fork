#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <furi_hal_bt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RECORD_BT "bt"

typedef struct Bt Bt;

typedef enum {
    BtStatusUnavailable,
    BtStatusOff,
    BtStatusAdvertising,
    BtStatusConnected,
} BtStatus;

typedef enum {
    BtProfileSerial,
    BtProfileHidKeyboard,
} BtProfile;

typedef void (*BtStatusChangedCallback)(BtStatus status, void* context);

/** Get BT Status
* @note Call this to get current status of BT
*
* @param bt Bt instance
*
* @return BtStatus
**/
BtStatus bt_get_status(Bt* bt);

/** Change BLE Profile
 * @note Call of this function leads to 2nd core restart
 *
 * @param bt        Bt instance
 * @param profile   BtProfile
 *
 * @return          true on success
 */
bool bt_set_profile(Bt* bt, BtProfile profile);

// Set BT Name
void bt_set_profile_adv_name(Bt* bt, const char* fmt, ...);
// Get BT Name
const char* bt_get_profile_adv_name(Bt* bt);

// Set BT MAC Address
void bt_set_profile_mac_address(Bt* bt, const uint8_t mac[6]);
// Get BT MAC Address
const uint8_t* bt_get_profile_mac_address(Bt* bt);

/** Disconnect from Central
 *
 * @param bt        Bt instance
 */
void bt_disconnect(Bt* bt);

/** Set callback for Bluetooth status change notification
 *
 * @param bt        Bt instance
 * @param callback  BtStatusChangedCallback instance
 * @param context   pointer to context
 */
void bt_set_status_changed_callback(Bt* bt, BtStatusChangedCallback callback, void* context);

/** Forget bonded devices
 * @note Leads to wipe ble key storage and deleting bt.keys
 *
 * @param bt        Bt instance
 */
void bt_forget_bonded_devices(Bt* bt);

/** Set keys storage file path
 *
 * @param bt                    Bt instance
 * @param keys_storage_path     Path to file with saved keys
 */
void bt_keys_storage_set_storage_path(Bt* bt, const char* keys_storage_path);

/** Set default keys storage file path
 *
 * @param bt                    Bt instance
 */
void bt_keys_storage_set_default_path(Bt* bt);

#ifdef __cplusplus
}
#endif
