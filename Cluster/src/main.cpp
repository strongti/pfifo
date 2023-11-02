#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>
#include <QMetaType>
#include <string>
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "ClusterStubImpl.hpp"
#include <fstream>

// //
// // TensorRT
// #include "config.h"
// #include "model.h"
// #include "cuda_utils.h"
// #include "logging.h"
// #include "utils.h"
// #include "preprocess.h"
// #include "postprocess.h"
#include "yolov7/mains.h"
//

using namespace nvinfer1;
using namespace std;
Q_DECLARE_METATYPE(std::string)



std::mutex mtx;
std::condition_variable condVar;
bool exitFlag = false;

cudaStream_t stream1;
IExecutionContext* context1;
float* device_buffers1[2];
float* output_buffer_host1 = nullptr;

cudaStream_t stream2;
IExecutionContext* context2;
float* device_buffers2[2];
float* output_buffer_host2 = nullptr;


void waitForExitSignal() {
    std::unique_lock<std::mutex> lock(mtx);
    condVar.wait(lock, [] { return exitFlag; });
}

int main(int argc, char *argv[]) {
    qRegisterMetaType<std::string>();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<ClusterStubImpl> myService = std::make_shared<ClusterStubImpl>();
    runtime->registerService("local", "cluster_service", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    //
    std::string model_name_1 = "yolov7.engine";
    std::string model_name_2 = "yolov7.engine";
    IRuntime* runtimes1 = nullptr;
    ICudaEngine* engine1 = nullptr;
    IRuntime* runtimes2 = nullptr;
    ICudaEngine* engine2 = nullptr;
    deserialize_engine(model_name_1, &runtimes1, &engine1, &context1);
    deserialize_engine(model_name_2, &runtimes2, &engine2, &context2);     
    CUDA_CHECK(cudaStreamCreate(&stream1));
    CUDA_CHECK(cudaStreamCreate(&stream2));        

    //
    cuda_preprocess_init(kMaxInputImageSize);

    prepare_buffer(engine1, &device_buffers1[0], &device_buffers1[1], &output_buffer_host1);
    prepare_buffer(engine2, &device_buffers2[0], &device_buffers2[1], &output_buffer_host2);



    while(true){
        
    }

    // GPU 메모리 해제
    // Release stream and buffers
    cudaStreamDestroy(stream1);
    cudaStreamDestroy(stream2);
    CUDA_CHECK(cudaFree(device_buffers1[0]));
    CUDA_CHECK(cudaFree(device_buffers1[1]));
    CUDA_CHECK(cudaFree(device_buffers2[0]));
    CUDA_CHECK(cudaFree(device_buffers2[1]));
    delete[] output_buffer_host1;
    delete[] output_buffer_host2;
    cuda_preprocess_destroy();

    // Destroy the engine
    delete context1;
    delete engine1;
    delete runtimes1;
    delete context2;
    delete engine2;
    delete runtimes2;
    
    return 0;
}