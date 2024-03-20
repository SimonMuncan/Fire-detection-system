/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef SMOKE_H    /* Guard against multiple inclusion */
#define SMOKE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
#define SMOKE_RETVAL  uint8_t

#define SMOKE_OK                0x00
#define SMOKE_INIT_ERROR        0xFF
#define SMOKE_PARAMETER_ERROR   0xFE
/** \} */

/**
 * \defgroup slave_address SMOKE click slave address
 * \{
 */
#define SMOKE_I2C_ADDRESS                 0x57
/** \} */

/**
 * \defgroup registers_addresses Registers addresses
 * \{
 */

/**
 * \defgroup status_registers Status Registers and flags
 * \{
 */
#define SMOKE_INT_STAT1                   0x00
#define SMOKE_INT_STAT2                   0x01
#define SMOKE_INT_ENABLE1                 0x02
#define SMOKE_INT_ENABLE2                 0x03
/** \} */

/**
 * \defgroup int_flags Interrupt function flags
 * \{
 */
#define SMOKE_INT_FLAG_GET_MAIN           1
#define SMOKE_INT_FLAG_GET_TEMP_DATA      2

#define SMOKE_INT_FLAG_SET_AFULL          0
#define SMOKE_INT_FLAG_SET_DATA_RDY       1
#define SMOKE_INT_FLAG_SET_ALS_OVF        2
#define SMOKE_INT_FLAG_SET_PROXY_THRESH   3
#define SMOKE_INT_FLAG_SET_TEMP           4

#define SMOKE_INT_FLAG_SET_ENABLE         1
#define SMOKE_INT_FLAG_SET_DISABLE        0
/** \} */

/**
 * \defgroup fifo_registers FIFO Registers
 * \{
 */
#define SMOKE_FIFO_WRITE_PTR              0x04
#define SMOKE_FIFO_OVERFLOW               0x05
#define SMOKE_FIFO_READ_PTR               0x06
#define SMOKE_FIFO_DATA                   0x07
#define SMOKE_BUFFER_LENGTH               32
/** \} */

/**
 * \defgroup configuration_registers Configuration Registers
 * \{
 */
#define SMOKE_REG_FIFO_CONFIG             0x08
#define SMOKE_REG_MODE_CONFIG             0x09
#define SMOKE_REG_PARTICLE_CONFIG         0x0A
#define SMOKE_REG_LED_RED_PULSE_AMP       0x0C
#define SMOKE_REG_LED_IR_PULSE_AMP        0x0D
#define SMOKE_REG_LED_GREEN_PULSE_AMP     0x0E
#define SMOKE_REG_LED_PROX_AMP            0x10
#define SMOKE_REG_LED_PROX_THRESH         0x30
#define SMOKE_REG_MULTI_LED_CONFIG1       0x11
#define SMOKE_REG_MULTI_LED_CONFIG2       0x12
#define SMOKE_REG_MIN_POWER_LEVEL         0x01
#define SMOKE_REG_AVG_POWER_LEVEL         0x1F
#define SMOKE_REG_MAX_POWER_LEVEL         0xFF
/** \} */

/**
 * \defgroup die_temperature_registers Die Temperature Registers
 * \{
 */
#define SMOKE_DIE_TEMP_INT                0x1F
#define SMOKE_DIE_TEMP_FRAC               0x20
#define SMOKE_DIE_TEMP_CONFIG             0x21
/** \} */

/**
 * \defgroup proximity_function_registers Proximity Function Registers
 * \{
 */
#define SMOKE_PROX_INT_THRESH             0x30
/** \} */

/**
 * \defgroup  part_id_registers  Part ID Registers
 * \{
 */
#define SMOKE_REVISION_ID                 0xFE
#define SMOKE_PART_ID                     0xFF
/** \} */
/** \} */


/**
 * \defgroup smoke_commands Smoke Commands
 * \{
 */

/**
 * \defgroup interrupt_configuration Interrupt configuration
 * \{
 */
#define SMOKE_INT_A_FULL_MASK             (uint8_t)~0b10000000
#define SMOKE_INT_A_FULL_ENABLE           0x80
#define SMOKE_INT_A_FULL_DISABLE          0x00
#define SMOKE_INT_DATA_RDY_MASK           (uint8_t)~0b01000000
#define SMOKE_INT_DATA_RDY_ENABLE         0x40
#define SMOKE_INT_DATA_RDY_DISABLE        0x00
#define SMOKE_INT_ALC_OVF_MASK            (uint8_t)~0b00100000
#define SMOKE_INT_ALC_OVF_ENABLE          0x20
#define SMOKE_INT_ALC_OVF_DISABLE         0x00
#define SMOKE_INT_PROX_INT_MASK           (uint8_t)~0b00010000
#define SMOKE_INT_PROX_INT_ENABLE         0x10
#define SMOKE_INT_PROX_INT_DISABLE        0x00
#define SMOKE_INT_DIE_TEMP_RDY_MASK       (uint8_t)~0b00000010
#define SMOKE_INT_DIE_TEMP_RDY_ENABLE     0x02
#define SMOKE_INT_DIE_TEMP_RDY_DISABLE    0x00
/** \} */

/**
 * \defgroup fifo_configuration_commands FIFO configuration commands
 * \{
 */
#define SMOKE_SAMPLEAVG_MASK              (uint8_t)~0b11100000
#define SMOKE_SAMPLEAVG_1                 0x00
#define SMOKE_SAMPLEAVG_2                 0x20
#define SMOKE_SAMPLEAVG_4                 0x40
#define SMOKE_SAMPLEAVG_8                 0x60
#define SMOKE_SAMPLEAVG_16                0x80
#define SMOKE_SAMPLEAVG_32                0xA0
#define SMOKE_ROLLOVER_MASK               0xEF
#define SMOKE_ROLLOVER_ENABLE             0x10
#define SMOKE_ROLLOVER_DISABLE            0x00
#define SMOKE_A_FULL_MASK                 0xF0
/** \} */

/**
 * \defgroup  mode_configuration_commands  Mode configuration commands
 * \{
 */
#define SMOKE_SHUTDOWN_MASK               0x7F
#define SMOKE_SHUTDOWN                    0x80
#define SMOKE_WAKEUP                      0x00
#define SMOKE_RESET_MASK                  0xBF
#define SMOKE_RESET                       0x40
#define SMOKE_MODE_MASK                   0xF8
#define SMOKE_MODE_REDONLY                0x02
#define SMOKE_MODE_REDIRONLY              0x03
#define SMOKE_MODE_MULTILED               0x07
/** \} */

/**
 * \defgroup particle_sensing_cconfiguration_commands Particle sensing configuration commands
 * \{
 */
#define SMOKE_ADCRANGE_MASK               0x9F
#define SMOKE_ADCRANGE_2048               0x00
#define SMOKE_ADCRANGE_4096               0x20
#define SMOKE_ADCRANGE_8192               0x40
#define SMOKE_ADCRANGE_16384              0x60
#define SMOKE_SAMPLERATE_MASK             0xE3
#define SMOKE_SAMPLERATE_50               0x00
#define SMOKE_SAMPLERATE_100              0x04
#define SMOKE_SAMPLERATE_200              0x08
#define SMOKE_SAMPLERATE_400              0x0C
#define SMOKE_SAMPLERATE_800              0x10
#define SMOKE_SAMPLERATE_1000             0x14
#define SMOKE_SAMPLERATE_1600             0x18
#define SMOKE_SAMPLERATE_3200             0x1C
#define SMOKE_PULSEWIDTH_MASK             0xFC
#define SMOKE_PULSEWIDTH_69               0x00
#define SMOKE_PULSEWIDTH_118              0x01
#define SMOKE_PULSEWIDTH_215              0x02
#define SMOKE_PULSEWIDTH_411              0x03
/** \} */

/**
 * \defgroup multi_led_mode_configuration Multi-LED Mode configuration
 * \{
 */
#define SMOKE_SLOT1_MASK                  0xF8
#define SMOKE_SLOT2_MASK                  0x8F
#define SMOKE_SLOT3_MASK                  0xF8
#define SMOKE_SLOT4_MASK                  0x8F

#define SMOKE_SLOT_NONE                   0x00
#define SMOKE_SLOT_RED_LED                0x01
#define SMOKE_SLOT_IR_LED                 0x02
#define SMOKE_SLOT_GREEN_LED              0x03

#define SMOKE_SLOT_NONE_PILOT             0x04
#define SMOKE_SLOT_RED_PILOT              0x05
#define SMOKE_SLOT_IR_PILOT               0x06
#define SMOKE_SLOT_GREEN_PILOT            0x07
/** \} */
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */
    typedef struct{
    
    uint32_t red_value;
    uint32_t ir_value;
    
}smoke_t;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Precondition
        List and describe any required preconditions. If there are no preconditions,
        enter "None."

      @Parameters
        @param param1 Describe the first parameter to the function.
    
        @param param2 Describe the second parameter to the function.

      @Returns
        List (if feasible) and describe the return values of the function.
        <ul>
          <li>1   Indicates an error occurred
          <li>0   Indicates an error did not occur
        </ul>

      @Remarks
        Describe any special behavior not described above.
        <p>
        Any additional remarks.

      @Example
        @code
        if(ExampleFunctionName(1, 2) == 0)
        {
            return 3;
        }
     */
    uint8_t ko_sam(void);

    void smoke_init(void);
    void FIFO_Config(void);
    void MODE_Config(void);
    void SPO2_Config(void);
    void LED_Amp(void);
    void FIFO_Clear(void);
    void FIFO_read(smoke_t* sens);
    void smoke_reset(void);
    void smoke_prox_int(void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* SMOKE_H */

/* *****************************************************************************
 End of File
 */
