typedef struct {
uint32   version;
uint16   numSignatures;
uint16   flags;
SignatureRecord*   signatureRecords;//[numSignatures]
}DsigHeader;
ACQRES(DsigHeader){
one(version);
one(numSignatures);
one(flags);
arr(signatureRecords, numSignatures);
 };
USE_ACQRES(DsigHeader)

typedef struct {
uint32   format;
uint32   length;
Offset32   signatureBlockOffset;
}SignatureRecord;
typedef struct {
uint16   reserved1;
uint16   reserved2;
uint32   signatureLength;
uint8*   signature;//[signatureLength]
}Signature/* Block Format 1*/;
ACQRES(Signature/* Block Format 1*/){
one(reserved1);
one(reserved2);
one(signatureLength);
arr(signature, signatureLength);
 };
USE_ACQRES(Signature/* Block Format 1*/)

