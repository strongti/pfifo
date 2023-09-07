#ifndef CLUSTER1STUBIMPL_H_
#define CLUSTER1STUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Cluster1StubDefault.hpp>
#include <QObject>

class Cluster1StubImpl: public QObject, public v1_0::commonapi::Cluster1StubDefault {
    Q_OBJECT
public:
    Cluster1StubImpl();
    virtual ~Cluster1StubImpl();
    virtual void sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply);
//signals:
//    void signalSpeed(int);
//    void signalRPM(int);
//    void signalButtons(std::string);
};
#endif /* CLUSTER1STUBIMPL_H_ */
