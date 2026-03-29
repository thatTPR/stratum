#ifndef HDMX_HPP
#define HFMX_HPP


typedef struct {
uint8   pixelSize;
uint8   maxWidth;
uint8*   widths;//[numGlyphs]
}DeviceRecord;
ACQRES(DeviceRecord){
one((f.pixelSize));
one((f.maxWidth));
arr(f.widths, f.numGlyphs);
 };
USE_ACQRES(DeviceRecord)

typedef struct {
uint16   version;
uint16   numRecords;
uint32   sizeDeviceRecord;
DeviceRecord*   records;//[numRecords]
}hdmx;
ACQRES(hdmx){
one((f.version));
one((f.numRecords));
one((f.sizeDeviceRecord));
arr(f.records, f.numRecords);
 };
USE_ACQRES(hdmx)
#endif