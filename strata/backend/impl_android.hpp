#ifndef IMPL_ANDROID_HPP
#define IMPL_ANDROID_HPP
#ifdef IMPL_VK
#include <android/../vulkan/vulkan_android.h>
#endif
#ifdef IMPL_GL
#include <android/../gl/GL.h>
#endif
#include <impl.hpp>
#include <android/input.h>
#include <android/log.h>
// #if defined(STRATA_CAP_MOUSE) | defined(STRATA_CAP_KEY) | defined(STRATA_CAP_JOY) | defined(STRATA_CAP_CONT) | defined(STRATA_CAP_TOUCH) 
// #endif
#include <android/looper.h>
namespace impl_android{
    #ifdef STRATA_CAP_KEY
    struct KEY : impl::KEY {
        void handleMeta(AInputEvent *keyevent){
            uint32_t mstate = AKeyEvent_getMetaState(keyevent);
          if(mstate & AMETA_ALT_ON){this->alt= true;}
          else {this->alt=false;};
          if(mstate & AMETA_ALT_LEFT_ON){this->lalt= true;}
          else {this->lalt=false;};
          if(mstate & AMETA_ALT_RIGHT_ON){this->ralt= true;}
          else {this->ralt=false;};
          if(mstate & AMETA_SHIFT_ON){this->shift= true;}
          else {this->shift=false;};
          if(mstate & AMETA_SHIFT_LEFT_ON){this->lshift= true;}
          else {this->lshift=false;};
          if(mstate & AMETA_SHIFT_RIGHT_ON){this->rshift= true;}
          else {this->rshift=false;};
          if(mstate & AMETA_SYM_ON){this->sym= true;}
          else {this->sym=false;};
          if(mstate & AMETA_FUNCTION_ON){this->function= true;}
          else {this->function=false;};
          if(mstate & AMETA_CTRL_ON){this->ctrl= true;}
          else {this->ctrl=false;};
          if(mstate & AMETA_CTRL_LEFT_ON){this->lctrl= true;}
          else {this->lctrl=false;};
          if(mstate & AMETA_CTRL_RIGHT_ON){this->rctrl= true;}
          else {this->rctrl=false;};
          if(mstate & AMETA_META_ON){this->meta= true;}
          else {this->meta=false;};
          if(mstate & AMETA_META_LEFT_ON){this->lmeta= true;};
          else {this->lmeta=false;};
          if(mstate & AMETA_META_RIGHT_ON){this->rmeta= true;};
          else {this->rmeta=false;};
        //   if(mstate & AMETA_CAPS_LOCK_ON){this->caps_lock= true;}
        //   else {this->caps_lock=false;};
        //   if(mstate & AMETA_NUM_LOCK_ON){this->num_lock= true;}
        //   else {this->num_lock=false;};
        //   if(mstate & AMETA_SCROLL_LOCK_ON){this->scroll_lock= true;}
        //   else {this->scroll_lock=false;};
      
        };
        void handle(AInput_event *keyevent){
         int32_t kc = keycodeAKeyEvent_getKeyCode(keyevent);
            int action = AKeyEvent_getAction(keyevent);
    switch (action) {
        case AKEY_EVENT_ACTION_DOWN: {this->down_cb(kc);break;};
        case AKEY_EVENT_ACTION_UP:{this->up_cb(kc);break};
        case AKEY_EVENT_ACTION_MULTIPLE:{;}
        default:
         inline this->handleMeta(keyevent);     
    };

        }
        int init(){return 1;};
    };
    #endif
    #ifdef STRATA_CAP_CONT 
    struct CONT : impl::CONT{
        void handlekey(AInputeEvent* ev){
           uint32_t act = AKeyEvent_GetAction(ev);
            uint32_t key = AKeyEvent_getKeyCode(ev);
            switch(act){
                case AKEY_EVENT_ACTION_DOWN : {
                    this->down_cb(key);
                };
                case AKEY_EVENT_ACTION_UP   : {
                    this->up_cb(key);
                };
            }
        };
        void handleMotion(AInputEvent* ev){
            uint32_t act = AmotionEvent_getAction(ev);
            this->laxis_cb( cont_axis(AMotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_X,0),AMotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_Y,0)));
            this->raxis_cb( cont_axis(AMotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_Z,0),AMotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_RZ,0)));
            this->trig_cb( cont_axis(AmotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_LTRIGGER,0),AmotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_RTRIGGER,0)))
        };
    };
    #ifdef STRATA_CAP_JOY
    struct JOY : impl::JOY {
        void handlekey(AInputEvnet *ev){
            uint32_t act = AKeyEvent_GetAction(ev);
            uint32_t key = AKeyEvent_getKeyCode(ev);
            switch(act){
                case AKEY_EVENT_ACTION_DOWN : {
                    this->down_cb(key);
                };
                case AKEY_EVENT_ACTION_UP   : {
                    this->up_cb(key);
                };
            }
        };
        void handlemotion(AInputEvent *ev){
            this->axis_cb( joy_axis(AMotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_X,0),AMotionEvent_getAxisValue(ev,AMOTION_EVENT_AXIS_Y,0)));
            this->throt_cb(AMotionEvent_getAxisValue(ev,AMITION_EVNET_AXIS_Z,0));
            this->rotate_cb(AMotionEvent_getAxisValue(ev,AMITION_EVNET_AXIS_RZ,0));
        };
    };
    #endif
    #ifdef STRTA_CAP_TOUCH
    struct TOUCH : impl::TOUCH {

        handle(AInputEvent *touchev){
            uint32_t act = AMotionEvent_getAction(touchev);
            switch(act){
                case AMOTION_EVENT_ACTION_MOVE : {this->move_cb( touch_move( AMotionEvent_getX(touchev)  ,  AMotionEvent_getY(touchev)  ) ) ; return ;};
                case AMOTION_EVENT_ACTION_DOWN : {this->down_cb( touch_tap( AMotionEvent_getX(touchev)  ,  AMotionEvent_getY(touchev)) ); return ;};
                case AMOTION_EVENT_ACTION_UP   : {this->up_cb( touch_tap ( AMotionEvent_getX(touchev)  ,  AMotionEvent_getY(touchev)) ) ; return ;};
            };
            

        };
    };
    #endif

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
void closelidar(){return;}
};

#ifdef STRATA_CAP_NET
struct NET : impl::NET{

};
#endif
    #include <android/native_window.h>
#define STRATA_CAP_DISPLAY
#ifdef STRATA_CAP_DISPLAY 
struct DISPLAY : impl:DISPLAY{
    std::vector<ANativeWindow* >* natwin;
int get_width(uint pos){return ANativeWindow_getWidth((*natwin)[pos]); }
int get_height(uint pos){return ANativeWindow_getHeight((*natwin)[pos]);}
vec2 get_data(uint pos){return glm::ivec2(ANativeWindow_getWidth((*natwin)[pos]),ANativeWindow_getHeight((*natwin)[pos]));}
void handle(){return;}
void init(){return;};
void close(){delete this;};

};

    class SYS : impl::SYS {

        
#ifdef STRATA_CAPABILITY_MOUSE 
MOUSE      mouse;
    void initMouse(){return};
#endif    
#ifdef STRATA_CAPABILITY_KEY
KEY        key;
    void initKey(){return;};
#endif
#ifdef STRATA_CAPABILITY_JOY 
JOY        joy;
    void initJoy(){return;};
#endif
#ifdef STRATA_CAPABILITY_CONT 
CONT       cont;
    void initCont(){return;};
#endif
#ifdef STRATA_CAPABILITY_TOUCH 
TOUCH      touch;
    void initTouch(){return;};
#endif

#ifdef STRATA_CAPABILITY_AUDIO 
AUDIO      audio;
    void initAudio(){return;};
#endif
#ifdef STRATA_CAPABILITY_SENSOR 
SENSOR     sensor;
    void initSensor(){return;};
#endif
#ifdef STRATA_CAP_CAM
CAM cam;

#endif
#ifdef STRATA_CAP_NET
NET net;
#endif
#ifdef STRATA_CAP_DISPLAY
DISPLAY display;

#endif 
        std::vector<ANativeWindow*> wins;
        AInputQueue* evq;
        ALooper* aloop;
int(* ALooper_callbackFunc)(int fd, int events, void *data)
        int ahandle(int fd,int events,void* data){

        };
void init(){this->aloop =  ALooper_prepare() ;this->ALoooper_callbackFunc=this->ahandle; AInputQueue_attachLooper(this->evq,this->aloop,this->ALooper_callbackFunc ,)};

void initDisplay(){this->display.natwin=&(this->wins);this->display.init();};


        int handle(){
            AInputEvent *outev;
            AInputQueue_getEvent(this->evq,&outev);
            int ty = AInputEvent_getType(outev);
            switch(ty){
                case AINPUT_EVENT_TYPE_KEY :  {
                    #ifdef STRATA_CAP_CONT
                    if((ty& AINPUT_SOURCE_GAMEPAD) == AINPUT_SOURCE_GAMEPAD){this->cont.handlekey(outev);return impl::SYS::dev::Cont;};
                    #endif
                    #ifdef STRATA_CAP_KEY
                    if((ty& AINPUT_SOURCE_KEYBOARD) == AINPUT_SOURCE_KEYBOARD){this->key.handle(outev);return impl::SYS::dev::Key;;};
                    #endif
                    #ifdef STRATA_CAP_JOY
                    if((ty & AINPUT_SOURCE_JOYSTICK) ==AINPUT_SOURCE_JOYSTICK ){this->joy.handlekey(outev);return impl::SYS::dev::Joy;}
                    #endif
                case AINPUT_EVENT_TYPE_MOTION : {
                    #ifdef STRATA_CAP_TOUCH
                    if( ty & AINPUT_SOURCE_TOUCHSCREEN ) == AINPUT_SOURCE_TOUCHSCREEN){this->touch.handle(outev);return impl::SYS::dev::Touch;;};
                    #endif
                    #ifdef STRATA_CAP_CONT
                    if((ty& AINPUT_SOURCE_GAMEPAD) == AINPUT_SOURCE_GAMEPAD){this->cont.handlemotion(outev);return impl::SYS::dev::Cont;};
                    #endif
                    #ifdef STRATA_CAP_JOY
                    if( ty & AINPUT_SOURCE_JOYSTICK ) == AINPUT_SOURCE_JOYSTICK){this->joy.handlemotion(outev);return impl::SYS::dev::Joy;};
                    #endif
                // case AINPUT_EVENT_TYPE_FOCUS: {}
                // case AINPUT_EVENT_TYPE_CAPTURE : {this->}
                // case AINPUT_EVENT_TYPE_DRAG : {}
                // case AINPUT_EVENT_TYPE_TOUCH_MODE : {}
                default: {}
            };
        };
        void createWin(){
            ANativeWindow* anatw;
            ANativeWindow_acquire(anatw);
            this->wins.push_back(anatw);
        };
        
    };
};

 #endif