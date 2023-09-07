/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.0.v202012010850.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_Cluster_PROXY_HPP_
#define V1_COMMONAPI_Cluster_PROXY_HPP_

#include <v1/commonapi/ClusterProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif


#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v1 {
namespace commonapi {

template <typename ... _AttributeExtensions>
class ClusterProxy
    : virtual public Cluster,
      virtual public ClusterProxyBase,
      virtual public _AttributeExtensions... {
public:
    ClusterProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~ClusterProxy();

    typedef Cluster InterfaceType;


    /**
     * Returns the CommonAPI address of the remote partner this proxy communicates with.
     */
    virtual const CommonAPI::Address &getAddress() const;

    /**
     * Returns true if the remote partner for this proxy is currently known to be available.
     */
    virtual bool isAvailable() const;

    /**
     * Returns true if the remote partner for this proxy is available.
     */
    virtual bool isAvailableBlocking() const;

    /**
     * Returns the wrapper class that is used to (de-)register for notifications about
     * the availability of the remote partner of this proxy.
     */
    virtual CommonAPI::ProxyStatusEvent& getProxyStatusEvent();

    /**
     * Returns the wrapper class that is used to access version information of the remote
     * partner of this proxy.
     */
    virtual CommonAPI::InterfaceVersionAttribute& getInterfaceVersionAttribute();

    virtual std::future<void> getCompletionFuture();

    /**
     * Calls sendImage1 with synchronous semantics.
     *
     * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void sendImage1(std::vector< uint8_t > _image1, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage1 with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> sendImage1Async(const std::vector< uint8_t > &_image1, SendImage1AsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage2 with synchronous semantics.
     *
     * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void sendImage2(std::vector< uint8_t > _image2, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage2 with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> sendImage2Async(const std::vector< uint8_t > &_image2, SendImage2AsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage3 with synchronous semantics.
     *
     * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void sendImage3(std::vector< uint8_t > _image3, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage3 with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> sendImage3Async(const std::vector< uint8_t > &_image3, SendImage3AsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage4 with synchronous semantics.
     *
     * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void sendImage4(std::vector< uint8_t > _image4, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls sendImage4 with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> sendImage4Async(const std::vector< uint8_t > &_image4, SendImage4AsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);



 private:
    std::shared_ptr< ClusterProxyBase> delegate_;
};

typedef ClusterProxy<> ClusterProxyDefault;


//
// ClusterProxy Implementation
//
template <typename ... _AttributeExtensions>
ClusterProxy<_AttributeExtensions...>::ClusterProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast< ClusterProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast< ClusterProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
ClusterProxy<_AttributeExtensions...>::~ClusterProxy() {
}

template <typename ... _AttributeExtensions>
void ClusterProxy<_AttributeExtensions...>::sendImage1(std::vector< uint8_t > _image1, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
    delegate_->sendImage1(_image1, _internalCallStatus, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ClusterProxy<_AttributeExtensions...>::sendImage1Async(const std::vector< uint8_t > &_image1, SendImage1AsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    return delegate_->sendImage1Async(_image1, _callback, _info);
}
template <typename ... _AttributeExtensions>
void ClusterProxy<_AttributeExtensions...>::sendImage2(std::vector< uint8_t > _image2, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
    delegate_->sendImage2(_image2, _internalCallStatus, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ClusterProxy<_AttributeExtensions...>::sendImage2Async(const std::vector< uint8_t > &_image2, SendImage2AsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    return delegate_->sendImage2Async(_image2, _callback, _info);
}
template <typename ... _AttributeExtensions>
void ClusterProxy<_AttributeExtensions...>::sendImage3(std::vector< uint8_t > _image3, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
    delegate_->sendImage3(_image3, _internalCallStatus, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ClusterProxy<_AttributeExtensions...>::sendImage3Async(const std::vector< uint8_t > &_image3, SendImage3AsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    return delegate_->sendImage3Async(_image3, _callback, _info);
}
template <typename ... _AttributeExtensions>
void ClusterProxy<_AttributeExtensions...>::sendImage4(std::vector< uint8_t > _image4, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
    delegate_->sendImage4(_image4, _internalCallStatus, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ClusterProxy<_AttributeExtensions...>::sendImage4Async(const std::vector< uint8_t > &_image4, SendImage4AsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    return delegate_->sendImage4Async(_image4, _callback, _info);
}

template <typename ... _AttributeExtensions>
const CommonAPI::Address &ClusterProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool ClusterProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool ClusterProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& ClusterProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& ClusterProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


template <typename ... _AttributeExtensions>
std::future<void> ClusterProxy<_AttributeExtensions...>::getCompletionFuture() {
    return delegate_->getCompletionFuture();
}

} // namespace commonapi
} // namespace v1



// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_Cluster_PROXY_HPP_
