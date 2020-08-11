#ifndef HIDL_GENERATED_ANDROID_HARDWARE_WIFI_OFFLOAD_V1_0_BNHWOFFLOADCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_WIFI_OFFLOAD_V1_0_BNHWOFFLOADCALLBACK_H

#include <android/hardware/wifi/offload/1.0/IHwOffloadCallback.h>

namespace android {
namespace hardware {
namespace wifi {
namespace offload {
namespace V1_0 {

struct BnHwOffloadCallback : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwOffloadCallback(const ::android::sp<IOffloadCallback> &_hidl_impl);
    explicit BnHwOffloadCallback(const ::android::sp<IOffloadCallback> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwOffloadCallback();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef IOffloadCallback Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<IOffloadCallback> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::hardware::wifi::offload::V1_0::IOffloadCallback follow.
    static ::android::status_t _hidl_onScanResult(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_onError(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::hardware::wifi::offload::V1_0::IOffloadCallback follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IOffloadCallback> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace offload
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_WIFI_OFFLOAD_V1_0_BNHWOFFLOADCALLBACK_H
