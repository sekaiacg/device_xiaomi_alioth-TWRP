#
# Copyright (C) 2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from sm8250-common
$(call inherit-product, device/xiaomi/sm8250-common/kona.mk)

# Descendant
TARGET_FACE_UNLOCK_SUPPORT := YES
PRODUCT_BOARD_PLATFORM := sm8250
TARGET_SUPPORTS_BLUR := true
BUILD_TYPE := Official

# Keylayout
PRODUCT_COPY_FILES += \
     $(LOCAL_PATH)/keylayout/gpio-keys.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/gpio-keys.kl

#KernelModules
#PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,$(LOCAL_PATH)/prebuilt/modules,$(TARGET_COPY_OUT_PRODUCT)/vendor_overlay/30/lib/modules)
