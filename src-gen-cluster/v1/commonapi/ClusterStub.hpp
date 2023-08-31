/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.0.v202012010850.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_Cluster_STUB_HPP_
#define V1_COMMONAPI_Cluster_STUB_HPP_

#include <functional>
#include <sstream>




#include <v1/commonapi/Cluster.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <vector>


#include <CommonAPI/Stub.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v1 {
namespace commonapi {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service Cluster. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class ClusterStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual Cluster {
 public:


    virtual void deactivateManagedInstances() = 0;


protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */

};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for Cluster.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class ClusterStubRemoteEvent
{
public:
    virtual ~ClusterStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service Cluster to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class ClusterStub
    : public virtual CommonAPI::Stub<ClusterStubAdapter, ClusterStubRemoteEvent>
{
public:
    typedef std::function<void (int32_t _status)> updateSpeedReply_t;
    typedef std::function<void (int32_t _status)> updateRPMReply_t;
    typedef std::function<void (int32_t _status)> clickButtonsReply_t;
    typedef std::function<void (int32_t _status)> sendDetectsReply_t;

    virtual ~ClusterStub() {}
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }
    bool hasElement(const uint32_t _id) const {
        return (_id < 4);
    }
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) = 0;

    /// This is the method that will be called on remote calls on the method updateSpeed.
    virtual void updateSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _speed, updateSpeedReply_t _reply) = 0;
    /// This is the method that will be called on remote calls on the method updateRPM.
    virtual void updateRPM(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _rpm, updateRPMReply_t _reply) = 0;
    /// This is the method that will be called on remote calls on the method clickButtons.
    virtual void clickButtons(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _command, clickButtonsReply_t _reply) = 0;
    /// This is the method that will be called on remote calls on the method sendDetects.
    virtual void sendDetects(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image, sendDetectsReply_t _reply) = 0;


    using CommonAPI::Stub<ClusterStubAdapter, ClusterStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<ClusterStubAdapter, ClusterStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<ClusterStubAdapter, ClusterStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef ClusterStubRemoteEvent RemoteEventType;
    typedef Cluster StubInterface;
};

} // namespace commonapi
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_Cluster_STUB_HPP_
