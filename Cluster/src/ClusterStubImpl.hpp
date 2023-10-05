#ifndef CLUSTERSTUBIMPL_H_
#define CLUSTERSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterStubDefault.hpp>
#include <QObject>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>

extern cv::dnn::Net net1;
extern cv::dnn::Net net2;
extern std::vector<std::string> classes1;
extern std::vector<std::string> classes2;

class ClusterStubImpl: public QObject, public v1_0::commonapi::ClusterStubDefault {
    Q_OBJECT
public:
    ClusterStubImpl();
    virtual ~ClusterStubImpl();
    virtual void sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply);
    virtual void sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply);
    virtual void sendImage3(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image3, sendImage3Reply_t _reply);
    virtual void sendImage4(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image4, sendImage4Reply_t _reply);
private:
    static std::chrono::high_resolution_clock::time_point lastTimestamp1;
    static std::chrono::high_resolution_clock::time_point lastTimestamp2;
    static std::chrono::high_resolution_clock::time_point lastTimestamp3;
    static std::chrono::high_resolution_clock::time_point lastTimestamp4;
    static double totalFPS1, totalFPS2, totalFPS3, totalFPS4;
    static int frameCount1, frameCount2, frameCount3, frameCount4;
//signals:
//    void signalSpeed(int);
//    void signalRPM(int);
//    void signalButtons(std::string);
};
#endif /* CLUSTERSTUBIMPL_H_ */