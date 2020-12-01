#ifndef HIDL_GENERATED_ANDROID_HARDWARE_NEURALNETWORKS_V1_0_BNHWPREPAREDMODEL_H
#define HIDL_GENERATED_ANDROID_HARDWARE_NEURALNETWORKS_V1_0_BNHWPREPAREDMODEL_H

#include <android/hardware/neuralnetworks/1.0/IHwPreparedModel.h>

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace V1_0 {

struct BnHwPreparedModel : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwPreparedModel(const ::android::sp<IPreparedModel> &_hidl_impl);
    explicit BnHwPreparedModel(const ::android::sp<IPreparedModel> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwPreparedModel();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef IPreparedModel Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<IPreparedModel> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::hardware::neuralnetworks::V1_0::IPreparedModel follow.
    static ::android::status_t _hidl_execute(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::hardware::neuralnetworks::V1_0::IPreparedModel follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IPreparedModel> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace neuralnetworks
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_NEURALNETWORKS_V1_0_BNHWPREPAREDMODEL_H
