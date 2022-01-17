#ifndef HIDL_GENERATED_ANDROID_HARDWARE_NEURALNETWORKS_V1_3_IEXECUTIONCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_NEURALNETWORKS_V1_3_IEXECUTIONCALLBACK_H

#include <android/hardware/neuralnetworks/1.2/IExecutionCallback.h>
#include <android/hardware/neuralnetworks/1.2/types.h>
#include <android/hardware/neuralnetworks/1.3/types.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace neuralnetworks {
namespace V1_3 {

/**
 * IExecutionCallback must be used to return the error status result from an
 * execution asynchronously launched from IPreparedModel::execute*.
 */
struct IExecutionCallback : public ::android::hardware::neuralnetworks::V1_2::IExecutionCallback {
    /**
     * Type tag for use in template logic that indicates this is a 'pure' class.
     */
    typedef ::android::hardware::details::i_tag _hidl_tag;

    /**
     * Fully qualified interface name: "android.hardware.neuralnetworks@1.3::IExecutionCallback"
     */
    static const char* descriptor;

    /**
     * Returns whether this object's implementation is outside of the current process.
     */
    virtual bool isRemote() const override { return false; }

    /**
     * notify must be invoked immediately after the asynchronous task has
     * finished performing the execution. notify must be provided with the
     * ErrorStatus resulting from the execution. If the asynchronous task
     * is not launched, notify must be invoked with the appropriate error.
     *
     * @param status Error status returned from launching the asynchronous task
     *               (if the launch fails) or from the asynchronous task itself
     *               (if the launch succeeds). Must be:
     *               - NONE if the asynchronous execution was successful
     *               - DEVICE_UNAVAILABLE if driver is offline or busy
     *               - GENERAL_FAILURE if the asynchronous task resulted in an
     *                 unspecified error
     *               - OUTPUT_INSUFFICIENT_SIZE if provided output buffer is
     *                 not large enough to store the resultant values
     *               - INVALID_ARGUMENT if one of the input arguments to
     *                 prepareModel is invalid
     */
    virtual ::android::hardware::Return<void> notify(::android::hardware::neuralnetworks::V1_0::ErrorStatus status) = 0;

    /**
     * Either notify_1_2 or notify must be invoked immediately after the asynchronous
     * task has finished performing the execution. Either notify_1_2 or notify must be
     * provided with the ErrorStatus from the execution. If the asynchronous task is
     * not launched, either notify_1_2 or notify must be invoked with the appropriate
     * error.
     *
     * @param status Error status returned from launching the asynchronous task
     *               (if the launch fails) or from the asynchronous task itself
     *               (if the launch succeeds). Must be:
     *               - NONE if the asynchronous execution was successful
     *               - DEVICE_UNAVAILABLE if driver is offline or busy
     *               - GENERAL_FAILURE if the asynchronous task resulted in an
     *                 unspecified error
     *               - OUTPUT_INSUFFICIENT_SIZE if at least one output
     *                 operand buffer is not large enough to store the
     *                 corresponding output
     *               - INVALID_ARGUMENT if one of the input arguments to
     *                 prepareModel is invalid
     * @param outputShapes A list of shape information of model output operands.
     *                     The index into "outputShapes" corresponds with to index
     *                     of the output operand in the Request outputs vector.
     *                     outputShapes must be empty unless the status is either
     *                     NONE or OUTPUT_INSUFFICIENT_SIZE.
     * @return Timing Duration of execution. Unless MeasureTiming::YES was passed when
     *                launching the execution and status is NONE, all times must
     *                be reported as UINT64_MAX. A driver may choose to report
     *                any time as UINT64_MAX, indicating that particular measurement is
     *                not available.
     */
    virtual ::android::hardware::Return<void> notify_1_2(::android::hardware::neuralnetworks::V1_0::ErrorStatus status, const ::android::hardware::hidl_vec<::android::hardware::neuralnetworks::V1_2::OutputShape>& outputShapes, const ::android::hardware::neuralnetworks::V1_2::Timing& timing) = 0;

    /**
     * There are three notify methods declared for the IExecutionCallback
     * interface: notify_1_3, notify_1_2, and notify. One of the three notify
     * methods must be invoked immediately after the asynchronous task has
     * finished performing the execution. One of the notify methods must be
     * provided with the ErrorStatus from the execution. If the asynchronous
     * task is not launched, one of the notify methods must be invoked with the
     * appropriate error.
     *
     * @param status Error status returned from launching the asynchronous task
     *               (if the launch fails) or from the asynchronous task itself
     *               (if the launch succeeds). Must be:
     *               - NONE if the asynchronous execution was successful
     *               - DEVICE_UNAVAILABLE if driver is offline or busy
     *               - GENERAL_FAILURE if the asynchronous task resulted in an
     *                 unspecified error
     *               - OUTPUT_INSUFFICIENT_SIZE if at least one output
     *                 operand buffer is not large enough to store the
     *                 corresponding output
     *               - INVALID_ARGUMENT if one of the input arguments to
     *                 prepareModel is invalid
     *               - MISSED_DEADLINE_* if the execution is aborted because it
     *                 cannot be completed by the deadline
     *               - RESOURCE_EXHAUSTED_* if the task was aborted by the driver
     * @param outputShapes A list of shape information of model output operands.
     *                     The index into "outputShapes" corresponds with to index
     *                     of the output operand in the Request outputs vector.
     *                     outputShapes must be empty unless the status is either
     *                     NONE or OUTPUT_INSUFFICIENT_SIZE.
     * @param timing Duration of execution. Unless MeasureTiming::YES was passed when
     *               launching the execution and status is NONE, all times must
     *               be reported as UINT64_MAX. A driver may choose to report
     *               any time as UINT64_MAX, indicating that particular measurement is
     *               not available.
     */
    virtual ::android::hardware::Return<void> notify_1_3(::android::hardware::neuralnetworks::V1_3::ErrorStatus status, const ::android::hardware::hidl_vec<::android::hardware::neuralnetworks::V1_2::OutputShape>& outputShapes, const ::android::hardware::neuralnetworks::V1_2::Timing& timing) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>> castFrom(const ::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>& parent, bool emitError = false);
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>> castFrom(const ::android::sp<::android::hardware::neuralnetworks::V1_2::IExecutionCallback>& parent, bool emitError = false);
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>> castFrom(const ::android::sp<::android::hardware::neuralnetworks::V1_0::IExecutionCallback>& parent, bool emitError = false);
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

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
    static ::android::sp<IExecutionCallback> tryGetService(const std::string &serviceName="default", bool getStub=false);
    /**
     * Deprecated. See tryGetService(std::string, bool)
     */
    static ::android::sp<IExecutionCallback> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    /**
     * Deprecated. See tryGetService(std::string, bool)
     */
    static ::android::sp<IExecutionCallback> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    /**
     * Calls tryGetService("default", bool). This is the recommended instance name for singleton services.
     */
    static ::android::sp<IExecutionCallback> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    /**
     * This gets the service of this type with the specified instance name. If the
     * service is not in the VINTF manifest on a Trebilized device, this will return
     * nullptr. If the service is not available, this will wait for the service to
     * become available. If the service is a lazy service, this will start the service
     * and return when it becomes available. If getStub is true, this will try to
     * return an unwrapped passthrough implementation in the same process. This is
     * useful when getting an implementation from the same partition/compilation group.
     */
    static ::android::sp<IExecutionCallback> getService(const std::string &serviceName="default", bool getStub=false);
    /**
     * Deprecated. See getService(std::string, bool)
     */
    static ::android::sp<IExecutionCallback> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    /**
     * Deprecated. See getService(std::string, bool)
     */
    static ::android::sp<IExecutionCallback> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    /**
     * Calls getService("default", bool). This is the recommended instance name for singleton services.
     */
    static ::android::sp<IExecutionCallback> getService(bool getStub) { return getService("default", getStub); }
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

static inline std::string toString(const ::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>& o);

//
// type header definitions for package
//

static inline std::string toString(const ::android::sp<::android::hardware::neuralnetworks::V1_3::IExecutionCallback>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::neuralnetworks::V1_3::IExecutionCallback::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_3
}  // namespace neuralnetworks
}  // namespace hardware
}  // namespace android

//
// global type declarations for package
//


#endif  // HIDL_GENERATED_ANDROID_HARDWARE_NEURALNETWORKS_V1_3_IEXECUTIONCALLBACK_H
