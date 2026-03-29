// ## Usage Note
evun evn
SYS sys;


while(sys.evmain[evn]) // poll in queue
    evmain.resolve(evn) // Calls callbacks which can be set;

while(sys.run();) // Goes throug all subsystems and sets lasts
while(sys.parallel();) // same as run but does so in parallel;

    sys.process() ; // same as run but also calls callback 
    sys.para_process() // parallel process;
    