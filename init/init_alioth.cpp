/*
   Copyright (c) 2016, The CyanogenMod Project
   Copyright (c) 2019, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <fstream>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

using android::base::GetProperty;
int property_set(const char *key, const char *value) {
    return __system_property_set(key, value);
}

char const *heapstartsize;
char const *heapgrowthlimit;
char const *heapsize;
char const *heapminfree;
char const *heapmaxfree;
char const *heaptargetutilization;
bool changed = false;
char const *ro_build_fingerprint = "google/redfin/redfin:11/RQ2A.210505.003/7255357:user/release-keys"; 
char const *ro_build_description = "redfin-user 11 RQ2A.210505.003 7255357 release-keys"; 
char const *ro_stock_fingerprint = "POCO/alioth_global/alioth:11/RKQ1.200826.002/V12.0.2.0.RKHMIXM:user/release-keys";
char const *ro_stock_description = "alioth-user 11 RKQ1.200826.002 V12.0.2.0.RKHMIXM release-keys"; 

void check_device()
{
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram < 6144ull * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heapmaxfree = "32m";
    } else {
        // 8GB & 12GB RAM
        heapstartsize = "32m";
        heapgrowthlimit = "512m";
        heapsize = "768m";
        heapmaxfree = "64m";
    }
        heaptargetutilization = "0.5";
        heapminfree = "8m";
}

void property_override(char const prop[], char const value[], bool add = true)
{
    prop_info *pi;
    pi = (prop_info *) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_fprop_redfin() {
    property_override("ro.build.description", ro_build_description);
    property_override("ro.build.fingerprint", ro_build_fingerprint);
    property_override("ro.bootimage.build.fingerprint", ro_build_fingerprint);
    property_override("ro.system.build.fingerprint", ro_build_fingerprint);
    property_override("ro.vendor.build.fingerprint", ro_build_fingerprint);
    property_override("ro.product.build.fingerprint", ro_build_fingerprint);
    property_override("ro.odm.build.fingerprint", ro_build_fingerprint);
    property_override("ro.system_ext.build.fingerprint", ro_build_fingerprint);
}

void load_fprop_stock_alioth() {
    property_override("ro.build.description", ro_stock_description);
    property_override("ro.build.fingerprint", ro_stock_fingerprint);
    property_override("ro.bootimage.build.fingerprint", ro_stock_fingerprint);
    property_override("ro.system.build.fingerprint", ro_stock_fingerprint);
    property_override("ro.vendor.build.fingerprint", ro_stock_fingerprint);
    property_override("ro.product.build.fingerprint", ro_stock_fingerprint);
    property_override("ro.odm.build.fingerprint", ro_stock_fingerprint);
    property_override("ro.system_ext.build.fingerprint", ro_stock_fingerprint);
}

void load_redmi_k40() {
    property_override("ro.product.model", "Redmi K40");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "alioth");
    property_override("ro.product.name", "alioth");
    load_fprop_redfin();
}
void load_poco_f3() {
    property_override("ro.product.model", "POCO F3");
    property_override("ro.product.brand", "POCO");
    property_override("ro.product.name", "alioth");
    property_override("ro.product.device", "alioth");
    load_fprop_redfin();
}
void load_mi11x() {
    property_override("ro.product.model", "M2012K11AI");
    property_override("ro.product.brand", "Mi");
    property_override("ro.product.name", "aliothin");
    property_override("ro.product.device", "aliothin");
    property_override("ro.product.board", "aliothin");
    property_override("ro.product.vendor.name", "aliothin");
    property_override("ro.product.vendor.device", "aliothin");
    property_override("ro.product.vendor.marketname", "Mi 11X");
    property_override("ro.product.vendor.model", "M2012K11AI");
    load_fprop_redfin();
}

void load_snet() {
   property_override("ro.boot.verifiedbootstate","green");
}

void vendor_load_properties()
{
    check_device();
    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
    
    // Hide all sensitive props
    load_snet();
    
    std::string region = android::base::GetProperty("ro.boot.hwc", "");
    
    if (region.find("CN") != std::string::npos) {
        load_redmi_k40();
    }if (region.find("INDIA") != std::string::npos) {
        load_mi11x();
    } else {
        load_poco_f3();
    }
}

