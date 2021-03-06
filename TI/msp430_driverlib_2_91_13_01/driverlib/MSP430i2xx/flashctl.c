//*****************************************************************************
//
// flashctl.c - Driver for the flashctl Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup flashctl_api flashctl
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_FLASH__
#include "flashctl.h"

#include <assert.h>

void FlashCtl_eraseSegment ( uint8_t *flash_ptr){
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Set Erase bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + ERASE;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

    //Clear ERASE bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_performMassErase ( uint8_t *flash_ptr){
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;
    
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

    //Set MERAS bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + MERAS + ERASE;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

    //Clear MERAS bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

bool FlashCtl_performEraseCheck (uint8_t *flash_ptr,
    uint16_t numberOfBytes
    )
{
    uint16_t i;

    for (i = 0; i < numberOfBytes; i++)
    {
        //was erasing successfull?
        if ((*(flash_ptr + i)) != 0xFF){
            return ( STATUS_FAIL) ;
        }
    }
    return ( STATUS_SUCCESS) ;
}

void FlashCtl_write8 (uint8_t *data_ptr,
    uint8_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + WRT;

    while (count > 0)
    {
        //test busy
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *data_ptr++;
        count--;
    }

    //Clear WRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_write16 (uint16_t *data_ptr,
    uint16_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + WRT;

    while (count > 0)
    {
        //test busy
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *data_ptr++;
        count--;
    }

    //Clear WRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_write32 (uint32_t *data_ptr,
    uint32_t *flash_ptr,
    uint16_t count
    )
{
    //Create 16-bit pointers and assign to same values as data_ptr and flash_ptr
    uint16_t *data_ptr16 = (uint16_t*)data_ptr;
    uint16_t *flash_ptr16 = (uint16_t*)flash_ptr;
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable write mode
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + WRT;

    while (count > 0)
    {
        //Test the busy bit
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY);

        //Write to the flash
        *(uint16_t*)flash_ptr16++ = *data_ptr16++;

        //Test the busy bit
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY);

        //Write to the flash
        *(uint16_t*)flash_ptr16++ = *data_ptr16++;

        count--;
    }

    //Clear BLKWRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_fillMemory32 (uint32_t value,
    uint32_t *flash_ptr,
    uint16_t count
    )
{
    //Create a 16-bit pointer and assign to same value as flash_ptr
    uint16_t *flash_ptr16 = (uint16_t*)flash_ptr;

    //Create two 16-bit data values from value
    uint16_t value_LSW = (uint16_t)value;
    uint16_t value_MSW = (uint16_t)(value >> 16);
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable write mode
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + WRT;

    //test busy
    while (count > 0)
    {
        //Test the busy bit
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY);

        //Write least-significant 16 bits to the flash
        *(uint16_t*)flash_ptr16++ = value_LSW;

        //Test the busy bit
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY);

        //Write most-significant 16 bits to the flash
        *(uint16_t*)flash_ptr16++ = value_MSW;

        count--;
    }

    //Clear BLKWRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

uint8_t FlashCtl_getStatus (uint8_t mask
    )
{
    return ((HWREG8(FLASH_BASE + OFS_FCTL3) & mask ));
}

void FlashCtl_lockInfo(void)
{
    //Disable global interrupts while doing RMW operation on LOCKSEG bit
    uint16_t gieStatus;                         //Local variable to store GIE status
    gieStatus = __get_SR_register() & GIE;      //Store current SR register
    __disable_interrupt();                      //Disable global interrupt

    //Set the LOCKSEG bit in FCTL3.
    //Since LOCKSEG toggles when you write a 1 (and writing 0 has no effect),
    //read the register, XOR with LOCKSEG mask, mask the lower byte, and write it back.
    HWREG16(FLASH_BASE + OFS_FCTL3) =
            FWKEY + ((HWREG16(FLASH_BASE + OFS_FCTL3) ^ LOCKSEG) & 0xFF);

    //Reinstate SR register to restore global interrupt enable status
    __bis_SR_register(gieStatus);
}

void FlashCtl_unlockInfo(void)
{
    //Disable global interrupts while doing RMW operation on LOCKSEG bit
    uint16_t gieStatus;                         //Local variable to store GIE status
    gieStatus = __get_SR_register() & GIE;      //Store current SR register
    __disable_interrupt();                      //Disable global interrupt

    //Clear the LOCKSEG bit in FCTL3.
    //Since LOCKSEG toggles when you write a 1 (and writing 0 has no effect),
    //read the register, mask the lower byte, and write it back.
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + (HWREG16(FLASH_BASE + OFS_FCTL3) & 0xFF);

    //Reinstate SR register to restore global interrupt enable status
    __bis_SR_register(gieStatus);
}

uint8_t FlashCtl_setupClock(uint32_t clockTargetFreq,
    uint32_t clockSourceFreq,
    uint16_t clockSource
    )
{

    uint16_t divider;

    //Compute clock divider
    divider = (clockSourceFreq/clockTargetFreq);

    // Divider must be between 1 and 64
    if(divider < 1 || divider > 64)
    {
        return(STATUS_FAIL);                        // Divider is out of range
    }
    else
    {
        divider = divider - 1;                      // Register value is FNx = (divider - 1)
    }

    //Set the clock source and divider in FCTL2 register
    HWREG16(FLASH_BASE + OFS_FCTL2) = FWKEY + clockSource + divider;

    return(STATUS_SUCCESS);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for flashctl_api
//! @}
//
//*****************************************************************************
