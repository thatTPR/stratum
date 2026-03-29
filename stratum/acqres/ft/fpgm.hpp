typedef struct {
    uint8* instr;
}fpgm;
ACQRES(fpgm){
    arr(f.instr,_length);
}
USE_ACQRES(fpgm)