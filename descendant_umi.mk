#
# Copyright (C) 2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from umi device
$(call inherit-product, device/xiaomi/umi/device.mk)

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/descendant/config/common_full_phone.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := descendant_umi
PRODUCT_DEVICE := umi
PRODUCT_BRAND := Xiaomi
PRODUCT_MANUFACTURER := Xiaomi
PRODUCT_MODEL := Mi 10

TARGET_BOOT_ANIMATION_RES := 1080

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi
