#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUTOMOTIVE_EVS_V1_0_BNHWEVSENUMERATOR_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUTOMOTIVE_EVS_V1_0_BNHWEVSENUMERATOR_H

#include <android/hardware/automotive/evs/1.0/IHwEvsEnumerator.h>

namespace android {
namespace hardware {
namespace automotive {
namespace evs {
namespace V1_0 {

struct BnHwEvsEnumerator : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwEvsEnumerator(const ::android::sp<IEvsEnumerator> &_hidl_impl);
    explicit BnHwEvsEnumerator(const ::android::sp<IEvsEnumerator> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwEvsEnumerator();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef IEvsEnumerator Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<IEvsEnumerator> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::hardware::automotive::evs::V1_0::IEvsEnumerator follow.
    static ::android::status_t _hidl_getCameraList(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_openCamera(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_closeCamera(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_openDisplay(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_closeDisplay(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_getDisplayState(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::hardware::automotive::evs::V1_0::IEvsEnumerator follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IEvsEnumerator> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace evs
}  // namespace automotive
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUTOMOTIVE_EVS_V1_0_BNHWEVSENUMERATOR_H
