#
# Copyright (C) 2020 The TwrpBuilder Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

PRODUCT_PACKAGES += \
    bootctrl.xiaomi_sm8250 \
    bootctrl.xiaomi_sm8250.recovery \
    android.hardware.boot@1.1-service \
    android.hardware.boot@1.1-impl-qti \
    android.hardware.boot@1.1-impl-qti.recovery \
    fastbootd

# SHIPPING API
PRODUCT_SHIPPING_API_LEVEL := 30
# VNDK API
PRODUCT_TARGET_VNDK_VERSION := 31

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(DEVICE_PATH)

PRODUCT_USE_DYNAMIC_PARTITIONS := true

#RECOVERY_LIBRARY_SOURCE_FILES += \
#    $(TARGET_OUT_SHARED_LIBRARIES)/libion.so \
#    $(TARGET_OUT_SYSTEM_EXT_SHARED_LIBRARIES)/vendor.display.config@1.0.so \
#    $(TARGET_OUT_SYSTEM_EXT_SHARED_LIBRARIES)/vendor.display.config@2.0.so \
#    $(TARGET_OUT_SYSTEM_EXT_SHARED_LIBRARIES)/libdisplayconfig.qti.so

# PRODUCT_RELEASE_NAME ro.twrp.device.name
PRODUCT_PROPERTY_OVERRIDES += ro.twrp.device.name=$(PRODUCT_RELEASE_NAME)

TWRP_REQUIRED_MODULES += miui_prebuilt
