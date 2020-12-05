#ifndef HIDL_GENERATED_ANDROID_FRAMEWORKS_SCHEDULERSERVICE_V1_0_BNHWSCHEDULINGPOLICYSERVICE_H
#define HIDL_GENERATED_ANDROID_FRAMEWORKS_SCHEDULERSERVICE_V1_0_BNHWSCHEDULINGPOLICYSERVICE_H

#include <android/frameworks/schedulerservice/1.0/IHwSchedulingPolicyService.h>

namespace android {
namespace frameworks {
namespace schedulerservice {
namespace V1_0 {

struct BnHwSchedulingPolicyService : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwSchedulingPolicyService(const ::android::sp<ISchedulingPolicyService> &_hidl_impl);
    explicit BnHwSchedulingPolicyService(const ::android::sp<ISchedulingPolicyService> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwSchedulingPolicyService();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef ISchedulingPolicyService Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef ::android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<ISchedulingPolicyService> getImpl() { return _hidl_mImpl; }
    // Methods from ::android::frameworks::schedulerservice::V1_0::ISchedulingPolicyService follow.
    static ::android::status_t _hidl_requestPriority(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_getMaxAllowedPriority(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::android::frameworks::schedulerservice::V1_0::ISchedulingPolicyService follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<ISchedulingPolicyService> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace schedulerservice
}  // namespace frameworks
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_FRAMEWORKS_SCHEDULERSERVICE_V1_0_BNHWSCHEDULINGPOLICYSERVICE_H
