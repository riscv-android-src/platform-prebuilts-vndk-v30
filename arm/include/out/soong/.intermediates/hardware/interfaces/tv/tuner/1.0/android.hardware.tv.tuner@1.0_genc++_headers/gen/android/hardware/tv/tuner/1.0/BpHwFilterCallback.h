#ifndef HIDL_GENERATED_ANDROID_HARDWARE_TV_TUNER_V1_0_BPHWFILTERCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_TV_TUNER_V1_0_BPHWFILTERCALLBACK_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/tv/tuner/1.0/IHwFilterCallback.h>

namespace android {
namespace hardware {
namespace tv {
namespace tuner {
namespace V1_0 {

struct BpHwFilterCallback : public ::android::hardware::BpInterface<IFilterCallback>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwFilterCallback(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    /**
     * The pure class is what this class wraps.
     */
    typedef IFilterCallback Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'proxy' class.
     */
    typedef ::android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    void onLastStrongRef(const void* id) override;

    // Methods from ::android::hardware::tv::tuner::V1_0::IFilterCallback follow.
    static ::android::hardware::Return<void>  _hidl_onFilterEvent(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::tv::tuner::V1_0::DemuxFilterEvent& filterEvent);
    static ::android::hardware::Return<void>  _hidl_onFilterStatus(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::tv::tuner::V1_0::DemuxFilterStatus status);

    // Methods from ::android::hardware::tv::tuner::V1_0::IFilterCallback follow.
    ::android::hardware::Return<void> onFilterEvent(const ::android::hardware::tv::tuner::V1_0::DemuxFilterEvent& filterEvent) override;
    ::android::hardware::Return<void> onFilterStatus(::android::hardware::tv::tuner::V1_0::DemuxFilterStatus status) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> setHALInstrumentation() override;
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<void> ping() override;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;
    ::android::hardware::Return<void> notifySyspropsChanged() override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};

}  // namespace V1_0
}  // namespace tuner
}  // namespace tv
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_TV_TUNER_V1_0_BPHWFILTERCALLBACK_H
