/*
 * Custom Battery Type Behavior for ZMK
 * v0.3 API対応版
 */

#define DT_DRV_COMPAT zmk_custom_battery_type

#include <device.h>
#include <drivers/behavior.h>
#include <zmk/behavior.h>
#include <zmk/ble.h>

// v0.3への修正: bluetooth を削除
#include <zmk/split/central.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_battery_type_config {
    // 設定構造体
};

struct behavior_battery_type_data {
    // データ構造体
};

static int behavior_battery_type_init(const struct device *dev) {
      return 0;
}

static int on_battery_type_binding_pressed(struct zmk_behavior_binding *binding,
                                          struct zmk_behavior_binding_processing_state *state) {
      LOG_DBG("Battery type behavior pressed");
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_battery_type_binding_released(struct zmk_behavior_binding *binding,
                                           struct zmk_behavior_binding_processing_state *state) {
      LOG_DBG("Battery type behavior released");

    // v0.3への修正: 関数名から bluetooth を削除
    uint8_t level = 0;
    int ret = zmk_split_central_get_peripheral_battery_level(0, &level);

    if (ret == 0) {
        LOG_INF("Peripheral battery level: %u%%", level);
    }

    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_battery_type_driver_api = {
    .binding_pressed = on_battery_type_binding_pressed,
    .binding_released = on_battery_type_binding_released,
};

DEVICE_DT_INST_DEFINE(0,
                     behavior_battery_type_init,
                     NULL,
                     NULL,
                     NULL,
                     APPLICATION,
                     CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                     &behavior_battery_type_driver_api);
