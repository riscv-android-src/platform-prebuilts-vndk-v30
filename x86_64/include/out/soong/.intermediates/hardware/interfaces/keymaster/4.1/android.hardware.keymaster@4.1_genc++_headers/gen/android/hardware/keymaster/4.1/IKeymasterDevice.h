#ifndef HIDL_GENERATED_ANDROID_HARDWARE_KEYMASTER_V4_1_IKEYMASTERDEVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_KEYMASTER_V4_1_IKEYMASTERDEVICE_H

#include <android/hardware/keymaster/4.0/IKeymasterDevice.h>
#include <android/hardware/keymaster/4.0/types.h>
#include <android/hardware/keymaster/4.1/types.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace keymaster {
namespace V4_1 {

/**
 * @4.1::IKeymasterDevice is a minor extension to @4.0::IKeymasterDevice.  It adds support for
 *
 * - Partial hardware enforcment of UNLOCKED_DEVICE_REQUIRED keys;
 * - Device-unique attestaion;
 * - Early boot only keys;
 * - Better cleanup of operations when clients die without completing or aborting them.
 *
 * @4.1::IKeymasterDevice::attestKey() must produce attestations with keymasterVersion 41.  An
 * oversight in the original numbering left no room for minor versions, so starting with 4.1 the
 * versions will be numbered as major_version * 10 + minor version.  The addition of new attestable
 * tags changes the attestation format again, slightly, so the attestationVersion must be 4.
 */
struct IKeymasterDevice : public ::android::hardware::keymaster::V4_0::IKeymasterDevice {
    /**
     * Type tag for use in template logic that indicates this is a 'pure' class.
     */
    typedef ::android::hardware::details::i_tag _hidl_tag;

    /**
     * Fully qualified interface name: "android.hardware.keymaster@4.1::IKeymasterDevice"
     */
    static const char* descriptor;

    /**
     * Returns whether this object's implementation is outside of the current process.
     */
    virtual bool isRemote() const override { return false; }

    /**
     * Return callback for getHardwareInfo
     */
    using getHardwareInfo_cb = std::function<void(::android::hardware::keymaster::V4_0::SecurityLevel securityLevel, const ::android::hardware::hidl_string& keymasterName, const ::android::hardware::hidl_string& keymasterAuthorName)>;
    /**
     * Returns information about the underlying IKeymasterDevice hardware.
     *
     * @return security level of the IKeymasterDevice implementation accessed through this HAL.
     *
     * @return keymasterName is the name of the IKeymasterDevice implementation.
     *
     * @return keymasterAuthorName is the name of the author of the IKeymasterDevice implementation
     *         (organization name, not individual).
     */
    virtual ::android::hardware::Return<void> getHardwareInfo(getHardwareInfo_cb _hidl_cb) = 0;

    /**
     * Return callback for getHmacSharingParameters
     */
    using getHmacSharingParameters_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::keymaster::V4_0::HmacSharingParameters& params)>;
    /**
     * Start the creation of an HMAC key, shared with another IKeymasterDevice implementation.  Any
     * device with a StrongBox IKeymasterDevice has two IKeymasterDevice instances, because there
     * must be a TEE Keymaster as well.  The HMAC key used to MAC and verify authentication tokens
     * (HardwareAuthToken, VerificationToken and ConfirmationToken all use this HMAC key) must be
     * shared between TEE and StrongBox so they can each validate tokens produced by the other.
     * This method is the first step in the process for agreeing on a shared key.  It is called by
     * Android during startup.  The system calls it on each of the HAL instances and collects the
     * results in preparation for the second step.
     *
     * @return error ErrorCode::OK on success, ErrorCode::UNIMPLEMENTED if HMAC agreement is not
     *         implemented (note that all 4.0::IKeymasterDevice HALS must implement HMAC agreement,
     *         regardless of whether or not the HAL will be used on a device with StrongBox), or
     *         ErrorCode::UNKNOWN_ERROR if the parameters cannot be returned.
     *
     * @return params The HmacSharingParameters to use.  As specified in the HmacSharingParameters
     *         documentation in types.hal, the seed must contain the same value in every invocation
     *         of the method on a given device, and the nonce must return the same value for every
     *         invocation during a boot session.
     */
    virtual ::android::hardware::Return<void> getHmacSharingParameters(getHmacSharingParameters_cb _hidl_cb) = 0;

    /**
     * Return callback for computeSharedHmac
     */
    using computeSharedHmac_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<uint8_t>& sharingCheck)>;
    /**
     * Complete the creation of an HMAC key, shared with another IKeymasterDevice implementation.
     * Any device with a StrongBox IKeymasterDevice has two IKeymasterDevice instances, because
     * there must be a TEE IKeymasterDevice as well.  The HMAC key used to MAC and verify
     * authentication tokens must be shared between TEE and StrongBox so they can each validate
     * tokens produced by the other.  This method is the second and final step in the process for
     * agreeing on a shared key.  It is called by Android during startup.  The system calls it on
     * each of the HAL instances, and sends to it all of the HmacSharingParameters returned by all
     * HALs.
     *
     * To ensure consistent ordering of the HmacSharingParameters, the caller must sort the
     * parameters lexicographically.  See the support/keymaster_utils.cpp for an operator< that
     * defines the appropriate ordering.
     *
     * This method computes the shared 32-byte HMAC ``H'' as follows (all IKeymasterDevice instances
     * perform the same computation to arrive at the same result):
     *
     *     H = CKDF(key = K,
     *              context = P1 || P2 || ... || Pn,
     *              label = "KeymasterSharedMac")
     *
     * where:
     *
     *     ``CKDF'' is the standard AES-CMAC KDF from NIST SP 800-108 in counter mode (see Section
     *           5.1 of the referenced publication).  ``key'', ``context'', and ``label'' are
     *           defined in the standard.  The counter is prefixed and length L appended, as shown
     *           in the construction on page 12 of the standard.  The label string is UTF-8 encoded.
     *
     *     ``K'' is a pre-established shared secret, set up during factory reset.  The mechanism for
     *           establishing this shared secret is implementation-defined, but see below for a
     *           recommended approach, which assumes that the TEE IKeymasterDevice does not have
     *           storage available to it, but the StrongBox IKeymasterDevice does.
     *
     *           CRITICAL SECURITY REQUIREMENT: All keys created by a IKeymasterDevice instance must
     *           be cryptographically bound to the value of K, such that establishing a new K
     *           permanently destroys them.
     *
     *     ``||'' represents concatenation.
     *
     *     ``Pi'' is the i'th HmacSharingParameters value in the params vector.  Note that at
     *           present only two IKeymasterDevice implementations are supported, but this mechanism
     *           extends without modification to any number of implementations.  Encoding of an
     *           HmacSharingParameters is the concatenation of its two fields, i.e. seed || nonce.
     *
     * Note that the label "KeymasterSharedMac" is the 18-byte UTF-8 encoding of the string.
     *
     * Process for establishing K:
     *
     *     Any method of securely establishing K that ensures that an attacker cannot obtain or
     *     derive its value is acceptable.  What follows is a recommended approach, to be executed
     *     during each factory reset.  It relies on use of the factory-installed attestation keys to
     *     mitigate man-in-the-middle attacks.  This protocol requires that one of the instances
     *     have secure persistent storage.  This model was chosen because StrongBox has secure
     *     persistent storage (by definition), but the TEE may not.  The instance without storage is
     *     assumed to be able to derive a unique hardware-bound key (HBK) which is used only for
     *     this purpose, and is not derivable outside the secure environment.
     *
     *     In what follows, T is the IKeymasterDevice instance without storage, S is the
     *     IKeymasterDevice instance with storage:
     *
     *     1. T generates an ephemeral EC P-256 key pair K1.
     *     2. T sends K1_pub to S, signed with T's attestation key.
     *     3. S validates the signature on K1_pub.
     *     4. S generates an ephemeral EC P-256 key pair K2.
     *     5. S sends {K1_pub, K2_pub}, to T, signed with S's attestation key.
     *     6. T validates the signature on {K1_pub, K2_pub}.
     *     7. T uses {K1_priv, K2_pub} with ECDH to compute session secret Q.
     *     8. T generates a random seed S.
     *     9. T computes K = KDF(HBK, S), where KDF is some secure key derivation function.
     *     10. T sends M = AES-GCM-ENCRYPT(Q, {S || K}) to S.
     *     10. S uses {K2_priv, K1_pub} with ECDH to compute session secret Q.
     *     11. S computes S || K = AES-GCM-DECRYPT(Q, M) and stores S and K.
     *
     *     When S receives the getHmacSharingParameters call, it returns the stored S as the seed
     *     and a nonce.  When T receives the same call, it returns an empty seed and a nonce.  When
     *     T receives the computeSharedHmac call, it uses the seed provided by S to compute K.  S,
     *     of course, has K stored.
     *
     * @param params The HmacSharingParameters data returned by all IKeymasterDevice instances when
     *        getHmacSharingParameters was called.
     *
     * @return error ErrorCode::OK in the event that there is no error.  ErrorCode::INVALID_ARGUMENT
     *         if one of the provided parameters is not the value returned by the prior call to
     *         getHmacParameters().
     *
     * @return sharingCheck A 32-byte value used to verify that all IKeymasterDevice instances have
     *         computed the same shared HMAC key.  The sharingCheck value is computed as follows:
     *
     *             sharingCheck = HMAC(H, "Keymaster HMAC Verification")
     *
     *         The string is UTF-8 encoded, 27 bytes in length.  If the returned values of all
     *         IKeymasterDevice instances don't match, clients must assume that HMAC agreement
     *         failed.
     */
    virtual ::android::hardware::Return<void> computeSharedHmac(const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::HmacSharingParameters>& params, computeSharedHmac_cb _hidl_cb) = 0;

    /**
     * Return callback for verifyAuthorization
     */
    using verifyAuthorization_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::keymaster::V4_0::VerificationToken& token)>;
    /**
     * Verify authorizations for another IKeymasterDevice instance.
     *
     * On systems with both a StrongBox and a TEE IKeymasterDevice instance it is sometimes useful
     * to ask the TEE IKeymasterDevice to verify authorizations for a key hosted in StrongBox.
     *
     * For every StrongBox operation, Keystore is required to call this method on the TEE Keymaster,
     * passing in the StrongBox key's hardwareEnforced authorization list and the operation handle
     * returned by StrongBox begin().  The TEE IKeymasterDevice must validate all of the
     * authorizations it can and return those it validated in the VerificationToken.  If it cannot
     * verify any, the parametersVerified field of the VerificationToken must be empty.  Keystore
     * must then pass the VerificationToken to the subsequent invocations of StrongBox update() and
     * finish().
     *
     * StrongBox implementations must return ErrorCode::UNIMPLEMENTED.
     *
     * @param operationHandle the operation handle returned by StrongBox Keymaster's begin().
     *
     * @param parametersToVerify Set of authorizations to verify.  The caller may provide an empty
     *        vector if the only required information is the TEE timestamp.
     *
     * @param authToken A HardwareAuthToken if needed to authorize key usage.
     *
     * @return error ErrorCode::OK on success or ErrorCode::UNIMPLEMENTED if the IKeymasterDevice is
     *         a StrongBox.  If the IKeymasterDevice cannot verify one or more elements of
     *         parametersToVerify it must not return an error code, but just omit the unverified
     *         parameter from the VerificationToken.
     *
     * @return token the verification token.  See VerificationToken in types.hal for details.
     */
    virtual ::android::hardware::Return<void> verifyAuthorization(uint64_t operationHandle, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& parametersToVerify, const ::android::hardware::keymaster::V4_0::HardwareAuthToken& authToken, verifyAuthorization_cb _hidl_cb) = 0;

    /**
     * Adds entropy to the RNG used by Keymaster.  Entropy added through this method must not be the
     * only source of entropy used, and a secure mixing function must be used to mix the entropy
     * provided by this method with internally-generated entropy.  The mixing function must be
     * secure in the sense that if any one of the mixing function inputs is provided with any data
     * the attacker cannot predict (or control), then the output of the seeded CRNG is
     * indistinguishable from random.  Thus, if the entropy from any source is good, the output must
     * be good.
     *
     * @param data Bytes to be mixed into the CRNG seed.  The caller must not provide more than 2
     *        KiB of data per invocation.
     *
     * @return error ErrorCode::OK on success; ErrorCode::INVALID_INPUT_LENGTH if the caller
     *         provides more than 2 KiB of data.
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_0::ErrorCode> addRngEntropy(const ::android::hardware::hidl_vec<uint8_t>& data) = 0;

    /**
     * Return callback for generateKey
     */
    using generateKey_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<uint8_t>& keyBlob, const ::android::hardware::keymaster::V4_0::KeyCharacteristics& keyCharacteristics)>;
    /**
     * Generates a new cryptographic key, specifying associated parameters, which must be
     * cryptographically bound to the key.  IKeymasterDevice implementations must disallow any use
     * of a key in any way inconsistent with the authorizations specified at generation time.  With
     * respect to parameters that the secure environment cannot enforce, the secure environment's
     * obligation is limited to ensuring that the unenforceable parameters associated with the key
     * cannot be modified, so that every call to getKeyCharacteristics returns the original
     * values.  In addition, the characteristics returned by generateKey places parameters correctly
     * in the hardware-enforced and software-enforced lists.  See getKeyCharacteristics for more
     * details.
     *
     * In addition to the parameters provided, generateKey must add the following to the returned
     * characteristics.
     *
     * o Tag::ORIGIN with the value KeyOrigin::GENERATED.
     *
     * o Tag::BLOB_USAGE_REQUIREMENTS with the appropriate value (see KeyBlobUsageRequirements in
     *   types.hal).
     *
     * o Tag::CREATION_DATETIME with the appropriate value.  Note that it is expected that this will
     *   generally be added by the HAL, not by the secure environment, and that it will be in the
     *   software-enforced list.  It must be cryptographically bound to the key, like all tags.
     *
     * o Tag::OS_VERSION, Tag::OS_PATCHLEVEL, Tag::VENDOR_PATCHLEVEL and Tag::BOOT_PATCHLEVEL with
     *   appropriate values.
     *
     * The parameters provided to generateKey depend on the type of key being generated.  This
     * section summarizes the necessary and optional tags for each type of key.  Tag::ALGORITHM is
     * always necessary, to specify the type.
     *
     * == RSA Keys ==
     *
     * The following parameters are required to generate an RSA key:
     *
     * o Tag::Key_SIZE specifies the size of the public modulus, in bits.  If omitted, generateKey
     *   must return ErrorCode::UNSUPPORTED_KEY_SIZE.  Required values for TEE IKeymasterDevice
     *   implementations are 1024, 2048, 3072 and 4096.  StrongBox IKeymasterDevice implementations
     *   must support 2048.
     *
     * o Tag::RSA_PUBLIC_EXPONENT specifies the RSA public exponent value.  If omitted, generateKey
     *   must return ErrorCode::INVALID_ARGUMENT.  The values 3 and 65537 must be supported.  It is
     *   recommended to support all prime values up to 2^64.  If provided with a non-prime value,
     *   generateKey must return ErrorCode::INVALID_ARGUMENT.
     *
     * The following parameters are not necessary to generate a usable RSA key, but generateKey must
     * not return an error if they are omitted:
     *
     * o Tag::PURPOSE specifies allowed purposes.  All KeyPurpose values (see types.hal) must be
     *   supported for RSA keys.
     *
     * o Tag::DIGEST specifies digest algorithms that may be used with the new key.  TEE
     *   IKeymasterDevice implementations must support all Digest values (see types.hal) for RSA
     *   keys.  StrongBox IKeymasterDevice implementations must support SHA_2_256.
     *
     * o Tag::PADDING specifies the padding modes that may be used with the new
     *   key.  IKeymasterDevice implementations must support PaddingMode::NONE,
     *   PaddingMode::RSA_OAEP, PaddingMode::RSA_PSS, PaddingMode::RSA_PKCS1_1_5_ENCRYPT and
     *   PaddingMode::RSA_PKCS1_1_5_SIGN for RSA keys.
     *
     * == ECDSA Keys ==
     *
     * Either Tag::KEY_SIZE or Tag::EC_CURVE must be provided to generate an ECDSA key.  If neither
     * is provided, generateKey must return ErrorCode::UNSUPPORTED_KEY_SIZE.  If Tag::KEY_SIZE is
     * provided, the possible values are 224, 256, 384 and 521, and must be mapped to Tag::EC_CURVE
     * values P_224, P_256, P_384 and P_521, respectively.  TEE IKeymasterDevice implementations
     * must support all curves.  StrongBox implementations must support P_256.
     *
     * == AES Keys ==
     *
     * Only Tag::KEY_SIZE is required to generate an AES key.  If omitted, generateKey must return
     * ErrorCode::UNSUPPORTED_KEY_SIZE.  128 and 256-bit key sizes must be supported.
     *
     * If Tag::BLOCK_MODE is specified with value BlockMode::GCM, then the caller must also provide
     * Tag::MIN_MAC_LENGTH.  If omitted, generateKey must return ErrorCode::MISSING_MIN_MAC_LENGTH.
     *
     *
     * @param keyParams Key generation parameters are defined as IKeymasterDevice tag/value pairs,
     *        provided in params.  See above for detailed specifications of which tags are required
     *        for which types of keys.
     *
     * @return keyBlob Opaque descriptor of the generated key.  The recommended implementation
     *         strategy is to include an encrypted copy of the key material, wrapped in a key
     *         unavailable outside secure hardware.
     *
     * @return keyCharacteristics Description of the generated key.  See the getKeyCharacteristics
     *         method below.
     */
    virtual ::android::hardware::Return<void> generateKey(const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& keyParams, generateKey_cb _hidl_cb) = 0;

    /**
     * Return callback for importKey
     */
    using importKey_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<uint8_t>& keyBlob, const ::android::hardware::keymaster::V4_0::KeyCharacteristics& keyCharacteristics)>;
    /**
     * Imports key material into an IKeymasterDevice.  Key definition parameters and return values
     * are the same as for generateKey, with the following exceptions:
     *
     * o Tag::KEY_SIZE is not necessary in the input parameters.  If not provided, the
     *   IKeymasterDevice must deduce the value from the provided key material and add the tag and
     *   value to the key characteristics.  If Tag::KEY_SIZE is provided, the IKeymasterDevice must
     *   validate it against the key material.  In the event of a mismatch, importKey must return
     *   ErrorCode::IMPORT_PARAMETER_MISMATCH.
     *
     * o Tag::RSA_PUBLIC_EXPONENT (for RSA keys only) is not necessary in the input parameters.  If
     *   not provided, the IKeymasterDevice must deduce the value from the provided key material and
     *   add the tag and value to the key characteristics.  If Tag::RSA_PUBLIC_EXPONENT is provided,
     *   the IKeymasterDevice must validate it against the key material.  In the event of a
     *   mismatch, importKey must return ErrorCode::IMPORT_PARAMETER_MISMATCH.
     *
     * o Tag::ORIGIN (returned in keyCharacteristics) must have the value KeyOrigin::IMPORTED.
     *
     * @param keyParams Key generation parameters are defined as IKeymasterDevice tag/value pairs,
     *        provided in params.
     *
     * @param keyFormat The format of the key material to import.  See KeyFormat in types.hal.
     *
     * @pram keyData The key material to import, in the format specified in keyFormat.
     *
     * @return keyBlob Opaque descriptor of the imported key.  The recommended implementation
     *         strategy is to include an encrypted copy of the key material, wrapped in a key
     *         unavailable outside secure hardware.
     *
     * @return keyCharacteristics Description of the generated key.  See the getKeyCharacteristics
     *         method below.
     */
    virtual ::android::hardware::Return<void> importKey(const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& keyParams, ::android::hardware::keymaster::V4_0::KeyFormat keyFormat, const ::android::hardware::hidl_vec<uint8_t>& keyData, importKey_cb _hidl_cb) = 0;

    /**
     * Return callback for importWrappedKey
     */
    using importWrappedKey_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<uint8_t>& keyBlob, const ::android::hardware::keymaster::V4_0::KeyCharacteristics& keyCharacteristics)>;
    /**
     * Securely imports a key, or key pair, returning a key blob and a description of the imported
     * key.
     *
     * @param wrappedKeyData The wrapped key material to import.  The wrapped key is in DER-encoded
     * ASN.1 format, specified by the following schema:
     *
     *     KeyDescription ::= SEQUENCE(
     *         keyFormat INTEGER,                   # Values from KeyFormat enum.
     *         keyParams AuthorizationList,
     *     )
     *
     *     SecureKeyWrapper ::= SEQUENCE(
     *         version INTEGER,                     # Contains value 0
     *         encryptedTransportKey OCTET_STRING,
     *         initializationVector OCTET_STRING,
     *         keyDescription KeyDescription,
     *         encryptedKey OCTET_STRING,
     *         tag OCTET_STRING
     *     )
     *
     *     Where:
     *
     *     o keyFormat is an integer from the KeyFormat enum, defining the format of the plaintext
     *       key material.
     *     o keyParams is the characteristics of the key to be imported (as with generateKey or
     *       importKey).  If the secure import is successful, these characteristics must be
     *       associated with the key exactly as if the key material had been insecurely imported
     *       with the @3.0::IKeymasterDevice::importKey.  See attestKey() for documentation of the
     *       AuthorizationList schema.
     *     o encryptedTransportKey is a 256-bit AES key, XORed with a masking key and then encrypted
     *       with the wrapping key specified by wrappingKeyBlob.
     *     o keyDescription is a KeyDescription, above.
     *     o encryptedKey is the key material of the key to be imported, in format keyFormat, and
     *       encrypted with encryptedEphemeralKey in AES-GCM mode, with the DER-encoded
     *       representation of keyDescription provided as additional authenticated data.
     *     o tag is the tag produced by the AES-GCM encryption of encryptedKey.
     *
     * So, importWrappedKey does the following:
     *
     *     1. Get the private key material for wrappingKeyBlob, verifying that the wrapping key has
     *        purpose KEY_WRAP, padding mode RSA_OAEP, and digest SHA_2_256, returning the
     *        appropriate error if any of those requirements fail.
     *     2. Extract the encryptedTransportKey field from the SecureKeyWrapper, and decrypt
     *        it with the wrapping key.
     *     3. XOR the result of step 2 with maskingKey.
     *     4. Use the result of step 3 as an AES-GCM key to decrypt encryptedKey, using the encoded
     *        value of keyDescription as the additional authenticated data.  Call the result
     *        "keyData" for the next step.
     *     5. Perform the equivalent of calling importKey(keyParams, keyFormat, keyData), except
     *        that the origin tag should be set to SECURELY_IMPORTED.
     *
     * @param wrappingKeyBlob The opaque key descriptor returned by generateKey() or importKey().
     *        This key must have been created with Purpose::WRAP_KEY.
     *
     * @param maskingKey The 32-byte value XOR'd with the transport key in the SecureWrappedKey
     *        structure.
     *
     * @param unwrappingParams must contain any parameters needed to perform the unwrapping
     *        operation.  For example, if the wrapping key is an AES key the block and padding modes
     *        must be specified in this argument.
     *
     * @param passwordSid specifies the password secure ID (SID) of the user that owns the key being
     *        installed.  If the authorization list in wrappedKeyData contains a Tag::USER_SECURE_ID
     *        with a value that has the HardwareAuthenticatorType::PASSWORD bit set, the constructed
     *        key must be bound to the SID value provided by this argument.  If the wrappedKeyData
     *        does not contain such a tag and value, this argument must be ignored.
     *
     * @param biometricSid specifies the biometric secure ID (SID) of the user that owns the key
     *        being installed.  If the authorization list in wrappedKeyData contains a
     *        Tag::USER_SECURE_ID with a value that has the HardwareAuthenticatorType::FINGERPRINT
     *        bit set, the constructed key must be bound to the SID value provided by this argument.
     *        If the wrappedKeyData does not contain such a tag and value, this argument must be
     *        ignored.
     *
     * @return keyBlob Opaque descriptor of the imported key.  It is recommended that the keyBlob
     *         contain a copy of the key material, wrapped in a key unavailable outside secure
     *         hardware.
     */
    virtual ::android::hardware::Return<void> importWrappedKey(const ::android::hardware::hidl_vec<uint8_t>& wrappedKeyData, const ::android::hardware::hidl_vec<uint8_t>& wrappingKeyBlob, const ::android::hardware::hidl_vec<uint8_t>& maskingKey, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& unwrappingParams, uint64_t passwordSid, uint64_t biometricSid, importWrappedKey_cb _hidl_cb) = 0;

    /**
     * Return callback for getKeyCharacteristics
     */
    using getKeyCharacteristics_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::keymaster::V4_0::KeyCharacteristics& keyCharacteristics)>;
    /**
     * Returns parameters associated with the provided key, divided into two sets: hardware-enforced
     * and software-enforced.  The description here applies equally to the key characteristics lists
     * returned by generateKey, importKey and importWrappedKey.  The characteristics returned by
     * this method completely describe the type and usage of the specified key.
     *
     * The rule that IKeymasterDevice implementations must use for deciding whether a given tag
     * belongs in the hardware-enforced or software-enforced list is that if the meaning of the tag
     * is fully assured by secure hardware, it is hardware enforced.  Otherwise, it's software
     * enforced.
     *
     *
     * @param keyBlob The opaque descriptor returned by generateKey, importKey or importWrappedKey.
     *
     * @param clientId An opaque byte string identifying the client.  This value must match the
     *        Tag::APPLICATION_ID data provided during key generation/import.  Without the correct
     *        value, it must be computationally infeasible for the secure hardware to obtain the key
     *        material.
     *
     * @param appData An opaque byte string provided by the application.  This value must match the
     *        Tag::APPLICATION_DATA data provided during key generation/import.  Without the correct
     *        value, it must be computationally infeasible for the secure hardware to obtain the key
     *        material.
     *
     * @return keyCharacteristics Description of the generated key.  See KeyCharacteristics in
     *         types.hal.
     */
    virtual ::android::hardware::Return<void> getKeyCharacteristics(const ::android::hardware::hidl_vec<uint8_t>& keyBlob, const ::android::hardware::hidl_vec<uint8_t>& clientId, const ::android::hardware::hidl_vec<uint8_t>& appData, getKeyCharacteristics_cb _hidl_cb) = 0;

    /**
     * Return callback for exportKey
     */
    using exportKey_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<uint8_t>& keyMaterial)>;
    /**
     * Exports a public key, returning the key in the specified format.
     *
     * @parm keyFormat The format used for export.  Must be KeyFormat::X509.
     *
     * @param keyBlob The opaque descriptor returned by generateKey() or importKey().  The
     *        referenced key must be asymmetric.
     *
     * @param clientId An opaque byte string identifying the client.  This value must match the
     *        Tag::APPLICATION_ID data provided during key generation/import.  Without the correct
     *        value, it must be computationally infeasible for the secure hardware to obtain the key
     *        material.
     *
     * @param appData An opaque byte string provided by the application.  This value must match the
     *        Tag::APPLICATION_DATA data provided during key generation/import.  Without the correct
     *        value, it must be computationally infeasible for the secure hardware to obtain the key
     *        material.
     *
     * @return keyMaterial The public key material in X.509 format.
     */
    virtual ::android::hardware::Return<void> exportKey(::android::hardware::keymaster::V4_0::KeyFormat keyFormat, const ::android::hardware::hidl_vec<uint8_t>& keyBlob, const ::android::hardware::hidl_vec<uint8_t>& clientId, const ::android::hardware::hidl_vec<uint8_t>& appData, exportKey_cb _hidl_cb) = 0;

    /**
     * Return callback for attestKey
     */
    using attestKey_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<::android::hardware::hidl_vec<uint8_t>>& certChain)>;
    /**
     * Generates a signed X.509 certificate chain attesting to the presence of keyToAttest in
     * Keymaster.
     *
     * The certificates in the chain must be ordered such that each certificate is signed by the
     * subsequent one, up to the root which must be self-signed.  The first certificate in the chain
     * signs the public key info of the attested key and must contain the following entries (see RFC
     * 5280 for details on each):
     *
     * o version -- with value 2
     *
     * o serialNumber -- with value 1 (same value for all keys)
     *
     * o signature -- contains an the AlgorithmIdentifier of the algorithm used to sign, must be
     *   ECDSA for EC keys, RSA for RSA keys.
     *
     * o issuer -- must contain the same value as the Subject field of the next certificate.
     *
     * o validity -- SEQUENCE of two dates, containing the values of Tag::ACTIVE_DATETIME and
     *   Tag::USAGE_EXPIRE_DATETIME.  The tag values are in milliseconds since Jan 1, 1970; see RFD
     *   5280 for the correct representation in certificates.  If Tag::ACTIVE_DATETIME is not
     *   present in the key, the IKeymasterDevice must use the value of Tag::CREATION_DATETIME.  If
     *   Tag::USAGE_EXPIRE_DATETIME is not present, the IKeymasterDevice must use the expiration
     *   date of the batch attestation certificate (see below).
     *
     * o subject -- CN="Android Keystore Key" (same value for all keys)
     *
     * o subjectPublicKeyInfo -- X.509 SubjectPublicKeyInfo containing the attested public key.
     *
     * o Key Usage extension -- digitalSignature bit must be set iff the attested key has
     *   KeyPurpose::SIGN.  dataEncipherment bit must be set iff the attested key has
     *   KeyPurpose::DECRYPT.  keyEncipherment bit must be set iff the attested key has
     *   KeyPurpose::KEY_WRAP.  All other bits must be clear.
     *
     * In addition to the above, the attestation certificate must contain an extension with OID
     * 1.3.6.1.4.1.11129.2.1.17 and value according to the KeyDescription schema defined as:
     *
     * KeyDescription ::= SEQUENCE {
     *     attestationVersion         INTEGER, # Value 3
     *     attestationSecurityLevel   SecurityLevel, # See below
     *     keymasterVersion           INTEGER, # Value 4
     *     keymasterSecurityLevel     SecurityLevel, # See below
     *     attestationChallenge       OCTET_STRING, # Tag::ATTESTATION_CHALLENGE from attestParams
     *     uniqueId                   OCTET_STRING, # Empty unless key has Tag::INCLUDE_UNIQUE_ID
     *     softwareEnforced           AuthorizationList, # See below
     *     hardwareEnforced           AuthorizationList, # See below
     * }
     *
     * SecurityLevel ::= ENUMERATED {
     *     Software                   (0),
     *     TrustedEnvironment         (1),
     *     StrongBox                  (2),
     * }
     *
     * RootOfTrust ::= SEQUENCE {
     *     verifiedBootKey            OCTET_STRING,
     *     deviceLocked               BOOLEAN,
     *     verifiedBootState          VerifiedBootState,
     *     # verifiedBootHash must contain 32-byte value that represents the state of all binaries
     *     # or other components validated by verified boot.  Updating any verified binary or
     *     # component must cause this value to change.
     *     verifiedBootHash           OCTET_STRING,
     * }
     *
     * VerifiedBootState ::= ENUMERATED {
     *     Verified                   (0),
     *     SelfSigned                 (1),
     *     Unverified                 (2),
     *     Failed                     (3),
     * }
     *
     * AuthorizationList ::= SEQUENCE {
     *     purpose                    [1] EXPLICIT SET OF INTEGER OPTIONAL,
     *     algorithm                  [2] EXPLICIT INTEGER OPTIONAL,
     *     keySize                    [3] EXPLICIT INTEGER OPTIONAL,
     *     blockMode                  [4] EXPLICIT SET OF INTEGER OPTIONAL,
     *     digest                     [5] EXPLICIT SET OF INTEGER OPTIONAL,
     *     padding                    [6] EXPLICIT SET OF INTEGER OPTIONAL,
     *     callerNonce                [7] EXPLICIT NULL OPTIONAL,
     *     minMacLength               [8] EXPLICIT INTEGER OPTIONAL,
     *     ecCurve                    [10] EXPLICIT INTEGER OPTIONAL,
     *     rsaPublicExponent          [200] EXPLICIT INTEGER OPTIONAL,
     *     rollbackResistance         [303] EXPLICIT NULL OPTIONAL,
     *     activeDateTime             [400] EXPLICIT INTEGER OPTIONAL,
     *     originationExpireDateTime  [401] EXPLICIT INTEGER OPTIONAL,
     *     usageExpireDateTime        [402] EXPLICIT INTEGER OPTIONAL,
     *     userSecureId               [502] EXPLICIT INTEGER OPTIONAL,
     *     noAuthRequired             [503] EXPLICIT NULL OPTIONAL,
     *     userAuthType               [504] EXPLICIT INTEGER OPTIONAL,
     *     authTimeout                [505] EXPLICIT INTEGER OPTIONAL,
     *     allowWhileOnBody           [506] EXPLICIT NULL OPTIONAL,
     *     trustedUserPresenceReq     [507] EXPLICIT NULL OPTIONAL,
     *     trustedConfirmationReq     [508] EXPLICIT NULL OPTIONAL,
     *     unlockedDeviceReq          [509] EXPLICIT NULL OPTIONAL,
     *     creationDateTime           [701] EXPLICIT INTEGER OPTIONAL,
     *     origin                     [702] EXPLICIT INTEGER OPTIONAL,
     *     rootOfTrust                [704] EXPLICIT RootOfTrust OPTIONAL,
     *     osVersion                  [705] EXPLICIT INTEGER OPTIONAL,
     *     osPatchLevel               [706] EXPLICIT INTEGER OPTIONAL,
     *     attestationApplicationId   [709] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdBrand         [710] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdDevice        [711] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdProduct       [712] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdSerial        [713] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdImei          [714] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdMeid          [715] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdManufacturer  [716] EXPLICIT OCTET_STRING OPTIONAL,
     *     attestationIdModel         [717] EXPLICIT OCTET_STRING OPTIONAL,
     *     vendorPatchLevel           [718] EXPLICIT INTEGER OPTIONAL,
     *     bootPatchLevel             [719] EXPLICIT INTEGER OPTIONAL,
     * }
     *
     * The above schema is mostly a straightforward translation of the IKeymasterDevice tag/value
     * parameter lists to ASN.1:
     *
     * o TagType::ENUM, TagType::UINT, TagType::ULONG and TagType::DATE tags are represented as
     *   ASN.1 INTEGER.
     *
     * o TagType::ENUM_REP, TagType::UINT_REP and TagType::ULONG_REP tags are represented as ASN.1
     *   SET of INTEGER.
     *
     * o TagType::BOOL tags are represented as ASN.1 NULL.  All entries in AuthorizationList are
     *   OPTIONAL, so the presence of the tag means "true", absence means "false".
     *
     * o TagType::BYTES tags are represented as ASN.1 OCTET_STRING.
     *
     * The numeric ASN.1 tag numbers are the same values as the IKeymasterDevice Tag enum values,
     * except with the TagType modifier stripped.
     *
     * The attestation certificate must be signed by a "batch" key, which must be securely
     * pre-installed into the device, generally in the factory, and securely stored to prevent
     * access or extraction.  The batch key must be used only for signing attestation certificates.
     * The batch attestation certificate must be signed by a chain or zero or more intermediates
     * leading to a self-signed roots.  The intermediate and root certificate signing keys must not
     * exist anywhere on the device.
     *
     * == ID Attestation ==
     *
     * ID attestation is a special case of key attestation in which unique device ID values are
     * included in the signed attestation certificate.
     *
     * @param keyToAttest The opaque descriptor returned by generateKey() or importKey().  The
     *        referenced key must be asymmetric.
     *
     * @param attestParams Parameters for the attestation.  Must contain Tag::ATTESTATION_CHALLENGE,
     *        the value of which must be put in the attestationChallenge field of the KeyDescription
     *        ASN.1 structure defined above.
     *
     * @return certChain The attestation certificate, and additional certificates back to the root
     *         attestation certificate, which clients will need to check against a known-good value.
     *         The certificates must be DER-encoded.
     */
    virtual ::android::hardware::Return<void> attestKey(const ::android::hardware::hidl_vec<uint8_t>& keyToAttest, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& attestParams, attestKey_cb _hidl_cb) = 0;

    /**
     * Return callback for upgradeKey
     */
    using upgradeKey_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<uint8_t>& upgradedKeyBlob)>;
    /**
     * Upgrades an old key blob.  Keys can become "old" in two ways: IKeymasterDevice can be
     * upgraded to a new version with an incompatible key blob format, or the system can be updated
     * to invalidate the OS version (OS_VERSION tag), system patch level (OS_PATCHLEVEL tag), vendor
     * patch level (VENDOR_PATCH_LEVEL tag), boot patch level (BOOT_PATCH_LEVEL tag) or other,
     * implementation-defined patch level (keymaster implementers are encouraged to extend this HAL
     * with a minor version extension to define validatable patch levels for other images; tags must
     * be defined in the implementer's namespace, starting at 10000).  In either case, attempts to
     * use an old key blob with getKeyCharacteristics(), exportKey(), attestKey() or begin() must
     * result in IKeymasterDevice returning ErrorCode::KEY_REQUIRES_UPGRADE.  The caller must use
     * this method to upgrade the key blob.
     *
     * The upgradeKey method must examine each version or patch level associated with the key.  If
     * any one of them is higher than the corresponding current device value upgradeKey() must
     * return ErrorCode::INVALID_ARGUMENT.  There is one exception: it is always permissible to
     * "downgrade" from any OS_VERSION number to OS_VERSION 0.  For example, if the key has
     * OS_VERSION 080001, it is permissible to upgrade the key if the current system version is
     * 080100, because the new version is larger, or if the current system version is 0, because
     * upgrades to 0 are always allowed.  If the system version were 080000, however, keymaster must
     * return ErrorCode::INVALID_ARGUMENT because that value is smaller than 080001.  Values other
     * than OS_VERSION must never be downgraded.
     *
     * Note that Keymaster versions 2 and 3 required that the system and boot images have the same
     * patch level and OS version.  This requirement is relaxed for 4.0::IKeymasterDevice, and the
     * OS version in the boot image footer is no longer used.
     *
     * @param keyBlobToUpgrade The opaque descriptor returned by generateKey() or importKey();
     *
     * @param upgradeParams A parameter list containing any parameters needed to complete the
     *        upgrade, including Tag::APPLICATION_ID and Tag::APPLICATION_DATA.
     *
     * @return upgradedKeyBlob A new key blob that references the same key as keyBlobToUpgrade, but
     *         is in the new format, or has the new version data.
     */
    virtual ::android::hardware::Return<void> upgradeKey(const ::android::hardware::hidl_vec<uint8_t>& keyBlobToUpgrade, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& upgradeParams, upgradeKey_cb _hidl_cb) = 0;

    /**
     * Deletes the key, or key pair, associated with the key blob.  Calling this function on a key
     * with Tag::ROLLBACK_RESISTANCE in its hardware-enforced authorization list must render the key
     * permanently unusable.  Keys without Tag::ROLLBACK_RESISTANCE may or may not be rendered
     * unusable.
     *
     * @param keyBlob The opaque descriptor returned by generateKey() or importKey();
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_0::ErrorCode> deleteKey(const ::android::hardware::hidl_vec<uint8_t>& keyBlob) = 0;

    /**
     * Deletes all keys in the hardware keystore.  Used when keystore is reset completely.  After
     * this function is called all keys with Tag::ROLLBACK_RESISTANCE in their hardware-enforced
     * authorization lists must be rendered permanently unusable.  Keys without
     * Tag::ROLLBACK_RESISTANCE may or may not be rendered unusable.
     *
     * @return error See the ErrorCode enum.
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_0::ErrorCode> deleteAllKeys() = 0;

    /**
     * Destroys knowledge of the device's ids.  This prevents all device id attestation in the
     * future.  The destruction must be permanent so that not even a factory reset will restore the
     * device ids.
     *
     * Device id attestation may be provided only if this method is fully implemented, allowing the
     * user to permanently disable device id attestation.  If this cannot be guaranteed, the device
     * must never attest any device ids.
     *
     * This is a NOP if device id attestation is not supported.
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_0::ErrorCode> destroyAttestationIds() = 0;

    /**
     * Return callback for begin
     */
    using begin_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& outParams, uint64_t operationHandle)>;
    /**
     * Begins a cryptographic operation using the specified key.  If all is well, begin() must
     * return ErrorCode::OK and create an operation handle which must be passed to subsequent calls
     * to update(), finish() or abort().
     *
     * It is critical that each call to begin() be paired with a subsequent call to finish() or
     * abort(), to allow the IKeymasterDevice implementation to clean up any internal operation
     * state.  The caller's failure to do this may leak internal state space or other internal
     * resources and may eventually cause begin() to return ErrorCode::TOO_MANY_OPERATIONS when it
     * runs out of space for operations.  Any result other than ErrorCode::OK from begin(), update()
     * or finish() implicitly aborts the operation, in which case abort() need not be called (and
     * must return ErrorCode::INVALID_OPERATION_HANDLE if called).  IKeymasterDevice implementations
     * must support 16 concurrent operations.
     *
     * If Tag::APPLICATION_ID or Tag::APPLICATION_DATA were specified during key generation or
     * import, calls to begin must include those tags with the originally-specified values in the
     * inParams argument to this method.  If not, begin() must return ErrorCode::INVALID_KEY_BLOB.
     *
     * == Authorization Enforcement ==
     *
     * The following key authorization parameters must be enforced by the IKeymasterDevice secure
     * environment if the tags were returned in the "hardwareEnforced" list in the
     * KeyCharacteristics.  Public key operations, meaning KeyPurpose::ENCRYPT and
     * KeyPurpose::VERIFY must be allowed to succeed even if authorization requirements are not met.
     *
     * -- All Key Types --
     *
     * The tags in this section apply to all key types.  See below for additional key type-specific
     * tags.
     *
     * o Tag::PURPOSE: The purpose specified in the begin() call must match one of the purposes in
     *   the key authorizations.  If the specified purpose does not match, begin() must return
     *   ErrorCode::UNSUPPORTED_PURPOSE.
     *
     * o Tag::ACTIVE_DATETIME can only be enforced if a trusted UTC time source is available.  If
     *   the current date and time is prior to the tag value, begin() must return
     *   ErrorCode::KEY_NOT_YET_VALID.
     *
     * o Tag::ORIGINATION_EXPIRE_DATETIME can only be enforced if a trusted UTC time source is
     *   available.  If the current date and time is later than the tag value and the purpose is
     *   KeyPurpose::ENCRYPT or KeyPurpose::SIGN, begin() must return ErrorCode::KEY_EXPIRED.
     *
     * o Tag::USAGE_EXPIRE_DATETIME can only be enforced if a trusted UTC time source is
     *   available.  If the current date and time is later than the tag value and the purpose is
     *   KeyPurpose::DECRYPT or KeyPurpose::VERIFY, begin() must return ErrorCode::KEY_EXPIRED.
     *
     * o Tag::MIN_SECONDS_BETWEEN_OPS must be compared with a trusted relative timer indicating the
     *   last use of the key.  If the last use time plus the tag value is less than the current
     *   time, begin() must return ErrorCode::KEY_RATE_LIMIT_EXCEEDED.  See the tag description for
     *   important implementation details.
     *
     * o Tag::MAX_USES_PER_BOOT must be compared against a secure counter that tracks the uses of
     *   the key since boot time.  If the count of previous uses exceeds the tag value, begin() must
     *   return ErrorCode::KEY_MAX_OPS_EXCEEDED.
     *
     * o Tag::USER_SECURE_ID must be enforced by this method if and only if the key also has
     *   Tag::AUTH_TIMEOUT (if it does not have Tag::AUTH_TIMEOUT, the Tag::USER_SECURE_ID
     *   requirement must be enforced by update() and finish()).  If the key has both, then this
     *   method must receive a non-empty HardwareAuthToken in the authToken argument.  For the auth
     *   token to be valid, all of the following have to be true:
     *
     *   o The HMAC field must validate correctly.
     *
     *   o At least one of the Tag::USER_SECURE_ID values from the key must match at least one of
     *     the secure ID values in the token.
     *
     *   o The key must have a Tag::USER_AUTH_TYPE that matches the auth type in the token.
     *
     *   o The timestamp in the auth token plus the value of the Tag::AUTH_TIMEOUT must be less than
     *     the current secure timestamp (which is a monotonic timer counting milliseconds since
     *     boot.)
     *
     *   If any of these conditions are not met, begin() must return
     *   ErrorCode::KEY_USER_NOT_AUTHENTICATED.
     *
     * o Tag::CALLER_NONCE allows the caller to specify a nonce or initialization vector (IV).  If
     *   the key doesn't have this tag, but the caller provided Tag::NONCE to this method,
     *   ErrorCode::CALLER_NONCE_PROHIBITED must be returned.
     *
     * o Tag::BOOTLOADER_ONLY specifies that only the bootloader may use the key.  If this method is
     *   called with a bootloader-only key after the bootloader has finished executing, it must
     *   return ErrorCode::INVALID_KEY_BLOB.  The mechanism for notifying the IKeymasterDevice that
     *   the bootloader has finished executing is implementation-defined.
     *
     * -- RSA Keys --
     *
     * All RSA key operations must specify exactly one padding mode in inParams.  If unspecified or
     * specified more than once, the begin() must return ErrorCode::UNSUPPORTED_PADDING_MODE.
     *
     * RSA signing and verification operations need a digest, as do RSA encryption and decryption
     * operations with OAEP padding mode.  For those cases, the caller must specify exactly one
     * digest in inParams.  If unspecified or specified more than once, begin() must return
     * ErrorCode::UNSUPPORTED_DIGEST.
     *
     * Private key operations (KeyPurpose::DECRYPT and KeyPurpose::SIGN) need authorization of
     * digest and padding, which means that the key authorizations need to contain the specified
     * values.  If not, begin() must return ErrorCode::INCOMPATIBLE_DIGEST or
     * ErrorCode::INCOMPATIBLE_PADDING, as appropriate.  Public key operations (KeyPurpose::ENCRYPT
     * and KeyPurpose::VERIFY) are permitted with unauthorized digest or padding modes.
     *
     * With the exception of PaddingMode::NONE, all RSA padding modes are applicable only to certain
     * purposes.  Specifically, PaddingMode::RSA_PKCS1_1_5_SIGN and PaddingMode::RSA_PSS only
     * support signing and verification, while PaddingMode::RSA_PKCS1_1_5_ENCRYPT and
     * PaddingMode::RSA_OAEP only support encryption and decryption.  begin() must return
     * ErrorCode::UNSUPPORTED_PADDING_MODE if the specified mode does not support the specified
     * purpose.
     *
     * There are some important interactions between padding modes and digests:
     *
     * o PaddingMode::NONE indicates that a "raw" RSA operation is performed.  If signing or
     *   verifying, Digest::NONE is specified for the digest.  No digest is necessary for unpadded
     *   encryption or decryption.
     *
     * o PaddingMode::RSA_PKCS1_1_5_SIGN padding requires a digest.  The digest may be Digest::NONE,
     *   in which case the Keymaster implementation cannot build a proper PKCS#1 v1.5 signature
     *   structure, because it cannot add the DigestInfo structure.  Instead, the IKeymasterDevice
     *   must construct 0x00 || 0x01 || PS || 0x00 || M, where M is the provided message and PS is a
     *   random padding string at least eight bytes in length.  The size of the RSA key has to be at
     *   least 11 bytes larger than the message, otherwise begin() must return
     *   ErrorCode::INVALID_INPUT_LENGTH.
     *
     * o PaddingMode::RSA_PKCS1_1_1_5_ENCRYPT padding does not require a digest.
     *
     * o PaddingMode::RSA_PSS padding requires a digest, which may not be Digest::NONE.  If
     *   Digest::NONE is specified, the begin() must return ErrorCode::INCOMPATIBLE_DIGEST.  In
     *   addition, the size of the RSA key must be at least 2 + D bytes larger than the output size
     *   of the digest, where D is the size of the digest, in bytes.  Otherwise begin() must
     *   return ErrorCode::INCOMPATIBLE_DIGEST.  The salt size must be D.
     *
     * o PaddingMode::RSA_OAEP padding requires a digest, which may not be Digest::NONE.  If
     *   Digest::NONE is specified, begin() must return ErrorCode::INCOMPATIBLE_DIGEST.  The OAEP
     *   mask generation function must be MGF1 and the MGF1 digest must be SHA1, regardless of the
     *   OAEP digest specified.
     *
     * -- EC Keys --
     *
     * EC private key operations must specify exactly one digest in inParams.  If unspecified or
     * specified more than once, begin() must return ErrorCode::UNSUPPORTED_DIGEST.  For private key
     * operations, (KeyPurpose::SIGN), if the specified digest is not in the key's authorization
     * list, begin() must return ErrorCode::INCOMPATIBLE_DIGEST.  Public key operations
     * (KeyPurpose::VERIFY) are permitted with unauthorized digest.
     *
     * -- AES Keys --
     *
     * AES key operations must specify exactly one block mode (Tag::BLOCK_MODE) and one padding mode
     * (Tag::PADDING) in inParams.  If either value is unspecified or specified more than once,
     * begin() must return ErrorCode::UNSUPPORTED_BLOCK_MODE or
     * ErrorCode::UNSUPPORTED_PADDING_MODE.  The specified modes must be authorized by the key,
     * otherwise begin() must return ErrorCode::INCOMPATIBLE_BLOCK_MODE or
     * ErrorCode::INCOMPATIBLE_PADDING_MODE.
     *
     * If the block mode is BlockMode::GCM, inParams must specify Tag::MAC_LENGTH, and the specified
     * value must be a multiple of 8 that is not greater than 128 or less than the value of
     * Tag::MIN_MAC_LENGTH in the key authorizations.  For MAC lengths greater than 128 or
     * non-multiples of 8, begin() must return ErrorCode::UNSUPPORTED_MAC_LENGTH.  For values less
     * than the key's minimum length, begin() must return ErrorCode::INVALID_MAC_LENGTH.
     *
     * If the block mode is BlockMode::GCM or BlockMode::CTR, the specified padding mode must be
     * PaddingMode::NONE.  For BlockMode::ECB or BlockMode::CBC, the mode may be PaddingMode::NONE
     * or PaddingMode::PKCS7.  If the padding mode doesn't meet these conditions, begin() must
     * return ErrorCode::INCOMPATIBLE_PADDING_MODE.
     *
     * If the block mode is BlockMode::CBC, BlockMode::CTR, or BlockMode::GCM, an initialization
     * vector or nonce is required.  In most cases, callers shouldn't provide an IV or nonce and the
     * IKeymasterDevice implementation must generate a random IV or nonce and return it via
     * Tag::NONCE in outParams.  CBC and CTR IVs are 16 bytes.  GCM nonces are 12 bytes.  If the key
     * authorizations contain Tag::CALLER_NONCE, then the caller may provide an IV/nonce with
     * Tag::NONCE in inParams.  If a nonce is provided when Tag::CALLER_NONCE is not authorized,
     * begin() must return ErrorCode::CALLER_NONCE_PROHIBITED.  If a nonce is not provided when
     * Tag::CALLER_NONCE is authorized, IKeymasterDevice must generate a random IV/nonce.
     *
     * -- HMAC keys --
     *
     * HMAC key operations must specify Tag::MAC_LENGTH in inParams.  The specified value must be a
     * multiple of 8 that is not greater than the digest length or less than the value of
     * Tag::MIN_MAC_LENGTH in the key authorizations.  For MAC lengths greater than the digest
     * length or non-multiples of 8, begin() must return ErrorCode::UNSUPPORTED_MAC_LENGTH.  For
     * values less than the key's minimum length, begin() must return ErrorCode::INVALID_MAC_LENGTH.
     *
     * @param purpose The purpose of the operation, one of KeyPurpose::ENCRYPT, KeyPurpose::DECRYPT,
     *        KeyPurpose::SIGN or KeyPurpose::VERIFY.  Note that for AEAD modes, encryption and
     *        decryption imply signing and verification, respectively, but must be specified as
     *        KeyPurpose::ENCRYPT and KeyPurpose::DECRYPT.
     *
     * @param keyBlob The opaque key descriptor returned by generateKey() or importKey().  The key
     *        must have a purpose compatible with purpose and all of its usage requirements must be
     *        satisfied, or begin() must return an appropriate error code (see above).
     *
     * @param inParams Additional parameters for the operation.  If Tag::APPLICATION_ID or
     *        Tag::APPLICATION_DATA were provided during generation, they must be provided here, or
     *        the operation must fail with ErrorCode::INVALID_KEY_BLOB.  For operations that require
     *        a nonce or IV, on keys that were generated with Tag::CALLER_NONCE, inParams may
     *        contain a tag Tag::NONCE.  If Tag::NONCE is provided for a key without
     *        Tag:CALLER_NONCE, ErrorCode::CALLER_NONCE_PROHIBITED must be returned.
     *
     * @param authToken Authentication token.  Callers that provide no token must set all numeric
     *        fields to zero and the MAC must be an empty vector.
     *
     * @return outParams Output parameters.  Used to return additional data from the operation
     *         initialization, notably to return the IV or nonce from operations that generate an IV
     *         or nonce.
     *
     * @return operationHandle The newly-created operation handle which must be passed to update(),
     *         finish() or abort().
     */
    virtual ::android::hardware::Return<void> begin(::android::hardware::keymaster::V4_0::KeyPurpose purpose, const ::android::hardware::hidl_vec<uint8_t>& keyBlob, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& inParams, const ::android::hardware::keymaster::V4_0::HardwareAuthToken& authToken, begin_cb _hidl_cb) = 0;

    /**
     * Return callback for update
     */
    using update_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, uint32_t inputConsumed, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& outParams, const ::android::hardware::hidl_vec<uint8_t>& output)>;
    /**
     * Provides data to, and possibly receives output from, an ongoing cryptographic operation begun
     * with begin().  The operation is specified by the operationHandle parameter.
     *
     * If operationHandle is invalid, update() must return ErrorCode::INVALID_OPERATION_HANDLE.
     *
     * To provide more flexibility for buffer handling, implementations of this method have the
     * option of consuming less data than was provided.  The caller is responsible for looping to
     * feed the rest of the data in subsequent calls.  The amount of input consumed must be returned
     * in the inputConsumed parameter.  Implementations must always consume at least one byte, unless
     * the operation cannot accept any more; if more than zero bytes are provided and zero bytes are
     * consumed, callers must consider this an error and abort the operation.
     *
     * Implementations may also choose how much data to return, as a result of the update.  This is
     * only relevant for encryption and decryption operations, because signing and verification
     * return no data until finish.  It is recommended to return data as early as possible, rather
     * than buffer it.
     *
     * If this method returns an error code other than ErrorCode::OK, the operation is aborted and
     * the operation handle must be invalidated.  Any future use of the handle, with this method,
     * finish, or abort, must return ErrorCode::INVALID_OPERATION_HANDLE.
     *
     * == Authorization Enforcement ==
     *
     * Key authorization enforcement is performed primarily in begin().  The one exception is the
     * case where the key has:
     *
     * o One or more Tag::USER_SECURE_IDs, and
     *
     * o Does not have a Tag::AUTH_TIMEOUT
     *
     * In this case, the key requires an authorization per operation, and the update method must
     * receive a non-empty and valid HardwareAuthToken.  For the auth token to be valid, all of the
     * following has to be true:
     *
     *   o The HMAC field must validate correctly.
     *
     *   o At least one of the Tag::USER_SECURE_ID values from the key must match at least one of
     *     the secure ID values in the token.
     *
     *   o The key must have a Tag::USER_AUTH_TYPE that matches the auth type in the token.
     *
     *   o The challenge field in the auth token must contain the operationHandle
     *
     *   If any of these conditions are not met, update() must return
     *   ErrorCode::KEY_USER_NOT_AUTHENTICATED.
     *
     * The caller must provide the auth token on every call to update() and finish().
     *
     * -- RSA keys --
     *
     * For signing and verification operations with Digest::NONE, this method must accept the entire
     * block to be signed or verified in a single update.  It may not consume only a portion of the
     * block in these cases.  However, the caller may choose to provide the data in multiple updates,
     * and update() must accept the data this way as well.  If the caller provides more data to sign
     * than can be used (length of data exceeds RSA key size), update() must return
     * ErrorCode::INVALID_INPUT_LENGTH.
     *
     * -- ECDSA keys --
     *
     * For signing and verification operations with Digest::NONE, this method must accept the entire
     * block to be signed or verified in a single update.  This method may not consume only a
     * portion of the block.  However, the caller may choose to provide the data in multiple updates
     * and update() must accept the data this way as well.  If the caller provides more data to sign
     * than can be used, the data is silently truncated.  (This differs from the handling of excess
     * data provided in similar RSA operations.  The reason for this is compatibility with legacy
     * clients.)
     *
     * -- AES keys --
     *
     * AES GCM mode supports "associated authentication data," provided via the Tag::ASSOCIATED_DATA
     * tag in the inParams argument.  The associated data may be provided in repeated calls
     * (important if the data is too large to send in a single block) but must always precede data
     * to be encrypted or decrypted.  An update call may receive both associated data and data to
     * encrypt/decrypt, but subsequent updates must not include associated data.  If the caller
     * provides associated data to an update call after a call that includes data to
     * encrypt/decrypt, update() must return ErrorCode::INVALID_TAG.
     *
     * For GCM encryption, the AEAD tag must be appended to the ciphertext by finish().  During
     * decryption, the last Tag::MAC_LENGTH bytes of the data provided to the last update call must
     * be the AEAD tag.  Since a given invocation of update cannot know if it's the last invocation,
     * it must process all but the tag length and buffer the possible tag data for processing during
     * finish().
     *
     * @param operationHandle The operation handle returned by begin().
     *
     * @param inParams Additional parameters for the operation.  For AEAD modes, this is used to
     *        specify Tag::ADDITIONAL_DATA.  Note that additional data may be provided in multiple
     *        calls to update(), but only until input data has been provided.
     *
     * @param input Data to be processed.  Note that update() may or may not consume all of the data
     *        provided.  See inputConsumed.
     *
     * @param authToken Authentication token.  Callers that provide no token must set all numeric
     *        fields to zero and the MAC must be an empty vector.
     *
     * @param verificationToken Verification token, used to prove that another IKeymasterDevice HAL
     *        has verified some parameters, and to deliver the other HAL's current timestamp, if
     *        needed.  If not provided, all fields must be initialized to zero and vectors must be
     *        empty.
     *
     * @return error See the ErrorCode enum in types.hal.
     *
     * @return inputConsumed Amount of data that was consumed by update().  If this is less than the
     *         amount provided, the caller may provide the remainder in a subsequent call to
     *         update() or finish().  Every call to update must consume at least one byte, unless
     *         the input is empty, and implementations should consume as much data as reasonably
     *         possible for each call.
     *
     * @return outParams Output parameters, used to return additional data from the operation.
     *
     * @return output The output data, if any.
     */
    virtual ::android::hardware::Return<void> update(uint64_t operationHandle, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& inParams, const ::android::hardware::hidl_vec<uint8_t>& input, const ::android::hardware::keymaster::V4_0::HardwareAuthToken& authToken, const ::android::hardware::keymaster::V4_0::VerificationToken& verificationToken, update_cb _hidl_cb) = 0;

    /**
     * Return callback for finish
     */
    using finish_cb = std::function<void(::android::hardware::keymaster::V4_0::ErrorCode error, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& outParams, const ::android::hardware::hidl_vec<uint8_t>& output)>;
    /**
     * Finalizes a cryptographic operation begun with begin() and invalidates operationHandle.
     *
     * This method is the last one called in an operation, so all processed data must be returned.
     *
     * Whether it completes successfully or returns an error, this method finalizes the operation
     * and therefore must invalidate the provided operation handle.  Any future use of the handle,
     * with finish(), update(), or abort(), must return ErrorCode::INVALID_OPERATION_HANDLE.
     *
     * Signing operations return the signature as the output.  Verification operations accept the
     * signature in the signature parameter, and return no output.
     *
     * == Authorization enforcement ==
     *
     * Key authorization enforcement is performed primarily in begin().  The exceptions are
     * authorization per operation keys and confirmation-required keys.
     *
     * Authorization per operation keys are the case where the key has one or more
     * Tag::USER_SECURE_IDs, and does not have a Tag::AUTH_TIMEOUT.  In this case, the key requires
     * an authorization per operation, and the finish method must receive a non-empty and valid
     * authToken.  For the auth token to be valid, all of the following has to be true:
     *
     *   o The HMAC field must validate correctly.
     *
     *   o At least one of the Tag::USER_SECURE_ID values from the key must match at least one of
     *     the secure ID values in the token.
     *
     *   o The key must have a Tag::USER_AUTH_TYPE that matches the auth type in the token.
     *
     *   o The challenge field in the auth token must contain the operationHandle
     *
     *   If any of these conditions are not met, update() must return
     *   ErrorCode::KEY_USER_NOT_AUTHENTICATED.
     *
     * The caller must provide the auth token on every call to update() and finish().
     *
     * Confirmation-required keys are keys that were generated with
     * Tag::TRUSTED_CONFIRMATION_REQUIRED.  For these keys, when doing a signing operation the
     * caller must pass a KeyParameter Tag::CONFIRMATION_TOKEN to finish().  Implementations must
     * check the confirmation token by computing the 32-byte HMAC-SHA256 over all of the
     * to-be-signed data, prefixed with the 18-byte UTF-8 encoded string "confirmation token". If
     * the computed value does not match the Tag::CONFIRMATION_TOKEN parameter, finish() must not
     * produce a signature and must return ErrorCode::NO_USER_CONFIRMATION.
     *
     * -- RSA keys --
     *
     * Some additional requirements, depending on the padding mode:
     *
     * o PaddingMode::NONE.  For unpadded signing and encryption operations, if the provided data is
     *   shorter than the key, the data must be zero-padded on the left before
     *   signing/encryption.  If the data is the same length as the key, but numerically larger,
     *   finish() must return ErrorCode::INVALID_ARGUMENT.  For verification and decryption
     *   operations, the data must be exactly as long as the key.  Otherwise, return
     *   ErrorCode::INVALID_INPUT_LENGTH.
     *
     * o PaddingMode::RSA_PSS.  For PSS-padded signature operations, the PSS salt length must match
     *   the size of the PSS digest selected.  The digest specified with Tag::DIGEST in inputParams
     *   on begin() must be used as the PSS digest algorithm, MGF1 must be used as the mask
     *   generation function and SHA1 must be used as the MGF1 digest algorithm.
     *
     * o PaddingMode::RSA_OAEP.  The digest specified with Tag::DIGEST in inputParams on begin is
     *   used as the OAEP digest algorithm, MGF1 must be used as the mask generation function and
     *   and SHA1 must be used as the MGF1 digest algorithm.
     *
     * -- ECDSA keys --
     *
     * If the data provided for unpadded signing or verification is too long, truncate it.
     *
     * -- AES keys --
     *
     * Some additional conditions, depending on block mode:
     *
     * o BlockMode::ECB or BlockMode::CBC.  If padding is PaddingMode::NONE and the data length is
     *  not a multiple of the AES block size, finish() must return
     *  ErrorCode::INVALID_INPUT_LENGTH.  If padding is PaddingMode::PKCS7, pad the data per the
     *  PKCS#7 specification, including adding an additional padding block if the data is a multiple
     *  of the block length.
     *
     * o BlockMode::GCM.  During encryption, after processing all plaintext, compute the tag
     *   (Tag::MAC_LENGTH bytes) and append it to the returned ciphertext.  During decryption,
     *   process the last Tag::MAC_LENGTH bytes as the tag.  If tag verification fails, finish()
     *   must return ErrorCode::VERIFICATION_FAILED.
     *
     * @param operationHandle The operation handle returned by begin().  This handle must be invalid
     *        when finish() returns.
     *
     * @param inParams Additional parameters for the operation.  For AEAD modes, this is used to
     *        specify Tag::ADDITIONAL_DATA, but only if no input data was provided to update().
     *
     * @param input Data to be processed, per the parameters established in the call to begin().
     *        finish() must consume all provided data or return ErrorCode::INVALID_INPUT_LENGTH.
     *
     * @param signature The signature to be verified if the purpose specified in the begin() call
     *        was KeyPurpose::VERIFY.
     *
     * @param authToken Authentication token.  Callers that provide no token must set all numeric
     *        fields to zero and the MAC must be an empty vector.
     *
     * @param verificationToken Verification token, used to prove that another IKeymasterDevice HAL
     *        has verified some parameters, and to deliver the other HAL's current timestamp, if
     *        needed.  If not provided, all fields must be initialized to zero and vectors empty.
     *
     * @return outParams Any output parameters generated by finish().
     *
     * @return output The output data, if any.
     */
    virtual ::android::hardware::Return<void> finish(uint64_t operationHandle, const ::android::hardware::hidl_vec<::android::hardware::keymaster::V4_0::KeyParameter>& inParams, const ::android::hardware::hidl_vec<uint8_t>& input, const ::android::hardware::hidl_vec<uint8_t>& signature, const ::android::hardware::keymaster::V4_0::HardwareAuthToken& authToken, const ::android::hardware::keymaster::V4_0::VerificationToken& verificationToken, finish_cb _hidl_cb) = 0;

    /**
     * Aborts a cryptographic operation begun with begin(), freeing all internal resources and
     * invalidating operationHandle.
     *
     * @param operationHandle The operation handle returned by begin().  This handle must be
     *        invalid when abort() returns.
     *
     * @return error See the ErrorCode enum in types.hal.
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_0::ErrorCode> abort(uint64_t operationHandle) = 0;

    /**
     * Called by client to notify the IKeymasterDevice that the device is now locked, and keys with
     * the UNLOCKED_DEVICE_REQUIRED tag should no longer be usable.  When this function is called,
     * the IKeymasterDevice should note the current timestamp, and attempts to use
     * UNLOCKED_DEVICE_REQUIRED keys must be rejected with Error::DEVICE_LOCKED until an
     * authentication token with a later timestamp is presented.  If the `passwordOnly' argument is
     * set to true the sufficiently-recent authentication token must indicate that the user
     * authenticated with a password, not a biometric.
     *
     * Note that the IKeymasterDevice UNLOCKED_DEVICE_REQUIRED semantics are slightly different from
     * the UNLOCKED_DEVICE_REQUIRED semantics enforced by keystore.  Keystore handles device locking
     * on a per-user basis.  Because auth tokens do not contain an Android user ID, it's not
     * possible to replicate the keystore enformcement logic in IKeymasterDevice.  So from the
     * IKeymasterDevice perspective, any user unlock unlocks all UNLOCKED_DEVICE_REQUIRED keys.
     * Keystore will continue enforcing the per-user device locking.
     *
     * @param passwordOnly specifies whether the device must be unlocked with a password, rather
     * than a biometric, before UNLOCKED_DEVICE_REQUIRED keys can be used.
     *
     * @param verificationToken is used by StrongBox implementations of IKeymasterDevice.  It
     * provides the StrongBox IKeymasterDevice with a fresh, MACed timestamp which it can use as the
     * device-lock time, for future comparison against auth tokens when operations using
     * UNLOCKED_DEVICE_REQUIRED keys are attempted.  Unless the auth token timestamp is newer than
     * the timestamp in the verificationToken, the device is still considered to be locked.
     * Crucially, if a StrongBox IKeymasterDevice receives a deviceLocked() call with a verification
     * token timestamp that is less than the timestamp in the last deviceLocked() call, it must
     * ignore the new timestamp.  TEE IKeymasterDevice implementations will receive an empty
     * verificationToken (zero values and empty vectors) and should use their own clock as the
     * device-lock time.
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_1::ErrorCode> deviceLocked(bool passwordOnly, const ::android::hardware::keymaster::V4_0::VerificationToken& verificationToken) = 0;

    /**
     * Called by client to notify the IKeymasterDevice that the device has left the early boot
     * state, and that keys with the EARLY_BOOT_ONLY tag may no longer be used.  All attempts to use
     * an EARLY_BOOT_ONLY key after this method is called must fail with Error::INVALID_KEY_BLOB.
     */
    virtual ::android::hardware::Return<::android::hardware::keymaster::V4_1::ErrorCode> earlyBootEnded() = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::keymaster::V4_1::IKeymasterDevice>> castFrom(const ::android::sp<::android::hardware::keymaster::V4_1::IKeymasterDevice>& parent, bool emitError = false);
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::keymaster::V4_1::IKeymasterDevice>> castFrom(const ::android::sp<::android::hardware::keymaster::V4_0::IKeymasterDevice>& parent, bool emitError = false);
    /**
     * This performs a checked cast based on what the underlying implementation actually is.
     */
    static ::android::hardware::Return<::android::sp<::android::hardware::keymaster::V4_1::IKeymasterDevice>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

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
    static ::android::sp<IKeymasterDevice> tryGetService(const std::string &serviceName="default", bool getStub=false);
    /**
     * Deprecated. See tryGetService(std::string, bool)
     */
    static ::android::sp<IKeymasterDevice> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    /**
     * Deprecated. See tryGetService(std::string, bool)
     */
    static ::android::sp<IKeymasterDevice> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    /**
     * Calls tryGetService("default", bool). This is the recommended instance name for singleton services.
     */
    static ::android::sp<IKeymasterDevice> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    /**
     * This gets the service of this type with the specified instance name. If the
     * service is not in the VINTF manifest on a Trebilized device, this will return
     * nullptr. If the service is not available, this will wait for the service to
     * become available. If the service is a lazy service, this will start the service
     * and return when it becomes available. If getStub is true, this will try to
     * return an unwrapped passthrough implementation in the same process. This is
     * useful when getting an implementation from the same partition/compilation group.
     */
    static ::android::sp<IKeymasterDevice> getService(const std::string &serviceName="default", bool getStub=false);
    /**
     * Deprecated. See getService(std::string, bool)
     */
    static ::android::sp<IKeymasterDevice> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    /**
     * Deprecated. See getService(std::string, bool)
     */
    static ::android::sp<IKeymasterDevice> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    /**
     * Calls getService("default", bool). This is the recommended instance name for singleton services.
     */
    static ::android::sp<IKeymasterDevice> getService(bool getStub) { return getService("default", getStub); }
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

static inline std::string toString(const ::android::sp<::android::hardware::keymaster::V4_1::IKeymasterDevice>& o);

//
// type header definitions for package
//

static inline std::string toString(const ::android::sp<::android::hardware::keymaster::V4_1::IKeymasterDevice>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::keymaster::V4_1::IKeymasterDevice::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V4_1
}  // namespace keymaster
}  // namespace hardware
}  // namespace android

//
// global type declarations for package
//


#endif  // HIDL_GENERATED_ANDROID_HARDWARE_KEYMASTER_V4_1_IKEYMASTERDEVICE_H
