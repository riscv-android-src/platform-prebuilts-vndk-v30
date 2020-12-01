#ifndef HIDL_GENERATED_ANDROID_HARDWARE_TV_TUNER_V1_0_BPHWDVR_H
#define HIDL_GENERATED_ANDROID_HARDWARE_TV_TUNER_V1_0_BPHWDVR_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/tv/tuner/1.0/IHwDvr.h>

namespace android {
namespace hardware {
namespace tv {
namespace tuner {
namespace V1_0 {

struct BpHwDvr : public ::android::hardware::BpInterface<IDvr>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwDvr(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    /**
     * The pure class is what this class wraps.
     */
    typedef IDvr Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'proxy' class.
     */
    typedef ::android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    void onLastStrongRef(const void* id) override;

    // Methods from ::android::hardware::tv::tuner::V1_0::IDvr follow.
    static ::android::hardware::Return<void>  _hidl_getQueueDesc(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getQueueDesc_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_configure(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::tv::tuner::V1_0::DvrSettings& settings);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_attachFilter(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::sp<::android::hardware::tv::tuner::V1_0::IFilter>& filter);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_detachFilter(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::sp<::android::hardware::tv::tuner::V1_0::IFilter>& filter);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_start(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_stop(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_flush(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);
    static ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result>  _hidl_close(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);

    // Methods from ::android::hardware::tv::tuner::V1_0::IDvr follow.
    ::android::hardware::Return<void> getQueueDesc(getQueueDesc_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> configure(const ::android::hardware::tv::tuner::V1_0::DvrSettings& settings) override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> attachFilter(const ::android::sp<::android::hardware::tv::tuner::V1_0::IFilter>& filter) override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> detachFilter(const ::android::sp<::android::hardware::tv::tuner::V1_0::IFilter>& filter) override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> start() override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> stop() override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> flush() override;
    ::android::hardware::Return<::android::hardware::tv::tuner::V1_0::Result> close() override;

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

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_TV_TUNER_V1_0_BPHWDVR_H
