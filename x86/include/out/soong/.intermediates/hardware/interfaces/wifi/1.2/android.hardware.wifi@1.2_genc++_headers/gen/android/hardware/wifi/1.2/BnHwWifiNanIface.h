#ifndef HIDL_GENERATED_ANDROID_HARDWARE_WIFI_V1_2_BNHWWIFINANIFACE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_WIFI_V1_2_BNHWWIFINANIFACE_H

#include <android/hardware/wifi/1.2/IHwWifiNanIface.h>

namespace android {
namespace hardware {
namespace wifi {
namespace V1_2 {

struct BnHwWifiNanIface : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwWifiNanIface(const ::android::sp<IWifiNanIface> &_hidl_impl);
    explicit BnHwWifiNanIface(const ::android::sp<IWifiNanIface> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwWifiNanIface();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef IWifiNanIface Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<IWifiNanIface> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::hardware::wifi::V1_2::IWifiNanIface follow.
    static ::android::status_t _hidl_registerEventCallback_1_2(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_enableRequest_1_2(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_configRequest_1_2(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::hardware::wifi::V1_0::IWifiIface follow.

    // Methods from ::android::hardware::wifi::V1_0::IWifiNanIface follow.

    // Methods from ::android::hardware::wifi::V1_2::IWifiNanIface follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IWifiNanIface> _hidl_mImpl;
};

}  // namespace V1_2
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_WIFI_V1_2_BNHWWIFINANIFACE_H
