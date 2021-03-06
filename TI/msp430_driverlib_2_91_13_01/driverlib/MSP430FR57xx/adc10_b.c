//*****************************************************************************
//
// adc10_b.c - Driver for the adc10_b Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup adc10_b_api adc10_b
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ADC10_B__
#include "adc10_b.h"

#include <assert.h>

bool ADC10_B_init (uint16_t baseAddress,
    uint16_t sampleHoldSignalSourceSelect,
    uint8_t clockSourceSelect,
    uint16_t clockSourceDivider)
{
    assert(sampleHoldSignalSourceSelect <= ADC10_B_SAMPLEHOLDSOURCE_3);
    assert(clockSourceSelect <= ADC10_B_CLOCKSOURCE_SMCLK);
    assert(clockSourceDivider <= ADC10_B_CLOCKDIVIDER_512);

    bool retVal = STATUS_SUCCESS;

    //Turn OFF ADC10B Module & Clear Interrupt Registers
    HWREG16(baseAddress + OFS_ADC10CTL0) &= ~(ADC10ON + ADC10ENC + ADC10SC);
    HWREG16(baseAddress + OFS_ADC10IE)   &= 0x0000; //Reset ALL interrupt enables
    HWREG16(baseAddress + OFS_ADC10IFG)  &= 0x0000; //Reset ALL interrupt flags

    //Set ADC10B Control 1
    HWREG16(baseAddress + OFS_ADC10CTL1) =
        sampleHoldSignalSourceSelect //Setup the Sample-and-Hold Source
        + (clockSourceDivider & ADC10DIV_7) //Set Clock Divider
        + clockSourceSelect; //Setup Clock Source

    //Set ADC10B Control 2
    HWREG16(baseAddress + OFS_ADC10CTL2) =
        (clockSourceDivider & (ADC10PDIV_1 | ADC10PDIV_2)) //Set Clock Pre-Divider
        + ADC10RES; //Default resolution to 10-bits

    return ( retVal) ;
}

void ADC10_B_enable (uint16_t baseAddress)
{
    //Reset the ADC10ON bit to enable the ADC10B Module
    HWREG16(baseAddress + OFS_ADC10CTL0) |= ADC10ON;
}

void ADC10_B_disable (uint16_t baseAddress)
{
    //Set the ADC10ON bit to disable the ADC10B Module
    HWREG16(baseAddress + OFS_ADC10CTL0) &= ~ADC10ON;
}

void ADC10_B_setupSamplingTimer (uint16_t baseAddress,
    uint16_t clockCycleHoldCount,
    uint16_t multipleSamplesEnabled)
{
    //Make sure the ENC bit is cleared before setting up sampling pulse mode
    assert( !(HWREG16(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    assert(clockCycleHoldCount <= ADC10_B_CYCLEHOLD_1024_CYCLES);

    HWREG16(baseAddress + OFS_ADC10CTL1) |= ADC10SHP;

    //Reset and Set CB Control 0 Bits
    HWREG16(baseAddress + OFS_ADC10CTL0) &= ~(ADC10SHT_15 + ADC10MSC);
    HWREG16(baseAddress + OFS_ADC10CTL0) |= clockCycleHoldCount
                                          + multipleSamplesEnabled;
}

void ADC10_B_disableSamplingTimer (uint16_t baseAddress)
{
    //Make sure the ENC bit is cleared before disabling sampling pulse mode
    assert( ~(HWREG16(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    HWREG16(baseAddress + OFS_ADC10CTL1) &= ~(ADC10SHP);
}

void ADC10_B_configureMemory(uint16_t baseAddress,
    uint8_t inputSourceSelect,
    uint8_t positiveRefVoltageSourceSelect,
    uint8_t negativeRefVoltageSourceSelect)
{
    //Make sure the ENC bit is cleared before configuring a Memory Buffer Control
    assert( !(HWREG16(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    if(!(HWREG16(baseAddress + OFS_ADC10CTL0) & ADC10ENC))
    {
        assert(inputSourceSelect <= ADC10_B_INPUT_A15);
        assert(positiveRefVoltageSourceSelect <= ADC10_B_VREFPOS_INT);
        assert(negativeRefVoltageSourceSelect <= ADC10_B_VREFNEG_EXT);

        //Reset and Set the Memory Buffer Control Bits
        HWREG8(baseAddress + OFS_ADC10MCTL0) = inputSourceSelect
                                               + positiveRefVoltageSourceSelect +
                                               negativeRefVoltageSourceSelect;
    }
}

void ADC10_B_enableInterrupt (uint16_t baseAddress,
    uint8_t interruptMask)
{
    HWREG16(baseAddress + OFS_ADC10IE) |= interruptMask;
}

void ADC10_B_disableInterrupt (uint16_t baseAddress,
    uint8_t interruptMask)
{
    HWREG16(baseAddress + OFS_ADC10IE) &= ~(interruptMask);
}

void ADC10_B_clearInterrupt (uint16_t baseAddress,
    uint8_t interruptFlagMask)
{
    HWREG16(baseAddress + OFS_ADC10IFG) &= ~(interruptFlagMask);
}

uint8_t ADC10_B_getInterruptStatus (uint16_t baseAddress,
    uint8_t interruptFlagMask)
{
    return ( HWREG16(baseAddress + OFS_ADC10IFG) & interruptFlagMask );
}

void ADC10_B_startConversion (uint16_t baseAddress,
    uint8_t conversionSequenceModeSelect)
{
    assert(conversionSequenceModeSelect <= ADC10_B_REPEATED_SEQOFCHANNELS);

    //Reset the ENC bit to set the conversion mode sequence
    HWREG16(baseAddress + OFS_ADC10CTL0) &= ~(ADC10ENC);

    HWREG16(baseAddress + OFS_ADC10CTL1) |= conversionSequenceModeSelect;
    HWREG16(baseAddress + OFS_ADC10CTL0) |= ADC10ENC + ADC10SC;
}

void ADC10_B_disableConversions (uint16_t baseAddress, bool preempt)
{
    if (ADC10_B_PREEMPTCONVERSION == preempt){
        HWREG16(baseAddress + OFS_ADC10CTL1) &= ~(ADC10CONSEQ_3);
        //Reset conversion sequence mode to single-channel, single-conversion
    } else if ( ~(HWREG16(baseAddress + OFS_ADC10CTL1) & ADC10CONSEQ_3) ){
        //To prevent preemoption of a single-channel, single-conversion we must
        //wait for the ADC core to finish the conversion.
        while (HWREG16(baseAddress + OFS_ADC10CTL1) & ADC10BUSY) ;
    }

    HWREG16(baseAddress + OFS_ADC10CTL0) &= ~(ADC10ENC);
}

uint16_t ADC10_B_getResults (uint16_t baseAddress)
{
    return ( HWREG16(baseAddress + OFS_ADC10MEM0) );
}

void ADC10_B_setResolution (uint16_t baseAddress,
    uint8_t resolutionSelect)
{
    assert(resolutionSelect <= ADC10_B_RESOLUTION_10BIT);

    HWREG16(baseAddress + OFS_ADC10CTL2) &= ~(ADC10RES);
    HWREG16(baseAddress + OFS_ADC10CTL2) |= resolutionSelect;
}

void ADC10_B_setSampleHoldSignalInversion (uint16_t baseAddress,
    uint16_t invertedSignal)
{
    //Make sure the ENC bit is cleared before using this function
    assert( !(HWREG16(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    HWREG16(baseAddress + OFS_ADC10CTL1) &= ~(ADC10ISSH);
    HWREG16(baseAddress + OFS_ADC10CTL1) |= invertedSignal;
}

void ADC10_B_setDataReadBackFormat (uint16_t baseAddress,
    uint16_t readBackFormat)
{
    assert(readBackFormat <= ADC10_B_SIGNED_2SCOMPLEMENT);

    HWREG16(baseAddress + OFS_ADC10CTL2) &= ~(ADC10DF);
    HWREG16(baseAddress + OFS_ADC10CTL2) |= readBackFormat;
}

void ADC10_B_enableReferenceBurst (uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_ADC10CTL2) |= ADC10REFBURST;
}

void ADC10_B_disableReferenceBurst (uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_ADC10CTL2) &= ~(ADC10REFBURST);
}

void ADC10_B_setReferenceBufferSamplingRate (uint16_t baseAddress,
    uint16_t samplingRateSelect)
{
    assert(samplingRateSelect <= ADC10_B_MAXSAMPLINGRATE_50KSPS);

    HWREG16(baseAddress + OFS_ADC10CTL2) &= ~(ADC10SR);
    HWREG16(baseAddress + OFS_ADC10CTL2) |= samplingRateSelect;
}

void ADC10_B_setWindowComp (uint16_t baseAddress,
    uint16_t highThreshold,
    uint16_t lowThreshold)
{
    HWREG16(baseAddress + OFS_ADC10HI) = highThreshold;
    HWREG16(baseAddress + OFS_ADC10LO) = lowThreshold;
}

uint32_t ADC10_B_getMemoryAddressForDMA (uint16_t baseAddress)
{
    return ( baseAddress + OFS_ADC10MEM0 );
}

uint8_t ADC10_B_isBusy (uint16_t baseAddress)
{
    return (HWREG16(baseAddress + OFS_ADC10CTL1) & ADC10BUSY);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for adc10_b_api
//! @}
//
//*****************************************************************************
