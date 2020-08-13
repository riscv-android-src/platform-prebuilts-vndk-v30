#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAMERA_DEVICE_V1_0_ICAMERADEVICEPREVIEWCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAMERA_DEVICE_V1_0_ICAMERADEVICEPREVIEWCALLBACK_H

#include <android/hardware/camera/common/1.0/types.h>
#include <android/hardware/graphics/common/1.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace camera {
namespace device {
namespace V1_0 {

/**
 * Camera device HAL@1.0 preview stream operation interface.
 */
struct ICameraDevicePreviewCallback : public ::android::hidl::base::V1_0::IBase {
    /**
     * Type tag for use in template logic that indicates this is a 'pure' class.
     */
    typedef ::android::hardware::details::i_tag _hidl_tag;

    /**
     * Fully qualified interface name: "android.hardware.camera.device@1.0::ICameraDevicePreviewCallback"
     */
    static const char* descriptor;

    /**
     * Returns whether this object's implementation is outside of the current process.
     */
    virtual bool isRemote() const override { return false; }

    /**
     * Return callback for dequeueBuffer
     */
    using dequeueBuffer_cb = std::function<void(::android::hardware::camera::common::V1_0::Status status, uint64_t bufferId, const ::android::hardware::hidl_handle& buffer, uint32_t stride)>;
    /**
     * Acquire a buffer to write a preview buffer into.
     *
     * @return status The status code for this operation. If not OK, then
     *     buffer and stride must not be used.
     * @return bufferId A unique ID for the returned buffer.
     * @return buffer A handle to the buffer to write into. Must be non-null if the bufferId has not
     *     been seen by HAL before. Must be null if the bufferId is seen before. HAL must keep track
     *     of the bufferId to actual buffer handle mapping.
     * @return stride The stride between two rows of pixels in this buffer.
     */
    virtual ::android::hardware::Return<void> dequeueBuffer(dequeueBuffer_cb _hidl_cb) = 0;

    /**
     * Send a filled preview buffer to its consumer.
     *
     * @param bufferId The bufferId of the preview buffer
     * @return status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> enqueueBuffer(uint64_t bufferId) = 0;

    /**
     * Return a preview buffer unfilled. This buffer must not be sent on to the
     * preview consumer as a valid buffer, but may be reused as if it were
     * empty.
     *
     * @param bufferId The bufferId of the preview buffer
     * @return status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> cancelBuffer(uint64_t bufferId) = 0;

    /**
     * Set the number of preview buffers needed by the HAL.
     *
     * @param count The maximum number of preview buffers to allocate.
     * @return status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> setBufferCount(uint32_t count) = 0;

    /**
     * Set the dimensions and format of future preview buffers.
     *
     * The next buffer that is dequeued must match the requested size and
     * format.
     *
     * @return Status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> setBuffersGeometry(uint32_t w, uint32_t h, ::android::hardware::graphics::common::V1_0::PixelFormat format) = 0;

    /**
     * Set the valid region of image data for the next buffer(s) to be enqueued.
     *
     * @return Status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> setCrop(int32_t left, int32_t top, int32_t right, int32_t bottom) = 0;

    /**
     * Set the producer usage flags for the next buffer(s) to be enqueued.
     *
     * @return Status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> setUsage(::android::hardware::graphics::common::V1_0::BufferUsage usage) = 0;

    /**
     * Set the expected buffering mode for the preview output.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> setSwapInterval(int32_t interval) = 0;

    /**
     * Return callback for getMinUndequeuedBufferCount
     */
    using getMinUndequeuedBufferCount_cb = std::function<void(::android::hardware::camera::common::V1_0::Status status, uint32_t count)>;
    /**
     * Get the minimum number of buffers the preview consumer endpoint needs
     * to hold for correct operation.
     *
     * @return Status The status code for this operation.
     * @return count The number of buffers the consumer has requested.
     */
    virtual ::android::hardware::Return<void> getMinUndequeuedBufferCount(getMinUndequeuedBufferCount_cb _hidl_cb) = 0;

    /**
     * Set the timestamp for the next buffer to enqueue
     *
     * Timestamps are measured in nanoseconds, and must be comparable
     * and monotonically increasing between two frames in the same
     * preview stream. They do not need to be comparable between
     * consecutive or parallel preview streams, cameras, or app runs.
     *
     * @param timestamp The timestamp to set for future buffers.
     * @return Status The status code for this operation.
     */
    virtual ::android::hardware::Return<::android::hardware::camera::common::V1_0::Status> setTimestamp(int64_t timestamp) = 0;

    /**
     * Return callback for interfaceChain
     */
    using interfaceChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& descriptors)>;
    /*
     * Provides run-time type information for this object.
     * For example, for the following interface definition:
     *     package android.hardware.foo@1.0;
     *     interface IParent {};
     *     interface IChild extends IParent {};
     * Calling interfaceChain on an IChild object must yield the following:
     *     ["android.hardware.foo@1.0::IChild",
     *      "android.hardware.foo@1.0::IParent"
     *      "android.hidl.base@1.0::IBase"]
     *
     * @return descriptors a vector of descriptors of the run-time type of the
     *         object.
     */
    virtual ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;

    /*
     * Emit diagnostic information to the given file.
     *
     * Optionally overriden.
     *
     * @param fd      File descriptor to dump data to.
     *                Must only be used for the duration of this call.
     * @param options Arguments for debugging.
     *                Must support empty for default debug information.
     */
    virtual ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;

    /**
     * Return callback for interfaceDescriptor
     */
    using interfaceDescriptor_cb = std::function<void(const ::android::hardware::hidl_string& descriptor)>;
    /*
     * Provides run-time type information for this object.
     * For example, for the following interface definition:
     *     package android.hardware.foo@1.0;
     *     interface IParent {};
     *     interface IChild extends IParent {};
     * Calling interfaceDescriptor on an IChild object must yield
     *     "android.hardware.foo@1.0::IChild"
     *
     * @return descriptor a descriptor of the run-time type of the
     *         object (the first element of the vector returned by
     *         interfaceChain())
     */
    virtual ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;

    /**
     * Return callback for getHashChain
     */
    using getHashChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_array<uint8_t, 32>>& hashchain)>;
    /*
     * Returns hashes of the source HAL files that define the interfaces of the
     * runtime type information on the object.
     * For example, for the following interface definition:
     *     package android.hardware.foo@1.0;
     *     interface IParent {};
     *     interface IChild extends IParent {};
     * Calling interfaceChain on an IChild object must yield the following:
     *     [(hash of IChild.hal),
     *      (hash of IParent.hal)
     *      (hash of IBase.hal)].
     *
     * SHA-256 is used as the hashing algorithm. Each hash has 32 bytes
     * according to SHA-256 standard.
     *
     * @return hashchain a vector of SHA-1 digests
     */
    virtual ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;

    /*
     * This method trigger the interface to enable/disable instrumentation based
     * on system property hal.instrumentation.enable.
     */
    virtual ::android::hardware::Return<void> setHALInstrumentation() override;

    /*
     * Registers a death recipient, to be called when the process hosting this
     * interface dies.
     *
     * @param recipient a hidl_death_recipient callback object
     * @param cookie a cookie that must be returned with the callback
     * @return success whether the death recipient was registered successfully.
     */
    virtual ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;

    /*
     * Provides way to determine if interface is running without requesting
     * any functionality.
     */
    virtual ::android::hardware::Return<void> ping() override;

    /**
     * Return callback for getDebugInfo
     */
    using getDebugInfo_cb = std::function<void(const ::android::hidl::base::V1_0::DebugInfo& info)>;
    /*
     * Get debug information on references on this interface.
     * @return info debugging information. See comments of DebugInfo.
     */
    virtual ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;

    /*
     * This method notifies the interface that one or more system properties
     * have changed. The default implementation calls
     * (C++)  report_sysprop_change() in libcutils or
     * (Java) android.os.SystemProperties.reportSyspropChanged,
     * which in turn calls a set of registered callbacks (eg to update trace
     * tags).
     */
    virtual ::android::hardware::Return<void> notifySyspropsChanged() override;

    /*
     * Unregisters the registered death recipient. If this service was registered
     * multiple times with the same exact death recipient, this unlinks the most
     * recently registered one.
     *
     * @param recipient a previously registered hidl_death_recipient callback
     * @return success whether the death recipient was unregistered successfully.
     */
    virtual ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

    // cast static functions
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::camera::device::V1_0::ICameraDevicePreviewCallback>> castFrom(const ::android::sp<::android::hardware::camera::device::V1_0::ICameraDevicePreviewCallback>& parent, bool emitError = false);
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::camera::device::V1_0::ICameraDevicePreviewCallback>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    // helper methods for interactions with the hwservicemanager
    /**
     * This gets the service of this type with the specified instance name. If the
     * service is currently not available or not in the VINTF manifest on a Trebilized
     * device, this will return nullptr. This is useful when you don't want to block
     * during device boot. If getStub is true, this will try to return an unwrapped
     * passthrough implementation in the same process. This is useful when getting an
     * implementation from the same partition/compilation group.
     *
     * In general, prefer getService(std::string,bool)
     */
    static ::android::sp<ICameraDevicePreviewCallback> tryGetService(const std::string &serviceName="default", bool getStub=false);
    /**
     * Deprecated. See tryGetService(std::string, bool)
     */
    static ::android::sp<ICameraDevicePreviewCallback> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    /**
     * Deprecated. See tryGetService(std::string, bool)
     */
    static ::android::sp<ICameraDevicePreviewCallback> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    /**
     * Calls tryGetService("default", bool). This is the recommended instance name for singleton services.
     */
    static ::android::sp<ICameraDevicePreviewCallback> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    /**
     * This gets the service of this type with the specified instance name. If the
     * service is not in the VINTF manifest on a Trebilized device, this will return
     * nullptr. If the service is not available, this will wait for the service to
     * become available. If the service is a lazy service, this will start the service
     * and return when it becomes available. If getStub is true, this will try to
     * return an unwrapped passthrough implementation in the same process. This is
     * useful when getting an implementation from the same partition/compilation group.
     */
    static ::android::sp<ICameraDevicePreviewCallback> getService(const std::string &serviceName="default", bool getStub=false);
    /**
     * Deprecated. See getService(std::string, bool)
     */
    static ::android::sp<ICameraDevicePreviewCallback> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    /**
     * Deprecated. See getService(std::string, bool)
     */
    static ::android::sp<ICameraDevicePreviewCallback> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    /**
     * Calls getService("default", bool). This is the recommended instance name for singleton services.
     */
    static ::android::sp<ICameraDevicePreviewCallback> getService(bool getStub) { return getService("default", getStub); }
    /**
     * Registers a service with the service manager. For Trebilized devices, the service
     * must also be in the VINTF manifest.
     */
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    /**
     * Registers for notifications for when a service is registered.
     */
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

//
// type declarations for package
//

static inline std::string toString(const ::android::sp<::android::hardware::camera::device::V1_0::ICameraDevicePreviewCallback>& o);

//
// type header definitions for package
//

static inline std::string toString(const ::android::sp<::android::hardware::camera::device::V1_0::ICameraDevicePreviewCallback>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::camera::device::V1_0::ICameraDevicePreviewCallback::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace device
}  // namespace camera
}  // namespace hardware
}  // namespace android

//
// global type declarations for package
//


#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAMERA_DEVICE_V1_0_ICAMERADEVICEPREVIEWCALLBACK_H
