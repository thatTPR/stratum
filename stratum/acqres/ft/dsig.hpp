#ifndef FTDSIG_HPP
#define FTDSIG_HPP

typedef struct {
uint16   reserved1;
uint16   reserved2;
uint32   signatureLength;
uint8*   signature;//[signatureLength]
}SignatureBlockFormat1;
ACQRES(SignatureBlockFormat1){
one((f.reserved1));
one((f.reserved2));
one((f.signatureLength));
arr(f.signature, f.signatureLength);
 };
USE_ACQRES(SignatureBlockFormat1)


typedef struct {
uint32   format;
uint32   length;
Offset32   signatureBlockOffset;
// SignatureBlockFormat1;
SignatureBlockFormat1 sbf;
}SignatureRecord;

typedef struct {
uint32   version;
uint16   numSignatures;
uint16   flags;
SignatureRecord*   signatureRecords;//[numSignatures]
}DSIG;
ACQRES(DSIG){
    set((f.version));
one((f.version));
one((f.numSignatures));
one((f.flags));
if(!f.signatureRecords){f.signatureRecords=new SignatureRecord[f.numSignatures];};
for(int i =0; i<f.numSigantures){
    one((f.signatureRecords[i].format));
    one((f.signatureRecords[i].length));
    one((f.signatureRecords[i].signatureBlockOffset));
    offone((f.signatureRecords[i].sbf),(f.signatureRecords[i].signatureBlockOffset));
}
};
USE_ACQRES(DSIG)
#endif