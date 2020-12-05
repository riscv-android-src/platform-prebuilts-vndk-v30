#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_1_BNHWSURFACEFLINGERCONFIGS_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_1_BNHWSURFACEFLINGERCONFIGS_H

#include <android/hardware/configstore/1.1/IHwSurfaceFlingerConfigs.h>

namespace android {
namespace hardware {
namespace configstore {
namespace V1_1 {

struct BnHwSurfaceFlingerConfigs : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwSurfaceFlingerConfigs(const ::android::sp<ISurfaceFlingerConfigs> &_hidl_impl);
    explicit BnHwSurfaceFlingerConfigs(const ::android::sp<ISurfaceFlingerConfigs> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwSurfaceFlingerConfigs();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef ISurfaceFlingerConfigs Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<ISurfaceFlingerConfigs> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs follow.
    static ::android::status_t _hidl_primaryDisplayOrientation(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::hardware::configstore::V1_0::ISurfaceFlingerConfigs follow.

    // Methods from ::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<ISurfaceFlingerConfigs> _hidl_mImpl;
};

}  // namespace V1_1
}  // namespace configstore
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_1_BNHWSURFACEFLINGERCONFIGS_H
