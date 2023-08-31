/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.0.v202012010850.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_Cluster_STUB_DEFAULT_HPP_
#define V1_COMMONAPI_Cluster_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/commonapi/ClusterStub.hpp>
#include <cassert>
#include <sstream>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace commonapi {

/**
 * Provides a default implementation for ClusterStubRemoteEvent and
 * ClusterStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT ClusterStubDefault
    : public virtual ClusterStub {
public:
    COMMONAPI_EXPORT ClusterStubDefault()
        : remoteEventHandler_(this),
          interfaceVersion_(Cluster::getInterfaceVersion()) {
    }

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
        (void)_client;
        return interfaceVersion_;
    }

    COMMONAPI_EXPORT ClusterStubRemoteEvent* initStubAdapter(const std::shared_ptr< ClusterStubAdapter> &_adapter) {
        CommonAPI::Stub<ClusterStubAdapter, ClusterStubRemoteEvent>::stubAdapter_ = _adapter;
        return &remoteEventHandler_;
    }

    COMMONAPI_EXPORT virtual void updateSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _speed, updateSpeedReply_t _reply) {
        (void)_client;
        (void)_speed;
        int32_t status = 0;
        _reply(status);
    }
    COMMONAPI_EXPORT virtual void updateRPM(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _rpm, updateRPMReply_t _reply) {
        (void)_client;
        (void)_rpm;
        int32_t status = 0;
        _reply(status);
    }
    COMMONAPI_EXPORT virtual void clickButtons(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _command, clickButtonsReply_t _reply) {
        (void)_client;
        (void)_command;
        int32_t status = 0;
        _reply(status);
    }
    COMMONAPI_EXPORT virtual void sendDetects(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image, sendDetectsReply_t _reply) {
        (void)_client;
        (void)_image;
        int32_t status = 0;
        _reply(status);
    }


protected:
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual ClusterStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(ClusterStubDefault *_defaultStub)
            : 
              defaultStub_(_defaultStub) {
        }


    private:
        ClusterStubDefault *defaultStub_;
    };
protected:
    ClusterStubDefault::RemoteEventHandler remoteEventHandler_;

private:


    CommonAPI::Version interfaceVersion_;
};

} // namespace commonapi
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_Cluster_STUB_DEFAULT
