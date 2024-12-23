
## Strata Engine

Rich Plugin Support 

Also support UX.

Live Colab Support,

Webassembly ready.

True Type Font editing

Engine provides a node editor that integrates with the c++ code it generates for the project

// TODO Functionality
[ ] Vocoding
[ ] Character Voice synthesis
[ ] Scene and animations prerendering (lighitng)



// TODO Libraries
[ ] Hair
[ ] Water
[ ] Smoke, steam
[ ] Face
## Formats
.splugin - plugin format , probably going to use python 
.s

## Plugin structure

|-plugin.json
|-main.cpp

In plugin.json

## Libraries
SMat - mathematics library
SG


## Dir Structure
---assets
|   |-images
|   |-fonts
|   |-materials
|   |-models
|-build 
|-docs
|-strata
    |-editor
    |- editor.cpp this is what gets called when a project is opened
    |
    |  // Various subsystems of the editor
    |
|-inc (plugin interface)
|-lib
|   |-entity
|   |-OpenAL
|   |-Scontainers
|   |-SDL2 (source)
|   |-sfwgui
|   |-stypes
|   |-vk
|   |-vk_
|   |and some other files\
|   |strata.hpp
|   |some scripts to automate download
|-mobile ( companion app)
|-nodes
|-shaders
|-tools
|-util
|-web
|-app.cpp // Contains the app entry point , includes projects select, and editor management
|-service.cpp
|-settings.json



    [ ] vk
    [ ] dx
    [ ] gles
    [ ] customRendering lib ; 


## Builing
Requires:
tinygltf 
    stbimage
    json
glm
vulkan
directx
emsdk
