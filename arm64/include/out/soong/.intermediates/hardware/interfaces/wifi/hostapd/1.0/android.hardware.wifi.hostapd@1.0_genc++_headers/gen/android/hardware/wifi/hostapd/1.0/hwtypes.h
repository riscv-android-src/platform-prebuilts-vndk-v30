#ifndef HIDL_GENERATED_ANDROID_HARDWARE_WIFI_HOSTAPD_V1_0_HWTYPES_H
#define HIDL_GENERATED_ANDROID_HARDWARE_WIFI_HOSTAPD_V1_0_HWTYPES_H

#include <android/hardware/wifi/hostapd/1.0/types.h>


#include <hidl/Status.h>
#include <hwbinder/IBinder.h>
#include <hwbinder/Parcel.h>

namespace android {
namespace hardware {
namespace wifi {
namespace hostapd {
namespace V1_0 {
::android::status_t readEmbeddedFromParcel(
        const ::android::hardware::wifi::hostapd::V1_0::HostapdStatus &obj,
        const ::android::hardware::Parcel &parcel,
        size_t parentHandle,
        size_t parentOffset);

::android::status_t writeEmbeddedToParcel(
        const ::android::hardware::wifi::hostapd::V1_0::HostapdStatus &obj,
        ::android::hardware::Parcel *parcel,
        size_t parentHandle,
        size_t parentOffset);

}  // namespace V1_0
}  // namespace hostapd
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_WIFI_HOSTAPD_V1_0_HWTYPES_H
