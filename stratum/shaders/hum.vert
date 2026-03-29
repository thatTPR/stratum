#version 450
struct humanBonesPos {


    vec4 eyes[2];
    float jaw;
    vec3 head ; 

    vec3 coreUp;
    vec3 coreUp2 ;

    vec3 shoulder[2];
    vec3 upArm[2];
    vec2 foreArm[2];
    vec4 carpals[2] ; 
    vec2 thumbsProximal[2];
    float distal[10]; 
    vec3 phalang[10];

    vec3 waist;
    vec4 upLeg[2] ;
    float foreLeg[2];
    vec4 tarsal[2];
    vec4 metaTarsal[10]
    vec2 phalanx[10];

    vec3 loca ;


    float height; 
    float shoulder;
    float bust;
    float waist;
    float clear ;

    float BMI ;
    float jawH; 
    float jawW;
    float eyePart;
    float eyeH
    float browPart;
    float browProm;
    float lips;
    float lipsSmile;
    float noseW;
    float noseH;
    float noseProm;

};  

/*
struct humanBone {


    vec4 eyes[2];
    float jaw;
    vec3 coreUp;
    vec3 coreUp2 ;
    vec3 shoulder[2];
    vec3 head ; 
    vec3 upArm[2];
    vec2 foreArm[2];
    vec4 carpals[2] ; 
    vec4 metaCarpals[10];
    vec2 thumbsProximal[2];
    float distal[10]; 
    vec3 phalang[8];

    vec4 upLeg[2] ;
    float foreLeg[2];
    vec4 tarsal[2];
    vec4 metaTarsal[10]
    vec2 phalanx[10];
};  
*/

struct 

layout (location=0 , std=430) buffer struct humanBonesPos huRig  ;
layout (location=1 , std=430) 

layout (location=0) out vec3 position ;


void main(){

};