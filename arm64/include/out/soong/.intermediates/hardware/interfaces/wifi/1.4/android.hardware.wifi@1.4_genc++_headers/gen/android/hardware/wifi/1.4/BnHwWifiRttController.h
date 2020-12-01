#ifndef HIDL_GENERATED_ANDROID_HARDWARE_WIFI_V1_4_BNHWWIFIRTTCONTROLLER_H
#define HIDL_GENERATED_ANDROID_HARDWARE_WIFI_V1_4_BNHWWIFIRTTCONTROLLER_H

#include <android/hardware/wifi/1.4/IHwWifiRttController.h>

namespace android {
namespace hardware {
namespace wifi {
namespace V1_4 {

struct BnHwWifiRttController : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwWifiRttController(const ::android::sp<IWifiRttController> &_hidl_impl);
    explicit BnHwWifiRttController(const ::android::sp<IWifiRttController> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwWifiRttController();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef IWifiRttController Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<IWifiRttController> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::hardware::wifi::V1_4::IWifiRttController follow.
    static ::android::status_t _hidl_registerEventCallback_1_4(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_rangeRequest_1_4(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_getCapabilities_1_4(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_getResponderInfo_1_4(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_enableResponder_1_4(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::hardware::wifi::V1_0::IWifiRttController follow.

    // Methods from ::android::hardware::wifi::V1_4::IWifiRttController follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IWifiRttController> _hidl_mImpl;
};

}  // namespace V1_4
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_WIFI_V1_4_BNHWWIFIRTTCONTROLLER_H
