#ifndef HIDL_GENERATED_ANDROID_HARDWARE_WIFI_SUPPLICANT_V1_2_BPHWSUPPLICANTSTAIFACECALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_WIFI_SUPPLICANT_V1_2_BPHWSUPPLICANTSTAIFACECALLBACK_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/wifi/supplicant/1.2/IHwSupplicantStaIfaceCallback.h>

namespace android {
namespace hardware {
namespace wifi {
namespace supplicant {
namespace V1_2 {

struct BpHwSupplicantStaIfaceCallback : public ::android::hardware::BpInterface<ISupplicantStaIfaceCallback>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwSupplicantStaIfaceCallback(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    /**
     * The pure class is what this class wraps.
     */
    typedef ISupplicantStaIfaceCallback Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'proxy' class.
     */
    typedef ::android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    void onLastStrongRef(const void* id) override;

    // Methods from ::android::hardware::wifi::supplicant::V1_2::ISupplicantStaIfaceCallback follow.
    static ::android::hardware::Return<void>  _hidl_onDppSuccessConfigReceived(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_vec<uint8_t>& ssid, const ::android::hardware::hidl_string& password, const ::android::hardware::hidl_array<uint8_t, 32>& psk, ::android::hardware::wifi::supplicant::V1_2::DppAkm securityAkm);
    static ::android::hardware::Return<void>  _hidl_onDppSuccessConfigSent(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);
    static ::android::hardware::Return<void>  _hidl_onDppProgress(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::wifi::supplicant::V1_2::DppProgressCode code);
    static ::android::hardware::Return<void>  _hidl_onDppFailure(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::wifi::supplicant::V1_2::DppFailureCode code);

    // Methods from ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback follow.
    ::android::hardware::Return<void> onNetworkAdded(uint32_t id) override;
    ::android::hardware::Return<void> onNetworkRemoved(uint32_t id) override;
    ::android::hardware::Return<void> onStateChanged(::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::State newState, const ::android::hardware::hidl_array<uint8_t, 6>& bssid, uint32_t id, const ::android::hardware::hidl_vec<uint8_t>& ssid) override;
    ::android::hardware::Return<void> onAnqpQueryDone(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, const ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::AnqpData& data, const ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::Hs20AnqpData& hs20Data) override;
    ::android::hardware::Return<void> onHs20IconQueryDone(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, const ::android::hardware::hidl_string& fileName, const ::android::hardware::hidl_vec<uint8_t>& data) override;
    ::android::hardware::Return<void> onHs20SubscriptionRemediation(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::OsuMethod osuMethod, const ::android::hardware::hidl_string& url) override;
    ::android::hardware::Return<void> onHs20DeauthImminentNotice(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, uint32_t reasonCode, uint32_t reAuthDelayInSec, const ::android::hardware::hidl_string& url) override;
    ::android::hardware::Return<void> onDisconnected(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, bool locallyGenerated, ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::ReasonCode reasonCode) override;
    ::android::hardware::Return<void> onAssociationRejected(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::StatusCode statusCode, bool timedOut) override;
    ::android::hardware::Return<void> onAuthenticationTimeout(const ::android::hardware::hidl_array<uint8_t, 6>& bssid) override;
    ::android::hardware::Return<void> onEapFailure() override;
    ::android::hardware::Return<void> onBssidChanged(::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::BssidChangeReason reason, const ::android::hardware::hidl_array<uint8_t, 6>& bssid) override;
    ::android::hardware::Return<void> onWpsEventSuccess() override;
    ::android::hardware::Return<void> onWpsEventFail(const ::android::hardware::hidl_array<uint8_t, 6>& bssid, ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::WpsConfigError configError, ::android::hardware::wifi::supplicant::V1_0::ISupplicantStaIfaceCallback::WpsErrorIndication errorInd) override;
    ::android::hardware::Return<void> onWpsEventPbcOverlap() override;
    ::android::hardware::Return<void> onExtRadioWorkStart(uint32_t id) override;
    ::android::hardware::Return<void> onExtRadioWorkTimeout(uint32_t id) override;

    // Methods from ::android::hardware::wifi::supplicant::V1_1::ISupplicantStaIfaceCallback follow.
    ::android::hardware::Return<void> onEapFailure_1_1(::android::hardware::wifi::supplicant::V1_1::ISupplicantStaIfaceCallback::EapErrorCode errorCode) override;

    // Methods from ::android::hardware::wifi::supplicant::V1_2::ISupplicantStaIfaceCallback follow.
    ::android::hardware::Return<void> onDppSuccessConfigReceived(const ::android::hardware::hidl_vec<uint8_t>& ssid, const ::android::hardware::hidl_string& password, const ::android::hardware::hidl_array<uint8_t, 32>& psk, ::android::hardware::wifi::supplicant::V1_2::DppAkm securityAkm) override;
    ::android::hardware::Return<void> onDppSuccessConfigSent() override;
    ::android::hardware::Return<void> onDppProgress(::android::hardware::wifi::supplicant::V1_2::DppProgressCode code) override;
    ::android::hardware::Return<void> onDppFailure(::android::hardware::wifi::supplicant::V1_2::DppFailureCode code) override;

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

}  // namespace V1_2
}  // namespace supplicant
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_WIFI_SUPPLICANT_V1_2_BPHWSUPPLICANTSTAIFACECALLBACK_H
