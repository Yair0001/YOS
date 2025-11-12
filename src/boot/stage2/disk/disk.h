#ifndef DISK_H
#define DISK_H

// currently im using Hard disk, maybe implementations will change in the future
// every function needs to remove protected mode so i can use BIOS interrupts

#include <stdbool.h>

typedef unsigned int uint;

typedef enum {
    ERR_ADDR_UNAVAILABLE        = 0x01, // Addressed function or unit not available
    ERR_ADDR_NOT_FOUND          = 0x02, // Address not found
    ERR_SECTOR_NOT_FOUND        = 0x04, // Sector not found
    ERR_CONTROLLER_RESET        = 0x05, // Error on controller reset
    ERR_CONTROLLER_INIT         = 0x07, // Error during controller initialization
    ERR_DMA_SEGMENT_BORDER      = 0x09, // DMA transmission error: Segment border exceeded
    ERR_DEFECTIVE_SECTOR        = 0x0A, // Defective sector
    ERR_READ_ERROR              = 0x10, // Read error
    ERR_READ_ECC_CORRECTED      = 0x11, // Read error corrected by ECC
    ERR_CONTROLLER_DEFECT       = 0x20, // Controller defect
    ERR_SEARCH_FAILED           = 0x40, // Search operation failed
    ERR_TIMEOUT_NOT_RESPONDING  = 0x80, // Time out, unit not responding
    ERR_UNIT_NOT_READY          = 0xAA, // Unit not ready
    ERR_WRITE_ERROR             = 0xCC  // Write error
} DiskErrorCode;

typedef enum {
    HDD = 0x80
    // if ill need more then ill add, right now i only support hdd
} DiskNum;

typedef struct {
    uint           carryFlag : 1;
    uint           numSectRead;
    DiskErrorCode *err;
} readDiskOut;

readDiskOut readDiskCHS(uint addrToLoad, uint numSectToRead, uint trackNumber, uint sectorNumber, DiskNum diskNum, bool diskSideNum, uint bufSegAddr);

#endif