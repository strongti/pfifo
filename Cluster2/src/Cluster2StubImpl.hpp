#ifndef CLUSTER2STUBIMPL_H_
#define CLUSTER2STUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Cluster2StubDefault.hpp>
#include <QObject>

class Cluster2StubImpl: public QObject, public v1_0::commonapi::Cluster2StubDefault {
    Q_OBJECT
public:
    Cluster2StubImpl();
    virtual ~Cluster2StubImpl();
    virtual void sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply);
//signals:
//    void signalSpeed(int);
//    void signalRPM(int);
//    void signalButtons(std::string);
};
#endif /* CLUSTER1STUBIMPL_H_ */
