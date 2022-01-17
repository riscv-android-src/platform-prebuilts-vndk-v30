#ifndef HIDL_GENERATED_ANDROID_HARDWARE_TETHEROFFLOAD_CONTROL_V1_0_BPHWTETHERINGOFFLOADCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_TETHEROFFLOAD_CONTROL_V1_0_BPHWTETHERINGOFFLOADCALLBACK_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/tetheroffload/control/1.0/IHwTetheringOffloadCallback.h>

namespace android {
namespace hardware {
namespace tetheroffload {
namespace control {
namespace V1_0 {

struct BpHwTetheringOffloadCallback : public ::android::hardware::BpInterface<ITetheringOffloadCallback>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwTetheringOffloadCallback(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    /**
     * The pure class is what this class wraps.
     */
    typedef ITetheringOffloadCallback Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'proxy' class.
     */
    typedef ::android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    void onLastStrongRef(const void* id) override;

    // Methods from ::android::hardware::tetheroffload::control::V1_0::ITetheringOffloadCallback follow.
    static ::android::hardware::Return<void>  _hidl_onEvent(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::tetheroffload::control::V1_0::OffloadCallbackEvent event);
    static ::android::hardware::Return<void>  _hidl_updateTimeout(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::tetheroffload::control::V1_0::NatTimeoutUpdate& params);

    // Methods from ::android::hardware::tetheroffload::control::V1_0::ITetheringOffloadCallback follow.
    ::android::hardware::Return<void> onEvent(::android::hardware::tetheroffload::control::V1_0::OffloadCallbackEvent event) override;
    ::android::hardware::Return<void> updateTimeout(const ::android::hardware::tetheroffload::control::V1_0::NatTimeoutUpdate& params) override;

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
}  // namespace control
}  // namespace tetheroffload
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_TETHEROFFLOAD_CONTROL_V1_0_BPHWTETHERINGOFFLOADCALLBACK_H
