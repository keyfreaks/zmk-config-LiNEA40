if(CONFIG_ZMK_BEHAVIOR_BATTERY_TYPE)
  zephyr_library()
    zephyr_library_sources(src/behavior_battery_type.c)
    endif()
