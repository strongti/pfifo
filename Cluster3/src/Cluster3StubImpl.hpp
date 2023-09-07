#ifndef CLUSTER3STUBIMPL_H_
#define CLUSTER3STUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Cluster3StubDefault.hpp>
#include <QObject>

class Cluster3StubImpl: public QObject, public v1_0::commonapi::Cluster3StubDefault {
    Q_OBJECT
public:
    Cluster3StubImpl();
    virtual ~Cluster3StubImpl();
    virtual void sendImage3(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image3, sendImage3Reply_t _reply);
//signals:
//    void signalSpeed(int);
//    void signalRPM(int);
//    void signalButtons(std::string);
};
#endif /* CLUSTER1STUBIMPL_H_ */
