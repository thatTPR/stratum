typedef struct {
uint16   version;
uint16   numRecords;
uint32   sizeDeviceRecord;
DeviceRecord*   records;//[numRecords]
}HdmxHeader;
ACQRES(HdmxHeader){
one(version);
one(numRecords);
one(sizeDeviceRecord);
arr(records, numRecords);
 };
USE_ACQRES(HdmxHeader)

typedef struct {
uint8   pixelSize;
uint8   maxWidth;
uint8*   widths;//[numGlyphs]
}DeviceRecord;
ACQRES(DeviceRecord){
one(pixelSize);
one(maxWidth);
arr(widths, numGlyphs);
 };
USE_ACQRES(DeviceRecord)

