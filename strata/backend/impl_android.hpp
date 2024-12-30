#include <impl.hpp>
#include <android/log.h>
#include <android/input.h>
namespace impl_android{
    struct MOUSE : impl::MOUSE {
        glm::vec2 Pos(){};
        void init();
    };
    struct KEY : impl::KEY {

    };
    struct JOY : impl::JOY {

    };
    struct CONT : IMPL::CONT {

    };
    struct TOUCH : impl::TOUCH {
        handle(){
            glm::vec2<>getTouch
        };
    };

#ifdef STRATA_CAP_AUDIO
#include <aaudio/AAudio.h>
#include <acqres/wav.hpp>
struct AUDIO : impl::AUDIO {
    const bool direction=true;
AAudioStreamBuilder* builder;
    std::vector<AAudioStream*> stream;
uint GetNum(){this->num = 1;return 1;};
virtual void getCaps()
    void open(uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz,uint index){this->pos++;
        if(AAudiostreamBuilder_createStreamBuilder(&(this->builder)) != AAUDIO_OK){LOGE("Failed to open audio stream builder");return;};
        AAudioStreamBuilder_setChannelCount(this->builder,channels);
        AAudioStreamBuilder_setSampleRate( this->builder, hz);
 AAudioStreamBuilder_delete(this->builder);
         AAudioStreamBuilder_openStream(this->builder,this->stream[index]);
          if (AAudioStream_requestStart(this->stream[index]) != AAUDIO_OK) {LOGE("Failed to start stream");    };

 };    
 uint open(){uint p = this->stream.size();this->stream.push_back(new (AAudioStream*));return p};
 void close(uint index=0){AAudioStream_close(this->stream[index]); AAudioStreamBuilder_delete(this->builder); this->stream.erase(index);};
 void _play_wav(wavh header,std::vector<uint8_t> data){ uint poss=this->open();
    AAudioStreamBuilder_setDirection(this->builder, AAUDIO_DIRECTION_OUTPUT);
    AAudioStreamBuilder_setSampleRate(this->builder, header.sampleRate);
    AAudioStreamBuilder_setChannelCount(this->builder, header.numChannels);
    AAudioStreamBuilder_setFormat(this->builder, AAUDIO_FORMAT_PCM_I16); // Assuming PCM 16-bit
    AAudioStreamBuilder_setDataCallback(this->builder, audioDataCallback, &pcmData);
    // Open the stream
    if (AAudioStreamBuilder_openStream(builder, this->stream[poss]) != AAUDIO_OK) {
        LOGE("Failed to open AAudio stream");
        AAudioStreamBuilder_delete(builder);
        return;
    };

    // Start the stream
    if (AAudioStream_requestStart(stream) != AAUDIO_OK) {
        LOGE("Failed to start AAudio stream");
    };

    // Wait for playback to finish
    while (AAudioStream_getState(stream) == AAUDIO_STREAM_STATE_STARTED) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    this->close(poss);
    delete poss;
 };


};
#endif

#if defined(STRATA_CAP_SENSOR) || defined(STRATA_CAP_LOCATION) 
#include <android/sensor.h>
    struct SENSOR : impl::SENSOR {
ASensorManager sensorManager;
 ALooper* looper ;
 ASensorEventQueue* evqueue;
 ASensor* accel;
 ASensor* magnet;
 ASensor* magnetrotation;
 ASensor* temp;
 ASensor* gyro;
 ASensor* light;
 ASensor* gravity;
 ASensor* proximity;
 ASensor* baro;
 ASensor* humid;
 ASensor* lidar;
 ASensor* motion;
 ASensor* Stationary;
 ASensor* rotation;
 ASensor* gamerotation;
 


 // Pollrate 1000 000 microseconds
bool inittemp(uint pollrateus=1000000){ASensorManager_getDefualtSensor(sensorManager,ASENSOR_TYPE_AMBIENT_TEMPERATURE);if(ASensorEventQueue_enableSensor(evqueue, temp) < 0) {LOGE("Failed to enable temp");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->temp, pollrateus);        return true;};
bool initgyro(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_GYROSCOPE); if(ASensorEventQueue_enableSensor(evqueue, gyro) < 0) {LOGE("Failed to enable gyro");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->gyro, pollrateus);        return true;};
bool initlight(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_LIGHT); if(ASensorEventQueue_enableSensor(evqueue, light) < 0) {LOGE("Failed to enable light");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->light, pollrateus);        return true;};
bool initgravity(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_GRAVITY); if(ASensorEventQueue_enableSensor(evqueue, gravity) < 0) {LOGE("Failed to enable gravity");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->gravity, pollrateus);        return true;};
bool initproximity(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_PROXIMITY); if(ASensorEventQueue_enableSensor(evqueue, proximity) < 0) {LOGE("Failed to enable proximity");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->proximity, pollrateus);        return true;};
bool initaccel(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_ACCELEROMETER); if(ASensorEventQueue_enableSensor(evqueue, accel) < 0) {LOGE("Failed to enable accel");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->accel, pollrateus);        return true;};
bool initmagnetrotoation(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_MAGNETIC_FIELD); if(ASensorEventQueue_enableSensor(evqueue, this->magnetrotation) < 0) {LOGE("Failed to enable accel");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->magnetrotation, pollrateus);        return true;};
bool initmagnet(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_MAGNETIC_FIELD); if(ASensorEventQueue_enableSensor(evqueue, mag) < 0) {LOGE("Failed to enable mag");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->mag, pollrateus);        return true;};
bool initbaro(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_PRESSURE); if(ASensorEventQueue_enableSensor(evqueue, baro) < 0) {LOGE("Failed to enable baro");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->baro, pollrateus);        return true;};
bool inithumid(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_RELATIVE_HUMIDITY); if(ASensorEventQueue_enableSensor(evqueue, humid) < 0) {LOGE("Failed to enable humid");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->humid, pollrateus);        return true;};
bool initmotion(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_MOTION_DETECT); if(ASensorEventQueue_enableSensor(evqueue, motion) < 0) {LOGE("Failed to enable motion");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->motion, pollrateus);        return true;};
bool initstationary(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_STATIONARY_DETECT); if(ASensorEventQueue_enableSensor(evqueue, motion) < 0) {LOGE("Failed to enable motion");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->motion, pollrateus);        return true;};
bool initrotation(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_ROTATION); if(ASensorEventQueue_enableSensor(evqueue, rotation) < 0) {LOGE("Failed to enable rotation");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->rotation, pollrateus);        return true;};
bool initgamerotation(uint pollrateus=1000000){ASensorManager_getDefaultSensor(sensorManager,ASENSOR_TYPE_GAME_ROTATION); if(ASensorEventQueue_enableSensor(evqueue, rotation) < 0) {LOGE("Failed to enable rotation");return false;};ASensorEventQueue_setEventRate(this->evqueue, this->gamerotation, pollrateus);        return true;};

void closegyro(){ASensorEventQueue_disableSensor(evqueue,this->gyro );};
void closelight(){ASensorEventQueue_disableSensor(evqueue,this->light );};
void closegravity(){ASensorEventQueue_disableSensor(evqueue,this->gravity );};
void closeproximity(){ASensorEventQueue_disableSensor(evqueue,this->proximity);};
void closeaccel(){ASensorEventQueue_disableSensor(evqueue,this->accel );};
void closemag(){ASensorEventQueue_disableSensor(evqueue,this->mag );};
void closebaro(){ASensorEventQueue_disableSensor(evqueue,this->baro );};
void closehumid(){ASensorEventQueue_disableSensor(evqueue,this->humid );};
void closemotion(){ASensorEventQueue_disableSensor(evqueue,this->motion );};
void closestationary(){ASensorEventQueue_disableSensor(evqueue,this->stationary );};
void closerotation(){ASensorEventQueue_disableSensor(evqueue,this->rotation );};
void closegamerotation(){ASensorEventQueue_disableSensor(evqueue,this->gamerotation );};

temp        gettemp(){};
gyro        getgyro(){};
loc         getloc(){};
light       getlight(){};
gravity     getgravity(){};
proximity   getproximity(){};
accel       getaccel(){};
mag         getmag(){};
baro        getbaro(){};
humid       gethumid(){};
pos         getpos(){};
lidar       getlidar(){};

rotation    getrotation(){};
rotation    getgamerotation(){};

void get(){
 ASensorEvent event;
 while (ALooper_pollAll(0, nullptr, nullptr, nullptr) >= 0) {
        if (ASensorEventQueue_getEvents(evqueue, &event, 1) > 0) {
            switch (event.type){
  case ASENSOR_TYPE_ACCELEROMETER :{this->last_accel=event.acceleration; break;}; 
  case ASENSOR_TYPE_MAGNETIC_FIELD :{this->last_magnet=event.magnetic; break;}; 
  case ASENSOR_TYPE_GYROSCOPE :{this->last_gyro=event.gyro; break;}; 
  case ASENSOR_TYPE_LIGHT :{this->last_light=event.light; break;}; 
  case ASENSOR_TYPE_PRESSURE :{this->last_pressure=event.pressure; break;}; 
  case ASENSOR_TYPE_PROXIMITY :{this->last_proximity=event.distance; break;}; 
  case ASENSOR_TYPE_GRAVITY :{this->last_gravity=glm::vec3(event.data[0],event.data[1],event.data[2]); break;}; 
//   case ASENSOR_TYPE_LINEAR_ACCELERATION :{}; 
  case ASENSOR_TYPE_ROTATION_VECTOR :{this->last_rotation=glm::vec3(event.data[0],event.data[1],event.data[2]);break;}; 
  case ASENSOR_TYPE_RELATIVE_HUMIDITY :{this->last_humidity=event.relative_humidtybreak;}; 
  case ASENSOR_TYPE_AMBIENT_TEMPERATURE :{this->last_temperature=event.temperature;break;}; 
//   case ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED :{}; 
  case ASENSOR_TYPE_GAME_ROTATION_VECTOR :{this->last_game_rotation=glm::vec3(event.data[0],event.data[1],event.data[2]);break;}; 
//   case ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED :{}; 
//   case ASENSOR_TYPE_SIGNIFICANT_MOTION :{}; 
//   case ASENSOR_TYPE_STEP_DETECTOR :{}; 
//   case ASENSOR_TYPE_STEP_COUNTER :{}; 
//   case ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR :{}; 
//   case ASENSOR_TYPE_HEART_RATE :{}; 
//   case ASENSOR_TYPE_POSE_6DOF :{}; 
 
//   case ASENSOR_TYPE_HEART_BEAT :{}; 
//   case ASENSOR_TYPE_DYNAMIC_SENSOR_META :{}; 
//   case ASENSOR_TYPE_ADDITIONAL_INFO :{}; 
//   case ASENSOR_TYPE_LOW_LATENCY_OFFBODY_DETECT :{}; 
//   case ASENSOR_TYPE_ACCELEROMETER_UNCALIBRATED :{}; 
//   case ASENSOR_TYPE_HINGE_ANGLE :{}; 
//   case ASENSOR_TYPE_HEAD_TRACKER :{}; 
//   case ASENSOR_TYPE_ACCELEROMETER_LIMITED_AXES :{}; 
//   case ASENSOR_TYPE_GYROSCOPE_LIMITED_AXES :{}; 
//   case ASENSOR_TYPE_ACCELEROMETER_LIMITED_AXES_UNCALIBRATED :{}; 
//   case ASENSOR_TYPE_GYROSCOPE_LIMITED_AXES_UNCALIBRATED :{}; 
  case ASENSOR_TYPE_HEADING :{this->last_heading=event.heading;break;};   
  };
        };

}
void init(){this->sensorManager=ASensorManager_getInstance();this->looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);sensorEventQueue = ASensorManager_createEventQueue(this->sensorManager, this->looper, 0, sensorCallback, nullptr);if (!sensorEventQueue) {LOGE("Failed to create sensor event queue");return;};};
void cleanup(){ASensorManager_destroyEventQueue(sensorManager, evqueue);};
};


#ifdef STRATA_CAP_CAM
#include <camera/NdkCameraManager.h>
#include <media/NdkImageReader.h>

struct CAM : impl::CAM{


#ifdef STRATA_CAP_LOCATION
bool initloc(){return;};
void closeloc(){;}
#endif


ACameraManager* cameraManager;
ACaptureSessionOutputContainer* outputContainer;
void initcam() {
     this->cameraManager= ACameraManager_create();
    ACameraIdList* cameraIdList;
    ACameraManager_getCameraIdList(cameraManager, &cameraIdList);
    if (cameraIdList->numCameras > 0) {
        LOGI("Found %d cameras", cameraIdList->numCameras);
        const char* cameraId = cameraIdList->cameraIds[0];
        ACameraDevice* cameraDevice;
        ACameraManager_openCamera(cameraManager, cameraId, nullptr, &cameraDevice);
        ACaptureSessionOutputContainer_create(&(this->outputContainer));
        // Clean up
    } else {
        LOGI("No cameras available");
    }

};


void closecam(){ ACaptureSessionOutputContainer_free(this->outputContainer);   ACameraManager_delete(this->cameraManager);};
bool initlidar(){return;};
void closelidar(){;}
};

    struct NET : impl::NET
    #include <android/native_window.h>
    class SYS : impl::SYS {

        
#ifdef STRATA_CAPABILITY_MOUSE 
MOUSE      mouse;
    void initMouse();
#endif    
#ifdef STRATA_CAPABILITY_KEY
KEY        key;
    void initKey();
#endif
#ifdef STRATA_CAPABILITY_JOY 
JOY        joy;
    void initJoy();
#endif
#ifdef STRATA_CAPABILITY_CONT 
CONT       cont;
    void initCont();
#endif
#ifdef STRATA_CAPABILITY_TOUCH 
TOUCH      touch;
    void initTouch();
#endif
// #ifdef STRATA_CAPABILITY_DISPLAY 
// DISPLAY    display;
//     void initDisplay();
// #endif
#ifdef STRATA_CAPABILITY_AUDIO 
AUDIO      audio;
    void initAudio();
#endif
#ifdef STRATA_CAPABILITY_SENSOR 
SENSOR     sensor;
    void initSensor();
#endif
#ifdef STRATA_CAP_CAM
CAM cam;
#endif
#ifdef STRATA_CAP_NET
NET net;
#endif
        std::vector<ANativeWindow*> wins;
        void handle();
        void createWin(){
            ANativeWindow* anatw;
            ANativeWindow_acquire(anatw);
            this->wins.push_back(anatw);
        };
        void 
    };
};

