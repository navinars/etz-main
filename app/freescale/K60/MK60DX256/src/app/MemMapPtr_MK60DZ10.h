/*
** ###################################################################
**     Processors:          MKL25Z128FM4
**                          MKL25Z128FT4
**                          MKL25Z128LH4
**                          MKL25Z128VLK4
**
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KL25RM, Rev.1, Jun 2012
**     Version:             rev. 1.2, 2012-06-21
**
**     Abstract:
**         This header file implements peripheral memory map pointers 
**          for the hard macros (backwards compatibility) of legacy 
**          Freescale Apps software.
**
**     Copyright: 1997 - 2012 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2012-05-17)
**         Initial version.
**     - rev. 1.1 (2012-06-08)
**         Update according to reference manual rev. 0, draft B.
**     - rev. 1.2 (2012-06-21)
**         Update according to reference manual rev. 1.
**
** ###################################################################
*/

/**
 * @file MKL25Z4.h
 * @version 1.2
 * @date 2012-06-21
 * @brief Peripheral memory map for MKL25Z4
 *
 * This header file implements peripheral memory map for MKL25Z4 processor.
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(MCU_MKL25Z4)  /* Check if memory map has not been already included */
#define MCU_MKL25Z4

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error MKL25Z4 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include <stdint.h>

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
//#define MCU_MEM_MAP_VERSION 0x0100u


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */


/**
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Peripheral type defines
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup Peripheral_defines Peripheral type defines
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ADC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ADC_Peripheral ADC
 * @{
 */

/** ADC - Peripheral register structure */
typedef struct ADC_MemMap {
  uint32_t SC1[2];                                 /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  uint32_t CFG1;                                   /**< ADC Configuration Register 1, offset: 0x8 */
  uint32_t CFG2;                                   /**< ADC Configuration Register 2, offset: 0xC */
  uint32_t R[2];                                   /**< ADC Data Result Register, array offset: 0x10, array step: 0x4 */
  uint32_t CV1;                                    /**< Compare Value Registers, offset: 0x18 */
  uint32_t CV2;                                    /**< Compare Value Registers, offset: 0x1C */
  uint32_t SC2;                                    /**< Status and Control Register 2, offset: 0x20 */
  uint32_t SC3;                                    /**< Status and Control Register 3, offset: 0x24 */
  uint32_t OFS;                                    /**< ADC Offset Correction Register, offset: 0x28 */
  uint32_t PG;                                     /**< ADC Plus-Side Gain Register, offset: 0x2C */
  uint32_t MG;                                     /**< ADC Minus-Side Gain Register, offset: 0x30 */
  uint32_t CLPD;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
  uint32_t CLPS;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
  uint32_t CLP4;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
  uint32_t CLP3;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
  uint32_t CLP2;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  uint32_t CLP1;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  uint32_t CLP0;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
  uint32_t PGA;									   /**< ADC PGA register, offset: 0x50 */
  uint32_t CLMD;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
  uint32_t CLMS;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
  uint32_t CLM4;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
  uint32_t CLM3;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
  uint32_t CLM2;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
  uint32_t CLM1;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
  uint32_t CLM0;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
} volatile *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register accessors */
#define ADC_SC1_REG(base,index)                  ((base)->SC1[index])
#define ADC_CFG1_REG(base)                       ((base)->CFG1)
#define ADC_CFG2_REG(base)                       ((base)->CFG2)
#define ADC_R_REG(base,index)                    ((base)->R[index])
#define ADC_CV1_REG(base)                        ((base)->CV1)
#define ADC_CV2_REG(base)                        ((base)->CV2)
#define ADC_SC2_REG(base)                        ((base)->SC2)
#define ADC_SC3_REG(base)                        ((base)->SC3)
#define ADC_OFS_REG(base)                        ((base)->OFS)
#define ADC_PG_REG(base)                         ((base)->PG)
#define ADC_MG_REG(base)                         ((base)->MG)
#define ADC_CLPD_REG(base)                       ((base)->CLPD)
#define ADC_CLPS_REG(base)                       ((base)->CLPS)
#define ADC_CLP4_REG(base)                       ((base)->CLP4)
#define ADC_CLP3_REG(base)                       ((base)->CLP3)
#define ADC_CLP2_REG(base)                       ((base)->CLP2)
#define ADC_CLP1_REG(base)                       ((base)->CLP1)
#define ADC_CLP0_REG(base)                       ((base)->CLP0)
#define ADC_PGA_REG(base)                        ((base)->PGA)
#define ADC_CLMD_REG(base)                       ((base)->CLMD)
#define ADC_CLMS_REG(base)                       ((base)->CLMS)
#define ADC_CLM4_REG(base)                       ((base)->CLM4)
#define ADC_CLM3_REG(base)                       ((base)->CLM3)
#define ADC_CLM2_REG(base)                       ((base)->CLM2)
#define ADC_CLM1_REG(base)                       ((base)->CLM1)
#define ADC_CLM0_REG(base)                       ((base)->CLM0)

/**
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */



/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base pointer */
#define ADC0_BASE_PTR                            ((ADC_MemMapPtr)0x4003B000u)
/** Peripheral ADC1 base pointer */
#define ADC1_BASE_PTR                            ((ADC_MemMapPtr)0x400BB000u)

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC0 */
#define ADC0_SC1A                                ADC_SC1_REG(ADC0_BASE_PTR,0)
#define ADC0_SC1B                                ADC_SC1_REG(ADC0_BASE_PTR,1)
#define ADC0_CFG1                                ADC_CFG1_REG(ADC0_BASE_PTR)
#define ADC0_CFG2                                ADC_CFG2_REG(ADC0_BASE_PTR)
#define ADC0_RA                                  ADC_R_REG(ADC0_BASE_PTR,0)
#define ADC0_RB                                  ADC_R_REG(ADC0_BASE_PTR,1)
#define ADC0_CV1                                 ADC_CV1_REG(ADC0_BASE_PTR)
#define ADC0_CV2                                 ADC_CV2_REG(ADC0_BASE_PTR)
#define ADC0_SC2                                 ADC_SC2_REG(ADC0_BASE_PTR)
#define ADC0_SC3                                 ADC_SC3_REG(ADC0_BASE_PTR)
#define ADC0_OFS                                 ADC_OFS_REG(ADC0_BASE_PTR)
#define ADC0_PG                                  ADC_PG_REG(ADC0_BASE_PTR)
#define ADC0_MG                                  ADC_MG_REG(ADC0_BASE_PTR)
#define ADC0_CLPD                                ADC_CLPD_REG(ADC0_BASE_PTR)
#define ADC0_CLPS                                ADC_CLPS_REG(ADC0_BASE_PTR)
#define ADC0_CLP4                                ADC_CLP4_REG(ADC0_BASE_PTR)
#define ADC0_CLP3                                ADC_CLP3_REG(ADC0_BASE_PTR)
#define ADC0_CLP2                                ADC_CLP2_REG(ADC0_BASE_PTR)
#define ADC0_CLP1                                ADC_CLP1_REG(ADC0_BASE_PTR)
#define ADC0_CLP0                                ADC_CLP0_REG(ADC0_BASE_PTR)
#define ADC0_PGA                                 ADC_PGA_REG(ADC0_BASE_PTR)
#define ADC0_CLMD                                ADC_CLMD_REG(ADC0_BASE_PTR)
#define ADC0_CLMS                                ADC_CLMS_REG(ADC0_BASE_PTR)
#define ADC0_CLM4                                ADC_CLM4_REG(ADC0_BASE_PTR)
#define ADC0_CLM3                                ADC_CLM3_REG(ADC0_BASE_PTR)
#define ADC0_CLM2                                ADC_CLM2_REG(ADC0_BASE_PTR)
#define ADC0_CLM1                                ADC_CLM1_REG(ADC0_BASE_PTR)
#define ADC0_CLM0                                ADC_CLM0_REG(ADC0_BASE_PTR)
/* ADC1 */
#define ADC1_SC1A                                ADC_SC1_REG(ADC1_BASE_PTR,0)
#define ADC1_SC1B                                ADC_SC1_REG(ADC1_BASE_PTR,1)
#define ADC1_CFG1                                ADC_CFG1_REG(ADC1_BASE_PTR)
#define ADC1_CFG2                                ADC_CFG2_REG(ADC1_BASE_PTR)
#define ADC1_RA                                  ADC_R_REG(ADC1_BASE_PTR,0)
#define ADC1_RB                                  ADC_R_REG(ADC1_BASE_PTR,1)
#define ADC1_CV1                                 ADC_CV1_REG(ADC1_BASE_PTR)
#define ADC1_CV2                                 ADC_CV2_REG(ADC1_BASE_PTR)
#define ADC1_SC2                                 ADC_SC2_REG(ADC1_BASE_PTR)
#define ADC1_SC3                                 ADC_SC3_REG(ADC1_BASE_PTR)
#define ADC1_OFS                                 ADC_OFS_REG(ADC1_BASE_PTR)
#define ADC1_PG                                  ADC_PG_REG(ADC1_BASE_PTR)
#define ADC1_MG                                  ADC_MG_REG(ADC1_BASE_PTR)
#define ADC1_CLPD                                ADC_CLPD_REG(ADC1_BASE_PTR)
#define ADC1_CLPS                                ADC_CLPS_REG(ADC1_BASE_PTR)
#define ADC1_CLP4                                ADC_CLP4_REG(ADC1_BASE_PTR)
#define ADC1_CLP3                                ADC_CLP3_REG(ADC1_BASE_PTR)
#define ADC1_CLP2                                ADC_CLP2_REG(ADC1_BASE_PTR)
#define ADC1_CLP1                                ADC_CLP1_REG(ADC1_BASE_PTR)
#define ADC1_CLP0                                ADC_CLP0_REG(ADC1_BASE_PTR)
#define ADC1_PGA                                 ADC_PGA_REG(ADC1_BASE_PTR)
#define ADC1_CLMD                                ADC_CLMD_REG(ADC1_BASE_PTR)
#define ADC1_CLMS                                ADC_CLMS_REG(ADC1_BASE_PTR)
#define ADC1_CLM4                                ADC_CLM4_REG(ADC1_BASE_PTR)
#define ADC1_CLM3                                ADC_CLM3_REG(ADC1_BASE_PTR)
#define ADC1_CLM2                                ADC_CLM2_REG(ADC1_BASE_PTR)
#define ADC1_CLM1                                ADC_CLM1_REG(ADC1_BASE_PTR)
#define ADC1_CLM0                                ADC_CLM0_REG(ADC1_BASE_PTR)

/* ADC - Register array accessors */
#define ADC0_SC1(index)                          ADC_SC1_REG(ADC0_BASE_PTR,index)
#define ADC1_SC1(index)                          ADC_SC1_REG(ADC1_BASE_PTR,index)
#define ADC0_R(index)                            ADC_R_REG(ADC0_BASE_PTR,index)
#define ADC1_R(index)                            ADC_R_REG(ADC1_BASE_PTR,index)

/**
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ADC_Peripheral */


/* ----------------------------------------------------------------------------
   -- AIPS
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup AIPS_Peripheral AIPS
 * @{
 */

/** AIPS - Peripheral register structure */
typedef struct AIPS_MemMap {
  uint32_t MPRA;                                   /**< Master Privilege Register A, offset: 0x0 */
  uint8_t RESERVED_0[28];
  uint32_t PACRA;                                  /**< Peripheral Access Control Register, offset: 0x20 */
  uint32_t PACRB;                                  /**< Peripheral Access Control Register, offset: 0x24 */
  uint32_t PACRC;                                  /**< Peripheral Access Control Register, offset: 0x28 */
  uint32_t PACRD;                                  /**< Peripheral Access Control Register, offset: 0x2C */
  uint8_t RESERVED_1[16];
  uint32_t PACRE;                                  /**< Peripheral Access Control Register, offset: 0x40 */
  uint32_t PACRF;                                  /**< Peripheral Access Control Register, offset: 0x44 */
  uint32_t PACRG;                                  /**< Peripheral Access Control Register, offset: 0x48 */
  uint32_t PACRH;                                  /**< Peripheral Access Control Register, offset: 0x4C */
  uint32_t PACRI;                                  /**< Peripheral Access Control Register, offset: 0x50 */
  uint32_t PACRJ;                                  /**< Peripheral Access Control Register, offset: 0x54 */
  uint32_t PACRK;                                  /**< Peripheral Access Control Register, offset: 0x58 */
  uint32_t PACRL;                                  /**< Peripheral Access Control Register, offset: 0x5C */
  uint32_t PACRM;                                  /**< Peripheral Access Control Register, offset: 0x60 */
  uint32_t PACRN;                                  /**< Peripheral Access Control Register, offset: 0x64 */
  uint32_t PACRO;                                  /**< Peripheral Access Control Register, offset: 0x68 */
  uint32_t PACRP;                                  /**< Peripheral Access Control Register, offset: 0x6C */
} volatile *AIPS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- AIPS - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup AIPS_Register_Accessor_Macros AIPS - Register accessor macros
 * @{
 */


/* AIPS - Register accessors */
#define AIPS_MPRA_REG(base)                      ((base)->MPRA)
#define AIPS_PACRA_REG(base)                     ((base)->PACRA)
#define AIPS_PACRB_REG(base)                     ((base)->PACRB)
#define AIPS_PACRC_REG(base)                     ((base)->PACRC)
#define AIPS_PACRD_REG(base)                     ((base)->PACRD)
#define AIPS_PACRE_REG(base)                     ((base)->PACRE)
#define AIPS_PACRF_REG(base)                     ((base)->PACRF)
#define AIPS_PACRG_REG(base)                     ((base)->PACRG)
#define AIPS_PACRH_REG(base)                     ((base)->PACRH)
#define AIPS_PACRI_REG(base)                     ((base)->PACRI)
#define AIPS_PACRJ_REG(base)                     ((base)->PACRJ)
#define AIPS_PACRK_REG(base)                     ((base)->PACRK)
#define AIPS_PACRL_REG(base)                     ((base)->PACRL)
#define AIPS_PACRM_REG(base)                     ((base)->PACRM)
#define AIPS_PACRN_REG(base)                     ((base)->PACRN)
#define AIPS_PACRO_REG(base)                     ((base)->PACRO)
#define AIPS_PACRP_REG(base)                     ((base)->PACRP)

/**
 * @}
 */ /* end of group AIPS_Register_Accessor_Macros */

/* AIPS - Peripheral instance base addresses */
/** Peripheral AIPS0 base pointer */
#define AIPS0_BASE_PTR                           ((AIPS_MemMapPtr)0x40000000u)
/** Peripheral AIPS1 base pointer */
#define AIPS1_BASE_PTR                           ((AIPS_MemMapPtr)0x40080000u)

/* ----------------------------------------------------------------------------
   -- AIPS - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup AIPS_Register_Accessor_Macros AIPS - Register accessor macros
 * @{
 */


/* AIPS - Register instance definitions */
/* AIPS0 */
#define AIPS0_MPRA                               AIPS_MPRA_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRA                              AIPS_PACRA_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRB                              AIPS_PACRB_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRC                              AIPS_PACRC_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRD                              AIPS_PACRD_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRE                              AIPS_PACRE_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRF                              AIPS_PACRF_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRG                              AIPS_PACRG_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRH                              AIPS_PACRH_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRI                              AIPS_PACRI_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRJ                              AIPS_PACRJ_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRK                              AIPS_PACRK_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRL                              AIPS_PACRL_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRM                              AIPS_PACRM_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRN                              AIPS_PACRN_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRO                              AIPS_PACRO_REG(AIPS0_BASE_PTR)
#define AIPS0_PACRP                              AIPS_PACRP_REG(AIPS0_BASE_PTR)
/* AIPS1 */
#define AIPS1_MPRA                               AIPS_MPRA_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRA                              AIPS_PACRA_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRB                              AIPS_PACRB_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRC                              AIPS_PACRC_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRD                              AIPS_PACRD_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRE                              AIPS_PACRE_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRF                              AIPS_PACRF_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRG                              AIPS_PACRG_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRH                              AIPS_PACRH_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRI                              AIPS_PACRI_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRJ                              AIPS_PACRJ_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRK                              AIPS_PACRK_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRL                              AIPS_PACRL_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRM                              AIPS_PACRM_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRN                              AIPS_PACRN_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRO                              AIPS_PACRO_REG(AIPS1_BASE_PTR)
#define AIPS1_PACRP                              AIPS_PACRP_REG(AIPS1_BASE_PTR)

/**
 * @}
 */ /* end of group AIPS_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group AIPS_Peripheral */


/* ----------------------------------------------------------------------------
   -- AXBS
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup AXBS_Peripheral AXBS
 * @{
 */

/** AXBS - Peripheral register structure */
typedef struct AXBS_MemMap {
  struct {                                         /* offset: 0x0, array step: 0x100 */
    uint32_t PRS;                                    /**< Priority Registers Slave, array offset: 0x0, array step: 0x100 */
    uint8_t RESERVED_0[12];
    uint32_t CRS;                                    /**< Control Register, array offset: 0x10, array step: 0x100 */
    uint8_t RESERVED_1[236];
  } SLAVE[5];
  uint8_t RESERVED_0[768];
  uint32_t MGPCR0;                                 /**< Master General Purpose Control Register, offset: 0x800 */
  uint8_t RESERVED_1[252];
  uint32_t MGPCR1;                                 /**< Master General Purpose Control Register, offset: 0x900 */
  uint8_t RESERVED_2[252];
  uint32_t MGPCR2;                                 /**< Master General Purpose Control Register, offset: 0xA00 */
  uint8_t RESERVED_3[252];
  uint32_t MGPCR3;                                 /**< Master General Purpose Control Register, offset: 0xB00 */
  uint8_t RESERVED_4[252];
  uint32_t MGPCR4;                                 /**< Master General Purpose Control Register, offset: 0xC00 */
  uint8_t RESERVED_5[252];
  uint32_t MGPCR5;                                 /**< Master General Purpose Control Register, offset: 0xD00 */
} volatile *AXBS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- AXBS - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup AXBS_Register_Accessor_Macros AXBS - Register accessor macros
 * @{
 */


/* AXBS - Register accessors */
#define AXBS_PRS_REG(base,index)                 ((base)->SLAVE[index].PRS)
#define AXBS_CRS_REG(base,index)                 ((base)->SLAVE[index].CRS)
#define AXBS_MGPCR0_REG(base)                    ((base)->MGPCR0)
#define AXBS_MGPCR1_REG(base)                    ((base)->MGPCR1)
#define AXBS_MGPCR2_REG(base)                    ((base)->MGPCR2)
#define AXBS_MGPCR3_REG(base)                    ((base)->MGPCR3)
#define AXBS_MGPCR4_REG(base)                    ((base)->MGPCR4)
#define AXBS_MGPCR5_REG(base)                    ((base)->MGPCR5)

/**
 * @}
 */ /* end of group AXBS_Register_Accessor_Macros */


/* AXBS - Peripheral instance base addresses */
/** Peripheral AXBS base pointer */
#define AXBS_BASE_PTR                            ((AXBS_MemMapPtr)0x40004000u)

/* ----------------------------------------------------------------------------
   -- AXBS - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup AXBS_Register_Accessor_Macros AXBS - Register accessor macros
 * @{
 */


/* AXBS - Register instance definitions */
/* AXBS */
#define AXBS_PRS0                                AXBS_PRS_REG(AXBS_BASE_PTR,0)
#define AXBS_CRS0                                AXBS_CRS_REG(AXBS_BASE_PTR,0)
#define AXBS_PRS1                                AXBS_PRS_REG(AXBS_BASE_PTR,1)
#define AXBS_CRS1                                AXBS_CRS_REG(AXBS_BASE_PTR,1)
#define AXBS_PRS2                                AXBS_PRS_REG(AXBS_BASE_PTR,2)
#define AXBS_CRS2                                AXBS_CRS_REG(AXBS_BASE_PTR,2)
#define AXBS_PRS3                                AXBS_PRS_REG(AXBS_BASE_PTR,3)
#define AXBS_CRS3                                AXBS_CRS_REG(AXBS_BASE_PTR,3)
#define AXBS_PRS4                                AXBS_PRS_REG(AXBS_BASE_PTR,4)
#define AXBS_CRS4                                AXBS_CRS_REG(AXBS_BASE_PTR,4)
#define AXBS_MGPCR0                              AXBS_MGPCR0_REG(AXBS_BASE_PTR)
#define AXBS_MGPCR1                              AXBS_MGPCR1_REG(AXBS_BASE_PTR)
#define AXBS_MGPCR2                              AXBS_MGPCR2_REG(AXBS_BASE_PTR)
#define AXBS_MGPCR3                              AXBS_MGPCR3_REG(AXBS_BASE_PTR)
#define AXBS_MGPCR4                              AXBS_MGPCR4_REG(AXBS_BASE_PTR)
#define AXBS_MGPCR5                              AXBS_MGPCR5_REG(AXBS_BASE_PTR)

/* AXBS - Register array accessors */
#define AXBS_PRS(index)                          AXBS_PRS_REG(AXBS_BASE_PTR,index)
#define AXBS_CRS(index)                          AXBS_CRS_REG(AXBS_BASE_PTR,index)

/**
 * @}
 */ /* end of group AXBS_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group AXBS_Peripheral */


/* ----------------------------------------------------------------------------
   -- BP
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup BP_Peripheral BP
 * @{
 */

/** BP - Peripheral register structure */
typedef struct BP_MemMap {
  uint32_t CTRL;                                   /**< FlashPatch Control Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  uint32_t COMP[2];                                /**< FlashPatch Comparator Register 0..FlashPatch Comparator Register 1, array offset: 0x8, array step: 0x4 */
  uint8_t RESERVED_1[4032];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *BP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register accessors */
#define BP_CTRL_REG(base)                        ((base)->CTRL)
#define BP_COMP_REG(base,index)                  ((base)->COMP[index])
#define BP_PID4_REG(base)                        ((base)->PID4)
#define BP_PID5_REG(base)                        ((base)->PID5)
#define BP_PID6_REG(base)                        ((base)->PID6)
#define BP_PID7_REG(base)                        ((base)->PID7)
#define BP_PID0_REG(base)                        ((base)->PID0)
#define BP_PID1_REG(base)                        ((base)->PID1)
#define BP_PID2_REG(base)                        ((base)->PID2)
#define BP_PID3_REG(base)                        ((base)->PID3)
#define BP_CID0_REG(base)                        ((base)->CID0)
#define BP_CID1_REG(base)                        ((base)->CID1)
#define BP_CID2_REG(base)                        ((base)->CID2)
#define BP_CID3_REG(base)                        ((base)->CID3)

/**
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- BP Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup BP_Register_Masks BP Register Masks
 * @{
 */


/**
 * @}
 */ /* end of group BP_Register_Masks */


/* BP - Peripheral instance base addresses */
/** Peripheral BP base pointer */
#define BP_BASE_PTR                              ((BP_MemMapPtr)0xE0002000u)
/** Array initializer of BP peripheral base pointers */
#define BP_BASE_PTRS                             { BP_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register instance definitions */
/* BP */
#define BP_CTRL                                  BP_CTRL_REG(BP_BASE_PTR)
#define BP_COMP0                                 BP_COMP_REG(BP_BASE_PTR,0)
#define BP_COMP1                                 BP_COMP_REG(BP_BASE_PTR,1)
#define BP_PID4                                  BP_PID4_REG(BP_BASE_PTR)
#define BP_PID5                                  BP_PID5_REG(BP_BASE_PTR)
#define BP_PID6                                  BP_PID6_REG(BP_BASE_PTR)
#define BP_PID7                                  BP_PID7_REG(BP_BASE_PTR)
#define BP_PID0                                  BP_PID0_REG(BP_BASE_PTR)
#define BP_PID1                                  BP_PID1_REG(BP_BASE_PTR)
#define BP_PID2                                  BP_PID2_REG(BP_BASE_PTR)
#define BP_PID3                                  BP_PID3_REG(BP_BASE_PTR)
#define BP_CID0                                  BP_CID0_REG(BP_BASE_PTR)
#define BP_CID1                                  BP_CID1_REG(BP_BASE_PTR)
#define BP_CID2                                  BP_CID2_REG(BP_BASE_PTR)
#define BP_CID3                                  BP_CID3_REG(BP_BASE_PTR)

/* BP - Register array accessors */
#define BP_COMP(index)                           BP_COMP_REG(BP_BASE_PTR,index)

/**
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group BP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CAN
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CAN_Peripheral CAN
 * @{
 */

/** CAN - Peripheral register structure */
typedef struct CAN_MemMap {
  uint32_t MCR;                                    /**< Module Configuration Register, offset: 0x0 */
  uint32_t CTRL1;                                  /**< Control 1 Register, offset: 0x4 */
  uint32_t TIMER;                                  /**< Free Running Timer, offset: 0x8 */
  uint8_t RESERVED_0[4];
  uint32_t RXMGMASK;                               /**< Rx Mailboxes Global Mask Register, offset: 0x10 */
  uint32_t RX14MASK;                               /**< Rx 14 Mask Register, offset: 0x14 */
  uint32_t RX15MASK;                               /**< Rx 15 Mask Register, offset: 0x18 */
  uint32_t ECR;                                    /**< Error Counter, offset: 0x1C */
  uint32_t ESR1;                                   /**< Error and Status 1 Register, offset: 0x20 */
  uint32_t IMASK2;                                 /**< Interrupt Masks 2 Register, offset: 0x24 */
  uint32_t IMASK1;                                 /**< Interrupt Masks 1 Register, offset: 0x28 */
  uint32_t IFLAG2;                                 /**< Interrupt Flags 2 Register, offset: 0x2C */
  uint32_t IFLAG1;                                 /**< Interrupt Flags 1 Register, offset: 0x30 */
  uint32_t CTRL2;                                  /**< Control 2 Register, offset: 0x34 */
  uint32_t ESR2;                                   /**< Error and Status 2 Register, offset: 0x38 */
  uint8_t RESERVED_1[8];
  uint32_t CRCR;                                   /**< CRC Register, offset: 0x44 */
  uint32_t RXFGMASK;                               /**< Rx FIFO Global Mask Register, offset: 0x48 */
  uint32_t RXFIR;                                  /**< Rx FIFO Information Register, offset: 0x4C */
  uint8_t RESERVED_2[48];
  struct {                                         /* offset: 0x80, array step: 0x10 */
    uint32_t CS;                                     /**< Message Buffer 0 CS Register..Message Buffer 15 CS Register, array offset: 0x80, array step: 0x10 */
    uint32_t ID;                                     /**< Message Buffer 0 ID Register..Message Buffer 15 ID Register, array offset: 0x84, array step: 0x10 */
    uint32_t WORD0;                                  /**< Message Buffer 0 WORD0 Register..Message Buffer 15 WORD0 Register, array offset: 0x88, array step: 0x10 */
    uint32_t WORD1;                                  /**< Message Buffer 0 WORD1 Register..Message Buffer 15 WORD1 Register, array offset: 0x8C, array step: 0x10 */
  } MB[16];
  uint8_t RESERVED_3[1792];
  uint32_t RXIMR[16];                              /**< Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 */
} volatile *CAN_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CAN - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CAN_Register_Accessor_Macros CAN - Register accessor macros
 * @{
 */


/* CAN - Register accessors */
#define CAN_MCR_REG(base)                        ((base)->MCR)
#define CAN_CTRL1_REG(base)                      ((base)->CTRL1)
#define CAN_TIMER_REG(base)                      ((base)->TIMER)
#define CAN_RXMGMASK_REG(base)                   ((base)->RXMGMASK)
#define CAN_RX14MASK_REG(base)                   ((base)->RX14MASK)
#define CAN_RX15MASK_REG(base)                   ((base)->RX15MASK)
#define CAN_ECR_REG(base)                        ((base)->ECR)
#define CAN_ESR1_REG(base)                       ((base)->ESR1)
#define CAN_IMASK2_REG(base)                     ((base)->IMASK2)
#define CAN_IMASK1_REG(base)                     ((base)->IMASK1)
#define CAN_IFLAG2_REG(base)                     ((base)->IFLAG2)
#define CAN_IFLAG1_REG(base)                     ((base)->IFLAG1)
#define CAN_CTRL2_REG(base)                      ((base)->CTRL2)
#define CAN_ESR2_REG(base)                       ((base)->ESR2)
#define CAN_CRCR_REG(base)                       ((base)->CRCR)
#define CAN_RXFGMASK_REG(base)                   ((base)->RXFGMASK)
#define CAN_RXFIR_REG(base)                      ((base)->RXFIR)
#define CAN_CS_REG(base,index)                   ((base)->MB[index].CS)
#define CAN_ID_REG(base,index)                   ((base)->MB[index].ID)
#define CAN_WORD0_REG(base,index)                ((base)->MB[index].WORD0)
#define CAN_WORD1_REG(base,index)                ((base)->MB[index].WORD1)
#define CAN_RXIMR_REG(base,index)                ((base)->RXIMR[index])

/**
 * @}
 */ /* end of group CAN_Register_Accessor_Macros */


/* CAN - Peripheral instance base addresses */
/** Peripheral CAN0 base pointer */
#define CAN0_BASE_PTR                            ((CAN_MemMapPtr)0x40024000u)
/** Peripheral CAN1 base pointer */
#define CAN1_BASE_PTR                            ((CAN_MemMapPtr)0x400A4000u)

/* ----------------------------------------------------------------------------
   -- CAN - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CAN_Register_Accessor_Macros CAN - Register accessor macros
 * @{
 */


/* CAN - Register instance definitions */
/* CAN0 */
#define CAN0_MCR                                 CAN_MCR_REG(CAN0_BASE_PTR)
#define CAN0_CTRL1                               CAN_CTRL1_REG(CAN0_BASE_PTR)
#define CAN0_TIMER                               CAN_TIMER_REG(CAN0_BASE_PTR)
#define CAN0_RXMGMASK                            CAN_RXMGMASK_REG(CAN0_BASE_PTR)
#define CAN0_RX14MASK                            CAN_RX14MASK_REG(CAN0_BASE_PTR)
#define CAN0_RX15MASK                            CAN_RX15MASK_REG(CAN0_BASE_PTR)
#define CAN0_ECR                                 CAN_ECR_REG(CAN0_BASE_PTR)
#define CAN0_ESR1                                CAN_ESR1_REG(CAN0_BASE_PTR)
#define CAN0_IMASK2                              CAN_IMASK2_REG(CAN0_BASE_PTR)
#define CAN0_IMASK1                              CAN_IMASK1_REG(CAN0_BASE_PTR)
#define CAN0_IFLAG2                              CAN_IFLAG2_REG(CAN0_BASE_PTR)
#define CAN0_IFLAG1                              CAN_IFLAG1_REG(CAN0_BASE_PTR)
#define CAN0_CTRL2                               CAN_CTRL2_REG(CAN0_BASE_PTR)
#define CAN0_ESR2                                CAN_ESR2_REG(CAN0_BASE_PTR)
#define CAN0_CRCR                                CAN_CRCR_REG(CAN0_BASE_PTR)
#define CAN0_RXFGMASK                            CAN_RXFGMASK_REG(CAN0_BASE_PTR)
#define CAN0_RXFIR                               CAN_RXFIR_REG(CAN0_BASE_PTR)
#define CAN0_RXIMR0                              CAN_RXIMR_REG(CAN0_BASE_PTR,0)
#define CAN0_RXIMR1                              CAN_RXIMR_REG(CAN0_BASE_PTR,1)
#define CAN0_RXIMR2                              CAN_RXIMR_REG(CAN0_BASE_PTR,2)
#define CAN0_RXIMR3                              CAN_RXIMR_REG(CAN0_BASE_PTR,3)
#define CAN0_RXIMR4                              CAN_RXIMR_REG(CAN0_BASE_PTR,4)
#define CAN0_RXIMR5                              CAN_RXIMR_REG(CAN0_BASE_PTR,5)
#define CAN0_RXIMR6                              CAN_RXIMR_REG(CAN0_BASE_PTR,6)
#define CAN0_RXIMR7                              CAN_RXIMR_REG(CAN0_BASE_PTR,7)
#define CAN0_RXIMR8                              CAN_RXIMR_REG(CAN0_BASE_PTR,8)
#define CAN0_RXIMR9                              CAN_RXIMR_REG(CAN0_BASE_PTR,9)
#define CAN0_RXIMR10                             CAN_RXIMR_REG(CAN0_BASE_PTR,10)
#define CAN0_RXIMR11                             CAN_RXIMR_REG(CAN0_BASE_PTR,11)
#define CAN0_RXIMR12                             CAN_RXIMR_REG(CAN0_BASE_PTR,12)
#define CAN0_RXIMR13                             CAN_RXIMR_REG(CAN0_BASE_PTR,13)
#define CAN0_RXIMR14                             CAN_RXIMR_REG(CAN0_BASE_PTR,14)
#define CAN0_RXIMR15                             CAN_RXIMR_REG(CAN0_BASE_PTR,15)
#define CAN0_CS0                                 CAN_CS_REG(CAN0_BASE_PTR,0)
#define CAN0_CS1                                 CAN_CS_REG(CAN0_BASE_PTR,1)
#define CAN0_CS2                                 CAN_CS_REG(CAN0_BASE_PTR,2)
#define CAN0_CS3                                 CAN_CS_REG(CAN0_BASE_PTR,3)
#define CAN0_CS4                                 CAN_CS_REG(CAN0_BASE_PTR,4)
#define CAN0_CS5                                 CAN_CS_REG(CAN0_BASE_PTR,5)
#define CAN0_CS6                                 CAN_CS_REG(CAN0_BASE_PTR,6)
#define CAN0_CS7                                 CAN_CS_REG(CAN0_BASE_PTR,7)
#define CAN0_CS8                                 CAN_CS_REG(CAN0_BASE_PTR,8)
#define CAN0_CS9                                 CAN_CS_REG(CAN0_BASE_PTR,9)
#define CAN0_CS10                                CAN_CS_REG(CAN0_BASE_PTR,10)
#define CAN0_CS11                                CAN_CS_REG(CAN0_BASE_PTR,11)
#define CAN0_CS12                                CAN_CS_REG(CAN0_BASE_PTR,12)
#define CAN0_CS13                                CAN_CS_REG(CAN0_BASE_PTR,13)
#define CAN0_CS14                                CAN_CS_REG(CAN0_BASE_PTR,14)
#define CAN0_CS15                                CAN_CS_REG(CAN0_BASE_PTR,15)
#define CAN0_ID0                                 CAN_ID_REG(CAN0_BASE_PTR,0)
#define CAN0_ID1                                 CAN_ID_REG(CAN0_BASE_PTR,1)
#define CAN0_ID2                                 CAN_ID_REG(CAN0_BASE_PTR,2)
#define CAN0_ID3                                 CAN_ID_REG(CAN0_BASE_PTR,3)
#define CAN0_ID4                                 CAN_ID_REG(CAN0_BASE_PTR,4)
#define CAN0_ID5                                 CAN_ID_REG(CAN0_BASE_PTR,5)
#define CAN0_ID6                                 CAN_ID_REG(CAN0_BASE_PTR,6)
#define CAN0_ID7                                 CAN_ID_REG(CAN0_BASE_PTR,7)
#define CAN0_ID8                                 CAN_ID_REG(CAN0_BASE_PTR,8)
#define CAN0_ID9                                 CAN_ID_REG(CAN0_BASE_PTR,9)
#define CAN0_ID10                                CAN_ID_REG(CAN0_BASE_PTR,10)
#define CAN0_ID11                                CAN_ID_REG(CAN0_BASE_PTR,11)
#define CAN0_ID12                                CAN_ID_REG(CAN0_BASE_PTR,12)
#define CAN0_ID13                                CAN_ID_REG(CAN0_BASE_PTR,13)
#define CAN0_ID14                                CAN_ID_REG(CAN0_BASE_PTR,14)
#define CAN0_ID15                                CAN_ID_REG(CAN0_BASE_PTR,15)
#define CAN0_WORD00                              CAN_WORD0_REG(CAN0_BASE_PTR,0)
#define CAN0_WORD01                              CAN_WORD0_REG(CAN0_BASE_PTR,1)
#define CAN0_WORD02                              CAN_WORD0_REG(CAN0_BASE_PTR,2)
#define CAN0_WORD03                              CAN_WORD0_REG(CAN0_BASE_PTR,3)
#define CAN0_WORD04                              CAN_WORD0_REG(CAN0_BASE_PTR,4)
#define CAN0_WORD05                              CAN_WORD0_REG(CAN0_BASE_PTR,5)
#define CAN0_WORD06                              CAN_WORD0_REG(CAN0_BASE_PTR,6)
#define CAN0_WORD07                              CAN_WORD0_REG(CAN0_BASE_PTR,7)
#define CAN0_WORD08                              CAN_WORD0_REG(CAN0_BASE_PTR,8)
#define CAN0_WORD09                              CAN_WORD0_REG(CAN0_BASE_PTR,9)
#define CAN0_WORD010                             CAN_WORD0_REG(CAN0_BASE_PTR,10)
#define CAN0_WORD011                             CAN_WORD0_REG(CAN0_BASE_PTR,11)
#define CAN0_WORD012                             CAN_WORD0_REG(CAN0_BASE_PTR,12)
#define CAN0_WORD013                             CAN_WORD0_REG(CAN0_BASE_PTR,13)
#define CAN0_WORD014                             CAN_WORD0_REG(CAN0_BASE_PTR,14)
#define CAN0_WORD015                             CAN_WORD0_REG(CAN0_BASE_PTR,15)
#define CAN0_WORD10                              CAN_WORD1_REG(CAN0_BASE_PTR,0)
#define CAN0_WORD11                              CAN_WORD1_REG(CAN0_BASE_PTR,1)
#define CAN0_WORD12                              CAN_WORD1_REG(CAN0_BASE_PTR,2)
#define CAN0_WORD13                              CAN_WORD1_REG(CAN0_BASE_PTR,3)
#define CAN0_WORD14                              CAN_WORD1_REG(CAN0_BASE_PTR,4)
#define CAN0_WORD15                              CAN_WORD1_REG(CAN0_BASE_PTR,5)
#define CAN0_WORD16                              CAN_WORD1_REG(CAN0_BASE_PTR,6)
#define CAN0_WORD17                              CAN_WORD1_REG(CAN0_BASE_PTR,7)
#define CAN0_WORD18                              CAN_WORD1_REG(CAN0_BASE_PTR,8)
#define CAN0_WORD19                              CAN_WORD1_REG(CAN0_BASE_PTR,9)
#define CAN0_WORD110                             CAN_WORD1_REG(CAN0_BASE_PTR,10)
#define CAN0_WORD111                             CAN_WORD1_REG(CAN0_BASE_PTR,11)
#define CAN0_WORD112                             CAN_WORD1_REG(CAN0_BASE_PTR,12)
#define CAN0_WORD113                             CAN_WORD1_REG(CAN0_BASE_PTR,13)
#define CAN0_WORD114                             CAN_WORD1_REG(CAN0_BASE_PTR,14)
#define CAN0_WORD115                             CAN_WORD1_REG(CAN0_BASE_PTR,15)
/* CAN1 */
#define CAN1_MCR                                 CAN_MCR_REG(CAN1_BASE_PTR)
#define CAN1_CTRL1                               CAN_CTRL1_REG(CAN1_BASE_PTR)
#define CAN1_TIMER                               CAN_TIMER_REG(CAN1_BASE_PTR)
#define CAN1_RXMGMASK                            CAN_RXMGMASK_REG(CAN1_BASE_PTR)
#define CAN1_RX14MASK                            CAN_RX14MASK_REG(CAN1_BASE_PTR)
#define CAN1_RX15MASK                            CAN_RX15MASK_REG(CAN1_BASE_PTR)
#define CAN1_ECR                                 CAN_ECR_REG(CAN1_BASE_PTR)
#define CAN1_ESR1                                CAN_ESR1_REG(CAN1_BASE_PTR)
#define CAN1_IMASK2                              CAN_IMASK2_REG(CAN1_BASE_PTR)
#define CAN1_IMASK1                              CAN_IMASK1_REG(CAN1_BASE_PTR)
#define CAN1_IFLAG2                              CAN_IFLAG2_REG(CAN1_BASE_PTR)
#define CAN1_IFLAG1                              CAN_IFLAG1_REG(CAN1_BASE_PTR)
#define CAN1_CTRL2                               CAN_CTRL2_REG(CAN1_BASE_PTR)
#define CAN1_ESR2                                CAN_ESR2_REG(CAN1_BASE_PTR)
#define CAN1_CRCR                                CAN_CRCR_REG(CAN1_BASE_PTR)
#define CAN1_RXFGMASK                            CAN_RXFGMASK_REG(CAN1_BASE_PTR)
#define CAN1_RXFIR                               CAN_RXFIR_REG(CAN1_BASE_PTR)
#define CAN1_RXIMR0                              CAN_RXIMR_REG(CAN1_BASE_PTR,0)
#define CAN1_RXIMR1                              CAN_RXIMR_REG(CAN1_BASE_PTR,1)
#define CAN1_RXIMR2                              CAN_RXIMR_REG(CAN1_BASE_PTR,2)
#define CAN1_RXIMR3                              CAN_RXIMR_REG(CAN1_BASE_PTR,3)
#define CAN1_RXIMR4                              CAN_RXIMR_REG(CAN1_BASE_PTR,4)
#define CAN1_RXIMR5                              CAN_RXIMR_REG(CAN1_BASE_PTR,5)
#define CAN1_RXIMR6                              CAN_RXIMR_REG(CAN1_BASE_PTR,6)
#define CAN1_RXIMR7                              CAN_RXIMR_REG(CAN1_BASE_PTR,7)
#define CAN1_RXIMR8                              CAN_RXIMR_REG(CAN1_BASE_PTR,8)
#define CAN1_RXIMR9                              CAN_RXIMR_REG(CAN1_BASE_PTR,9)
#define CAN1_RXIMR10                             CAN_RXIMR_REG(CAN1_BASE_PTR,10)
#define CAN1_RXIMR11                             CAN_RXIMR_REG(CAN1_BASE_PTR,11)
#define CAN1_RXIMR12                             CAN_RXIMR_REG(CAN1_BASE_PTR,12)
#define CAN1_RXIMR13                             CAN_RXIMR_REG(CAN1_BASE_PTR,13)
#define CAN1_RXIMR14                             CAN_RXIMR_REG(CAN1_BASE_PTR,14)
#define CAN1_RXIMR15                             CAN_RXIMR_REG(CAN1_BASE_PTR,15)
#define CAN1_CS0                                 CAN_CS_REG(CAN1_BASE_PTR,0)
#define CAN1_CS1                                 CAN_CS_REG(CAN1_BASE_PTR,1)
#define CAN1_CS2                                 CAN_CS_REG(CAN1_BASE_PTR,2)
#define CAN1_CS3                                 CAN_CS_REG(CAN1_BASE_PTR,3)
#define CAN1_CS4                                 CAN_CS_REG(CAN1_BASE_PTR,4)
#define CAN1_CS5                                 CAN_CS_REG(CAN1_BASE_PTR,5)
#define CAN1_CS6                                 CAN_CS_REG(CAN1_BASE_PTR,6)
#define CAN1_CS7                                 CAN_CS_REG(CAN1_BASE_PTR,7)
#define CAN1_CS8                                 CAN_CS_REG(CAN1_BASE_PTR,8)
#define CAN1_CS9                                 CAN_CS_REG(CAN1_BASE_PTR,9)
#define CAN1_CS10                                CAN_CS_REG(CAN1_BASE_PTR,10)
#define CAN1_CS11                                CAN_CS_REG(CAN1_BASE_PTR,11)
#define CAN1_CS12                                CAN_CS_REG(CAN1_BASE_PTR,12)
#define CAN1_CS13                                CAN_CS_REG(CAN1_BASE_PTR,13)
#define CAN1_CS14                                CAN_CS_REG(CAN1_BASE_PTR,14)
#define CAN1_CS15                                CAN_CS_REG(CAN1_BASE_PTR,15)
#define CAN1_ID0                                 CAN_ID_REG(CAN1_BASE_PTR,0)
#define CAN1_ID1                                 CAN_ID_REG(CAN1_BASE_PTR,1)
#define CAN1_ID2                                 CAN_ID_REG(CAN1_BASE_PTR,2)
#define CAN1_ID3                                 CAN_ID_REG(CAN1_BASE_PTR,3)
#define CAN1_ID4                                 CAN_ID_REG(CAN1_BASE_PTR,4)
#define CAN1_ID5                                 CAN_ID_REG(CAN1_BASE_PTR,5)
#define CAN1_ID6                                 CAN_ID_REG(CAN1_BASE_PTR,6)
#define CAN1_ID7                                 CAN_ID_REG(CAN1_BASE_PTR,7)
#define CAN1_ID8                                 CAN_ID_REG(CAN1_BASE_PTR,8)
#define CAN1_ID9                                 CAN_ID_REG(CAN1_BASE_PTR,9)
#define CAN1_ID10                                CAN_ID_REG(CAN1_BASE_PTR,10)
#define CAN1_ID11                                CAN_ID_REG(CAN1_BASE_PTR,11)
#define CAN1_ID12                                CAN_ID_REG(CAN1_BASE_PTR,12)
#define CAN1_ID13                                CAN_ID_REG(CAN1_BASE_PTR,13)
#define CAN1_ID14                                CAN_ID_REG(CAN1_BASE_PTR,14)
#define CAN1_ID15                                CAN_ID_REG(CAN1_BASE_PTR,15)
#define CAN1_WORD00                              CAN_WORD0_REG(CAN1_BASE_PTR,0)
#define CAN1_WORD01                              CAN_WORD0_REG(CAN1_BASE_PTR,1)
#define CAN1_WORD02                              CAN_WORD0_REG(CAN1_BASE_PTR,2)
#define CAN1_WORD03                              CAN_WORD0_REG(CAN1_BASE_PTR,3)
#define CAN1_WORD04                              CAN_WORD0_REG(CAN1_BASE_PTR,4)
#define CAN1_WORD05                              CAN_WORD0_REG(CAN1_BASE_PTR,5)
#define CAN1_WORD06                              CAN_WORD0_REG(CAN1_BASE_PTR,6)
#define CAN1_WORD07                              CAN_WORD0_REG(CAN1_BASE_PTR,7)
#define CAN1_WORD08                              CAN_WORD0_REG(CAN1_BASE_PTR,8)
#define CAN1_WORD09                              CAN_WORD0_REG(CAN1_BASE_PTR,9)
#define CAN1_WORD010                             CAN_WORD0_REG(CAN1_BASE_PTR,10)
#define CAN1_WORD011                             CAN_WORD0_REG(CAN1_BASE_PTR,11)
#define CAN1_WORD012                             CAN_WORD0_REG(CAN1_BASE_PTR,12)
#define CAN1_WORD013                             CAN_WORD0_REG(CAN1_BASE_PTR,13)
#define CAN1_WORD014                             CAN_WORD0_REG(CAN1_BASE_PTR,14)
#define CAN1_WORD015                             CAN_WORD0_REG(CAN1_BASE_PTR,15)
#define CAN1_WORD10                              CAN_WORD1_REG(CAN1_BASE_PTR,0)
#define CAN1_WORD11                              CAN_WORD1_REG(CAN1_BASE_PTR,1)
#define CAN1_WORD12                              CAN_WORD1_REG(CAN1_BASE_PTR,2)
#define CAN1_WORD13                              CAN_WORD1_REG(CAN1_BASE_PTR,3)
#define CAN1_WORD14                              CAN_WORD1_REG(CAN1_BASE_PTR,4)
#define CAN1_WORD15                              CAN_WORD1_REG(CAN1_BASE_PTR,5)
#define CAN1_WORD16                              CAN_WORD1_REG(CAN1_BASE_PTR,6)
#define CAN1_WORD17                              CAN_WORD1_REG(CAN1_BASE_PTR,7)
#define CAN1_WORD18                              CAN_WORD1_REG(CAN1_BASE_PTR,8)
#define CAN1_WORD19                              CAN_WORD1_REG(CAN1_BASE_PTR,9)
#define CAN1_WORD110                             CAN_WORD1_REG(CAN1_BASE_PTR,10)
#define CAN1_WORD111                             CAN_WORD1_REG(CAN1_BASE_PTR,11)
#define CAN1_WORD112                             CAN_WORD1_REG(CAN1_BASE_PTR,12)
#define CAN1_WORD113                             CAN_WORD1_REG(CAN1_BASE_PTR,13)
#define CAN1_WORD114                             CAN_WORD1_REG(CAN1_BASE_PTR,14)
#define CAN1_WORD115                             CAN_WORD1_REG(CAN1_BASE_PTR,15)

/* CAN - Register array accessors */
#define CAN0_CS(index)                           CAN_CS_REG(CAN0_BASE_PTR,index)
#define CAN1_CS(index)                           CAN_CS_REG(CAN1_BASE_PTR,index)
#define CAN0_ID(index)                           CAN_ID_REG(CAN0_BASE_PTR,index)
#define CAN1_ID(index)                           CAN_ID_REG(CAN1_BASE_PTR,index)
#define CAN0_WORD0(index)                        CAN_WORD0_REG(CAN0_BASE_PTR,index)
#define CAN1_WORD0(index)                        CAN_WORD0_REG(CAN1_BASE_PTR,index)
#define CAN0_WORD1(index)                        CAN_WORD1_REG(CAN0_BASE_PTR,index)
#define CAN1_WORD1(index)                        CAN_WORD1_REG(CAN1_BASE_PTR,index)
#define CAN0_RXIMR(index)                        CAN_RXIMR_REG(CAN0_BASE_PTR,index)
#define CAN1_RXIMR(index)                        CAN_RXIMR_REG(CAN1_BASE_PTR,index)

/**
 * @}
 */ /* end of group CAN_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CAN_Peripheral */


/* ----------------------------------------------------------------------------
   -- CAU
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CAU_Peripheral CAU
 * @{
 */

/** CAU - Peripheral register structure */
typedef struct CAU_MemMap {
  uint32_t DIRECT[16];                             /**< Direct access register 0..Direct access register 15, array offset: 0x0, array step: 0x4 */
  uint8_t RESERVED_0[2048];
  uint32_t LDR_CASR;                               /**< Status register  - Load Register command, offset: 0x840 */
  uint32_t LDR_CAA;                                /**< Accumulator register - Load Register command, offset: 0x844 */
  uint32_t LDR_CA[9];                              /**< General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load Register command, array offset: 0x848, array step: 0x4 */
  uint8_t RESERVED_1[20];
  uint32_t STR_CASR;                               /**< Status register  - Store Register command, offset: 0x880 */
  uint32_t STR_CAA;                                /**< Accumulator register - Store Register command, offset: 0x884 */
  uint32_t STR_CA[9];                              /**< General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store Register command, array offset: 0x888, array step: 0x4 */
  uint8_t RESERVED_2[20];
  uint32_t ADR_CASR;                               /**< Status register  - Add Register command, offset: 0x8C0 */
  uint32_t ADR_CAA;                                /**< Accumulator register - Add to register command, offset: 0x8C4 */
  uint32_t ADR_CA[9];                              /**< General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add to register command, array offset: 0x8C8, array step: 0x4 */
  uint8_t RESERVED_3[20];
  uint32_t RADR_CASR;                              /**< Status register  - Reverse and Add to Register command, offset: 0x900 */
  uint32_t RADR_CAA;                               /**< Accumulator register - Reverse and Add to Register command, offset: 0x904 */
  uint32_t RADR_CA[9];                             /**< General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 - Reverse and Add to Register command, array offset: 0x908, array step: 0x4 */
  uint8_t RESERVED_4[84];
  uint32_t XOR_CASR;                               /**< Status register  - Exclusive Or command, offset: 0x980 */
  uint32_t XOR_CAA;                                /**< Accumulator register - Exclusive Or command, offset: 0x984 */
  uint32_t XOR_CA[9];                              /**< General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 - Exclusive Or command, array offset: 0x988, array step: 0x4 */
  uint8_t RESERVED_5[20];
  uint32_t ROTL_CASR;                              /**< Status register  - Rotate Left command, offset: 0x9C0 */
  uint32_t ROTL_CAA;                               /**< Accumulator register - Rotate Left command, offset: 0x9C4 */
  uint32_t ROTL_CA[9];                             /**< General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate Left command, array offset: 0x9C8, array step: 0x4 */
  uint8_t RESERVED_6[276];
  uint32_t AESC_CASR;                              /**< Status register  - AES Column Operation command, offset: 0xB00 */
  uint32_t AESC_CAA;                               /**< Accumulator register - AES Column Operation command, offset: 0xB04 */
  uint32_t AESC_CA[9];                             /**< General Purpose Register 0 - AES Column Operation command..General Purpose Register 8 - AES Column Operation command, array offset: 0xB08, array step: 0x4 */
  uint8_t RESERVED_7[20];
  uint32_t AESIC_CASR;                             /**< Status register  - AES Inverse Column Operation command, offset: 0xB40 */
  uint32_t AESIC_CAA;                              /**< Accumulator register - AES Inverse Column Operation command, offset: 0xB44 */
  uint32_t AESIC_CA[9];                            /**< General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8 - AES Inverse Column Operation command, array offset: 0xB48, array step: 0x4 */
} volatile *CAU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CAU_Register_Accessor_Macros CAU - Register accessor macros
 * @{
 */


/* CAU - Register accessors */
#define CAU_DIRECT_REG(base,index)               ((base)->DIRECT[index])
#define CAU_LDR_CASR_REG(base)                   ((base)->LDR_CASR)
#define CAU_LDR_CAA_REG(base)                    ((base)->LDR_CAA)
#define CAU_LDR_CA_REG(base,index)               ((base)->LDR_CA[index])
#define CAU_STR_CASR_REG(base)                   ((base)->STR_CASR)
#define CAU_STR_CAA_REG(base)                    ((base)->STR_CAA)
#define CAU_STR_CA_REG(base,index)               ((base)->STR_CA[index])
#define CAU_ADR_CASR_REG(base)                   ((base)->ADR_CASR)
#define CAU_ADR_CAA_REG(base)                    ((base)->ADR_CAA)
#define CAU_ADR_CA_REG(base,index)               ((base)->ADR_CA[index])
#define CAU_RADR_CASR_REG(base)                  ((base)->RADR_CASR)
#define CAU_RADR_CAA_REG(base)                   ((base)->RADR_CAA)
#define CAU_RADR_CA_REG(base,index)              ((base)->RADR_CA[index])
#define CAU_XOR_CASR_REG(base)                   ((base)->XOR_CASR)
#define CAU_XOR_CAA_REG(base)                    ((base)->XOR_CAA)
#define CAU_XOR_CA_REG(base,index)               ((base)->XOR_CA[index])
#define CAU_ROTL_CASR_REG(base)                  ((base)->ROTL_CASR)
#define CAU_ROTL_CAA_REG(base)                   ((base)->ROTL_CAA)
#define CAU_ROTL_CA_REG(base,index)              ((base)->ROTL_CA[index])
#define CAU_AESC_CASR_REG(base)                  ((base)->AESC_CASR)
#define CAU_AESC_CAA_REG(base)                   ((base)->AESC_CAA)
#define CAU_AESC_CA_REG(base,index)              ((base)->AESC_CA[index])
#define CAU_AESIC_CASR_REG(base)                 ((base)->AESIC_CASR)
#define CAU_AESIC_CAA_REG(base)                  ((base)->AESIC_CAA)
#define CAU_AESIC_CA_REG(base,index)             ((base)->AESIC_CA[index])

/**
 * @}
 */ /* end of group CAU_Register_Accessor_Macros */



/* CAU - Peripheral instance base addresses */
/** Peripheral CAU base pointer */
#define CAU_BASE_PTR                             ((CAU_MemMapPtr)0xE0081000u)

/* ----------------------------------------------------------------------------
   -- CAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CAU_Register_Accessor_Macros CAU - Register accessor macros
 * @{
 */


/* CAU - Register instance definitions */
/* CAU */
#define CAU_LDR_CASR                             CAU_LDR_CASR_REG(CAU_BASE_PTR)
#define CAU_LDR_CAA                              CAU_LDR_CAA_REG(CAU_BASE_PTR)
#define CAU_LDR_CA0                              CAU_LDR_CA_REG(CAU_BASE_PTR,0)
#define CAU_LDR_CA1                              CAU_LDR_CA_REG(CAU_BASE_PTR,1)
#define CAU_LDR_CA2                              CAU_LDR_CA_REG(CAU_BASE_PTR,2)
#define CAU_LDR_CA3                              CAU_LDR_CA_REG(CAU_BASE_PTR,3)
#define CAU_LDR_CA4                              CAU_LDR_CA_REG(CAU_BASE_PTR,4)
#define CAU_LDR_CA5                              CAU_LDR_CA_REG(CAU_BASE_PTR,5)
#define CAU_LDR_CA6                              CAU_LDR_CA_REG(CAU_BASE_PTR,6)
#define CAU_LDR_CA7                              CAU_LDR_CA_REG(CAU_BASE_PTR,7)
#define CAU_LDR_CA8                              CAU_LDR_CA_REG(CAU_BASE_PTR,8)
#define CAU_STR_CASR                             CAU_STR_CASR_REG(CAU_BASE_PTR)
#define CAU_STR_CAA                              CAU_STR_CAA_REG(CAU_BASE_PTR)
#define CAU_STR_CA0                              CAU_STR_CA_REG(CAU_BASE_PTR,0)
#define CAU_STR_CA1                              CAU_STR_CA_REG(CAU_BASE_PTR,1)
#define CAU_STR_CA2                              CAU_STR_CA_REG(CAU_BASE_PTR,2)
#define CAU_STR_CA3                              CAU_STR_CA_REG(CAU_BASE_PTR,3)
#define CAU_STR_CA4                              CAU_STR_CA_REG(CAU_BASE_PTR,4)
#define CAU_STR_CA5                              CAU_STR_CA_REG(CAU_BASE_PTR,5)
#define CAU_STR_CA6                              CAU_STR_CA_REG(CAU_BASE_PTR,6)
#define CAU_STR_CA7                              CAU_STR_CA_REG(CAU_BASE_PTR,7)
#define CAU_STR_CA8                              CAU_STR_CA_REG(CAU_BASE_PTR,8)
#define CAU_ADR_CASR                             CAU_ADR_CASR_REG(CAU_BASE_PTR)
#define CAU_ADR_CAA                              CAU_ADR_CAA_REG(CAU_BASE_PTR)
#define CAU_ADR_CA0                              CAU_ADR_CA_REG(CAU_BASE_PTR,0)
#define CAU_ADR_CA1                              CAU_ADR_CA_REG(CAU_BASE_PTR,1)
#define CAU_ADR_CA2                              CAU_ADR_CA_REG(CAU_BASE_PTR,2)
#define CAU_ADR_CA3                              CAU_ADR_CA_REG(CAU_BASE_PTR,3)
#define CAU_ADR_CA4                              CAU_ADR_CA_REG(CAU_BASE_PTR,4)
#define CAU_ADR_CA5                              CAU_ADR_CA_REG(CAU_BASE_PTR,5)
#define CAU_ADR_CA6                              CAU_ADR_CA_REG(CAU_BASE_PTR,6)
#define CAU_ADR_CA7                              CAU_ADR_CA_REG(CAU_BASE_PTR,7)
#define CAU_ADR_CA8                              CAU_ADR_CA_REG(CAU_BASE_PTR,8)
#define CAU_RADR_CASR                            CAU_RADR_CASR_REG(CAU_BASE_PTR)
#define CAU_RADR_CAA                             CAU_RADR_CAA_REG(CAU_BASE_PTR)
#define CAU_RADR_CA0                             CAU_RADR_CA_REG(CAU_BASE_PTR,0)
#define CAU_RADR_CA1                             CAU_RADR_CA_REG(CAU_BASE_PTR,1)
#define CAU_RADR_CA2                             CAU_RADR_CA_REG(CAU_BASE_PTR,2)
#define CAU_RADR_CA3                             CAU_RADR_CA_REG(CAU_BASE_PTR,3)
#define CAU_RADR_CA4                             CAU_RADR_CA_REG(CAU_BASE_PTR,4)
#define CAU_RADR_CA5                             CAU_RADR_CA_REG(CAU_BASE_PTR,5)
#define CAU_RADR_CA6                             CAU_RADR_CA_REG(CAU_BASE_PTR,6)
#define CAU_RADR_CA7                             CAU_RADR_CA_REG(CAU_BASE_PTR,7)
#define CAU_RADR_CA8                             CAU_RADR_CA_REG(CAU_BASE_PTR,8)
#define CAU_XOR_CASR                             CAU_XOR_CASR_REG(CAU_BASE_PTR)
#define CAU_XOR_CAA                              CAU_XOR_CAA_REG(CAU_BASE_PTR)
#define CAU_XOR_CA0                              CAU_XOR_CA_REG(CAU_BASE_PTR,0)
#define CAU_XOR_CA1                              CAU_XOR_CA_REG(CAU_BASE_PTR,1)
#define CAU_XOR_CA2                              CAU_XOR_CA_REG(CAU_BASE_PTR,2)
#define CAU_XOR_CA3                              CAU_XOR_CA_REG(CAU_BASE_PTR,3)
#define CAU_XOR_CA4                              CAU_XOR_CA_REG(CAU_BASE_PTR,4)
#define CAU_XOR_CA5                              CAU_XOR_CA_REG(CAU_BASE_PTR,5)
#define CAU_XOR_CA6                              CAU_XOR_CA_REG(CAU_BASE_PTR,6)
#define CAU_XOR_CA7                              CAU_XOR_CA_REG(CAU_BASE_PTR,7)
#define CAU_XOR_CA8                              CAU_XOR_CA_REG(CAU_BASE_PTR,8)
#define CAU_ROTL_CASR                            CAU_ROTL_CASR_REG(CAU_BASE_PTR)
#define CAU_ROTL_CAA                             CAU_ROTL_CAA_REG(CAU_BASE_PTR)
#define CAU_ROTL_CA0                             CAU_ROTL_CA_REG(CAU_BASE_PTR,0)
#define CAU_ROTL_CA1                             CAU_ROTL_CA_REG(CAU_BASE_PTR,1)
#define CAU_ROTL_CA2                             CAU_ROTL_CA_REG(CAU_BASE_PTR,2)
#define CAU_ROTL_CA3                             CAU_ROTL_CA_REG(CAU_BASE_PTR,3)
#define CAU_ROTL_CA4                             CAU_ROTL_CA_REG(CAU_BASE_PTR,4)
#define CAU_ROTL_CA5                             CAU_ROTL_CA_REG(CAU_BASE_PTR,5)
#define CAU_ROTL_CA6                             CAU_ROTL_CA_REG(CAU_BASE_PTR,6)
#define CAU_ROTL_CA7                             CAU_ROTL_CA_REG(CAU_BASE_PTR,7)
#define CAU_ROTL_CA8                             CAU_ROTL_CA_REG(CAU_BASE_PTR,8)
#define CAU_AESC_CASR                            CAU_AESC_CASR_REG(CAU_BASE_PTR)
#define CAU_AESC_CAA                             CAU_AESC_CAA_REG(CAU_BASE_PTR)
#define CAU_AESC_CA0                             CAU_AESC_CA_REG(CAU_BASE_PTR,0)
#define CAU_AESC_CA1                             CAU_AESC_CA_REG(CAU_BASE_PTR,1)
#define CAU_AESC_CA2                             CAU_AESC_CA_REG(CAU_BASE_PTR,2)
#define CAU_AESC_CA3                             CAU_AESC_CA_REG(CAU_BASE_PTR,3)
#define CAU_AESC_CA4                             CAU_AESC_CA_REG(CAU_BASE_PTR,4)
#define CAU_AESC_CA5                             CAU_AESC_CA_REG(CAU_BASE_PTR,5)
#define CAU_AESC_CA6                             CAU_AESC_CA_REG(CAU_BASE_PTR,6)
#define CAU_AESC_CA7                             CAU_AESC_CA_REG(CAU_BASE_PTR,7)
#define CAU_AESC_CA8                             CAU_AESC_CA_REG(CAU_BASE_PTR,8)
#define CAU_AESIC_CASR                           CAU_AESIC_CASR_REG(CAU_BASE_PTR)
#define CAU_AESIC_CAA                            CAU_AESIC_CAA_REG(CAU_BASE_PTR)
#define CAU_AESIC_CA0                            CAU_AESIC_CA_REG(CAU_BASE_PTR,0)
#define CAU_AESIC_CA1                            CAU_AESIC_CA_REG(CAU_BASE_PTR,1)
#define CAU_AESIC_CA2                            CAU_AESIC_CA_REG(CAU_BASE_PTR,2)
#define CAU_AESIC_CA3                            CAU_AESIC_CA_REG(CAU_BASE_PTR,3)
#define CAU_AESIC_CA4                            CAU_AESIC_CA_REG(CAU_BASE_PTR,4)
#define CAU_AESIC_CA5                            CAU_AESIC_CA_REG(CAU_BASE_PTR,5)
#define CAU_AESIC_CA6                            CAU_AESIC_CA_REG(CAU_BASE_PTR,6)
#define CAU_AESIC_CA7                            CAU_AESIC_CA_REG(CAU_BASE_PTR,7)
#define CAU_AESIC_CA8                            CAU_AESIC_CA_REG(CAU_BASE_PTR,8)
#define CAU_DIRECT0                              CAU_DIRECT_REG(CAU_BASE_PTR,0)
#define CAU_DIRECT1                              CAU_DIRECT_REG(CAU_BASE_PTR,1)
#define CAU_DIRECT2                              CAU_DIRECT_REG(CAU_BASE_PTR,2)
#define CAU_DIRECT3                              CAU_DIRECT_REG(CAU_BASE_PTR,3)
#define CAU_DIRECT4                              CAU_DIRECT_REG(CAU_BASE_PTR,4)
#define CAU_DIRECT5                              CAU_DIRECT_REG(CAU_BASE_PTR,5)
#define CAU_DIRECT6                              CAU_DIRECT_REG(CAU_BASE_PTR,6)
#define CAU_DIRECT7                              CAU_DIRECT_REG(CAU_BASE_PTR,7)
#define CAU_DIRECT8                              CAU_DIRECT_REG(CAU_BASE_PTR,8)
#define CAU_DIRECT9                              CAU_DIRECT_REG(CAU_BASE_PTR,9)
#define CAU_DIRECT10                             CAU_DIRECT_REG(CAU_BASE_PTR,10)
#define CAU_DIRECT11                             CAU_DIRECT_REG(CAU_BASE_PTR,11)
#define CAU_DIRECT12                             CAU_DIRECT_REG(CAU_BASE_PTR,12)
#define CAU_DIRECT13                             CAU_DIRECT_REG(CAU_BASE_PTR,13)
#define CAU_DIRECT14                             CAU_DIRECT_REG(CAU_BASE_PTR,14)
#define CAU_DIRECT15                             CAU_DIRECT_REG(CAU_BASE_PTR,15)

/* CAU - Register array accessors */
#define CAU_DIRECT(index)                        CAU_DIRECT_REG(CAU_BASE_PTR,index)
#define CAU_LDR_CA(index)                        CAU_LDR_CA_REG(CAU_BASE_PTR,index)
#define CAU_STR_CA(index)                        CAU_STR_CA_REG(CAU_BASE_PTR,index)
#define CAU_ADR_CA(index)                        CAU_ADR_CA_REG(CAU_BASE_PTR,index)
#define CAU_RADR_CA(index)                       CAU_RADR_CA_REG(CAU_BASE_PTR,index)
#define CAU_XOR_CA(index)                        CAU_XOR_CA_REG(CAU_BASE_PTR,index)
#define CAU_ROTL_CA(index)                       CAU_ROTL_CA_REG(CAU_BASE_PTR,index)
#define CAU_AESC_CA(index)                       CAU_AESC_CA_REG(CAU_BASE_PTR,index)
#define CAU_AESIC_CA(index)                      CAU_AESIC_CA_REG(CAU_BASE_PTR,index)

/**
 * @}
 */ /* end of group CAU_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CAU_Peripheral */


/* ----------------------------------------------------------------------------
   -- CMP
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMP_Peripheral CMP
 * @{
 */

/** CMP - Peripheral register structure */
typedef struct CMP_MemMap {
  uint8_t CR0;                                     /**< CMP Control Register 0, offset: 0x0 */
  uint8_t CR1;                                     /**< CMP Control Register 1, offset: 0x1 */
  uint8_t FPR;                                     /**< CMP Filter Period Register, offset: 0x2 */
  uint8_t SCR;                                     /**< CMP Status and Control Register, offset: 0x3 */
  uint8_t DACCR;                                   /**< DAC Control Register, offset: 0x4 */
  uint8_t MUXCR;                                   /**< MUX Control Register, offset: 0x5 */
} volatile *CMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register accessors */
#define CMP_CR0_REG(base)                        ((base)->CR0)
#define CMP_CR1_REG(base)                        ((base)->CR1)
#define CMP_FPR_REG(base)                        ((base)->FPR)
#define CMP_SCR_REG(base)                        ((base)->SCR)
#define CMP_DACCR_REG(base)                      ((base)->DACCR)
#define CMP_MUXCR_REG(base)                      ((base)->MUXCR)

/**
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base pointer */
#define CMP0_BASE_PTR                            ((CMP_MemMapPtr)0x40073000u)
/** Peripheral CMP1 base pointer */
#define CMP1_BASE_PTR                            ((CMP_MemMapPtr)0x40073008u)
/** Peripheral CMP2 base pointer */
#define CMP2_BASE_PTR                            ((CMP_MemMapPtr)0x40073010u)

/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register instance definitions */
/* CMP0 */
#define CMP0_CR0                                 CMP_CR0_REG(CMP0_BASE_PTR)
#define CMP0_CR1                                 CMP_CR1_REG(CMP0_BASE_PTR)
#define CMP0_FPR                                 CMP_FPR_REG(CMP0_BASE_PTR)
#define CMP0_SCR                                 CMP_SCR_REG(CMP0_BASE_PTR)
#define CMP0_DACCR                               CMP_DACCR_REG(CMP0_BASE_PTR)
#define CMP0_MUXCR                               CMP_MUXCR_REG(CMP0_BASE_PTR)
/* CMP1 */
#define CMP1_CR0                                 CMP_CR0_REG(CMP1_BASE_PTR)
#define CMP1_CR1                                 CMP_CR1_REG(CMP1_BASE_PTR)
#define CMP1_FPR                                 CMP_FPR_REG(CMP1_BASE_PTR)
#define CMP1_SCR                                 CMP_SCR_REG(CMP1_BASE_PTR)
#define CMP1_DACCR                               CMP_DACCR_REG(CMP1_BASE_PTR)
#define CMP1_MUXCR                               CMP_MUXCR_REG(CMP1_BASE_PTR)
/* CMP2 */
#define CMP2_CR0                                 CMP_CR0_REG(CMP2_BASE_PTR)
#define CMP2_CR1                                 CMP_CR1_REG(CMP2_BASE_PTR)
#define CMP2_FPR                                 CMP_FPR_REG(CMP2_BASE_PTR)
#define CMP2_SCR                                 CMP_SCR_REG(CMP2_BASE_PTR)
#define CMP2_DACCR                               CMP_DACCR_REG(CMP2_BASE_PTR)
#define CMP2_MUXCR                               CMP_MUXCR_REG(CMP2_BASE_PTR)

/**
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CMP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register instance definitions */
/* CMP0 */
#define CMP0_CR0                                 CMP_CR0_REG(CMP0_BASE_PTR)
#define CMP0_CR1                                 CMP_CR1_REG(CMP0_BASE_PTR)
#define CMP0_FPR                                 CMP_FPR_REG(CMP0_BASE_PTR)
#define CMP0_SCR                                 CMP_SCR_REG(CMP0_BASE_PTR)
#define CMP0_DACCR                               CMP_DACCR_REG(CMP0_BASE_PTR)
#define CMP0_MUXCR                               CMP_MUXCR_REG(CMP0_BASE_PTR)

/**
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CMP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CMT
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMT_Peripheral CMT
 * @{
 */

/** CMT - Peripheral register structure */
typedef struct CMT_MemMap {
  uint8_t CGH1;                                    /**< CMT Carrier Generator High Data Register 1, offset: 0x0 */
  uint8_t CGL1;                                    /**< CMT Carrier Generator Low Data Register 1, offset: 0x1 */
  uint8_t CGH2;                                    /**< CMT Carrier Generator High Data Register 2, offset: 0x2 */
  uint8_t CGL2;                                    /**< CMT Carrier Generator Low Data Register 2, offset: 0x3 */
  uint8_t OC;                                      /**< CMT Output Control Register, offset: 0x4 */
  uint8_t MSC;                                     /**< CMT Modulator Status and Control Register, offset: 0x5 */
  uint8_t CMD1;                                    /**< CMT Modulator Data Register Mark High, offset: 0x6 */
  uint8_t CMD2;                                    /**< CMT Modulator Data Register Mark Low, offset: 0x7 */
  uint8_t CMD3;                                    /**< CMT Modulator Data Register Space High, offset: 0x8 */
  uint8_t CMD4;                                    /**< CMT Modulator Data Register Space Low, offset: 0x9 */
  uint8_t PPS;                                     /**< CMT Primary Prescaler Register, offset: 0xA */
  uint8_t DMA;                                     /**< CMT Direct Memory Access, offset: 0xB */
} volatile *CMT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CMT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMT_Register_Accessor_Macros CMT - Register accessor macros
 * @{
 */


/* CMT - Register accessors */
#define CMT_CGH1_REG(base)                       ((base)->CGH1)
#define CMT_CGL1_REG(base)                       ((base)->CGL1)
#define CMT_CGH2_REG(base)                       ((base)->CGH2)
#define CMT_CGL2_REG(base)                       ((base)->CGL2)
#define CMT_OC_REG(base)                         ((base)->OC)
#define CMT_MSC_REG(base)                        ((base)->MSC)
#define CMT_CMD1_REG(base)                       ((base)->CMD1)
#define CMT_CMD2_REG(base)                       ((base)->CMD2)
#define CMT_CMD3_REG(base)                       ((base)->CMD3)
#define CMT_CMD4_REG(base)                       ((base)->CMD4)
#define CMT_PPS_REG(base)                        ((base)->PPS)
#define CMT_DMA_REG(base)                        ((base)->DMA)

/**
 * @}
 */ /* end of group CMT_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CMT_Register_Masks */


/* CMT - Peripheral instance base addresses */
/** Peripheral CMT base pointer */
#define CMT_BASE_PTR                             ((CMT_MemMapPtr)0x40062000u)

/* ----------------------------------------------------------------------------
   -- CMT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CMT_Register_Accessor_Macros CMT - Register accessor macros
 * @{
 */


/* CMT - Register instance definitions */
/* CMT */
#define CMT_CGH1                                 CMT_CGH1_REG(CMT_BASE_PTR)
#define CMT_CGL1                                 CMT_CGL1_REG(CMT_BASE_PTR)
#define CMT_CGH2                                 CMT_CGH2_REG(CMT_BASE_PTR)
#define CMT_CGL2                                 CMT_CGL2_REG(CMT_BASE_PTR)
#define CMT_OC                                   CMT_OC_REG(CMT_BASE_PTR)
#define CMT_MSC                                  CMT_MSC_REG(CMT_BASE_PTR)
#define CMT_CMD1                                 CMT_CMD1_REG(CMT_BASE_PTR)
#define CMT_CMD2                                 CMT_CMD2_REG(CMT_BASE_PTR)
#define CMT_CMD3                                 CMT_CMD3_REG(CMT_BASE_PTR)
#define CMT_CMD4                                 CMT_CMD4_REG(CMT_BASE_PTR)
#define CMT_PPS                                  CMT_PPS_REG(CMT_BASE_PTR)
#define CMT_DMA                                  CMT_DMA_REG(CMT_BASE_PTR)

/**
 * @}
 */ /* end of group CMT_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CMT_Peripheral */


/* ----------------------------------------------------------------------------
   -- CRC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Peripheral CRC
 * @{
 */

/** CRC - Peripheral register structure */
typedef struct CRC_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t CRC;                                    /**< CRC Data Register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint16_t CRCL;                                   /**< CRC_CRCL register., offset: 0x0 */
      uint16_t CRCH;                                   /**< CRC_CRCH register., offset: 0x2 */
    } ACCESS16BIT;
    struct {                                         /* offset: 0x0 */
      uint8_t CRCLL;                                   /**< CRC_CRCLL register., offset: 0x0 */
      uint8_t CRCLU;                                   /**< CRC_CRCLU register., offset: 0x1 */
      uint8_t CRCHL;                                   /**< CRC_CRCHL register., offset: 0x2 */
      uint8_t CRCHU;                                   /**< CRC_CRCHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    uint32_t GPOLY;                                  /**< CRC Polynomial Register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint16_t GPOLYL;                                 /**< CRC_GPOLYL register., offset: 0x4 */
      uint16_t GPOLYH;                                 /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    struct {                                         /* offset: 0x4 */
      uint8_t GPOLYLL;                                 /**< CRC_GPOLYLL register., offset: 0x4 */
      uint8_t GPOLYLU;                                 /**< CRC_GPOLYLU register., offset: 0x5 */
      uint8_t GPOLYHL;                                 /**< CRC_GPOLYHL register., offset: 0x6 */
      uint8_t GPOLYHU;                                 /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    uint32_t CTRL;                                   /**< CRC Control Register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
      uint8_t RESERVED_0[3];
      uint8_t CTRLHU;                                  /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} volatile *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register accessors */
#define CRC_CRC_REG(base)                        ((base)->CRC)
#define CRC_CRCL_REG(base)                       ((base)->ACCESS16BIT.CRCL)
#define CRC_CRCH_REG(base)                       ((base)->ACCESS16BIT.CRCH)
#define CRC_CRCLL_REG(base)                      ((base)->ACCESS8BIT.CRCLL)
#define CRC_CRCLU_REG(base)                      ((base)->ACCESS8BIT.CRCLU)
#define CRC_CRCHL_REG(base)                      ((base)->ACCESS8BIT.CRCHL)
#define CRC_CRCHU_REG(base)                      ((base)->ACCESS8BIT.CRCHU)
#define CRC_GPOLY_REG(base)                      ((base)->GPOLY)
#define CRC_GPOLYL_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYL)
#define CRC_GPOLYH_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYH)
#define CRC_GPOLYLL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLL)
#define CRC_GPOLYLU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLU)
#define CRC_GPOLYHL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHL)
#define CRC_GPOLYHU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHU)
#define CRC_CTRL_REG(base)                       ((base)->CTRL)
#define CRC_CTRLHU_REG(base)                     ((base)->CTRL_ACCESS8BIT.CTRLHU)

/**
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base pointer */
#define CRC_BASE_PTR                             ((CRC_MemMapPtr)0x40032000u)

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register instance definitions */
/* CRC */
#define CRC_CRC                                  CRC_CRC_REG(CRC_BASE_PTR)
#define CRC_GPOLY                                CRC_GPOLY_REG(CRC_BASE_PTR)
#define CRC_CTRL                                 CRC_CTRL_REG(CRC_BASE_PTR)
#define CRC_CRCL                                 CRC_CRCL_REG(CRC_BASE_PTR)
#define CRC_CRCH                                 CRC_CRCH_REG(CRC_BASE_PTR)
#define CRC_CRCLL                                CRC_CRCLL_REG(CRC_BASE_PTR)
#define CRC_CRCLU                                CRC_CRCLU_REG(CRC_BASE_PTR)
#define CRC_CRCHL                                CRC_CRCHL_REG(CRC_BASE_PTR)
#define CRC_CRCHU                                CRC_CRCHU_REG(CRC_BASE_PTR)
#define CRC_GPOLYL                               CRC_GPOLYL_REG(CRC_BASE_PTR)
#define CRC_GPOLYH                               CRC_GPOLYH_REG(CRC_BASE_PTR)
#define CRC_GPOLYLL                              CRC_GPOLYLL_REG(CRC_BASE_PTR)
#define CRC_GPOLYLU                              CRC_GPOLYLU_REG(CRC_BASE_PTR)
#define CRC_GPOLYHL                              CRC_GPOLYHL_REG(CRC_BASE_PTR)
#define CRC_GPOLYHU                              CRC_GPOLYHU_REG(CRC_BASE_PTR)
#define CRC_CTRLHU                               CRC_CTRLHU_REG(CRC_BASE_PTR)

/**
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CRC_Peripheral */


/* ----------------------------------------------------------------------------
   -- CoreDebug
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CoreDebug_Peripheral CoreDebug
 * @{
 */

/** CoreDebug - Peripheral register structure */
typedef struct CoreDebug_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t base_DHCSR_Read;                        /**< Debug Halting Control and Status Register, offset: 0x0 */
    uint32_t base_DHCSR_Write;                       /**< Debug Halting Control and Status Register, offset: 0x0 */
  };
  uint32_t base_DCRSR;                             /**< Debug Core Register Selector Register, offset: 0x4 */
  uint32_t base_DCRDR;                             /**< Debug Core Register Data Register, offset: 0x8 */
  uint32_t base_DEMCR;                             /**< Debug Exception and Monitor Control Register, offset: 0xC */
} volatile *CoreDebug_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register accessors */
#define CoreDebug_base_DHCSR_Read_REG(base)      ((base)->base_DHCSR_Read)
#define CoreDebug_base_DHCSR_Write_REG(base)     ((base)->base_DHCSR_Write)
#define CoreDebug_base_DCRSR_REG(base)           ((base)->base_DCRSR)
#define CoreDebug_base_DCRDR_REG(base)           ((base)->base_DCRDR)
#define CoreDebug_base_DEMCR_REG(base)           ((base)->base_DEMCR)

/**
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/* CoreDebug - Peripheral instance base addresses */
/** Peripheral CoreDebug base pointer */
#define CoreDebug_BASE_PTR                       ((CoreDebug_MemMapPtr)0xE000EDF0u)
/** Array initializer of CoreDebug peripheral base pointers */
#define CoreDebug_BASE_PTRS                      { CoreDebug_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register instance definitions */
/* CoreDebug */
#define DHCSR_Read                               CoreDebug_base_DHCSR_Read_REG(CoreDebug_BASE_PTR)
#define DHCSR_Write                              CoreDebug_base_DHCSR_Write_REG(CoreDebug_BASE_PTR)
#define DCRSR                                    CoreDebug_base_DCRSR_REG(CoreDebug_BASE_PTR)
#define DCRDR                                    CoreDebug_base_DCRDR_REG(CoreDebug_BASE_PTR)
#define DEMCR                                    CoreDebug_base_DEMCR_REG(CoreDebug_BASE_PTR)

/**
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CoreDebug_Peripheral */


/* ----------------------------------------------------------------------------
   -- DAC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DAC_Peripheral DAC
 * @{
 */

/** DAC - Peripheral register structure */
typedef struct DAC_MemMap {
  struct {                                         /* offset: 0x0, array step: 0x2 */
    uint8_t DATL;                                    /**< DAC Data Low Register, array offset: 0x0, array step: 0x2 */
    uint8_t DATH;                                    /**< DAC Data High Register, array offset: 0x1, array step: 0x2 */
  } DAT[2];
  uint8_t RESERVED_0[28];
  uint8_t SR;                                      /**< DAC Status Register, offset: 0x20 */
  uint8_t C0;                                      /**< DAC Control Register, offset: 0x21 */
  uint8_t C1;                                      /**< DAC Control Register 1, offset: 0x22 */
  uint8_t C2;                                      /**< DAC Control Register 2, offset: 0x23 */
} volatile *DAC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DAC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DAC_Register_Accessor_Macros DAC - Register accessor macros
 * @{
 */


/* DAC - Register accessors */
#define DAC_DATL_REG(base,index)                 ((base)->DAT[index].DATL)
#define DAC_DATH_REG(base,index)                 ((base)->DAT[index].DATH)
#define DAC_SR_REG(base)                         ((base)->SR)
#define DAC_C0_REG(base)                         ((base)->C0)
#define DAC_C1_REG(base)                         ((base)->C1)
#define DAC_C2_REG(base)                         ((base)->C2)

/**
 * @}
 */ /* end of group DAC_Register_Accessor_Macros */

/* DAC - Peripheral instance base addresses */
/** Peripheral DAC0 base pointer */
#define DAC0_BASE_PTR                            ((DAC_MemMapPtr)0x400CC000u)
/** Peripheral DAC1 base pointer */
#define DAC1_BASE_PTR                            ((DAC_MemMapPtr)0x400CD000u)

/* ----------------------------------------------------------------------------
   -- DAC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DAC_Register_Accessor_Macros DAC - Register accessor macros
 * @{
 */


/* DAC - Register instance definitions */
/* DAC0 */
#define DAC0_DAT0L                               DAC_DATL_REG(DAC0_BASE_PTR,0)
#define DAC0_DAT0H                               DAC_DATH_REG(DAC0_BASE_PTR,0)
#define DAC0_DAT1L                               DAC_DATL_REG(DAC0_BASE_PTR,1)
#define DAC0_DAT1H                               DAC_DATH_REG(DAC0_BASE_PTR,1)
#define DAC0_SR                                  DAC_SR_REG(DAC0_BASE_PTR)
#define DAC0_C0                                  DAC_C0_REG(DAC0_BASE_PTR)
#define DAC0_C1                                  DAC_C1_REG(DAC0_BASE_PTR)
#define DAC0_C2                                  DAC_C2_REG(DAC0_BASE_PTR)

/* DAC - Register array accessors */
#define DAC0_DATL(index)                         DAC_DATL_REG(DAC0_BASE_PTR,index)
#define DAC0_DATH(index)                         DAC_DATH_REG(DAC0_BASE_PTR,index)

/**
 * @}
 */ /* end of group DAC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group DAC_Peripheral */


/* ----------------------------------------------------------------------------
   -- DMA
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMA_Peripheral DMA
 * @{
 */

/** DMA - Peripheral register structure */
typedef struct DMA_MemMap {
  uint32_t CR;                                     /**< Control Register, offset: 0x0 */
  uint32_t ES;                                     /**< Error Status Register, offset: 0x4 */
  uint8_t RESERVED_0[4];
  uint32_t ERQ;                                    /**< Enable Request Register, offset: 0xC */
  uint8_t RESERVED_1[4];
  uint32_t EEI;                                    /**< Enable Error Interrupt Register, offset: 0x14 */
  uint8_t CEEI;                                    /**< Clear Enable Error Interrupt Register, offset: 0x18 */
  uint8_t SEEI;                                    /**< Set Enable Error Interrupt Register, offset: 0x19 */
  uint8_t CERQ;                                    /**< Clear Enable Request Register, offset: 0x1A */
  uint8_t SERQ;                                    /**< Set Enable Request Register, offset: 0x1B */
  uint8_t CDNE;                                    /**< Clear DONE Status Bit Register, offset: 0x1C */
  uint8_t SSRT;                                    /**< Set START Bit Register, offset: 0x1D */
  uint8_t CERR;                                    /**< Clear Error Register, offset: 0x1E */
  uint8_t CINT;                                    /**< Clear Interrupt Request Register, offset: 0x1F */
  uint8_t RESERVED_2[4];
  uint32_t INT;                                    /**< Interrupt Request Register, offset: 0x24 */
  uint8_t RESERVED_3[4];
  uint32_t ERR;                                    /**< Error Register, offset: 0x2C */
  uint8_t RESERVED_4[4];
  uint32_t HRS;                                    /**< Hardware Request Status Register, offset: 0x34 */
  uint8_t RESERVED_5[200];
  uint8_t DCHPRI3;                                 /**< Channel n Priority Register, offset: 0x100 */
  uint8_t DCHPRI2;                                 /**< Channel n Priority Register, offset: 0x101 */
  uint8_t DCHPRI1;                                 /**< Channel n Priority Register, offset: 0x102 */
  uint8_t DCHPRI0;                                 /**< Channel n Priority Register, offset: 0x103 */
  uint8_t DCHPRI7;                                 /**< Channel n Priority Register, offset: 0x104 */
  uint8_t DCHPRI6;                                 /**< Channel n Priority Register, offset: 0x105 */
  uint8_t DCHPRI5;                                 /**< Channel n Priority Register, offset: 0x106 */
  uint8_t DCHPRI4;                                 /**< Channel n Priority Register, offset: 0x107 */
  uint8_t DCHPRI11;                                /**< Channel n Priority Register, offset: 0x108 */
  uint8_t DCHPRI10;                                /**< Channel n Priority Register, offset: 0x109 */
  uint8_t DCHPRI9;                                 /**< Channel n Priority Register, offset: 0x10A */
  uint8_t DCHPRI8;                                 /**< Channel n Priority Register, offset: 0x10B */
  uint8_t DCHPRI15;                                /**< Channel n Priority Register, offset: 0x10C */
  uint8_t DCHPRI14;                                /**< Channel n Priority Register, offset: 0x10D */
  uint8_t DCHPRI13;                                /**< Channel n Priority Register, offset: 0x10E */
  uint8_t DCHPRI12;                                /**< Channel n Priority Register, offset: 0x10F */
  uint8_t RESERVED_6[3824];
  struct {                                         /* offset: 0x1000, array step: 0x20 */
    uint32_t SADDR;                                  /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    uint16_t SOFF;                                   /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
    uint16_t ATTR;                                   /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
    union {                                          /* offset: 0x1008, array step: 0x20 */
      uint32_t NBYTES_MLNO;                            /**< TCD Minor Byte Count (Minor Loop Disabled), array offset: 0x1008, array step: 0x20 */
      uint32_t NBYTES_MLOFFNO;                         /**< TCD Signed Minor Loop Offset (Minor Loop Enabled and Offset Disabled), array offset: 0x1008, array step: 0x20 */
      uint32_t NBYTES_MLOFFYES;                        /**< TCD Signed Minor Loop Offset (Minor Loop and Offset Enabled), array offset: 0x1008, array step: 0x20 */
    };
    uint32_t SLAST;                                  /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    uint32_t DADDR;                                  /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    uint16_t DOFF;                                   /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
    union {                                          /* offset: 0x1016, array step: 0x20 */
      uint16_t CITER_ELINKYES;                         /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x1016, array step: 0x20 */
      uint16_t CITER_ELINKNO;                          /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
    };
    uint32_t DLAST_SGA;                              /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    uint16_t CSR;                                    /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
    union {                                          /* offset: 0x101E, array step: 0x20 */
      uint16_t BITER_ELINKNO;                          /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
      uint16_t BITER_ELINKYES;                         /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x101E, array step: 0x20 */
    };
  } TCD[16];
} volatile *DMA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register accessors */
#define DMA_CR_REG(base)                         ((base)->CR)
#define DMA_ES_REG(base)                         ((base)->ES)
#define DMA_ERQ_REG(base)                        ((base)->ERQ)
#define DMA_EEI_REG(base)                        ((base)->EEI)
#define DMA_CEEI_REG(base)                       ((base)->CEEI)
#define DMA_SEEI_REG(base)                       ((base)->SEEI)
#define DMA_CERQ_REG(base)                       ((base)->CERQ)
#define DMA_SERQ_REG(base)                       ((base)->SERQ)
#define DMA_CDNE_REG(base)                       ((base)->CDNE)
#define DMA_SSRT_REG(base)                       ((base)->SSRT)
#define DMA_CERR_REG(base)                       ((base)->CERR)
#define DMA_CINT_REG(base)                       ((base)->CINT)
#define DMA_INT_REG(base)                        ((base)->INT)
#define DMA_ERR_REG(base)                        ((base)->ERR)
#define DMA_HRS_REG(base)                        ((base)->HRS)
#define DMA_DCHPRI3_REG(base)                    ((base)->DCHPRI3)
#define DMA_DCHPRI2_REG(base)                    ((base)->DCHPRI2)
#define DMA_DCHPRI1_REG(base)                    ((base)->DCHPRI1)
#define DMA_DCHPRI0_REG(base)                    ((base)->DCHPRI0)
#define DMA_DCHPRI7_REG(base)                    ((base)->DCHPRI7)
#define DMA_DCHPRI6_REG(base)                    ((base)->DCHPRI6)
#define DMA_DCHPRI5_REG(base)                    ((base)->DCHPRI5)
#define DMA_DCHPRI4_REG(base)                    ((base)->DCHPRI4)
#define DMA_DCHPRI11_REG(base)                   ((base)->DCHPRI11)
#define DMA_DCHPRI10_REG(base)                   ((base)->DCHPRI10)
#define DMA_DCHPRI9_REG(base)                    ((base)->DCHPRI9)
#define DMA_DCHPRI8_REG(base)                    ((base)->DCHPRI8)
#define DMA_DCHPRI15_REG(base)                   ((base)->DCHPRI15)
#define DMA_DCHPRI14_REG(base)                   ((base)->DCHPRI14)
#define DMA_DCHPRI13_REG(base)                   ((base)->DCHPRI13)
#define DMA_DCHPRI12_REG(base)                   ((base)->DCHPRI12)
#define DMA_SADDR_REG(base,index)                ((base)->TCD[index].SADDR)
#define DMA_SOFF_REG(base,index)                 ((base)->TCD[index].SOFF)
#define DMA_ATTR_REG(base,index)                 ((base)->TCD[index].ATTR)
#define DMA_NBYTES_MLNO_REG(base,index)          ((base)->TCD[index].NBYTES_MLNO)
#define DMA_NBYTES_MLOFFNO_REG(base,index)       ((base)->TCD[index].NBYTES_MLOFFNO)
#define DMA_NBYTES_MLOFFYES_REG(base,index)      ((base)->TCD[index].NBYTES_MLOFFYES)
#define DMA_SLAST_REG(base,index)                ((base)->TCD[index].SLAST)
#define DMA_DADDR_REG(base,index)                ((base)->TCD[index].DADDR)
#define DMA_DOFF_REG(base,index)                 ((base)->TCD[index].DOFF)
#define DMA_CITER_ELINKYES_REG(base,index)       ((base)->TCD[index].CITER_ELINKYES)
#define DMA_CITER_ELINKNO_REG(base,index)        ((base)->TCD[index].CITER_ELINKNO)
#define DMA_DLAST_SGA_REG(base,index)            ((base)->TCD[index].DLAST_SGA)
#define DMA_CSR_REG(base,index)                  ((base)->TCD[index].CSR)
#define DMA_BITER_ELINKNO_REG(base,index)        ((base)->TCD[index].BITER_ELINKNO)
#define DMA_BITER_ELINKYES_REG(base,index)       ((base)->TCD[index].BITER_ELINKYES)

/**
 * @}
 */ /* end of group DMA_Register_Accessor_Macros */



/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base pointer */
#define DMA_BASE_PTR                             ((DMA_MemMapPtr)0x40008000u)
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register instance definitions */
/* DMA */
#define DMA_CR                                   DMA_CR_REG(DMA_BASE_PTR)
#define DMA_ES                                   DMA_ES_REG(DMA_BASE_PTR)
#define DMA_ERQ                                  DMA_ERQ_REG(DMA_BASE_PTR)
#define DMA_EEI                                  DMA_EEI_REG(DMA_BASE_PTR)
#define DMA_CEEI                                 DMA_CEEI_REG(DMA_BASE_PTR)
#define DMA_SEEI                                 DMA_SEEI_REG(DMA_BASE_PTR)
#define DMA_CERQ                                 DMA_CERQ_REG(DMA_BASE_PTR)
#define DMA_SERQ                                 DMA_SERQ_REG(DMA_BASE_PTR)
#define DMA_CDNE                                 DMA_CDNE_REG(DMA_BASE_PTR)
#define DMA_SSRT                                 DMA_SSRT_REG(DMA_BASE_PTR)
#define DMA_CERR                                 DMA_CERR_REG(DMA_BASE_PTR)
#define DMA_CINT                                 DMA_CINT_REG(DMA_BASE_PTR)
#define DMA_INT                                  DMA_INT_REG(DMA_BASE_PTR)
#define DMA_ERR                                  DMA_ERR_REG(DMA_BASE_PTR)
#define DMA_HRS                                  DMA_HRS_REG(DMA_BASE_PTR)
#define DMA_DCHPRI0                              DMA_DCHPRI0_REG(DMA_BASE_PTR)
#define DMA_DCHPRI1                              DMA_DCHPRI1_REG(DMA_BASE_PTR)
#define DMA_DCHPRI2                              DMA_DCHPRI2_REG(DMA_BASE_PTR)
#define DMA_DCHPRI3                              DMA_DCHPRI3_REG(DMA_BASE_PTR)
#define DMA_DCHPRI4                              DMA_DCHPRI4_REG(DMA_BASE_PTR)
#define DMA_DCHPRI5                              DMA_DCHPRI5_REG(DMA_BASE_PTR)
#define DMA_DCHPRI6                              DMA_DCHPRI6_REG(DMA_BASE_PTR)
#define DMA_DCHPRI7                              DMA_DCHPRI7_REG(DMA_BASE_PTR)
#define DMA_DCHPRI8                              DMA_DCHPRI8_REG(DMA_BASE_PTR)
#define DMA_DCHPRI9                              DMA_DCHPRI9_REG(DMA_BASE_PTR)
#define DMA_DCHPRI10                             DMA_DCHPRI10_REG(DMA_BASE_PTR)
#define DMA_DCHPRI11                             DMA_DCHPRI11_REG(DMA_BASE_PTR)
#define DMA_DCHPRI12                             DMA_DCHPRI12_REG(DMA_BASE_PTR)
#define DMA_DCHPRI13                             DMA_DCHPRI13_REG(DMA_BASE_PTR)
#define DMA_DCHPRI14                             DMA_DCHPRI14_REG(DMA_BASE_PTR)
#define DMA_DCHPRI15                             DMA_DCHPRI15_REG(DMA_BASE_PTR)
#define DMA_TCD0_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_CSR                             DMA_CSR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,0)
#define DMA_TCD1_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_CSR                             DMA_CSR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD2_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_CSR                             DMA_CSR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,2)
#define DMA_TCD3_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_CSR                             DMA_CSR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,3)
#define DMA_TCD4_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_CSR                             DMA_CSR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,4)
#define DMA_TCD5_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_CSR                             DMA_CSR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,5)
#define DMA_TCD6_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_CSR                             DMA_CSR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,6)
#define DMA_TCD7_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_CSR                             DMA_CSR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,7)
#define DMA_TCD8_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_CSR                             DMA_CSR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD9_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_CSR                             DMA_CSR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,9)
#define DMA_TCD10_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_CSR                            DMA_CSR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD11_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_CSR                            DMA_CSR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,11)
#define DMA_TCD12_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_CSR                            DMA_CSR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD13_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_CSR                            DMA_CSR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD14_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_CSR                            DMA_CSR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD15_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_CSR                            DMA_CSR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,15)

/* DMA - Register array accessors */
#define DMA_SADDR(index)                         DMA_SADDR_REG(DMA_BASE_PTR,index)
#define DMA_SOFF(index)                          DMA_SOFF_REG(DMA_BASE_PTR,index)
#define DMA_ATTR(index)                          DMA_ATTR_REG(DMA_BASE_PTR,index)
#define DMA_NBYTES_MLNO(index)                   DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,index)
#define DMA_NBYTES_MLOFFNO(index)                DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,index)
#define DMA_NBYTES_MLOFFYES(index)               DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,index)
#define DMA_SLAST(index)                         DMA_SLAST_REG(DMA_BASE_PTR,index)
#define DMA_DADDR(index)                         DMA_DADDR_REG(DMA_BASE_PTR,index)
#define DMA_DOFF(index)                          DMA_DOFF_REG(DMA_BASE_PTR,index)
#define DMA_CITER_ELINKYES(index)                DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,index)
#define DMA_CITER_ELINKNO(index)                 DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,index)
#define DMA_DLAST_SGA(index)                     DMA_DLAST_SGA_REG(DMA_BASE_PTR,index)
#define DMA_CSR(index)                           DMA_CSR_REG(DMA_BASE_PTR,index)
#define DMA_BITER_ELINKNO(index)                 DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,index)
#define DMA_BITER_ELINKYES(index)                DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,index)

/**
 * @}
 */ /* end of group DMA_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group DMA_Peripheral */


/* ----------------------------------------------------------------------------
   -- DMAMUX
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMAMUX_Peripheral DMAMUX
 * @{
 */

/** DMAMUX - Peripheral register structure */
typedef struct DMAMUX_MemMap {
  uint8_t CHCFG[4];                                /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
} volatile *DMAMUX_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMAMUX - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMAMUX_Register_Accessor_Macros DMAMUX - Register accessor macros
 * @{
 */


/* DMAMUX - Register accessors */
#define DMAMUX_CHCFG_REG(base,index)             ((base)->CHCFG[index])

/**
 * @}
 */ /* end of group DMAMUX_Register_Accessor_Macros */


/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX0 base pointer */
#define DMAMUX_BASE_PTR                         ((DMAMUX_MemMapPtr)0x40021000u)
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         { DMAMUX_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- DMAMUX - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMAMUX_Register_Accessor_Macros DMAMUX - Register accessor macros
 * @{
 */


/* DMAMUX - Register instance definitions */
/* DMAMUX0 */
#define DMAMUX_CHCFG0                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,0)
#define DMAMUX_CHCFG1                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,1)
#define DMAMUX_CHCFG2                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,2)
#define DMAMUX_CHCFG3                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,3)
#define DMAMUX_CHCFG4                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,4)
#define DMAMUX_CHCFG5                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,5)
#define DMAMUX_CHCFG6                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,6)
#define DMAMUX_CHCFG7                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,7)
#define DMAMUX_CHCFG8                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,8)
#define DMAMUX_CHCFG9                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,9)
#define DMAMUX_CHCFG10                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,10)
#define DMAMUX_CHCFG11                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,11)
#define DMAMUX_CHCFG12                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,12)
#define DMAMUX_CHCFG13                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,13)
#define DMAMUX_CHCFG14                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,14)
#define DMAMUX_CHCFG15                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,15)

/* DMAMUX - Register array accessors */
#define DMAMUX_CHCFG(index)                      DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,index)

/**
 * @}
 */ /* end of group DMAMUX_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group DMAMUX_Peripheral */


/* ----------------------------------------------------------------------------
   -- DWT
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DWT_Peripheral DWT
 * @{
 */

/** DWT - Peripheral register structure */
typedef struct DWT_MemMap {
  uint32_t CTRL;                                   /**< Control Register, offset: 0x0 */
  uint32_t CYCCNT;                                 /**< Cycle Count Register, offset: 0x4 */
  uint32_t CPICNT;                                 /**< CPI Count Register, offset: 0x8 */
  uint32_t EXCCNT;                                 /**< Exception Overhead Count Register, offset: 0xC */
  uint32_t SLEEPCNT;                               /**< Sleep Count Register, offset: 0x10 */
  uint32_t LSUCNT;                                 /**< LSU Count Register, offset: 0x14 */
  uint32_t FOLDCNT;                                /**< Folded-instruction Count Register, offset: 0x18 */
  uint32_t PCSR;                                   /**< Program Counter Sample Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< Comparator Register 0..Comparator Register 3, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< Mask Register 0..Mask Register 3, array offset: 0x24, array step: 0x10 */
    uint32_t FUNCTION;                               /**< Function Register 0..Function Register 3, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[4];
  uint8_t RESERVED_0[3952];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *DWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register accessors */
#define DWT_CTRL_REG(base)                       ((base)->CTRL)
#define DWT_CYCCNT_REG(base)                     ((base)->CYCCNT)
#define DWT_CPICNT_REG(base)                     ((base)->CPICNT)
#define DWT_EXCCNT_REG(base)                     ((base)->EXCCNT)
#define DWT_SLEEPCNT_REG(base)                   ((base)->SLEEPCNT)
#define DWT_LSUCNT_REG(base)                     ((base)->LSUCNT)
#define DWT_FOLDCNT_REG(base)                    ((base)->FOLDCNT)
#define DWT_PCSR_REG(base)                       ((base)->PCSR)
#define DWT_COMP_REG(base,index)                 ((base)->COMPARATOR[index].COMP)
#define DWT_MASK_REG(base,index)                 ((base)->COMPARATOR[index].MASK)
#define DWT_FUNCTION_REG(base,index)             ((base)->COMPARATOR[index].FUNCTION)
#define DWT_PID4_REG(base)                       ((base)->PID4)
#define DWT_PID5_REG(base)                       ((base)->PID5)
#define DWT_PID6_REG(base)                       ((base)->PID6)
#define DWT_PID7_REG(base)                       ((base)->PID7)
#define DWT_PID0_REG(base)                       ((base)->PID0)
#define DWT_PID1_REG(base)                       ((base)->PID1)
#define DWT_PID2_REG(base)                       ((base)->PID2)
#define DWT_PID3_REG(base)                       ((base)->PID3)
#define DWT_CID0_REG(base)                       ((base)->CID0)
#define DWT_CID1_REG(base)                       ((base)->CID1)
#define DWT_CID2_REG(base)                       ((base)->CID2)
#define DWT_CID3_REG(base)                       ((base)->CID3)

/**
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/* DWT - Peripheral instance base addresses */
/** Peripheral DWT base pointer */
#define DWT_BASE_PTR                             ((DWT_MemMapPtr)0xE0001000u)
/** Array initializer of DWT peripheral base pointers */
#define DWT_BASE_PTRS                            { DWT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register instance definitions */
/* DWT */
#define DWT_CTRL                                 DWT_CTRL_REG(DWT_BASE_PTR)
#define DWT_CYCCNT                               DWT_CYCCNT_REG(DWT_BASE_PTR)
#define DWT_CPICNT                               DWT_CPICNT_REG(DWT_BASE_PTR)
#define DWT_EXCCNT                               DWT_EXCCNT_REG(DWT_BASE_PTR)
#define DWT_SLEEPCNT                             DWT_SLEEPCNT_REG(DWT_BASE_PTR)
#define DWT_LSUCNT                               DWT_LSUCNT_REG(DWT_BASE_PTR)
#define DWT_FOLDCNT                              DWT_FOLDCNT_REG(DWT_BASE_PTR)
#define DWT_PCSR                                 DWT_PCSR_REG(DWT_BASE_PTR)
#define DWT_COMP0                                DWT_COMP_REG(DWT_BASE_PTR,0)
#define DWT_MASK0                                DWT_MASK_REG(DWT_BASE_PTR,0)
#define DWT_FUNCTION0                            DWT_FUNCTION_REG(DWT_BASE_PTR,0)
#define DWT_COMP1                                DWT_COMP_REG(DWT_BASE_PTR,1)
#define DWT_MASK1                                DWT_MASK_REG(DWT_BASE_PTR,1)
#define DWT_FUNCTION1                            DWT_FUNCTION_REG(DWT_BASE_PTR,1)
#define DWT_COMP2                                DWT_COMP_REG(DWT_BASE_PTR,2)
#define DWT_MASK2                                DWT_MASK_REG(DWT_BASE_PTR,2)
#define DWT_FUNCTION2                            DWT_FUNCTION_REG(DWT_BASE_PTR,2)
#define DWT_COMP3                                DWT_COMP_REG(DWT_BASE_PTR,3)
#define DWT_MASK3                                DWT_MASK_REG(DWT_BASE_PTR,3)
#define DWT_FUNCTION3                            DWT_FUNCTION_REG(DWT_BASE_PTR,3)
#define DWT_PID4                                 DWT_PID4_REG(DWT_BASE_PTR)
#define DWT_PID5                                 DWT_PID5_REG(DWT_BASE_PTR)
#define DWT_PID6                                 DWT_PID6_REG(DWT_BASE_PTR)
#define DWT_PID7                                 DWT_PID7_REG(DWT_BASE_PTR)
#define DWT_PID0                                 DWT_PID0_REG(DWT_BASE_PTR)
#define DWT_PID1                                 DWT_PID1_REG(DWT_BASE_PTR)
#define DWT_PID2                                 DWT_PID2_REG(DWT_BASE_PTR)
#define DWT_PID3                                 DWT_PID3_REG(DWT_BASE_PTR)
#define DWT_CID0                                 DWT_CID0_REG(DWT_BASE_PTR)
#define DWT_CID1                                 DWT_CID1_REG(DWT_BASE_PTR)
#define DWT_CID2                                 DWT_CID2_REG(DWT_BASE_PTR)
#define DWT_CID3                                 DWT_CID3_REG(DWT_BASE_PTR)

/* DWT - Register array accessors */
#define DWT_COMP(index)                          DWT_COMP_REG(DWT_BASE_PTR,index)
#define DWT_MASK(index)                          DWT_MASK_REG(DWT_BASE_PTR,index)
#define DWT_FUNCTION(index)                      DWT_FUNCTION_REG(DWT_BASE_PTR,index)

/**
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group DWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- ENET
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ENET_Peripheral ENET
 * @{
 */

/** ENET - Peripheral register structure */
typedef struct ENET_MemMap {
  uint8_t RESERVED_0[4];
  uint32_t EIR;                                    /**< Interrupt Event Register, offset: 0x4 */
  uint32_t EIMR;                                   /**< Interrupt Mask Register, offset: 0x8 */
  uint8_t RESERVED_1[4];
  uint32_t RDAR;                                   /**< Receive Descriptor Active Register, offset: 0x10 */
  uint32_t TDAR;                                   /**< Transmit Descriptor Active Register, offset: 0x14 */
  uint8_t RESERVED_2[12];
  uint32_t ECR;                                    /**< Ethernet Control Register, offset: 0x24 */
  uint8_t RESERVED_3[24];
  uint32_t MMFR;                                   /**< MII Management Frame Register, offset: 0x40 */
  uint32_t MSCR;                                   /**< MII Speed Control Register, offset: 0x44 */
  uint8_t RESERVED_4[28];
  uint32_t MIBC;                                   /**< MIB Control Register, offset: 0x64 */
  uint8_t RESERVED_5[28];
  uint32_t RCR;                                    /**< Receive Control Register, offset: 0x84 */
  uint8_t RESERVED_6[60];
  uint32_t TCR;                                    /**< Transmit Control Register, offset: 0xC4 */
  uint8_t RESERVED_7[28];
  uint32_t PALR;                                   /**< Physical Address Lower Register, offset: 0xE4 */
  uint32_t PAUR;                                   /**< Physical Address Upper Register, offset: 0xE8 */
  uint32_t OPD;                                    /**< Opcode/Pause Duration Register, offset: 0xEC */
  uint8_t RESERVED_8[40];
  uint32_t IAUR;                                   /**< Descriptor Individual Upper Address Register, offset: 0x118 */
  uint32_t IALR;                                   /**< Descriptor Individual Lower Address Register, offset: 0x11C */
  uint32_t GAUR;                                   /**< Descriptor Group Upper Address Register, offset: 0x120 */
  uint32_t GALR;                                   /**< Descriptor Group Lower Address Register, offset: 0x124 */
  uint8_t RESERVED_9[28];
  uint32_t TFWR;                                   /**< Transmit FIFO Watermark Register, offset: 0x144 */
  uint8_t RESERVED_10[56];
  uint32_t RDSR;                                   /**< Receive Descriptor Ring Start Register, offset: 0x180 */
  uint32_t TDSR;                                   /**< Transmit Buffer Descriptor Ring Start Register, offset: 0x184 */
  uint32_t MRBR;                                   /**< Maximum Receive Buffer Size Register, offset: 0x188 */
  uint8_t RESERVED_11[4];
  uint32_t RSFL;                                   /**< Receive FIFO Section Full Threshold, offset: 0x190 */
  uint32_t RSEM;                                   /**< Receive FIFO Section Empty Threshold, offset: 0x194 */
  uint32_t RAEM;                                   /**< Receive FIFO Almost Empty Threshold, offset: 0x198 */
  uint32_t RAFL;                                   /**< Receive FIFO Almost Full Threshold, offset: 0x19C */
  uint32_t TSEM;                                   /**< Transmit FIFO Section Empty Threshold, offset: 0x1A0 */
  uint32_t TAEM;                                   /**< Transmit FIFO Almost Empty Threshold, offset: 0x1A4 */
  uint32_t TAFL;                                   /**< Transmit FIFO Almost Full Threshold, offset: 0x1A8 */
  uint32_t TIPG;                                   /**< Transmit Inter-Packet Gap, offset: 0x1AC */
  uint32_t FTRL;                                   /**< Frame Truncation Length, offset: 0x1B0 */
  uint8_t RESERVED_12[12];
  uint32_t TACC;                                   /**< Transmit Accelerator Function Configuration, offset: 0x1C0 */
  uint32_t RACC;                                   /**< Receive Accelerator Function Configuration, offset: 0x1C4 */
  uint8_t RESERVED_13[56];
  uint32_t RMON_T_DROP;                            /**< Count of frames not counted correctly (RMON_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x200 */
  uint32_t RMON_T_PACKETS;                         /**< RMON Tx packet count (RMON_T_PACKETS), offset: 0x204 */
  uint32_t RMON_T_BC_PKT;                          /**< RMON Tx Broadcast Packets (RMON_T_BC_PKT), offset: 0x208 */
  uint32_t RMON_T_MC_PKT;                          /**< RMON Tx Multicast Packets (RMON_T_MC_PKT), offset: 0x20C */
  uint32_t RMON_T_CRC_ALIGN;                       /**< RMON Tx Packets w CRC/Align error (RMON_T_CRC_ALIGN), offset: 0x210 */
  uint32_t RMON_T_UNDERSIZE;                       /**< RMON Tx Packets < 64 bytes, good CRC (RMON_T_UNDERSIZE), offset: 0x214 */
  uint32_t RMON_T_OVERSIZE;                        /**< RMON Tx Packets > MAX_FL bytes, good CRC (RMON_T_OVERSIZE), offset: 0x218 */
  uint32_t RMON_T_FRAG;                            /**< RMON Tx Packets < 64 bytes, bad CRC (RMON_T_FRAG), offset: 0x21C */
  uint32_t RMON_T_JAB;                             /**< RMON Tx Packets > MAX_FL bytes, bad CRC (RMON_T_JAB), offset: 0x220 */
  uint32_t RMON_T_COL;                             /**< RMON Tx collision count (RMON_T_COL), offset: 0x224 */
  uint32_t RMON_T_P64;                             /**< RMON Tx 64 byte packets (RMON_T_P64), offset: 0x228 */
  uint32_t RMON_T_P65TO127;                        /**< RMON Tx 65 to 127 byte packets (RMON_T_P65TO127), offset: 0x22C */
  uint32_t RMON_T_P128TO255;                       /**< RMON Tx 128 to 255 byte packets (RMON_T_P128TO255), offset: 0x230 */
  uint32_t RMON_T_P256TO511;                       /**< RMON Tx 256 to 511 byte packets (RMON_T_P256TO511), offset: 0x234 */
  uint32_t RMON_T_P512TO1023;                      /**< RMON Tx 512 to 1023 byte packets (RMON_T_P512TO1023), offset: 0x238 */
  uint32_t RMON_T_P1024TO2047;                     /**< RMON Tx 1024 to 2047 byte packets (RMON_T_P1024TO2047), offset: 0x23C */
  uint32_t RMON_T_P_GTE2048;                       /**< RMON Tx packets w > 2048 bytes (RMON_T_P_GTE2048), offset: 0x240 */
  uint32_t RMON_T_OCTETS;                          /**< RMON Tx Octets (RMON_T_OCTETS), offset: 0x244 */
  uint32_t IEEE_T_DROP;                            /**< Count of frames not counted correctly (IEEE_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x248 */
  uint32_t IEEE_T_FRAME_OK;                        /**< Frames Transmitted OK (IEEE_T_FRAME_OK), offset: 0x24C */
  uint32_t IEEE_T_1COL;                            /**< Frames Transmitted with Single Collision (IEEE_T_1COL), offset: 0x250 */
  uint32_t IEEE_T_MCOL;                            /**< Frames Transmitted with Multiple Collisions (IEEE_T_MCOL), offset: 0x254 */
  uint32_t IEEE_T_DEF;                             /**< Frames Transmitted after Deferral Delay (IEEE_T_DEF), offset: 0x258 */
  uint32_t IEEE_T_LCOL;                            /**< Frames Transmitted with Late Collision (IEEE_T_LCOL), offset: 0x25C */
  uint32_t IEEE_T_EXCOL;                           /**< Frames Transmitted with Excessive Collisions (IEEE_T_EXCOL), offset: 0x260 */
  uint32_t IEEE_T_MACERR;                          /**< Frames Transmitted with Tx FIFO Underrun (IEEE_T_MACERR), offset: 0x264 */
  uint32_t IEEE_T_CSERR;                           /**< Frames Transmitted with Carrier Sense Error (IEEE_T_CSERR), offset: 0x268 */
  uint32_t IEEE_T_SQE;                             /**< Frames Transmitted with SQE Error (IEEE_T_SQE). NOTE: Counter not implemented (read 0 always) as no SQE information is available., offset: 0x26C */
  uint32_t IEEE_T_FDXFC;                           /**< Flow Control Pause frames transmitted (IEEE_T_FDXFC), offset: 0x270 */
  uint32_t IEEE_T_OCTETS_OK;                       /**< Octet count for Frames Transmitted w/o Error (IEEE_T_OCTETS_OK). NOTE: Counts total octets (includes header and FCS fields)., offset: 0x274 */
  uint8_t RESERVED_14[12];
  uint32_t RMON_R_PACKETS;                         /**< RMON Rx packet count (RMON_R_PACKETS), offset: 0x284 */
  uint32_t RMON_R_BC_PKT;                          /**< RMON Rx Broadcast Packets (RMON_R_BC_PKT), offset: 0x288 */
  uint32_t RMON_R_MC_PKT;                          /**< RMON Rx Multicast Packets (RMON_R_MC_PKT), offset: 0x28C */
  uint32_t RMON_R_CRC_ALIGN;                       /**< RMON Rx Packets w CRC/Align error (RMON_R_CRC_ALIGN), offset: 0x290 */
  uint32_t RMON_R_UNDERSIZE;                       /**< RMON Rx Packets < 64 bytes, good CRC (RMON_R_UNDERSIZE), offset: 0x294 */
  uint32_t RMON_R_OVERSIZE;                        /**< RMON Rx Packets > MAX_FL bytes, good CRC (RMON_R_OVERSIZE), offset: 0x298 */
  uint32_t RMON_R_FRAG;                            /**< RMON Rx Packets < 64 bytes, bad CRC (RMON_R_FRAG), offset: 0x29C */
  uint32_t RMON_R_JAB;                             /**< RMON Rx Packets > MAX_FL bytes, bad CRC (RMON_R_JAB), offset: 0x2A0 */
  uint32_t RMON_R_RESVD_0;                         /**< Reserved (RMON_R_RESVD_0), offset: 0x2A4 */
  uint32_t RMON_R_P64;                             /**< RMON Rx 64 byte packets (RMON_R_P64), offset: 0x2A8 */
  uint32_t RMON_R_P65TO127;                        /**< RMON Rx 65 to 127 byte packets (RMON_R_P65TO127), offset: 0x2AC */
  uint32_t RMON_R_P128TO255;                       /**< RMON Rx 128 to 255 byte packets (RMON_R_P128TO255), offset: 0x2B0 */
  uint32_t RMON_R_P256TO511;                       /**< RMON Rx 256 to 511 byte packets (RMON_R_P256TO511), offset: 0x2B4 */
  uint32_t RMON_R_P512TO1023;                      /**< RMON Rx 512 to 1023 byte packets (RMON_R_P512TO1023), offset: 0x2B8 */
  uint32_t RMON_R_P1024TO2047;                     /**< RMON Rx 1024 to 2047 byte packets (RMON_R_P1024TO2047), offset: 0x2BC */
  uint32_t RMON_R_P_GTE2048;                       /**< RMON Rx packets w > 2048 bytes (RMON_R_P_GTE2048), offset: 0x2C0 */
  uint32_t RMON_R_OCTETS;                          /**< RMON Rx Octets (RMON_R_OCTETS), offset: 0x2C4 */
  uint32_t RMON_R_DROP;                            /**< Count of frames not counted correctly (IEEE_R_DROP). NOTE: Counter increments if a frame with valid/missing SFD character is detected and has been dropped. None of the other counters increments if this counter increments., offset: 0x2C8 */
  uint32_t RMON_R_FRAME_OK;                        /**< Frames Received OK (IEEE_R_FRAME_OK), offset: 0x2CC */
  uint32_t IEEE_R_CRC;                             /**< Frames Received with CRC Error (IEEE_R_CRC), offset: 0x2D0 */
  uint32_t IEEE_R_ALIGN;                           /**< Frames Received with Alignment Error (IEEE_R_ALIGN), offset: 0x2D4 */
  uint32_t IEEE_R_MACERR;                          /**< Receive Fifo Overflow count (IEEE_R_MACERR), offset: 0x2D8 */
  uint32_t IEEE_R_FDXFC;                           /**< Flow Control Pause frames received (IEEE_R_FDXFC), offset: 0x2DC */
  uint32_t IEEE_R_OCTETS_OK;                       /**< Octet count for Frames Rcvd w/o Error (IEEE_R_OCTETS_OK). Counts total octets (includes header and FCS fields)., offset: 0x2E0 */
  uint8_t RESERVED_15[284];
  uint32_t ATCR;                                   /**< Timer Control Register, offset: 0x400 */
  uint32_t ATVR;                                   /**< Timer Value Register, offset: 0x404 */
  uint32_t ATOFF;                                  /**< Timer Offset Register, offset: 0x408 */
  uint32_t ATPER;                                  /**< Timer Period Register, offset: 0x40C */
  uint32_t ATCOR;                                  /**< Timer Correction Register, offset: 0x410 */
  uint32_t ATINC;                                  /**< Time-Stamping Clock Period Register, offset: 0x414 */
  uint32_t ATSTMP;                                 /**< Timestamp of Last Transmitted Frame, offset: 0x418 */
  uint8_t RESERVED_16[488];
  uint32_t TGSR;                                   /**< Timer Global Status Register, offset: 0x604 */
  struct {                                         /* offset: 0x608, array step: 0x8 */
    uint32_t TCSR;                                   /**< Timer Control Status Register, array offset: 0x608, array step: 0x8 */
    uint32_t TCCR;                                   /**< Timer Compare Capture Register, array offset: 0x60C, array step: 0x8 */
  } CHANNEL[4];
} volatile *ENET_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ENET - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ENET_Register_Accessor_Macros ENET - Register accessor macros
 * @{
 */


/* ENET - Register accessors */
#define ENET_EIR_REG(base)                       ((base)->EIR)
#define ENET_EIMR_REG(base)                      ((base)->EIMR)
#define ENET_RDAR_REG(base)                      ((base)->RDAR)
#define ENET_TDAR_REG(base)                      ((base)->TDAR)
#define ENET_ECR_REG(base)                       ((base)->ECR)
#define ENET_MMFR_REG(base)                      ((base)->MMFR)
#define ENET_MSCR_REG(base)                      ((base)->MSCR)
#define ENET_MIBC_REG(base)                      ((base)->MIBC)
#define ENET_RCR_REG(base)                       ((base)->RCR)
#define ENET_TCR_REG(base)                       ((base)->TCR)
#define ENET_PALR_REG(base)                      ((base)->PALR)
#define ENET_PAUR_REG(base)                      ((base)->PAUR)
#define ENET_OPD_REG(base)                       ((base)->OPD)
#define ENET_IAUR_REG(base)                      ((base)->IAUR)
#define ENET_IALR_REG(base)                      ((base)->IALR)
#define ENET_GAUR_REG(base)                      ((base)->GAUR)
#define ENET_GALR_REG(base)                      ((base)->GALR)
#define ENET_TFWR_REG(base)                      ((base)->TFWR)
#define ENET_RDSR_REG(base)                      ((base)->RDSR)
#define ENET_TDSR_REG(base)                      ((base)->TDSR)
#define ENET_MRBR_REG(base)                      ((base)->MRBR)
#define ENET_RSFL_REG(base)                      ((base)->RSFL)
#define ENET_RSEM_REG(base)                      ((base)->RSEM)
#define ENET_RAEM_REG(base)                      ((base)->RAEM)
#define ENET_RAFL_REG(base)                      ((base)->RAFL)
#define ENET_TSEM_REG(base)                      ((base)->TSEM)
#define ENET_TAEM_REG(base)                      ((base)->TAEM)
#define ENET_TAFL_REG(base)                      ((base)->TAFL)
#define ENET_TIPG_REG(base)                      ((base)->TIPG)
#define ENET_FTRL_REG(base)                      ((base)->FTRL)
#define ENET_TACC_REG(base)                      ((base)->TACC)
#define ENET_RACC_REG(base)                      ((base)->RACC)
#define ENET_RMON_T_DROP_REG(base)               ((base)->RMON_T_DROP)
#define ENET_RMON_T_PACKETS_REG(base)            ((base)->RMON_T_PACKETS)
#define ENET_RMON_T_BC_PKT_REG(base)             ((base)->RMON_T_BC_PKT)
#define ENET_RMON_T_MC_PKT_REG(base)             ((base)->RMON_T_MC_PKT)
#define ENET_RMON_T_CRC_ALIGN_REG(base)          ((base)->RMON_T_CRC_ALIGN)
#define ENET_RMON_T_UNDERSIZE_REG(base)          ((base)->RMON_T_UNDERSIZE)
#define ENET_RMON_T_OVERSIZE_REG(base)           ((base)->RMON_T_OVERSIZE)
#define ENET_RMON_T_FRAG_REG(base)               ((base)->RMON_T_FRAG)
#define ENET_RMON_T_JAB_REG(base)                ((base)->RMON_T_JAB)
#define ENET_RMON_T_COL_REG(base)                ((base)->RMON_T_COL)
#define ENET_RMON_T_P64_REG(base)                ((base)->RMON_T_P64)
#define ENET_RMON_T_P65TO127_REG(base)           ((base)->RMON_T_P65TO127)
#define ENET_RMON_T_P128TO255_REG(base)          ((base)->RMON_T_P128TO255)
#define ENET_RMON_T_P256TO511_REG(base)          ((base)->RMON_T_P256TO511)
#define ENET_RMON_T_P512TO1023_REG(base)         ((base)->RMON_T_P512TO1023)
#define ENET_RMON_T_P1024TO2047_REG(base)        ((base)->RMON_T_P1024TO2047)
#define ENET_RMON_T_P_GTE2048_REG(base)          ((base)->RMON_T_P_GTE2048)
#define ENET_RMON_T_OCTETS_REG(base)             ((base)->RMON_T_OCTETS)
#define ENET_IEEE_T_DROP_REG(base)               ((base)->IEEE_T_DROP)
#define ENET_IEEE_T_FRAME_OK_REG(base)           ((base)->IEEE_T_FRAME_OK)
#define ENET_IEEE_T_1COL_REG(base)               ((base)->IEEE_T_1COL)
#define ENET_IEEE_T_MCOL_REG(base)               ((base)->IEEE_T_MCOL)
#define ENET_IEEE_T_DEF_REG(base)                ((base)->IEEE_T_DEF)
#define ENET_IEEE_T_LCOL_REG(base)               ((base)->IEEE_T_LCOL)
#define ENET_IEEE_T_EXCOL_REG(base)              ((base)->IEEE_T_EXCOL)
#define ENET_IEEE_T_MACERR_REG(base)             ((base)->IEEE_T_MACERR)
#define ENET_IEEE_T_CSERR_REG(base)              ((base)->IEEE_T_CSERR)
#define ENET_IEEE_T_SQE_REG(base)                ((base)->IEEE_T_SQE)
#define ENET_IEEE_T_FDXFC_REG(base)              ((base)->IEEE_T_FDXFC)
#define ENET_IEEE_T_OCTETS_OK_REG(base)          ((base)->IEEE_T_OCTETS_OK)
#define ENET_RMON_R_PACKETS_REG(base)            ((base)->RMON_R_PACKETS)
#define ENET_RMON_R_BC_PKT_REG(base)             ((base)->RMON_R_BC_PKT)
#define ENET_RMON_R_MC_PKT_REG(base)             ((base)->RMON_R_MC_PKT)
#define ENET_RMON_R_CRC_ALIGN_REG(base)          ((base)->RMON_R_CRC_ALIGN)
#define ENET_RMON_R_UNDERSIZE_REG(base)          ((base)->RMON_R_UNDERSIZE)
#define ENET_RMON_R_OVERSIZE_REG(base)           ((base)->RMON_R_OVERSIZE)
#define ENET_RMON_R_FRAG_REG(base)               ((base)->RMON_R_FRAG)
#define ENET_RMON_R_JAB_REG(base)                ((base)->RMON_R_JAB)
#define ENET_RMON_R_RESVD_0_REG(base)            ((base)->RMON_R_RESVD_0)
#define ENET_RMON_R_P64_REG(base)                ((base)->RMON_R_P64)
#define ENET_RMON_R_P65TO127_REG(base)           ((base)->RMON_R_P65TO127)
#define ENET_RMON_R_P128TO255_REG(base)          ((base)->RMON_R_P128TO255)
#define ENET_RMON_R_P256TO511_REG(base)          ((base)->RMON_R_P256TO511)
#define ENET_RMON_R_P512TO1023_REG(base)         ((base)->RMON_R_P512TO1023)
#define ENET_RMON_R_P1024TO2047_REG(base)        ((base)->RMON_R_P1024TO2047)
#define ENET_RMON_R_P_GTE2048_REG(base)          ((base)->RMON_R_P_GTE2048)
#define ENET_RMON_R_OCTETS_REG(base)             ((base)->RMON_R_OCTETS)
#define ENET_RMON_R_DROP_REG(base)               ((base)->RMON_R_DROP)
#define ENET_RMON_R_FRAME_OK_REG(base)           ((base)->RMON_R_FRAME_OK)
#define ENET_IEEE_R_CRC_REG(base)                ((base)->IEEE_R_CRC)
#define ENET_IEEE_R_ALIGN_REG(base)              ((base)->IEEE_R_ALIGN)
#define ENET_IEEE_R_MACERR_REG(base)             ((base)->IEEE_R_MACERR)
#define ENET_IEEE_R_FDXFC_REG(base)              ((base)->IEEE_R_FDXFC)
#define ENET_IEEE_R_OCTETS_OK_REG(base)          ((base)->IEEE_R_OCTETS_OK)
#define ENET_ATCR_REG(base)                      ((base)->ATCR)
#define ENET_ATVR_REG(base)                      ((base)->ATVR)
#define ENET_ATOFF_REG(base)                     ((base)->ATOFF)
#define ENET_ATPER_REG(base)                     ((base)->ATPER)
#define ENET_ATCOR_REG(base)                     ((base)->ATCOR)
#define ENET_ATINC_REG(base)                     ((base)->ATINC)
#define ENET_ATSTMP_REG(base)                    ((base)->ATSTMP)
#define ENET_TGSR_REG(base)                      ((base)->TGSR)
#define ENET_TCSR_REG(base,index)                ((base)->CHANNEL[index].TCSR)
#define ENET_TCCR_REG(base,index)                ((base)->CHANNEL[index].TCCR)

/**
 * @}
 */ /* end of group ENET_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ENET_Register_Masks */


/* ENET - Peripheral instance base addresses */
/** Peripheral ENET base pointer */
#define ENET_BASE_PTR                            ((ENET_MemMapPtr)0x400C0000u)

/* ----------------------------------------------------------------------------
   -- ENET - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ENET_Register_Accessor_Macros ENET - Register accessor macros
 * @{
 */


/* ENET - Register instance definitions */
/* ENET */
#define ENET_EIR                                 ENET_EIR_REG(ENET_BASE_PTR)
#define ENET_EIMR                                ENET_EIMR_REG(ENET_BASE_PTR)
#define ENET_RDAR                                ENET_RDAR_REG(ENET_BASE_PTR)
#define ENET_TDAR                                ENET_TDAR_REG(ENET_BASE_PTR)
#define ENET_ECR                                 ENET_ECR_REG(ENET_BASE_PTR)
#define ENET_MMFR                                ENET_MMFR_REG(ENET_BASE_PTR)
#define ENET_MSCR                                ENET_MSCR_REG(ENET_BASE_PTR)
#define ENET_MIBC                                ENET_MIBC_REG(ENET_BASE_PTR)
#define ENET_RCR                                 ENET_RCR_REG(ENET_BASE_PTR)
#define ENET_TCR                                 ENET_TCR_REG(ENET_BASE_PTR)
#define ENET_PALR                                ENET_PALR_REG(ENET_BASE_PTR)
#define ENET_PAUR                                ENET_PAUR_REG(ENET_BASE_PTR)
#define ENET_OPD                                 ENET_OPD_REG(ENET_BASE_PTR)
#define ENET_IAUR                                ENET_IAUR_REG(ENET_BASE_PTR)
#define ENET_IALR                                ENET_IALR_REG(ENET_BASE_PTR)
#define ENET_GAUR                                ENET_GAUR_REG(ENET_BASE_PTR)
#define ENET_GALR                                ENET_GALR_REG(ENET_BASE_PTR)
#define ENET_TFWR                                ENET_TFWR_REG(ENET_BASE_PTR)
#define ENET_RDSR                                ENET_RDSR_REG(ENET_BASE_PTR)
#define ENET_TDSR                                ENET_TDSR_REG(ENET_BASE_PTR)
#define ENET_MRBR                                ENET_MRBR_REG(ENET_BASE_PTR)
#define ENET_RSFL                                ENET_RSFL_REG(ENET_BASE_PTR)
#define ENET_RSEM                                ENET_RSEM_REG(ENET_BASE_PTR)
#define ENET_RAEM                                ENET_RAEM_REG(ENET_BASE_PTR)
#define ENET_RAFL                                ENET_RAFL_REG(ENET_BASE_PTR)
#define ENET_TSEM                                ENET_TSEM_REG(ENET_BASE_PTR)
#define ENET_TAEM                                ENET_TAEM_REG(ENET_BASE_PTR)
#define ENET_TAFL                                ENET_TAFL_REG(ENET_BASE_PTR)
#define ENET_TIPG                                ENET_TIPG_REG(ENET_BASE_PTR)
#define ENET_FTRL                                ENET_FTRL_REG(ENET_BASE_PTR)
#define ENET_TACC                                ENET_TACC_REG(ENET_BASE_PTR)
#define ENET_RACC                                ENET_RACC_REG(ENET_BASE_PTR)
#define ENET_ATCR                                ENET_ATCR_REG(ENET_BASE_PTR)
#define ENET_ATVR                                ENET_ATVR_REG(ENET_BASE_PTR)
#define ENET_ATOFF                               ENET_ATOFF_REG(ENET_BASE_PTR)
#define ENET_ATPER                               ENET_ATPER_REG(ENET_BASE_PTR)
#define ENET_ATCOR                               ENET_ATCOR_REG(ENET_BASE_PTR)
#define ENET_ATINC                               ENET_ATINC_REG(ENET_BASE_PTR)
#define ENET_ATSTMP                              ENET_ATSTMP_REG(ENET_BASE_PTR)
#define ENET_TGSR                                ENET_TGSR_REG(ENET_BASE_PTR)
#define ENET_TCSR0                               ENET_TCSR_REG(ENET_BASE_PTR,0)
#define ENET_TCCR0                               ENET_TCCR_REG(ENET_BASE_PTR,0)
#define ENET_TCSR1                               ENET_TCSR_REG(ENET_BASE_PTR,1)
#define ENET_TCCR1                               ENET_TCCR_REG(ENET_BASE_PTR,1)
#define ENET_TCSR2                               ENET_TCSR_REG(ENET_BASE_PTR,2)
#define ENET_TCCR2                               ENET_TCCR_REG(ENET_BASE_PTR,2)
#define ENET_TCSR3                               ENET_TCSR_REG(ENET_BASE_PTR,3)
#define ENET_TCCR3                               ENET_TCCR_REG(ENET_BASE_PTR,3)
#define ENET_RMON_T_DROP                         ENET_RMON_T_DROP_REG(ENET_BASE_PTR)
#define ENET_RMON_T_PACKETS                      ENET_RMON_T_PACKETS_REG(ENET_BASE_PTR)
#define ENET_RMON_T_BC_PKT                       ENET_RMON_T_BC_PKT_REG(ENET_BASE_PTR)
#define ENET_RMON_T_MC_PKT                       ENET_RMON_T_MC_PKT_REG(ENET_BASE_PTR)
#define ENET_RMON_T_CRC_ALIGN                    ENET_RMON_T_CRC_ALIGN_REG(ENET_BASE_PTR)
#define ENET_RMON_T_UNDERSIZE                    ENET_RMON_T_UNDERSIZE_REG(ENET_BASE_PTR)
#define ENET_RMON_T_OVERSIZE                     ENET_RMON_T_OVERSIZE_REG(ENET_BASE_PTR)
#define ENET_RMON_T_FRAG                         ENET_RMON_T_FRAG_REG(ENET_BASE_PTR)
#define ENET_RMON_T_JAB                          ENET_RMON_T_JAB_REG(ENET_BASE_PTR)
#define ENET_RMON_T_COL                          ENET_RMON_T_COL_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P64                          ENET_RMON_T_P64_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P65TO127                     ENET_RMON_T_P65TO127_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P128TO255                    ENET_RMON_T_P128TO255_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P256TO511                    ENET_RMON_T_P256TO511_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P512TO1023                   ENET_RMON_T_P512TO1023_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P1024TO2047                  ENET_RMON_T_P1024TO2047_REG(ENET_BASE_PTR)
#define ENET_RMON_T_P_GTE2048                    ENET_RMON_T_P_GTE2048_REG(ENET_BASE_PTR)
#define ENET_RMON_T_OCTETS                       ENET_RMON_T_OCTETS_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_DROP                         ENET_IEEE_T_DROP_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_FRAME_OK                     ENET_IEEE_T_FRAME_OK_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_1COL                         ENET_IEEE_T_1COL_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_MCOL                         ENET_IEEE_T_MCOL_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_DEF                          ENET_IEEE_T_DEF_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_LCOL                         ENET_IEEE_T_LCOL_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_EXCOL                        ENET_IEEE_T_EXCOL_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_MACERR                       ENET_IEEE_T_MACERR_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_CSERR                        ENET_IEEE_T_CSERR_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_SQE                          ENET_IEEE_T_SQE_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_FDXFC                        ENET_IEEE_T_FDXFC_REG(ENET_BASE_PTR)
#define ENET_IEEE_T_OCTETS_OK                    ENET_IEEE_T_OCTETS_OK_REG(ENET_BASE_PTR)
#define ENET_RMON_R_PACKETS                      ENET_RMON_R_PACKETS_REG(ENET_BASE_PTR)
#define ENET_RMON_R_BC_PKT                       ENET_RMON_R_BC_PKT_REG(ENET_BASE_PTR)
#define ENET_RMON_R_MC_PKT                       ENET_RMON_R_MC_PKT_REG(ENET_BASE_PTR)
#define ENET_RMON_R_CRC_ALIGN                    ENET_RMON_R_CRC_ALIGN_REG(ENET_BASE_PTR)
#define ENET_RMON_R_UNDERSIZE                    ENET_RMON_R_UNDERSIZE_REG(ENET_BASE_PTR)
#define ENET_RMON_R_OVERSIZE                     ENET_RMON_R_OVERSIZE_REG(ENET_BASE_PTR)
#define ENET_RMON_R_FRAG                         ENET_RMON_R_FRAG_REG(ENET_BASE_PTR)
#define ENET_RMON_R_JAB                          ENET_RMON_R_JAB_REG(ENET_BASE_PTR)
#define ENET_RMON_R_RESVD_0                      ENET_RMON_R_RESVD_0_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P64                          ENET_RMON_R_P64_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P65TO127                     ENET_RMON_R_P65TO127_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P128TO255                    ENET_RMON_R_P128TO255_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P256TO511                    ENET_RMON_R_P256TO511_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P512TO1023                   ENET_RMON_R_P512TO1023_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P1024TO2047                  ENET_RMON_R_P1024TO2047_REG(ENET_BASE_PTR)
#define ENET_RMON_R_P_GTE2048                    ENET_RMON_R_P_GTE2048_REG(ENET_BASE_PTR)
#define ENET_RMON_R_OCTETS                       ENET_RMON_R_OCTETS_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_DROP                         ENET_RMON_R_DROP_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_FRAME_OK                     ENET_RMON_R_FRAME_OK_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_CRC                          ENET_IEEE_R_CRC_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_ALIGN                        ENET_IEEE_R_ALIGN_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_MACERR                       ENET_IEEE_R_MACERR_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_FDXFC                        ENET_IEEE_R_FDXFC_REG(ENET_BASE_PTR)
#define ENET_IEEE_R_OCTETS_OK                    ENET_IEEE_R_OCTETS_OK_REG(ENET_BASE_PTR)

/* ENET - Register array accessors */
#define ENET_TCSR(index)                         ENET_TCSR_REG(ENET_BASE_PTR,index)
#define ENET_TCCR(index)                         ENET_TCCR_REG(ENET_BASE_PTR,index)

/**
 * @}
 */ /* end of group ENET_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ENET_Peripheral */


/* ----------------------------------------------------------------------------
   -- ETB
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETB_Peripheral ETB
 * @{
 */

/** ETB - Peripheral register structure */
typedef struct ETB_MemMap {
  uint8_t RESERVED_0[4];
  uint32_t RDP;                                    /**< RAM Depth Register, offset: 0x4 */
  uint8_t RESERVED_1[4];
  uint32_t STS;                                    /**< Status Register, offset: 0xC */
  uint32_t RRD;                                    /**< RAM Read Data Register, offset: 0x10 */
  uint32_t RRP;                                    /**< RAM Read Pointer Register, offset: 0x14 */
  uint32_t RWP;                                    /**< RAM Write Pointer Register, offset: 0x18 */
  uint32_t TRG;                                    /**< Trigger Counter Register, offset: 0x1C */
  uint32_t CTL;                                    /**< Control Register, offset: 0x20 */
  uint32_t RWD;                                    /**< RAM Write Data Register, offset: 0x24 */
  uint8_t RESERVED_2[728];
  uint32_t FFSR;                                   /**< Formatter and Flush Status Register, offset: 0x300 */
  uint32_t FFCR;                                   /**< Formatter and Flush Control Register, offset: 0x304 */
  uint8_t RESERVED_3[3032];
  uint32_t ITMISCOP0;                              /**< Integration Register, ITMISCOP0, offset: 0xEE0 */
  uint32_t ITTRFLINACK;                            /**< Integration Register, ITTRFLINACK, offset: 0xEE4 */
  uint32_t ITTRFLIN;                               /**< Integration Register, ITTRFLIN, offset: 0xEE8 */
  uint32_t ITATBDATA0;                             /**< Integration Register, ITATBDATA0, offset: 0xEEC */
  uint32_t ITATBCTR2;                              /**< Integration Register, ITATBCTR2, offset: 0xEF0 */
  uint32_t ITATBCTR1;                              /**< Integration Register, ITATBCTR1, offset: 0xEF4 */
  uint32_t ITATBCTR0;                              /**< Integration Register, ITATBCTR0, offset: 0xEF8 */
  uint8_t RESERVED_4[4];
  uint32_t ITCTRL;                                 /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_5[156];
  uint32_t CLAIMSET;                               /**< Claim Tag Set Register, offset: 0xFA0 */
  uint32_t CLAIMCLR;                               /**< Claim Tag Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_6[8];
  uint32_t LAR;                                    /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LSR;                                    /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTATUS;                             /**< Authentication Status Register, offset: 0xFB8 */
  uint8_t RESERVED_7[12];
  uint32_t DEVID;                                  /**< Device ID Register, offset: 0xFC8 */
  uint32_t DEVTYPE;                                /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PIDR4;                                  /**< Peripheral Identification Register 4, offset: 0xFD0 */
  uint32_t PIDR5;                                  /**< Peripheral Identification Register 5, offset: 0xFD4 */
  uint32_t PIDR6;                                  /**< Peripheral Identification Register 6, offset: 0xFD8 */
  uint32_t PIDR7;                                  /**< Peripheral Identification Register 7, offset: 0xFDC */
  uint32_t PIDR0;                                  /**< Peripheral Identification Register 0, offset: 0xFE0 */
  uint32_t PIDR1;                                  /**< Peripheral Identification Register 1, offset: 0xFE4 */
  uint32_t PIDR2;                                  /**< Peripheral Identification Register 2, offset: 0xFE8 */
  uint32_t PIDR3;                                  /**< Peripheral Identification Register 3, offset: 0xFEC */
  uint32_t CIDR0;                                  /**< Component Identification Register 0, offset: 0xFF0 */
  uint32_t CIDR1;                                  /**< Component Identification Register 1, offset: 0xFF4 */
  uint32_t CIDR2;                                  /**< Component Identification Register 2, offset: 0xFF8 */
  uint32_t CIDR3;                                  /**< Component Identification Register 3, offset: 0xFFC */
} volatile *ETB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ETB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETB_Register_Accessor_Macros ETB - Register accessor macros
 * @{
 */


/* ETB - Register accessors */
#define ETB_RDP_REG(base)                        ((base)->RDP)
#define ETB_STS_REG(base)                        ((base)->STS)
#define ETB_RRD_REG(base)                        ((base)->RRD)
#define ETB_RRP_REG(base)                        ((base)->RRP)
#define ETB_RWP_REG(base)                        ((base)->RWP)
#define ETB_TRG_REG(base)                        ((base)->TRG)
#define ETB_CTL_REG(base)                        ((base)->CTL)
#define ETB_RWD_REG(base)                        ((base)->RWD)
#define ETB_FFSR_REG(base)                       ((base)->FFSR)
#define ETB_FFCR_REG(base)                       ((base)->FFCR)
#define ETB_ITMISCOP0_REG(base)                  ((base)->ITMISCOP0)
#define ETB_ITTRFLINACK_REG(base)                ((base)->ITTRFLINACK)
#define ETB_ITTRFLIN_REG(base)                   ((base)->ITTRFLIN)
#define ETB_ITATBDATA0_REG(base)                 ((base)->ITATBDATA0)
#define ETB_ITATBCTR2_REG(base)                  ((base)->ITATBCTR2)
#define ETB_ITATBCTR1_REG(base)                  ((base)->ITATBCTR1)
#define ETB_ITATBCTR0_REG(base)                  ((base)->ITATBCTR0)
#define ETB_ITCTRL_REG(base)                     ((base)->ITCTRL)
#define ETB_CLAIMSET_REG(base)                   ((base)->CLAIMSET)
#define ETB_CLAIMCLR_REG(base)                   ((base)->CLAIMCLR)
#define ETB_LAR_REG(base)                        ((base)->LAR)
#define ETB_LSR_REG(base)                        ((base)->LSR)
#define ETB_AUTHSTATUS_REG(base)                 ((base)->AUTHSTATUS)
#define ETB_DEVID_REG(base)                      ((base)->DEVID)
#define ETB_DEVTYPE_REG(base)                    ((base)->DEVTYPE)
#define ETB_PIDR4_REG(base)                      ((base)->PIDR4)
#define ETB_PIDR5_REG(base)                      ((base)->PIDR5)
#define ETB_PIDR6_REG(base)                      ((base)->PIDR6)
#define ETB_PIDR7_REG(base)                      ((base)->PIDR7)
#define ETB_PIDR0_REG(base)                      ((base)->PIDR0)
#define ETB_PIDR1_REG(base)                      ((base)->PIDR1)
#define ETB_PIDR2_REG(base)                      ((base)->PIDR2)
#define ETB_PIDR3_REG(base)                      ((base)->PIDR3)
#define ETB_CIDR0_REG(base)                      ((base)->CIDR0)
#define ETB_CIDR1_REG(base)                      ((base)->CIDR1)
#define ETB_CIDR2_REG(base)                      ((base)->CIDR2)
#define ETB_CIDR3_REG(base)                      ((base)->CIDR3)

/**
 * @}
 */ /* end of group ETB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ETB Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETB_Register_Masks ETB Register Masks
 * @{
 */


/**
 * @}
 */ /* end of group ETB_Register_Masks */


/* ETB - Peripheral instance base addresses */
/** Peripheral ETB base pointer */
#define ETB_BASE_PTR                             ((ETB_MemMapPtr)0xE0042000u)

/* ----------------------------------------------------------------------------
   -- ETB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETB_Register_Accessor_Macros ETB - Register accessor macros
 * @{
 */


/* ETB - Register instance definitions */
/* ETB */
#define ETB_RDP                                  ETB_RDP_REG(ETB_BASE_PTR)
#define ETB_STS                                  ETB_STS_REG(ETB_BASE_PTR)
#define ETB_RRD                                  ETB_RRD_REG(ETB_BASE_PTR)
#define ETB_RRP                                  ETB_RRP_REG(ETB_BASE_PTR)
#define ETB_RWP                                  ETB_RWP_REG(ETB_BASE_PTR)
#define ETB_TRG                                  ETB_TRG_REG(ETB_BASE_PTR)
#define ETB_CTL                                  ETB_CTL_REG(ETB_BASE_PTR)
#define ETB_RWD                                  ETB_RWD_REG(ETB_BASE_PTR)
#define ETB_FFSR                                 ETB_FFSR_REG(ETB_BASE_PTR)
#define ETB_FFCR                                 ETB_FFCR_REG(ETB_BASE_PTR)
#define ETB_ITMISCOP0                            ETB_ITMISCOP0_REG(ETB_BASE_PTR)
#define ETB_ITTRFLINACK                          ETB_ITTRFLINACK_REG(ETB_BASE_PTR)
#define ETB_ITTRFLIN                             ETB_ITTRFLIN_REG(ETB_BASE_PTR)
#define ETB_ITATBDATA0                           ETB_ITATBDATA0_REG(ETB_BASE_PTR)
#define ETB_ITATBCTR2                            ETB_ITATBCTR2_REG(ETB_BASE_PTR)
#define ETB_ITATBCTR1                            ETB_ITATBCTR1_REG(ETB_BASE_PTR)
#define ETB_ITATBCTR0                            ETB_ITATBCTR0_REG(ETB_BASE_PTR)
#define ETB_ITCTRL                               ETB_ITCTRL_REG(ETB_BASE_PTR)
#define ETB_CLAIMSET                             ETB_CLAIMSET_REG(ETB_BASE_PTR)
#define ETB_CLAIMCLR                             ETB_CLAIMCLR_REG(ETB_BASE_PTR)
#define ETB_LAR                                  ETB_LAR_REG(ETB_BASE_PTR)
#define ETB_LSR                                  ETB_LSR_REG(ETB_BASE_PTR)
#define ETB_AUTHSTATUS                           ETB_AUTHSTATUS_REG(ETB_BASE_PTR)
#define ETB_DEVID                                ETB_DEVID_REG(ETB_BASE_PTR)
#define ETB_DEVTYPE                              ETB_DEVTYPE_REG(ETB_BASE_PTR)
#define ETB_PIDR4                                ETB_PIDR4_REG(ETB_BASE_PTR)
#define ETB_PIDR5                                ETB_PIDR5_REG(ETB_BASE_PTR)
#define ETB_PIDR6                                ETB_PIDR6_REG(ETB_BASE_PTR)
#define ETB_PIDR7                                ETB_PIDR7_REG(ETB_BASE_PTR)
#define ETB_PIDR0                                ETB_PIDR0_REG(ETB_BASE_PTR)
#define ETB_PIDR1                                ETB_PIDR1_REG(ETB_BASE_PTR)
#define ETB_PIDR2                                ETB_PIDR2_REG(ETB_BASE_PTR)
#define ETB_PIDR3                                ETB_PIDR3_REG(ETB_BASE_PTR)
#define ETB_CIDR0                                ETB_CIDR0_REG(ETB_BASE_PTR)
#define ETB_CIDR1                                ETB_CIDR1_REG(ETB_BASE_PTR)
#define ETB_CIDR2                                ETB_CIDR2_REG(ETB_BASE_PTR)
#define ETB_CIDR3                                ETB_CIDR3_REG(ETB_BASE_PTR)

/**
 * @}
 */ /* end of group ETB_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ETB_Peripheral */


/* ----------------------------------------------------------------------------
   -- ETF
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETF_Peripheral ETF
 * @{
 */

/** ETF - Peripheral register structure */
typedef struct ETF_MemMap {
  uint32_t FCR;                                    /**< Funnel Control Register, offset: 0x0 */
  uint32_t PCR;                                    /**< Priority Control Register, offset: 0x4 */
  uint8_t RESERVED_0[3812];
  uint32_t ITATBDATA0;                             /**< Integration Register, ITATBDATA0, offset: 0xEEC */
  uint32_t ITATBCTR2;                              /**< Integration Register, ITATBCTR2, offset: 0xEF0 */
  uint32_t ITATBCTR1;                              /**< Integration Register, ITATBCTR1, offset: 0xEF4 */
  uint32_t ITATBCTR0;                              /**< Integration Register, ITATBCTR0, offset: 0xEF8 */
  uint8_t RESERVED_1[4];
  uint32_t ITCTRL;                                 /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_2[156];
  uint32_t CLAIMSET;                               /**< Claim Tag Set Register, offset: 0xFA0 */
  uint32_t CLAIMCLR;                               /**< Claim Tag Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_3[8];
  uint32_t LAR;                                    /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LSR;                                    /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTATUS;                             /**< Authentication Status Register, offset: 0xFB8 */
  uint8_t RESERVED_4[12];
  uint32_t DEVID;                                  /**< Device ID Register, offset: 0xFC8 */
  uint32_t DEVTYPE;                                /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PIDR4;                                  /**< Peripheral Identification Register 4, offset: 0xFD0 */
  uint32_t PIDR5;                                  /**< Peripheral Identification Register 5, offset: 0xFD4 */
  uint32_t PIDR6;                                  /**< Peripheral Identification Register 6, offset: 0xFD8 */
  uint32_t PIDR7;                                  /**< Peripheral Identification Register 7, offset: 0xFDC */
  uint32_t PIDR0;                                  /**< Peripheral Identification Register 0, offset: 0xFE0 */
  uint32_t PIDR1;                                  /**< Peripheral Identification Register 1, offset: 0xFE4 */
  uint32_t PIDR2;                                  /**< Peripheral Identification Register 2, offset: 0xFE8 */
  uint32_t PIDR3;                                  /**< Peripheral Identification Register 3, offset: 0xFEC */
  uint32_t CIDR0;                                  /**< Component Identification Register 0, offset: 0xFF0 */
  uint32_t CIDR1;                                  /**< Component Identification Register 1, offset: 0xFF4 */
  uint32_t CIDR2;                                  /**< Component Identification Register 2, offset: 0xFF8 */
  uint32_t CIDR3;                                  /**< Component Identification Register 3, offset: 0xFFC */
} volatile *ETF_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ETF - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETF_Register_Accessor_Macros ETF - Register accessor macros
 * @{
 */


/* ETF - Register accessors */
#define ETF_FCR_REG(base)                        ((base)->FCR)
#define ETF_PCR_REG(base)                        ((base)->PCR)
#define ETF_ITATBDATA0_REG(base)                 ((base)->ITATBDATA0)
#define ETF_ITATBCTR2_REG(base)                  ((base)->ITATBCTR2)
#define ETF_ITATBCTR1_REG(base)                  ((base)->ITATBCTR1)
#define ETF_ITATBCTR0_REG(base)                  ((base)->ITATBCTR0)
#define ETF_ITCTRL_REG(base)                     ((base)->ITCTRL)
#define ETF_CLAIMSET_REG(base)                   ((base)->CLAIMSET)
#define ETF_CLAIMCLR_REG(base)                   ((base)->CLAIMCLR)
#define ETF_LAR_REG(base)                        ((base)->LAR)
#define ETF_LSR_REG(base)                        ((base)->LSR)
#define ETF_AUTHSTATUS_REG(base)                 ((base)->AUTHSTATUS)
#define ETF_DEVID_REG(base)                      ((base)->DEVID)
#define ETF_DEVTYPE_REG(base)                    ((base)->DEVTYPE)
#define ETF_PIDR4_REG(base)                      ((base)->PIDR4)
#define ETF_PIDR5_REG(base)                      ((base)->PIDR5)
#define ETF_PIDR6_REG(base)                      ((base)->PIDR6)
#define ETF_PIDR7_REG(base)                      ((base)->PIDR7)
#define ETF_PIDR0_REG(base)                      ((base)->PIDR0)
#define ETF_PIDR1_REG(base)                      ((base)->PIDR1)
#define ETF_PIDR2_REG(base)                      ((base)->PIDR2)
#define ETF_PIDR3_REG(base)                      ((base)->PIDR3)
#define ETF_CIDR0_REG(base)                      ((base)->CIDR0)
#define ETF_CIDR1_REG(base)                      ((base)->CIDR1)
#define ETF_CIDR2_REG(base)                      ((base)->CIDR2)
#define ETF_CIDR3_REG(base)                      ((base)->CIDR3)

/**
 * @}
 */ /* end of group ETF_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ETF Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETF_Register_Masks ETF Register Masks
 * @{
 */


/**
 * @}
 */ /* end of group ETF_Register_Masks */


/* ETF - Peripheral instance base addresses */
/** Peripheral ETF base pointer */
#define ETF_BASE_PTR                             ((ETF_MemMapPtr)0xE0043000u)

/* ----------------------------------------------------------------------------
   -- ETF - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETF_Register_Accessor_Macros ETF - Register accessor macros
 * @{
 */


/* ETF - Register instance definitions */
/* ETF */
#define ETF_FCR                                  ETF_FCR_REG(ETF_BASE_PTR)
#define ETF_PCR                                  ETF_PCR_REG(ETF_BASE_PTR)
#define ETF_ITATBDATA0                           ETF_ITATBDATA0_REG(ETF_BASE_PTR)
#define ETF_ITATBCTR2                            ETF_ITATBCTR2_REG(ETF_BASE_PTR)
#define ETF_ITATBCTR1                            ETF_ITATBCTR1_REG(ETF_BASE_PTR)
#define ETF_ITATBCTR0                            ETF_ITATBCTR0_REG(ETF_BASE_PTR)
#define ETF_ITCTRL                               ETF_ITCTRL_REG(ETF_BASE_PTR)
#define ETF_CLAIMSET                             ETF_CLAIMSET_REG(ETF_BASE_PTR)
#define ETF_CLAIMCLR                             ETF_CLAIMCLR_REG(ETF_BASE_PTR)
#define ETF_LAR                                  ETF_LAR_REG(ETF_BASE_PTR)
#define ETF_LSR                                  ETF_LSR_REG(ETF_BASE_PTR)
#define ETF_AUTHSTATUS                           ETF_AUTHSTATUS_REG(ETF_BASE_PTR)
#define ETF_DEVID                                ETF_DEVID_REG(ETF_BASE_PTR)
#define ETF_DEVTYPE                              ETF_DEVTYPE_REG(ETF_BASE_PTR)
#define ETF_PIDR4                                ETF_PIDR4_REG(ETF_BASE_PTR)
#define ETF_PIDR5                                ETF_PIDR5_REG(ETF_BASE_PTR)
#define ETF_PIDR6                                ETF_PIDR6_REG(ETF_BASE_PTR)
#define ETF_PIDR7                                ETF_PIDR7_REG(ETF_BASE_PTR)
#define ETF_PIDR0                                ETF_PIDR0_REG(ETF_BASE_PTR)
#define ETF_PIDR1                                ETF_PIDR1_REG(ETF_BASE_PTR)
#define ETF_PIDR2                                ETF_PIDR2_REG(ETF_BASE_PTR)
#define ETF_PIDR3                                ETF_PIDR3_REG(ETF_BASE_PTR)
#define ETF_CIDR0                                ETF_CIDR0_REG(ETF_BASE_PTR)
#define ETF_CIDR1                                ETF_CIDR1_REG(ETF_BASE_PTR)
#define ETF_CIDR2                                ETF_CIDR2_REG(ETF_BASE_PTR)
#define ETF_CIDR3                                ETF_CIDR3_REG(ETF_BASE_PTR)

/**
 * @}
 */ /* end of group ETF_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ETF_Peripheral */


/* ----------------------------------------------------------------------------
   -- ETM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETM_Peripheral ETM
 * @{
 */

/** ETM - Peripheral register structure */
typedef struct ETM_MemMap {
  uint32_t CR;                                     /**< Main Control Register, offset: 0x0 */
  uint32_t CCR;                                    /**< Configuration Code Register, offset: 0x4 */
  uint32_t TRIGGER;                                /**< Trigger Event Register, offset: 0x8 */
  uint8_t RESERVED_0[4];
  uint32_t SR;                                     /**< ETM Status Register, offset: 0x10 */
  uint32_t SCR;                                    /**< System Configuration Register, offset: 0x14 */
  uint8_t RESERVED_1[8];
  uint32_t EEVR;                                   /**< Trace Enable Event Register, offset: 0x20 */
  uint32_t TECR1;                                  /**< Trace Enable Control 1 Register, offset: 0x24 */
  uint32_t FFLR;                                   /**< FIFOFULL Level Register, offset: 0x28 */
  uint8_t RESERVED_2[276];
  uint32_t CNTRLDVR1;                              /**< Free-running counter reload value, offset: 0x140 */
  uint8_t RESERVED_3[156];
  uint32_t SYNCFR;                                 /**< Synchronization Frequency Register, offset: 0x1E0 */
  uint32_t IDR;                                    /**< ID Register, offset: 0x1E4 */
  uint32_t CCER;                                   /**< Configuration Code Extension Register, offset: 0x1E8 */
  uint8_t RESERVED_4[4];
  uint32_t TESSEICR;                               /**< TraceEnable Start/Stop EmbeddedICE Control Register, offset: 0x1F0 */
  uint8_t RESERVED_5[4];
  uint32_t TSEVR;                                  /**< Timestamp Event Register, offset: 0x1F8 */
  uint8_t RESERVED_6[4];
  uint32_t TRACEIDR;                               /**< CoreSight Trace ID Register, offset: 0x200 */
  uint8_t RESERVED_7[4];
  uint32_t IDR2;                                   /**< ETM ID Register 2, offset: 0x208 */
  uint8_t RESERVED_8[264];
  uint32_t PDSR;                                   /**< Device Power-Down Status Register, offset: 0x314 */
  uint8_t RESERVED_9[3016];
  uint32_t ITMISCIN;                               /**< Integration Test Miscelaneous Inputs Register, offset: 0xEE0 */
  uint8_t RESERVED_10[4];
  uint32_t ITTRIGOUT;                              /**< Integration Test Trigger Out Register, offset: 0xEE8 */
  uint8_t RESERVED_11[4];
  uint32_t ITATBCTR2;                              /**< ETM Integration Test ATB Control 2 Register, offset: 0xEF0 */
  uint8_t RESERVED_12[4];
  uint32_t ITATBCTR0;                              /**< ETM Integration Test ATB Control 0 Register, offset: 0xEF8 */
  uint8_t RESERVED_13[4];
  uint32_t ITCTRL;                                 /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_14[156];
  uint32_t CLAIMSET;                               /**< Claim Tag Set Register, offset: 0xFA0 */
  uint32_t CLAIMCLR;                               /**< Claim Tag Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_15[8];
  uint32_t LAR;                                    /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LSR;                                    /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTATUS;                             /**< Authentication Status Register, offset: 0xFB8 */
  uint8_t RESERVED_16[16];
  uint32_t DEVTYPE;                                /**< CoreSight Device Type Register, offset: 0xFCC */
  uint32_t PIDR4;                                  /**< Peripheral Identification Register 4, offset: 0xFD0 */
  uint32_t PIDR5;                                  /**< Peripheral Identification Register 5, offset: 0xFD4 */
  uint32_t PIDR6;                                  /**< Peripheral Identification Register 6, offset: 0xFD8 */
  uint32_t PIDR7;                                  /**< Peripheral Identification Register 7, offset: 0xFDC */
  uint32_t PIDR0;                                  /**< Peripheral Identification Register 0, offset: 0xFE0 */
  uint32_t PIDR1;                                  /**< Peripheral Identification Register 1, offset: 0xFE4 */
  uint32_t PIDR2;                                  /**< Peripheral Identification Register 2, offset: 0xFE8 */
  uint32_t PIDR3;                                  /**< Peripheral Identification Register 3, offset: 0xFEC */
  uint32_t CIDR0;                                  /**< Component Identification Register 0, offset: 0xFF0 */
  uint32_t CIDR1;                                  /**< Component Identification Register 1, offset: 0xFF4 */
  uint32_t CIDR2;                                  /**< Component Identification Register 2, offset: 0xFF8 */
  uint32_t CIDR3;                                  /**< Component Identification Register 3, offset: 0xFFC */
} volatile *ETM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ETM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETM_Register_Accessor_Macros ETM - Register accessor macros
 * @{
 */


/* ETM - Register accessors */
#define ETM_CR_REG(base)                         ((base)->CR)
#define ETM_CCR_REG(base)                        ((base)->CCR)
#define ETM_TRIGGER_REG(base)                    ((base)->TRIGGER)
#define ETM_SR_REG(base)                         ((base)->SR)
#define ETM_SCR_REG(base)                        ((base)->SCR)
#define ETM_EEVR_REG(base)                       ((base)->EEVR)
#define ETM_TECR1_REG(base)                      ((base)->TECR1)
#define ETM_FFLR_REG(base)                       ((base)->FFLR)
#define ETM_CNTRLDVR1_REG(base)                  ((base)->CNTRLDVR1)
#define ETM_SYNCFR_REG(base)                     ((base)->SYNCFR)
#define ETM_IDR_REG(base)                        ((base)->IDR)
#define ETM_CCER_REG(base)                       ((base)->CCER)
#define ETM_TESSEICR_REG(base)                   ((base)->TESSEICR)
#define ETM_TSEVR_REG(base)                      ((base)->TSEVR)
#define ETM_TRACEIDR_REG(base)                   ((base)->TRACEIDR)
#define ETM_IDR2_REG(base)                       ((base)->IDR2)
#define ETM_PDSR_REG(base)                       ((base)->PDSR)
#define ETM_ITMISCIN_REG(base)                   ((base)->ITMISCIN)
#define ETM_ITTRIGOUT_REG(base)                  ((base)->ITTRIGOUT)
#define ETM_ITATBCTR2_REG(base)                  ((base)->ITATBCTR2)
#define ETM_ITATBCTR0_REG(base)                  ((base)->ITATBCTR0)
#define ETM_ITCTRL_REG(base)                     ((base)->ITCTRL)
#define ETM_CLAIMSET_REG(base)                   ((base)->CLAIMSET)
#define ETM_CLAIMCLR_REG(base)                   ((base)->CLAIMCLR)
#define ETM_LAR_REG(base)                        ((base)->LAR)
#define ETM_LSR_REG(base)                        ((base)->LSR)
#define ETM_AUTHSTATUS_REG(base)                 ((base)->AUTHSTATUS)
#define ETM_DEVTYPE_REG(base)                    ((base)->DEVTYPE)
#define ETM_PIDR4_REG(base)                      ((base)->PIDR4)
#define ETM_PIDR5_REG(base)                      ((base)->PIDR5)
#define ETM_PIDR6_REG(base)                      ((base)->PIDR6)
#define ETM_PIDR7_REG(base)                      ((base)->PIDR7)
#define ETM_PIDR0_REG(base)                      ((base)->PIDR0)
#define ETM_PIDR1_REG(base)                      ((base)->PIDR1)
#define ETM_PIDR2_REG(base)                      ((base)->PIDR2)
#define ETM_PIDR3_REG(base)                      ((base)->PIDR3)
#define ETM_CIDR0_REG(base)                      ((base)->CIDR0)
#define ETM_CIDR1_REG(base)                      ((base)->CIDR1)
#define ETM_CIDR2_REG(base)                      ((base)->CIDR2)
#define ETM_CIDR3_REG(base)                      ((base)->CIDR3)

/**
 * @}
 */ /* end of group ETM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ETM Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETM_Register_Masks ETM Register Masks
 * @{
 */


/**
 * @}
 */ /* end of group ETM_Register_Masks */


/* ETM - Peripheral instance base addresses */
/** Peripheral ETM base pointer */
#define ETM_BASE_PTR                             ((ETM_MemMapPtr)0xE0041000u)

/* ----------------------------------------------------------------------------
   -- ETM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ETM_Register_Accessor_Macros ETM - Register accessor macros
 * @{
 */


/* ETM - Register instance definitions */
/* ETM */
#define ETMCR                                    ETM_CR_REG(ETM_BASE_PTR)
#define ETMCCR                                   ETM_CCR_REG(ETM_BASE_PTR)
#define ETMTRIGGER                               ETM_TRIGGER_REG(ETM_BASE_PTR)
#define ETMSR                                    ETM_SR_REG(ETM_BASE_PTR)
#define ETMSCR                                   ETM_SCR_REG(ETM_BASE_PTR)
#define ETMEEVR                                  ETM_EEVR_REG(ETM_BASE_PTR)
#define ETMTECR1                                 ETM_TECR1_REG(ETM_BASE_PTR)
#define ETMFFLR                                  ETM_FFLR_REG(ETM_BASE_PTR)
#define ETMCNTRLDVR1                             ETM_CNTRLDVR1_REG(ETM_BASE_PTR)
#define ETMSYNCFR                                ETM_SYNCFR_REG(ETM_BASE_PTR)
#define ETMIDR                                   ETM_IDR_REG(ETM_BASE_PTR)
#define ETMCCER                                  ETM_CCER_REG(ETM_BASE_PTR)
#define ETMTESSEICR                              ETM_TESSEICR_REG(ETM_BASE_PTR)
#define ETMTSEVR                                 ETM_TSEVR_REG(ETM_BASE_PTR)
#define ETMTRACEIDR                              ETM_TRACEIDR_REG(ETM_BASE_PTR)
#define ETMIDR2                                  ETM_IDR2_REG(ETM_BASE_PTR)
#define ETMPDSR                                  ETM_PDSR_REG(ETM_BASE_PTR)
#define ETM_ITMISCIN                             ETM_ITMISCIN_REG(ETM_BASE_PTR)
#define ETM_ITTRIGOUT                            ETM_ITTRIGOUT_REG(ETM_BASE_PTR)
#define ETM_ITATBCTR2                            ETM_ITATBCTR2_REG(ETM_BASE_PTR)
#define ETM_ITATBCTR0                            ETM_ITATBCTR0_REG(ETM_BASE_PTR)
#define ETMITCTRL                                ETM_ITCTRL_REG(ETM_BASE_PTR)
#define ETMCLAIMSET                              ETM_CLAIMSET_REG(ETM_BASE_PTR)
#define ETMCLAIMCLR                              ETM_CLAIMCLR_REG(ETM_BASE_PTR)
#define ETMLAR                                   ETM_LAR_REG(ETM_BASE_PTR)
#define ETMLSR                                   ETM_LSR_REG(ETM_BASE_PTR)
#define ETMAUTHSTATUS                            ETM_AUTHSTATUS_REG(ETM_BASE_PTR)
#define ETMDEVTYPE                               ETM_DEVTYPE_REG(ETM_BASE_PTR)
#define ETMPIDR4                                 ETM_PIDR4_REG(ETM_BASE_PTR)
#define ETMPIDR5                                 ETM_PIDR5_REG(ETM_BASE_PTR)
#define ETMPIDR6                                 ETM_PIDR6_REG(ETM_BASE_PTR)
#define ETMPIDR7                                 ETM_PIDR7_REG(ETM_BASE_PTR)
#define ETMPIDR0                                 ETM_PIDR0_REG(ETM_BASE_PTR)
#define ETMPIDR1                                 ETM_PIDR1_REG(ETM_BASE_PTR)
#define ETMPIDR2                                 ETM_PIDR2_REG(ETM_BASE_PTR)
#define ETMPIDR3                                 ETM_PIDR3_REG(ETM_BASE_PTR)
#define ETMCIDR0                                 ETM_CIDR0_REG(ETM_BASE_PTR)
#define ETMCIDR1                                 ETM_CIDR1_REG(ETM_BASE_PTR)
#define ETMCIDR2                                 ETM_CIDR2_REG(ETM_BASE_PTR)
#define ETMCIDR3                                 ETM_CIDR3_REG(ETM_BASE_PTR)

/**
 * @}
 */ /* end of group ETM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ETM_Peripheral */


/* ----------------------------------------------------------------------------
   -- EWM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup EWM_Peripheral EWM
 * @{
 */

/** EWM - Peripheral register structure */
typedef struct EWM_MemMap {
  uint8_t CTRL;                                    /**< Control Register, offset: 0x0 */
  uint8_t SERV;                                    /**< Service Register, offset: 0x1 */
  uint8_t CMPL;                                    /**< Compare Low Register, offset: 0x2 */
  uint8_t CMPH;                                    /**< Compare High Register, offset: 0x3 */
} volatile *EWM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- EWM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup EWM_Register_Accessor_Macros EWM - Register accessor macros
 * @{
 */


/* EWM - Register accessors */
#define EWM_CTRL_REG(base)                       ((base)->CTRL)
#define EWM_SERV_REG(base)                       ((base)->SERV)
#define EWM_CMPL_REG(base)                       ((base)->CMPL)
#define EWM_CMPH_REG(base)                       ((base)->CMPH)

/**
 * @}
 */ /* end of group EWM_Register_Accessor_Macros */



/* EWM - Peripheral instance base addresses */
/** Peripheral EWM base pointer */
#define EWM_BASE_PTR                             ((EWM_MemMapPtr)0x40061000u)

/* ----------------------------------------------------------------------------
   -- EWM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup EWM_Register_Accessor_Macros EWM - Register accessor macros
 * @{
 */


/* EWM - Register instance definitions */
/* EWM */
#define EWM_CTRL                                 EWM_CTRL_REG(EWM_BASE_PTR)
#define EWM_SERV                                 EWM_SERV_REG(EWM_BASE_PTR)
#define EWM_CMPL                                 EWM_CMPL_REG(EWM_BASE_PTR)
#define EWM_CMPH                                 EWM_CMPH_REG(EWM_BASE_PTR)

/**
 * @}
 */ /* end of group EWM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group EWM_Peripheral */


/* ----------------------------------------------------------------------------
   -- FB
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FB_Peripheral FB
 * @{
 */

/** FB - Peripheral register structure */
typedef struct FB_MemMap {
  struct {                                         /* offset: 0x0, array step: 0xC */
    uint32_t CSAR;                                   /**< Chip select address register, array offset: 0x0, array step: 0xC */
    uint32_t CSMR;                                   /**< Chip select mask register, array offset: 0x4, array step: 0xC */
    uint32_t CSCR;                                   /**< Chip select control register, array offset: 0x8, array step: 0xC */
  } CS[6];
  uint8_t RESERVED_0[24];
  uint32_t CSPMCR;                                 /**< Chip select port multiplexing control register, offset: 0x60 */
} volatile *FB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FB_Register_Accessor_Macros FB - Register accessor macros
 * @{
 */


/* FB - Register accessors */
#define FB_CSAR_REG(base,index)                  ((base)->CS[index].CSAR)
#define FB_CSMR_REG(base,index)                  ((base)->CS[index].CSMR)
#define FB_CSCR_REG(base,index)                  ((base)->CS[index].CSCR)
#define FB_CSPMCR_REG(base)                      ((base)->CSPMCR)

/**
 * @}
 */ /* end of group FB_Register_Accessor_Macros */



/* FB - Peripheral instance base addresses */
/** Peripheral FB base pointer */
#define FB_BASE_PTR                              ((FB_MemMapPtr)0x4000C000u)

/* ----------------------------------------------------------------------------
   -- FB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FB_Register_Accessor_Macros FB - Register accessor macros
 * @{
 */


/* FB - Register instance definitions */
/* FB */
#define FB_CSAR0                                 FB_CSAR_REG(FB_BASE_PTR,0)
#define FB_CSMR0                                 FB_CSMR_REG(FB_BASE_PTR,0)
#define FB_CSCR0                                 FB_CSCR_REG(FB_BASE_PTR,0)
#define FB_CSAR1                                 FB_CSAR_REG(FB_BASE_PTR,1)
#define FB_CSMR1                                 FB_CSMR_REG(FB_BASE_PTR,1)
#define FB_CSCR1                                 FB_CSCR_REG(FB_BASE_PTR,1)
#define FB_CSAR2                                 FB_CSAR_REG(FB_BASE_PTR,2)
#define FB_CSMR2                                 FB_CSMR_REG(FB_BASE_PTR,2)
#define FB_CSCR2                                 FB_CSCR_REG(FB_BASE_PTR,2)
#define FB_CSAR3                                 FB_CSAR_REG(FB_BASE_PTR,3)
#define FB_CSMR3                                 FB_CSMR_REG(FB_BASE_PTR,3)
#define FB_CSCR3                                 FB_CSCR_REG(FB_BASE_PTR,3)
#define FB_CSAR4                                 FB_CSAR_REG(FB_BASE_PTR,4)
#define FB_CSMR4                                 FB_CSMR_REG(FB_BASE_PTR,4)
#define FB_CSCR4                                 FB_CSCR_REG(FB_BASE_PTR,4)
#define FB_CSAR5                                 FB_CSAR_REG(FB_BASE_PTR,5)
#define FB_CSMR5                                 FB_CSMR_REG(FB_BASE_PTR,5)
#define FB_CSCR5                                 FB_CSCR_REG(FB_BASE_PTR,5)
#define FB_CSPMCR                                FB_CSPMCR_REG(FB_BASE_PTR)

/* FB - Register array accessors */
#define FB_CSAR(index)                           FB_CSAR_REG(FB_BASE_PTR,index)
#define FB_CSMR(index)                           FB_CSMR_REG(FB_BASE_PTR,index)
#define FB_CSCR(index)                           FB_CSCR_REG(FB_BASE_PTR,index)

/**
 * @}
 */ /* end of group FB_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group FB_Peripheral */


/* ----------------------------------------------------------------------------
   -- FMC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FMC_Peripheral FMC
 * @{
 */

/** FMC - Peripheral register structure */
typedef struct FMC_MemMap {
  uint32_t PFAPR;                                  /**< Flash Access Protection Register, offset: 0x0 */
  uint32_t PFB0CR;                                 /**< Flash Bank 0 Control Register, offset: 0x4 */
  uint32_t PFB1CR;                                 /**< Flash Bank 1 Control Register, offset: 0x8 */
  uint8_t RESERVED_0[244];
  uint32_t TAGVD[4][8];                            /**< Cache Directory Storage, array offset: 0x100, array step: index*0x20, index2*0x4 */
  uint8_t RESERVED_1[128];
  struct {                                         /* offset: 0x200, array step: index*0x40, index2*0x8 */
    uint32_t DATA_U;                                 /**< Cache Data Storage (upper word), array offset: 0x200, array step: index*0x40, index2*0x8 */
    uint32_t DATA_L;                                 /**< Cache Data Storage (lower word), array offset: 0x204, array step: index*0x40, index2*0x8 */
  } SET[4][8];
} volatile *FMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FMC_Register_Accessor_Macros FMC - Register accessor macros
 * @{
 */


/* FMC - Register accessors */
#define FMC_PFAPR_REG(base)                      ((base)->PFAPR)
#define FMC_PFB0CR_REG(base)                     ((base)->PFB0CR)
#define FMC_PFB1CR_REG(base)                     ((base)->PFB1CR)
#define FMC_TAGVD_REG(base,index,index2)         ((base)->TAGVD[index][index2])
#define FMC_DATA_U_REG(base,index,index2)        ((base)->SET[index][index2].DATA_U)
#define FMC_DATA_L_REG(base,index,index2)        ((base)->SET[index][index2].DATA_L)

/**
 * @}
 */ /* end of group FMC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group FMC_Register_Masks */


/* FMC - Peripheral instance base addresses */
/** Peripheral FMC base pointer */
#define FMC_BASE_PTR                             ((FMC_MemMapPtr)0x4001F000u)

/* ----------------------------------------------------------------------------
   -- FMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FMC_Register_Accessor_Macros FMC - Register accessor macros
 * @{
 */


/* FMC - Register instance definitions */
/* FMC */
#define FMC_PFAPR                                FMC_PFAPR_REG(FMC_BASE_PTR)
#define FMC_PFB0CR                               FMC_PFB0CR_REG(FMC_BASE_PTR)
#define FMC_PFB1CR                               FMC_PFB1CR_REG(FMC_BASE_PTR)
#define FMC_TAGVDW0S0                            FMC_TAGVD_REG(FMC_BASE_PTR,0,0)
#define FMC_TAGVDW0S1                            FMC_TAGVD_REG(FMC_BASE_PTR,0,1)
#define FMC_TAGVDW0S2                            FMC_TAGVD_REG(FMC_BASE_PTR,0,2)
#define FMC_TAGVDW0S3                            FMC_TAGVD_REG(FMC_BASE_PTR,0,3)
#define FMC_TAGVDW0S4                            FMC_TAGVD_REG(FMC_BASE_PTR,0,4)
#define FMC_TAGVDW0S5                            FMC_TAGVD_REG(FMC_BASE_PTR,0,5)
#define FMC_TAGVDW0S6                            FMC_TAGVD_REG(FMC_BASE_PTR,0,6)
#define FMC_TAGVDW0S7                            FMC_TAGVD_REG(FMC_BASE_PTR,0,7)
#define FMC_TAGVDW1S0                            FMC_TAGVD_REG(FMC_BASE_PTR,1,0)
#define FMC_TAGVDW1S1                            FMC_TAGVD_REG(FMC_BASE_PTR,1,1)
#define FMC_TAGVDW1S2                            FMC_TAGVD_REG(FMC_BASE_PTR,1,2)
#define FMC_TAGVDW1S3                            FMC_TAGVD_REG(FMC_BASE_PTR,1,3)
#define FMC_TAGVDW1S4                            FMC_TAGVD_REG(FMC_BASE_PTR,1,4)
#define FMC_TAGVDW1S5                            FMC_TAGVD_REG(FMC_BASE_PTR,1,5)
#define FMC_TAGVDW1S6                            FMC_TAGVD_REG(FMC_BASE_PTR,1,6)
#define FMC_TAGVDW1S7                            FMC_TAGVD_REG(FMC_BASE_PTR,1,7)
#define FMC_TAGVDW2S0                            FMC_TAGVD_REG(FMC_BASE_PTR,2,0)
#define FMC_TAGVDW2S1                            FMC_TAGVD_REG(FMC_BASE_PTR,2,1)
#define FMC_TAGVDW2S2                            FMC_TAGVD_REG(FMC_BASE_PTR,2,2)
#define FMC_TAGVDW2S3                            FMC_TAGVD_REG(FMC_BASE_PTR,2,3)
#define FMC_TAGVDW2S4                            FMC_TAGVD_REG(FMC_BASE_PTR,2,4)
#define FMC_TAGVDW2S5                            FMC_TAGVD_REG(FMC_BASE_PTR,2,5)
#define FMC_TAGVDW2S6                            FMC_TAGVD_REG(FMC_BASE_PTR,2,6)
#define FMC_TAGVDW2S7                            FMC_TAGVD_REG(FMC_BASE_PTR,2,7)
#define FMC_TAGVDW3S0                            FMC_TAGVD_REG(FMC_BASE_PTR,3,0)
#define FMC_TAGVDW3S1                            FMC_TAGVD_REG(FMC_BASE_PTR,3,1)
#define FMC_TAGVDW3S2                            FMC_TAGVD_REG(FMC_BASE_PTR,3,2)
#define FMC_TAGVDW3S3                            FMC_TAGVD_REG(FMC_BASE_PTR,3,3)
#define FMC_TAGVDW3S4                            FMC_TAGVD_REG(FMC_BASE_PTR,3,4)
#define FMC_TAGVDW3S5                            FMC_TAGVD_REG(FMC_BASE_PTR,3,5)
#define FMC_TAGVDW3S6                            FMC_TAGVD_REG(FMC_BASE_PTR,3,6)
#define FMC_TAGVDW3S7                            FMC_TAGVD_REG(FMC_BASE_PTR,3,7)
#define FMC_DATAW0S0U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,0)
#define FMC_DATAW0S0L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,0)
#define FMC_DATAW0S1U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,1)
#define FMC_DATAW0S1L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,1)
#define FMC_DATAW0S2U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,2)
#define FMC_DATAW0S2L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,2)
#define FMC_DATAW0S3U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,3)
#define FMC_DATAW0S3L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,3)
#define FMC_DATAW0S4U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,4)
#define FMC_DATAW0S4L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,4)
#define FMC_DATAW0S5U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,5)
#define FMC_DATAW0S5L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,5)
#define FMC_DATAW0S6U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,6)
#define FMC_DATAW0S6L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,6)
#define FMC_DATAW0S7U                            FMC_DATA_U_REG(FMC_BASE_PTR,0,7)
#define FMC_DATAW0S7L                            FMC_DATA_L_REG(FMC_BASE_PTR,0,7)
#define FMC_DATAW1S0U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,0)
#define FMC_DATAW1S0L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,0)
#define FMC_DATAW1S1U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,1)
#define FMC_DATAW1S1L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,1)
#define FMC_DATAW1S2U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,2)
#define FMC_DATAW1S2L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,2)
#define FMC_DATAW1S3U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,3)
#define FMC_DATAW1S3L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,3)
#define FMC_DATAW1S4U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,4)
#define FMC_DATAW1S4L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,4)
#define FMC_DATAW1S5U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,5)
#define FMC_DATAW1S5L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,5)
#define FMC_DATAW1S6U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,6)
#define FMC_DATAW1S6L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,6)
#define FMC_DATAW1S7U                            FMC_DATA_U_REG(FMC_BASE_PTR,1,7)
#define FMC_DATAW1S7L                            FMC_DATA_L_REG(FMC_BASE_PTR,1,7)
#define FMC_DATAW2S0U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,0)
#define FMC_DATAW2S0L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,0)
#define FMC_DATAW2S1U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,1)
#define FMC_DATAW2S1L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,1)
#define FMC_DATAW2S2U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,2)
#define FMC_DATAW2S2L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,2)
#define FMC_DATAW2S3U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,3)
#define FMC_DATAW2S3L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,3)
#define FMC_DATAW2S4U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,4)
#define FMC_DATAW2S4L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,4)
#define FMC_DATAW2S5U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,5)
#define FMC_DATAW2S5L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,5)
#define FMC_DATAW2S6U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,6)
#define FMC_DATAW2S6L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,6)
#define FMC_DATAW2S7U                            FMC_DATA_U_REG(FMC_BASE_PTR,2,7)
#define FMC_DATAW2S7L                            FMC_DATA_L_REG(FMC_BASE_PTR,2,7)
#define FMC_DATAW3S0U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,0)
#define FMC_DATAW3S0L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,0)
#define FMC_DATAW3S1U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,1)
#define FMC_DATAW3S1L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,1)
#define FMC_DATAW3S2U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,2)
#define FMC_DATAW3S2L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,2)
#define FMC_DATAW3S3U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,3)
#define FMC_DATAW3S3L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,3)
#define FMC_DATAW3S4U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,4)
#define FMC_DATAW3S4L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,4)
#define FMC_DATAW3S5U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,5)
#define FMC_DATAW3S5L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,5)
#define FMC_DATAW3S6U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,6)
#define FMC_DATAW3S6L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,6)
#define FMC_DATAW3S7U                            FMC_DATA_U_REG(FMC_BASE_PTR,3,7)
#define FMC_DATAW3S7L                            FMC_DATA_L_REG(FMC_BASE_PTR,3,7)

/* FMC - Register array accessors */
#define FMC_TAGVD(index,index2)                  FMC_TAGVD_REG(FMC_BASE_PTR,index,index2)
#define FMC_DATA_U(index,index2)                 FMC_DATA_U_REG(FMC_BASE_PTR,index,index2)
#define FMC_DATA_L(index,index2)                 FMC_DATA_L_REG(FMC_BASE_PTR,index,index2)

/**
 * @}
 */ /* end of group FMC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group FMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- GPIO
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup GPIO_Peripheral GPIO
 * @{
 */

/** GPIO - Peripheral register structure */
typedef struct GPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
} volatile *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register accessors */
#define GPIO_PDOR_REG(base)                      ((base)->PDOR)
#define GPIO_PSOR_REG(base)                      ((base)->PSOR)
#define GPIO_PCOR_REG(base)                      ((base)->PCOR)
#define GPIO_PTOR_REG(base)                      ((base)->PTOR)
#define GPIO_PDIR_REG(base)                      ((base)->PDIR)
#define GPIO_PDDR_REG(base)                      ((base)->PDDR)

/**
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */

/* GPIO - Peripheral instance base addresses */
/** Peripheral PTA base pointer */
#define PTA_BASE_PTR                             ((GPIO_MemMapPtr)0x400FF000u)
/** Peripheral PTB base pointer */
#define PTB_BASE_PTR                             ((GPIO_MemMapPtr)0x400FF040u)
/** Peripheral PTC base pointer */
#define PTC_BASE_PTR                             ((GPIO_MemMapPtr)0x400FF080u)
/** Peripheral PTD base pointer */
#define PTD_BASE_PTR                             ((GPIO_MemMapPtr)0x400FF0C0u)
/** Peripheral PTE base pointer */
#define PTE_BASE_PTR                             ((GPIO_MemMapPtr)0x400FF100u)
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register instance definitions */
/* PTA */
#define GPIOA_PDOR                               GPIO_PDOR_REG(PTA_BASE_PTR)
#define GPIOA_PSOR                               GPIO_PSOR_REG(PTA_BASE_PTR)
#define GPIOA_PCOR                               GPIO_PCOR_REG(PTA_BASE_PTR)
#define GPIOA_PTOR                               GPIO_PTOR_REG(PTA_BASE_PTR)
#define GPIOA_PDIR                               GPIO_PDIR_REG(PTA_BASE_PTR)
#define GPIOA_PDDR                               GPIO_PDDR_REG(PTA_BASE_PTR)
/* PTB */
#define GPIOB_PDOR                               GPIO_PDOR_REG(PTB_BASE_PTR)
#define GPIOB_PSOR                               GPIO_PSOR_REG(PTB_BASE_PTR)
#define GPIOB_PCOR                               GPIO_PCOR_REG(PTB_BASE_PTR)
#define GPIOB_PTOR                               GPIO_PTOR_REG(PTB_BASE_PTR)
#define GPIOB_PDIR                               GPIO_PDIR_REG(PTB_BASE_PTR)
#define GPIOB_PDDR                               GPIO_PDDR_REG(PTB_BASE_PTR)
/* PTC */
#define GPIOC_PDOR                               GPIO_PDOR_REG(PTC_BASE_PTR)
#define GPIOC_PSOR                               GPIO_PSOR_REG(PTC_BASE_PTR)
#define GPIOC_PCOR                               GPIO_PCOR_REG(PTC_BASE_PTR)
#define GPIOC_PTOR                               GPIO_PTOR_REG(PTC_BASE_PTR)
#define GPIOC_PDIR                               GPIO_PDIR_REG(PTC_BASE_PTR)
#define GPIOC_PDDR                               GPIO_PDDR_REG(PTC_BASE_PTR)
/* PTD */
#define GPIOD_PDOR                               GPIO_PDOR_REG(PTD_BASE_PTR)
#define GPIOD_PSOR                               GPIO_PSOR_REG(PTD_BASE_PTR)
#define GPIOD_PCOR                               GPIO_PCOR_REG(PTD_BASE_PTR)
#define GPIOD_PTOR                               GPIO_PTOR_REG(PTD_BASE_PTR)
#define GPIOD_PDIR                               GPIO_PDIR_REG(PTD_BASE_PTR)
#define GPIOD_PDDR                               GPIO_PDDR_REG(PTD_BASE_PTR)
/* PTE */
#define GPIOE_PDOR                               GPIO_PDOR_REG(PTE_BASE_PTR)
#define GPIOE_PSOR                               GPIO_PSOR_REG(PTE_BASE_PTR)
#define GPIOE_PCOR                               GPIO_PCOR_REG(PTE_BASE_PTR)
#define GPIOE_PTOR                               GPIO_PTOR_REG(PTE_BASE_PTR)
#define GPIOE_PDIR                               GPIO_PDIR_REG(PTE_BASE_PTR)
#define GPIOE_PDDR                               GPIO_PDDR_REG(PTE_BASE_PTR)

/**
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group GPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- I2C
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup I2C_Peripheral I2C
 * @{
 */

/** I2C - Peripheral register structure */
typedef struct I2C_MemMap {
  uint8_t A1;                                      /**< I2C Address Register 1, offset: 0x0 */
  uint8_t F;                                       /**< I2C Frequency Divider register, offset: 0x1 */
  uint8_t C1;                                      /**< I2C Control Register 1, offset: 0x2 */
  uint8_t S;                                       /**< I2C Status register, offset: 0x3 */
  uint8_t D;                                       /**< I2C Data I/O register, offset: 0x4 */
  uint8_t C2;                                      /**< I2C Control Register 2, offset: 0x5 */
  uint8_t FLT;                                     /**< I2C Programmable Input Glitch Filter register, offset: 0x6 */
  uint8_t RA;                                      /**< I2C Range Address register, offset: 0x7 */
  uint8_t SMB;                                     /**< I2C SMBus Control and Status register, offset: 0x8 */
  uint8_t A2;                                      /**< I2C Address Register 2, offset: 0x9 */
  uint8_t SLTH;                                    /**< I2C SCL Low Timeout Register High, offset: 0xA */
  uint8_t SLTL;                                    /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} volatile *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#define I2C_A1_REG(base)                         ((base)->A1)
#define I2C_F_REG(base)                          ((base)->F)
#define I2C_C1_REG(base)                         ((base)->C1)
#define I2C_S_REG(base)                          ((base)->S)
#define I2C_D_REG(base)                          ((base)->D)
#define I2C_C2_REG(base)                         ((base)->C2)
#define I2C_FLT_REG(base)                        ((base)->FLT)
#define I2C_RA_REG(base)                         ((base)->RA)
#define I2C_SMB_REG(base)                        ((base)->SMB)
#define I2C_A2_REG(base)                         ((base)->A2)
#define I2C_SLTH_REG(base)                       ((base)->SLTH)
#define I2C_SLTL_REG(base)                       ((base)->SLTL)

/**
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */

/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base pointer */
#define I2C0_BASE_PTR                            ((I2C_MemMapPtr)0x40066000u)
/** Peripheral I2C1 base pointer */
#define I2C1_BASE_PTR                            ((I2C_MemMapPtr)0x40067000u)
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0_BASE_PTR, I2C1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register instance definitions */
/* I2C0 */
#define I2C0_A1                                  I2C_A1_REG(I2C0_BASE_PTR)
#define I2C0_F                                   I2C_F_REG(I2C0_BASE_PTR)
#define I2C0_C1                                  I2C_C1_REG(I2C0_BASE_PTR)
#define I2C0_S                                   I2C_S_REG(I2C0_BASE_PTR)
#define I2C0_D                                   I2C_D_REG(I2C0_BASE_PTR)
#define I2C0_C2                                  I2C_C2_REG(I2C0_BASE_PTR)
#define I2C0_FLT                                 I2C_FLT_REG(I2C0_BASE_PTR)
#define I2C0_RA                                  I2C_RA_REG(I2C0_BASE_PTR)
#define I2C0_SMB                                 I2C_SMB_REG(I2C0_BASE_PTR)
#define I2C0_A2                                  I2C_A2_REG(I2C0_BASE_PTR)
#define I2C0_SLTH                                I2C_SLTH_REG(I2C0_BASE_PTR)
#define I2C0_SLTL                                I2C_SLTL_REG(I2C0_BASE_PTR)
/* I2C1 */
#define I2C1_A1                                  I2C_A1_REG(I2C1_BASE_PTR)
#define I2C1_F                                   I2C_F_REG(I2C1_BASE_PTR)
#define I2C1_C1                                  I2C_C1_REG(I2C1_BASE_PTR)
#define I2C1_S                                   I2C_S_REG(I2C1_BASE_PTR)
#define I2C1_D                                   I2C_D_REG(I2C1_BASE_PTR)
#define I2C1_C2                                  I2C_C2_REG(I2C1_BASE_PTR)
#define I2C1_FLT                                 I2C_FLT_REG(I2C1_BASE_PTR)
#define I2C1_RA                                  I2C_RA_REG(I2C1_BASE_PTR)
#define I2C1_SMB                                 I2C_SMB_REG(I2C1_BASE_PTR)
#define I2C1_A2                                  I2C_A2_REG(I2C1_BASE_PTR)
#define I2C1_SLTH                                I2C_SLTH_REG(I2C1_BASE_PTR)
#define I2C1_SLTL                                I2C_SLTL_REG(I2C1_BASE_PTR)

/**
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group I2C_Peripheral */


/* ----------------------------------------------------------------------------
   -- LLWU
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup LLWU_Peripheral LLWU
 * @{
 */

/** LLWU - Peripheral register structure */
typedef struct LLWU_MemMap {
  uint8_t PE1;                                     /**< LLWU Pin Enable 1 Register, offset: 0x0 */
  uint8_t PE2;                                     /**< LLWU Pin Enable 2 Register, offset: 0x1 */
  uint8_t PE3;                                     /**< LLWU Pin Enable 3 Register, offset: 0x2 */
  uint8_t PE4;                                     /**< LLWU Pin Enable 4 Register, offset: 0x3 */
  uint8_t ME;                                      /**< LLWU Module Enable Register, offset: 0x4 */
  uint8_t F1;                                      /**< LLWU Flag 1 Register, offset: 0x5 */
  uint8_t F2;                                      /**< LLWU Flag 2 Register, offset: 0x6 */
  uint8_t F3;                                      /**< LLWU Flag 3 Register, offset: 0x7 */
  uint8_t CS;                                      /**< LLWU Control and Status Register, offset: 0x8 */
} volatile *LLWU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register accessors */
#define LLWU_PE1_REG(base)                       ((base)->PE1)
#define LLWU_PE2_REG(base)                       ((base)->PE2)
#define LLWU_PE3_REG(base)                       ((base)->PE3)
#define LLWU_PE4_REG(base)                       ((base)->PE4)
#define LLWU_ME_REG(base)                        ((base)->ME)
#define LLWU_F1_REG(base)                        ((base)->F1)
#define LLWU_F2_REG(base)                        ((base)->F2)
#define LLWU_F3_REG(base)                        ((base)->F3)
#define LLWU_CS_REG(base)                        ((base)->CS)

/**
 * @}
 */ /* end of group LLWU_Register_Accessor_Macros */

/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base pointer */
#define LLWU_BASE_PTR                            ((LLWU_MemMapPtr)0x4007C000u)
/** Array initializer of LLWU peripheral base pointers */
#define LLWU_BASE_PTRS                           { LLWU_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register instance definitions */
/* LLWU */
#define LLWU_PE1                                 LLWU_PE1_REG(LLWU_BASE_PTR)
#define LLWU_PE2                                 LLWU_PE2_REG(LLWU_BASE_PTR)
#define LLWU_PE3                                 LLWU_PE3_REG(LLWU_BASE_PTR)
#define LLWU_PE4                                 LLWU_PE4_REG(LLWU_BASE_PTR)
#define LLWU_ME                                  LLWU_ME_REG(LLWU_BASE_PTR)
#define LLWU_F1                                  LLWU_F1_REG(LLWU_BASE_PTR)
#define LLWU_F2                                  LLWU_F2_REG(LLWU_BASE_PTR)
#define LLWU_F3                                  LLWU_F3_REG(LLWU_BASE_PTR)
#define LLWU_CS                                  LLWU_CS_REG(LLWU_BASE_PTR)

/**
 * @}
 */ /* end of group LLWU_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group LLWU_Peripheral */


/* ----------------------------------------------------------------------------
   -- LPTMR
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup LPTMR_Peripheral LPTMR
 * @{
 */

/** LPTMR - Peripheral register structure */
typedef struct LPTMR_MemMap {
  uint32_t CSR;                                    /**< Low Power Timer Control Status Register, offset: 0x0 */
  uint32_t PSR;                                    /**< Low Power Timer Prescale Register, offset: 0x4 */
  uint32_t CMR;                                    /**< Low Power Timer Compare Register, offset: 0x8 */
  uint32_t CNR;                                    /**< Low Power Timer Counter Register, offset: 0xC */
} volatile *LPTMR_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register accessors */
#define LPTMR_CSR_REG(base)                      ((base)->CSR)
#define LPTMR_PSR_REG(base)                      ((base)->PSR)
#define LPTMR_CMR_REG(base)                      ((base)->CMR)
#define LPTMR_CNR_REG(base)                      ((base)->CNR)

/**
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */

/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR0 base pointer */
#define LPTMR0_BASE_PTR                          ((LPTMR_MemMapPtr)0x40040000u)
/** Array initializer of LPTMR peripheral base pointers */
#define LPTMR_BASE_PTRS                          { LPTMR0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register instance definitions */
/* LPTMR0 */
#define LPTMR0_CSR                               LPTMR_CSR_REG(LPTMR0_BASE_PTR)
#define LPTMR0_PSR                               LPTMR_PSR_REG(LPTMR0_BASE_PTR)
#define LPTMR0_CMR                               LPTMR_CMR_REG(LPTMR0_BASE_PTR)
#define LPTMR0_CNR                               LPTMR_CNR_REG(LPTMR0_BASE_PTR)

/**
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group LPTMR_Peripheral */


/* ----------------------------------------------------------------------------
   -- MC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MC_Peripheral MC
 * @{
 */

/** MC - Peripheral register structure */
typedef struct MC_MemMap {
  uint8_t SRSH;                                    /**< System Reset Status Register High, offset: 0x0 */
  uint8_t SRSL;                                    /**< System Reset Status Register Low, offset: 0x1 */
  uint8_t PMPROT;                                  /**< Power Mode Protection Register, offset: 0x2 */
  uint8_t PMCTRL;                                  /**< Power Mode Control Register, offset: 0x3 */
} volatile *MC_MemMapPtr;


/* ----------------------------------------------------------------------------
   -- MC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MC_Register_Accessor_Macros MC - Register accessor macros
 * @{
 */


/* MC - Register accessors */
#define MC_SRSH_REG(base)                        ((base)->SRSH)
#define MC_SRSL_REG(base)                        ((base)->SRSL)
#define MC_PMPROT_REG(base)                      ((base)->PMPROT)
#define MC_PMCTRL_REG(base)                      ((base)->PMCTRL)

/**
 * @}
 */ /* end of group MC_Register_Accessor_Macros */


/* MC - Peripheral instance base addresses */
/** Peripheral MC base pointer */
#define MC_BASE_PTR                              ((MC_MemMapPtr)0x4007E000u)

/* ----------------------------------------------------------------------------
   -- MC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MC_Register_Accessor_Macros MC - Register accessor macros
 * @{
 */


/* MC - Register instance definitions */
/* MC */
#define MC_SRSH                                  MC_SRSH_REG(MC_BASE_PTR)
#define MC_SRSL                                  MC_SRSL_REG(MC_BASE_PTR)
#define MC_PMPROT                                MC_PMPROT_REG(MC_BASE_PTR)
#define MC_PMCTRL                                MC_PMCTRL_REG(MC_BASE_PTR)

/**
 * @}
 */ /* end of group MC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group MC_Peripheral */



/* ----------------------------------------------------------------------------
   -- MCG
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MCG_Peripheral MCG
 * @{
 */

/** MCG - Peripheral register structure */
typedef struct MCG_MemMap {
  uint8_t C1;                                      /**< MCG Control 1 Register, offset: 0x0 */
  uint8_t C2;                                      /**< MCG Control 2 Register, offset: 0x1 */
  uint8_t C3;                                      /**< MCG Control 3 Register, offset: 0x2 */
  uint8_t C4;                                      /**< MCG Control 4 Register, offset: 0x3 */
  uint8_t C5;                                      /**< MCG Control 5 Register, offset: 0x4 */
  uint8_t C6;                                      /**< MCG Control 6 Register, offset: 0x5 */
  uint8_t S;                                       /**< MCG Status Register, offset: 0x6 */
  uint8_t RESERVED_0[1];
  uint8_t SC;                                      /**< MCG Status and Control Register, offset: 0x8 */
  uint8_t RESERVED_1[1];
  uint8_t ATCVH;                                   /**< MCG Auto Trim Compare Value High Register, offset: 0xA */
  uint8_t ATCVL;                                   /**< MCG Auto Trim Compare Value Low Register, offset: 0xB */
  uint8_t C7;                                      /**< MCG Control 7 Register, offset: 0xC */
  uint8_t C8;                                      /**< MCG Control 8 Register, offset: 0xD */
  uint8_t C9;                                      /**< MCG Control 9 Register, offset: 0xE */
  uint8_t C10;                                     /**< MCG Control 10 Register, offset: 0xF */
} volatile *MCG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register accessors */
#define MCG_C1_REG(base)                         ((base)->C1)
#define MCG_C2_REG(base)                         ((base)->C2)
#define MCG_C3_REG(base)                         ((base)->C3)
#define MCG_C4_REG(base)                         ((base)->C4)
#define MCG_C5_REG(base)                         ((base)->C5)
#define MCG_C6_REG(base)                         ((base)->C6)
#define MCG_S_REG(base)                          ((base)->S)
#define MCG_SC_REG(base)                         ((base)->SC)
#define MCG_ATCVH_REG(base)                      ((base)->ATCVH)
#define MCG_ATCVL_REG(base)                      ((base)->ATCVL)
#define MCG_C7_REG(base)                         ((base)->C7)
#define MCG_C8_REG(base)                         ((base)->C8)
#define MCG_C9_REG(base)                         ((base)->C9)
#define MCG_C10_REG(base)                        ((base)->C10)

/**
 * @}
 */ /* end of group MCG_Register_Accessor_Macros */

/* MCG - Peripheral instance base addresses */
/** Peripheral MCG base pointer */
#define MCG_BASE_PTR                             ((MCG_MemMapPtr)0x40064000u)
/** Array initializer of MCG peripheral base pointers */
#define MCG_BASE_PTRS                            { MCG_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register instance definitions */
/* MCG */
#define MCG_C1                                   MCG_C1_REG(MCG_BASE_PTR)
#define MCG_C2                                   MCG_C2_REG(MCG_BASE_PTR)
#define MCG_C3                                   MCG_C3_REG(MCG_BASE_PTR)
#define MCG_C4                                   MCG_C4_REG(MCG_BASE_PTR)
#define MCG_C5                                   MCG_C5_REG(MCG_BASE_PTR)
#define MCG_C6                                   MCG_C6_REG(MCG_BASE_PTR)
#define MCG_S                                    MCG_S_REG(MCG_BASE_PTR)
#define MCG_SC                                   MCG_SC_REG(MCG_BASE_PTR)
#define MCG_ATCVH                                MCG_ATCVH_REG(MCG_BASE_PTR)
#define MCG_ATCVL                                MCG_ATCVL_REG(MCG_BASE_PTR)
#define MCG_C7                                   MCG_C7_REG(MCG_BASE_PTR)
#define MCG_C8                                   MCG_C8_REG(MCG_BASE_PTR)
#define MCG_C9                                   MCG_C9_REG(MCG_BASE_PTR)
#define MCG_C10                                  MCG_C10_REG(MCG_BASE_PTR)

/**
 * @}
 */ /* end of group MCG_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group MCG_Peripheral */


/* ----------------------------------------------------------------------------
   -- MCM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MCM_Peripheral MCM
 * @{
 */

/** MCM - Peripheral register structure */
typedef struct MCM_MemMap {
  uint8_t RESERVED_0[8];
  uint16_t PLASC;                                  /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  uint16_t PLAMC;                                  /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  uint32_t PLACR;                                  /**< Platform Control Register, offset: 0xC */
  uint8_t RESERVED_1[48];
  uint32_t CPO;                                    /**< Compute Operation Control Register, offset: 0x40 */
} volatile *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register accessors */
#define MCM_PLASC_REG(base)                      ((base)->PLASC)
#define MCM_PLAMC_REG(base)                      ((base)->PLAMC)
#define MCM_PLACR_REG(base)                      ((base)->PLACR)
#define MCM_CPO_REG(base)                        ((base)->CPO)

/**
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */

/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base pointer */
#define MCM_BASE_PTR                             ((MCM_MemMapPtr)0xF0003000u)
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register instance definitions */
/* MCM */
#define MCM_PLASC                                MCM_PLASC_REG(MCM_BASE_PTR)
#define MCM_PLAMC                                MCM_PLAMC_REG(MCM_BASE_PTR)
#define MCM_PLACR                                MCM_PLACR_REG(MCM_BASE_PTR)
#define MCM_CPO                                  MCM_CPO_REG(MCM_BASE_PTR)

/**
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group MCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- MPU
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MPU_Peripheral MPU
 * @{
 */

/** MPU - Peripheral register structure */
typedef struct MPU_MemMap {
  uint32_t CESR;                                   /**< Control/Error Status Register, offset: 0x0 */
  uint8_t RESERVED_0[12];
  struct {                                         /* offset: 0x10, array step: 0x8 */
    uint32_t EAR;                                    /**< Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 */
    uint32_t EDR;                                    /**< Error Detail Register, Slave Port n, array offset: 0x14, array step: 0x8 */
  } SP[5];
  uint8_t RESERVED_1[968];
  uint32_t WORD[12][4];                            /**< Region Descriptor n, Word 0..Region Descriptor n, Word 3, array offset: 0x400, array step: index*0x10, index2*0x4 */
  uint8_t RESERVED_2[832];
  uint32_t RGDAAC[12];                             /**< Region Descriptor Alternate Access Control n, array offset: 0x800, array step: 0x4 */
} volatile *MPU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MPU - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MPU_Register_Accessor_Macros MPU - Register accessor macros
 * @{
 */


/* MPU - Register accessors */
#define MPU_CESR_REG(base)                       ((base)->CESR)
#define MPU_EAR_REG(base,index)                  ((base)->SP[index].EAR)
#define MPU_EDR_REG(base,index)                  ((base)->SP[index].EDR)
#define MPU_WORD_REG(base,index,index2)          ((base)->WORD[index][index2])
#define MPU_RGDAAC_REG(base,index)               ((base)->RGDAAC[index])

/**
 * @}
 */ /* end of group MPU_Register_Accessor_Macros */


/* MPU - Peripheral instance base addresses */
/** Peripheral MPU base pointer */
#define MPU_BASE_PTR                             ((MPU_MemMapPtr)0x4000D000u)

/* ----------------------------------------------------------------------------
   -- MPU - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MPU_Register_Accessor_Macros MPU - Register accessor macros
 * @{
 */


/* MPU - Register instance definitions */
/* MPU */
#define MPU_CESR                                 MPU_CESR_REG(MPU_BASE_PTR)
#define MPU_EAR0                                 MPU_EAR_REG(MPU_BASE_PTR,0)
#define MPU_EDR0                                 MPU_EDR_REG(MPU_BASE_PTR,0)
#define MPU_EAR1                                 MPU_EAR_REG(MPU_BASE_PTR,1)
#define MPU_EDR1                                 MPU_EDR_REG(MPU_BASE_PTR,1)
#define MPU_EAR2                                 MPU_EAR_REG(MPU_BASE_PTR,2)
#define MPU_EDR2                                 MPU_EDR_REG(MPU_BASE_PTR,2)
#define MPU_EAR3                                 MPU_EAR_REG(MPU_BASE_PTR,3)
#define MPU_EDR3                                 MPU_EDR_REG(MPU_BASE_PTR,3)
#define MPU_EAR4                                 MPU_EAR_REG(MPU_BASE_PTR,4)
#define MPU_EDR4                                 MPU_EDR_REG(MPU_BASE_PTR,4)
#define MPU_RGD0_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,0,0)
#define MPU_RGD0_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,0,1)
#define MPU_RGD0_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,0,2)
#define MPU_RGD0_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,0,3)
#define MPU_RGD1_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,1,0)
#define MPU_RGD1_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,1,1)
#define MPU_RGD1_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,1,2)
#define MPU_RGD1_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,1,3)
#define MPU_RGD2_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,2,0)
#define MPU_RGD2_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,2,1)
#define MPU_RGD2_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,2,2)
#define MPU_RGD2_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,2,3)
#define MPU_RGD3_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,3,0)
#define MPU_RGD3_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,3,1)
#define MPU_RGD3_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,3,2)
#define MPU_RGD3_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,3,3)
#define MPU_RGD4_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,4,0)
#define MPU_RGD4_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,4,1)
#define MPU_RGD4_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,4,2)
#define MPU_RGD4_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,4,3)
#define MPU_RGD5_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,5,0)
#define MPU_RGD5_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,5,1)
#define MPU_RGD5_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,5,2)
#define MPU_RGD5_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,5,3)
#define MPU_RGD6_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,6,0)
#define MPU_RGD6_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,6,1)
#define MPU_RGD6_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,6,2)
#define MPU_RGD6_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,6,3)
#define MPU_RGD7_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,7,0)
#define MPU_RGD7_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,7,1)
#define MPU_RGD7_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,7,2)
#define MPU_RGD7_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,7,3)
#define MPU_RGD8_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,8,0)
#define MPU_RGD8_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,8,1)
#define MPU_RGD8_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,8,2)
#define MPU_RGD8_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,8,3)
#define MPU_RGD9_WORD0                           MPU_WORD_REG(MPU_BASE_PTR,9,0)
#define MPU_RGD9_WORD1                           MPU_WORD_REG(MPU_BASE_PTR,9,1)
#define MPU_RGD9_WORD2                           MPU_WORD_REG(MPU_BASE_PTR,9,2)
#define MPU_RGD9_WORD3                           MPU_WORD_REG(MPU_BASE_PTR,9,3)
#define MPU_RGD10_WORD0                          MPU_WORD_REG(MPU_BASE_PTR,10,0)
#define MPU_RGD10_WORD1                          MPU_WORD_REG(MPU_BASE_PTR,10,1)
#define MPU_RGD10_WORD2                          MPU_WORD_REG(MPU_BASE_PTR,10,2)
#define MPU_RGD10_WORD3                          MPU_WORD_REG(MPU_BASE_PTR,10,3)
#define MPU_RGD11_WORD0                          MPU_WORD_REG(MPU_BASE_PTR,11,0)
#define MPU_RGD11_WORD1                          MPU_WORD_REG(MPU_BASE_PTR,11,1)
#define MPU_RGD11_WORD2                          MPU_WORD_REG(MPU_BASE_PTR,11,2)
#define MPU_RGD11_WORD3                          MPU_WORD_REG(MPU_BASE_PTR,11,3)
#define MPU_RGDAAC0                              MPU_RGDAAC_REG(MPU_BASE_PTR,0)
#define MPU_RGDAAC1                              MPU_RGDAAC_REG(MPU_BASE_PTR,1)
#define MPU_RGDAAC2                              MPU_RGDAAC_REG(MPU_BASE_PTR,2)
#define MPU_RGDAAC3                              MPU_RGDAAC_REG(MPU_BASE_PTR,3)
#define MPU_RGDAAC4                              MPU_RGDAAC_REG(MPU_BASE_PTR,4)
#define MPU_RGDAAC5                              MPU_RGDAAC_REG(MPU_BASE_PTR,5)
#define MPU_RGDAAC6                              MPU_RGDAAC_REG(MPU_BASE_PTR,6)
#define MPU_RGDAAC7                              MPU_RGDAAC_REG(MPU_BASE_PTR,7)
#define MPU_RGDAAC8                              MPU_RGDAAC_REG(MPU_BASE_PTR,8)
#define MPU_RGDAAC9                              MPU_RGDAAC_REG(MPU_BASE_PTR,9)
#define MPU_RGDAAC10                             MPU_RGDAAC_REG(MPU_BASE_PTR,10)
#define MPU_RGDAAC11                             MPU_RGDAAC_REG(MPU_BASE_PTR,11)

/* MPU - Register array accessors */
#define MPU_EAR(index)                           MPU_EAR_REG(MPU_BASE_PTR,index)
#define MPU_EDR(index)                           MPU_EDR_REG(MPU_BASE_PTR,index)
#define MPU_WORD(index,index2)                   MPU_WORD_REG(MPU_BASE_PTR,index,index2)
#define MPU_RGDAAC(index)                        MPU_RGDAAC_REG(MPU_BASE_PTR,index)

/**
 * @}
 */ /* end of group MPU_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group MPU_Peripheral */


/* ----------------------------------------------------------------------------
   -- MTB
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MTB_Peripheral MTB
 * @{
 */

/** MTB - Peripheral register structure */
typedef struct MTB_MemMap {
  uint32_t POSITION;                               /**< MTB Position Register, offset: 0x0 */
  uint32_t MASTER;                                 /**< MTB Master Register, offset: 0x4 */
  uint32_t FLOW;                                   /**< MTB Flow Register, offset: 0x8 */
  uint32_t BASE;                                   /**< MTB Base Register, offset: 0xC */
  uint8_t RESERVED_0[3824];
  uint32_t MODECTRL;                               /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_1[156];
  uint32_t TAGSET;                                 /**< Claim TAG Set Register, offset: 0xFA0 */
  uint32_t TAGCLEAR;                               /**< Claim TAG Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_2[8];
  uint32_t LOCKACCESS;                             /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LOCKSTAT;                               /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTAT;                               /**< Authentication Status Register, offset: 0xFB8 */
  uint32_t DEVICEARCH;                             /**< Device Architecture Register, offset: 0xFBC */
  uint8_t RESERVED_3[8];
  uint32_t DEVICECFG;                              /**< Device Configuration Register, offset: 0xFC8 */
  uint32_t DEVICETYPID;                            /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PERIPHID[8];                            /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *MTB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MTB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MTB_Register_Accessor_Macros MTB - Register accessor macros
 * @{
 */


/* MTB - Register accessors */
#define MTB_POSITION_REG(base)                   ((base)->POSITION)
#define MTB_MASTER_REG(base)                     ((base)->MASTER)
#define MTB_FLOW_REG(base)                       ((base)->FLOW)
#define MTB_BASE_REG(base)                       ((base)->BASE)
#define MTB_MODECTRL_REG(base)                   ((base)->MODECTRL)
#define MTB_TAGSET_REG(base)                     ((base)->TAGSET)
#define MTB_TAGCLEAR_REG(base)                   ((base)->TAGCLEAR)
#define MTB_LOCKACCESS_REG(base)                 ((base)->LOCKACCESS)
#define MTB_LOCKSTAT_REG(base)                   ((base)->LOCKSTAT)
#define MTB_AUTHSTAT_REG(base)                   ((base)->AUTHSTAT)
#define MTB_DEVICEARCH_REG(base)                 ((base)->DEVICEARCH)
#define MTB_DEVICECFG_REG(base)                  ((base)->DEVICECFG)
#define MTB_DEVICETYPID_REG(base)                ((base)->DEVICETYPID)
#define MTB_PERIPHID_REG(base,index)             ((base)->PERIPHID[index])
#define MTB_COMPID_REG(base,index)               ((base)->COMPID[index])

/**
 * @}
 */ /* end of group MTB_Register_Accessor_Macros */

/* MTB - Peripheral instance base addresses */
/** Peripheral MTB base pointer */
#define MTB_BASE_PTR                             ((MTB_MemMapPtr)0xF0000000u)
/** Array initializer of MTB peripheral base pointers */
#define MTB_BASE_PTRS                            { MTB_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MTB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MTB_Register_Accessor_Macros MTB - Register accessor macros
 * @{
 */


/* MTB - Register instance definitions */
/* MTB */
#define MTB_POSITION                             MTB_POSITION_REG(MTB_BASE_PTR)
#define MTB_MASTER                               MTB_MASTER_REG(MTB_BASE_PTR)
#define MTB_FLOW                                 MTB_FLOW_REG(MTB_BASE_PTR)
#define MTB_BASE_CR                              MTB_BASE_REG(MTB_BASE_PTR)
#define MTB_MODECTRL                             MTB_MODECTRL_REG(MTB_BASE_PTR)
#define MTB_TAGSET                               MTB_TAGSET_REG(MTB_BASE_PTR)
#define MTB_TAGCLEAR                             MTB_TAGCLEAR_REG(MTB_BASE_PTR)
#define MTB_LOCKACCESS                           MTB_LOCKACCESS_REG(MTB_BASE_PTR)
#define MTB_LOCKSTAT                             MTB_LOCKSTAT_REG(MTB_BASE_PTR)
#define MTB_AUTHSTAT                             MTB_AUTHSTAT_REG(MTB_BASE_PTR)
#define MTB_DEVICEARCH                           MTB_DEVICEARCH_REG(MTB_BASE_PTR)
#define MTB_DEVICECFG                            MTB_DEVICECFG_REG(MTB_BASE_PTR)
#define MTB_DEVICETYPID                          MTB_DEVICETYPID_REG(MTB_BASE_PTR)
#define MTB_PERIPHID4                            MTB_PERIPHID_REG(MTB_BASE_PTR,0)
#define MTB_PERIPHID5                            MTB_PERIPHID_REG(MTB_BASE_PTR,1)
#define MTB_PERIPHID6                            MTB_PERIPHID_REG(MTB_BASE_PTR,2)
#define MTB_PERIPHID7                            MTB_PERIPHID_REG(MTB_BASE_PTR,3)
#define MTB_PERIPHID0                            MTB_PERIPHID_REG(MTB_BASE_PTR,4)
#define MTB_PERIPHID1                            MTB_PERIPHID_REG(MTB_BASE_PTR,5)
#define MTB_PERIPHID2                            MTB_PERIPHID_REG(MTB_BASE_PTR,6)
#define MTB_PERIPHID3                            MTB_PERIPHID_REG(MTB_BASE_PTR,7)
#define MTB_COMPID0                              MTB_COMPID_REG(MTB_BASE_PTR,0)
#define MTB_COMPID1                              MTB_COMPID_REG(MTB_BASE_PTR,1)
#define MTB_COMPID2                              MTB_COMPID_REG(MTB_BASE_PTR,2)
#define MTB_COMPID3                              MTB_COMPID_REG(MTB_BASE_PTR,3)

/* MTB - Register array accessors */
#define MTB_PERIPHID(index)                      MTB_PERIPHID_REG(MTB_BASE_PTR,index)
#define MTB_COMPID(index)                        MTB_COMPID_REG(MTB_BASE_PTR,index)

/**
 * @}
 */ /* end of group MTB_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group MTB_Peripheral */


/* ----------------------------------------------------------------------------
   -- MTBDWT
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MTBDWT_Peripheral MTBDWT
 * @{
 */

/** MTBDWT - Peripheral register structure */
typedef struct MTBDWT_MemMap {
  uint32_t CTRL;                                   /**< MTB DWT Control Register, offset: 0x0 */
  uint8_t RESERVED_0[28];
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< MTB_DWT Comparator Register, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< MTB_DWT Comparator Mask Register, array offset: 0x24, array step: 0x10 */
    uint32_t FCT;                                    /**< MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
  uint8_t RESERVED_1[448];
  uint32_t TBCTRL;                                 /**< MTB_DWT Trace Buffer Control Register, offset: 0x200 */
  uint8_t RESERVED_2[3524];
  uint32_t DEVICECFG;                              /**< Device Configuration Register, offset: 0xFC8 */
  uint32_t DEVICETYPID;                            /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PERIPHID[8];                            /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *MTBDWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MTBDWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MTBDWT_Register_Accessor_Macros MTBDWT - Register accessor macros
 * @{
 */


/* MTBDWT - Register accessors */
#define MTBDWT_CTRL_REG(base)                    ((base)->CTRL)
#define MTBDWT_COMP_REG(base,index)              ((base)->COMPARATOR[index].COMP)
#define MTBDWT_MASK_REG(base,index)              ((base)->COMPARATOR[index].MASK)
#define MTBDWT_FCT_REG(base,index)               ((base)->COMPARATOR[index].FCT)
#define MTBDWT_TBCTRL_REG(base)                  ((base)->TBCTRL)
#define MTBDWT_DEVICECFG_REG(base)               ((base)->DEVICECFG)
#define MTBDWT_DEVICETYPID_REG(base)             ((base)->DEVICETYPID)
#define MTBDWT_PERIPHID_REG(base,index)          ((base)->PERIPHID[index])
#define MTBDWT_COMPID_REG(base,index)            ((base)->COMPID[index])

/**
 * @}
 */ /* end of group MTBDWT_Register_Accessor_Macros */

/* MTBDWT - Peripheral instance base addresses */
/** Peripheral MTBDWT base pointer */
#define MTBDWT_BASE_PTR                          ((MTBDWT_MemMapPtr)0xF0001000u)
/** Array initializer of MTBDWT peripheral base pointers */
#define MTBDWT_BASE_PTRS                         { MTBDWT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MTBDWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup MTBDWT_Register_Accessor_Macros MTBDWT - Register accessor macros
 * @{
 */


/* MTBDWT - Register instance definitions */
/* MTBDWT */
#define MTBDWT_CTRL                              MTBDWT_CTRL_REG(MTBDWT_BASE_PTR)
#define MTBDWT_COMP0                             MTBDWT_COMP_REG(MTBDWT_BASE_PTR,0)
#define MTBDWT_MASK0                             MTBDWT_MASK_REG(MTBDWT_BASE_PTR,0)
#define MTBDWT_FCT0                              MTBDWT_FCT_REG(MTBDWT_BASE_PTR,0)
#define MTBDWT_COMP1                             MTBDWT_COMP_REG(MTBDWT_BASE_PTR,1)
#define MTBDWT_MASK1                             MTBDWT_MASK_REG(MTBDWT_BASE_PTR,1)
#define MTBDWT_FCT1                              MTBDWT_FCT_REG(MTBDWT_BASE_PTR,1)
#define MTBDWT_TBCTRL                            MTBDWT_TBCTRL_REG(MTBDWT_BASE_PTR)
#define MTBDWT_DEVICECFG                         MTBDWT_DEVICECFG_REG(MTBDWT_BASE_PTR)
#define MTBDWT_DEVICETYPID                       MTBDWT_DEVICETYPID_REG(MTBDWT_BASE_PTR)
#define MTBDWT_PERIPHID4                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,0)
#define MTBDWT_PERIPHID5                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,1)
#define MTBDWT_PERIPHID6                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,2)
#define MTBDWT_PERIPHID7                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,3)
#define MTBDWT_PERIPHID0                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,4)
#define MTBDWT_PERIPHID1                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,5)
#define MTBDWT_PERIPHID2                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,6)
#define MTBDWT_PERIPHID3                         MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,7)
#define MTBDWT_COMPID0                           MTBDWT_COMPID_REG(MTBDWT_BASE_PTR,0)
#define MTBDWT_COMPID1                           MTBDWT_COMPID_REG(MTBDWT_BASE_PTR,1)
#define MTBDWT_COMPID2                           MTBDWT_COMPID_REG(MTBDWT_BASE_PTR,2)
#define MTBDWT_COMPID3                           MTBDWT_COMPID_REG(MTBDWT_BASE_PTR,3)

/* MTBDWT - Register array accessors */
#define MTBDWT_COMP(index)                       MTBDWT_COMP_REG(MTBDWT_BASE_PTR,index)
#define MTBDWT_MASK(index)                       MTBDWT_MASK_REG(MTBDWT_BASE_PTR,index)
#define MTBDWT_FCT(index)                        MTBDWT_FCT_REG(MTBDWT_BASE_PTR,index)
#define MTBDWT_PERIPHID(index)                   MTBDWT_PERIPHID_REG(MTBDWT_BASE_PTR,index)
#define MTBDWT_COMPID(index)                     MTBDWT_COMPID_REG(MTBDWT_BASE_PTR,index)

/**
 * @}
 */ /* end of group MTBDWT_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group MTBDWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- NV
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup NV_Peripheral NV
 * @{
 */

/** NV - Peripheral register structure */
typedef struct NV_MemMap {
  uint8_t BACKKEY3;                                /**< Backdoor Comparison Key 3., offset: 0x0 */
  uint8_t BACKKEY2;                                /**< Backdoor Comparison Key 2., offset: 0x1 */
  uint8_t BACKKEY1;                                /**< Backdoor Comparison Key 1., offset: 0x2 */
  uint8_t BACKKEY0;                                /**< Backdoor Comparison Key 0., offset: 0x3 */
  uint8_t BACKKEY7;                                /**< Backdoor Comparison Key 7., offset: 0x4 */
  uint8_t BACKKEY6;                                /**< Backdoor Comparison Key 6., offset: 0x5 */
  uint8_t BACKKEY5;                                /**< Backdoor Comparison Key 5., offset: 0x6 */
  uint8_t BACKKEY4;                                /**< Backdoor Comparison Key 4., offset: 0x7 */
  uint8_t FPROT3;                                  /**< Non-volatile P-Flash Protection 1 - Low Register, offset: 0x8 */
  uint8_t FPROT2;                                  /**< Non-volatile P-Flash Protection 1 - High Register, offset: 0x9 */
  uint8_t FPROT1;                                  /**< Non-volatile P-Flash Protection 0 - Low Register, offset: 0xA */
  uint8_t FPROT0;                                  /**< Non-volatile P-Flash Protection 0 - High Register, offset: 0xB */
  uint8_t FSEC;                                    /**< Non-volatile Flash Security Register, offset: 0xC */
  uint8_t FOPT;                                    /**< Non-volatile Flash Option Register, offset: 0xD */
} volatile *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#define NV_BACKKEY3_REG(base)                    ((base)->BACKKEY3)
#define NV_BACKKEY2_REG(base)                    ((base)->BACKKEY2)
#define NV_BACKKEY1_REG(base)                    ((base)->BACKKEY1)
#define NV_BACKKEY0_REG(base)                    ((base)->BACKKEY0)
#define NV_BACKKEY7_REG(base)                    ((base)->BACKKEY7)
#define NV_BACKKEY6_REG(base)                    ((base)->BACKKEY6)
#define NV_BACKKEY5_REG(base)                    ((base)->BACKKEY5)
#define NV_BACKKEY4_REG(base)                    ((base)->BACKKEY4)
#define NV_FPROT3_REG(base)                      ((base)->FPROT3)
#define NV_FPROT2_REG(base)                      ((base)->FPROT2)
#define NV_FPROT1_REG(base)                      ((base)->FPROT1)
#define NV_FPROT0_REG(base)                      ((base)->FPROT0)
#define NV_FSEC_REG(base)                        ((base)->FSEC)
#define NV_FOPT_REG(base)                        ((base)->FOPT)

/**
 * @}
 */ /* end of group NV_Register_Accessor_Macros */

/* NV - Peripheral instance base addresses */
/** Peripheral FTFA_FlashConfig base pointer */
#define FTFA_FlashConfig_BASE_PTR                ((NV_MemMapPtr)0x400u)
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTFA_FlashConfig_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTFA_FlashConfig */
#define NV_BACKKEY3                              NV_BACKKEY3_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY2                              NV_BACKKEY2_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY1                              NV_BACKKEY1_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY0                              NV_BACKKEY0_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY7                              NV_BACKKEY7_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY6                              NV_BACKKEY6_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY5                              NV_BACKKEY5_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_BACKKEY4                              NV_BACKKEY4_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_FPROT3                                NV_FPROT3_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_FPROT2                                NV_FPROT2_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_FPROT1                                NV_FPROT1_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_FPROT0                                NV_FPROT0_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_FSEC                                  NV_FSEC_REG(FTFA_FlashConfig_BASE_PTR)
#define NV_FOPT                                  NV_FOPT_REG(FTFA_FlashConfig_BASE_PTR)

/**
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group NV_Peripheral */


/* ----------------------------------------------------------------------------
   -- NVIC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup NVIC_Peripheral NVIC
 * @{
 */

/** NVIC - Peripheral register structure */
typedef struct NVIC_MemMap {
  uint32_t ISER[4];                                /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
  uint8_t RESERVED_0[112];
  uint32_t ICER[4];                                /**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
  uint8_t RESERVED_1[112];
  uint32_t ISPR[4];                                /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
  uint8_t RESERVED_2[112];
  uint32_t ICPR[4];                                /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
  uint8_t RESERVED_3[112];
  uint32_t IABR[4];                                /**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
  uint8_t RESERVED_4[240];
  uint8_t IP[104];                                 /**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
  uint8_t RESERVED_5[2712];
  uint32_t STIR[1];                                /**< Software Trigger Interrupt Register, array offset: 0xE00, array step: 0x4 */
} volatile *NVIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register accessors */
#define NVIC_ISER_REG(base,index)                ((base)->ISER[index])
#define NVIC_ICER_REG(base,index)                ((base)->ICER[index])
#define NVIC_ISPR_REG(base,index)                ((base)->ISPR[index])
#define NVIC_ICPR_REG(base,index)                ((base)->ICPR[index])
#define NVIC_IABR_REG(base,index)                ((base)->IABR[index])
#define NVIC_IP_REG(base,index)                  ((base)->IP[index])
#define NVIC_STIR_REG(base,index)                ((base)->STIR[index])
/**
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */

/* NVIC - Peripheral instance base addresses */
/** Peripheral NVIC base pointer */
#define NVIC_BASE_PTR                            ((NVIC_MemMapPtr)0xE000E100u)
/** Array initializer of NVIC peripheral base pointers */
#define NVIC_BASE_PTRS                           { NVIC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register instance definitions */
/* NVIC */
#define NVICISER0                                NVIC_ISER_REG(NVIC_BASE_PTR,0)
#define NVICISER1                                NVIC_ISER_REG(NVIC_BASE_PTR,1)
#define NVICISER2                                NVIC_ISER_REG(NVIC_BASE_PTR,2)
#define NVICISER3                                NVIC_ISER_REG(NVIC_BASE_PTR,3)
#define NVICICER0                                NVIC_ICER_REG(NVIC_BASE_PTR,0)
#define NVICICER1                                NVIC_ICER_REG(NVIC_BASE_PTR,1)
#define NVICICER2                                NVIC_ICER_REG(NVIC_BASE_PTR,2)
#define NVICICER3                                NVIC_ICER_REG(NVIC_BASE_PTR,3)
#define NVICISPR0                                NVIC_ISPR_REG(NVIC_BASE_PTR,0)
#define NVICISPR1                                NVIC_ISPR_REG(NVIC_BASE_PTR,1)
#define NVICISPR2                                NVIC_ISPR_REG(NVIC_BASE_PTR,2)
#define NVICISPR3                                NVIC_ISPR_REG(NVIC_BASE_PTR,3)
#define NVICICPR0                                NVIC_ICPR_REG(NVIC_BASE_PTR,0)
#define NVICICPR1                                NVIC_ICPR_REG(NVIC_BASE_PTR,1)
#define NVICICPR2                                NVIC_ICPR_REG(NVIC_BASE_PTR,2)
#define NVICICPR3                                NVIC_ICPR_REG(NVIC_BASE_PTR,3)
#define NVICIABR0                                NVIC_IABR_REG(NVIC_BASE_PTR,0)
#define NVICIABR1                                NVIC_IABR_REG(NVIC_BASE_PTR,1)
#define NVICIABR2                                NVIC_IABR_REG(NVIC_BASE_PTR,2)
#define NVICIABR3                                NVIC_IABR_REG(NVIC_BASE_PTR,3)
#define NVICIP0                                  NVIC_IP_REG(NVIC_BASE_PTR,0)
#define NVICIP1                                  NVIC_IP_REG(NVIC_BASE_PTR,1)
#define NVICIP2                                  NVIC_IP_REG(NVIC_BASE_PTR,2)
#define NVICIP3                                  NVIC_IP_REG(NVIC_BASE_PTR,3)
#define NVICIP4                                  NVIC_IP_REG(NVIC_BASE_PTR,4)
#define NVICIP5                                  NVIC_IP_REG(NVIC_BASE_PTR,5)
#define NVICIP6                                  NVIC_IP_REG(NVIC_BASE_PTR,6)
#define NVICIP7                                  NVIC_IP_REG(NVIC_BASE_PTR,7)
#define NVICIP8                                  NVIC_IP_REG(NVIC_BASE_PTR,8)
#define NVICIP9                                  NVIC_IP_REG(NVIC_BASE_PTR,9)
#define NVICIP10                                 NVIC_IP_REG(NVIC_BASE_PTR,10)
#define NVICIP11                                 NVIC_IP_REG(NVIC_BASE_PTR,11)
#define NVICIP12                                 NVIC_IP_REG(NVIC_BASE_PTR,12)
#define NVICIP13                                 NVIC_IP_REG(NVIC_BASE_PTR,13)
#define NVICIP14                                 NVIC_IP_REG(NVIC_BASE_PTR,14)
#define NVICIP15                                 NVIC_IP_REG(NVIC_BASE_PTR,15)
#define NVICIP16                                 NVIC_IP_REG(NVIC_BASE_PTR,16)
#define NVICIP17                                 NVIC_IP_REG(NVIC_BASE_PTR,17)
#define NVICIP18                                 NVIC_IP_REG(NVIC_BASE_PTR,18)
#define NVICIP19                                 NVIC_IP_REG(NVIC_BASE_PTR,19)
#define NVICIP20                                 NVIC_IP_REG(NVIC_BASE_PTR,20)
#define NVICIP21                                 NVIC_IP_REG(NVIC_BASE_PTR,21)
#define NVICIP22                                 NVIC_IP_REG(NVIC_BASE_PTR,22)
#define NVICIP23                                 NVIC_IP_REG(NVIC_BASE_PTR,23)
#define NVICIP24                                 NVIC_IP_REG(NVIC_BASE_PTR,24)
#define NVICIP25                                 NVIC_IP_REG(NVIC_BASE_PTR,25)
#define NVICIP26                                 NVIC_IP_REG(NVIC_BASE_PTR,26)
#define NVICIP27                                 NVIC_IP_REG(NVIC_BASE_PTR,27)
#define NVICIP28                                 NVIC_IP_REG(NVIC_BASE_PTR,28)
#define NVICIP29                                 NVIC_IP_REG(NVIC_BASE_PTR,29)
#define NVICIP30                                 NVIC_IP_REG(NVIC_BASE_PTR,30)
#define NVICIP31                                 NVIC_IP_REG(NVIC_BASE_PTR,31)
#define NVICIP32                                 NVIC_IP_REG(NVIC_BASE_PTR,32)
#define NVICIP33                                 NVIC_IP_REG(NVIC_BASE_PTR,33)
#define NVICIP34                                 NVIC_IP_REG(NVIC_BASE_PTR,34)
#define NVICIP35                                 NVIC_IP_REG(NVIC_BASE_PTR,35)
#define NVICIP36                                 NVIC_IP_REG(NVIC_BASE_PTR,36)
#define NVICIP37                                 NVIC_IP_REG(NVIC_BASE_PTR,37)
#define NVICIP38                                 NVIC_IP_REG(NVIC_BASE_PTR,38)
#define NVICIP39                                 NVIC_IP_REG(NVIC_BASE_PTR,39)
#define NVICIP40                                 NVIC_IP_REG(NVIC_BASE_PTR,40)
#define NVICIP41                                 NVIC_IP_REG(NVIC_BASE_PTR,41)
#define NVICIP42                                 NVIC_IP_REG(NVIC_BASE_PTR,42)
#define NVICIP43                                 NVIC_IP_REG(NVIC_BASE_PTR,43)
#define NVICIP44                                 NVIC_IP_REG(NVIC_BASE_PTR,44)
#define NVICIP45                                 NVIC_IP_REG(NVIC_BASE_PTR,45)
#define NVICIP46                                 NVIC_IP_REG(NVIC_BASE_PTR,46)
#define NVICIP47                                 NVIC_IP_REG(NVIC_BASE_PTR,47)
#define NVICIP48                                 NVIC_IP_REG(NVIC_BASE_PTR,48)
#define NVICIP49                                 NVIC_IP_REG(NVIC_BASE_PTR,49)
#define NVICIP50                                 NVIC_IP_REG(NVIC_BASE_PTR,50)
#define NVICIP51                                 NVIC_IP_REG(NVIC_BASE_PTR,51)
#define NVICIP52                                 NVIC_IP_REG(NVIC_BASE_PTR,52)
#define NVICIP53                                 NVIC_IP_REG(NVIC_BASE_PTR,53)
#define NVICIP54                                 NVIC_IP_REG(NVIC_BASE_PTR,54)
#define NVICIP55                                 NVIC_IP_REG(NVIC_BASE_PTR,55)
#define NVICIP56                                 NVIC_IP_REG(NVIC_BASE_PTR,56)
#define NVICIP57                                 NVIC_IP_REG(NVIC_BASE_PTR,57)
#define NVICIP58                                 NVIC_IP_REG(NVIC_BASE_PTR,58)
#define NVICIP59                                 NVIC_IP_REG(NVIC_BASE_PTR,59)
#define NVICIP60                                 NVIC_IP_REG(NVIC_BASE_PTR,60)
#define NVICIP61                                 NVIC_IP_REG(NVIC_BASE_PTR,61)
#define NVICIP62                                 NVIC_IP_REG(NVIC_BASE_PTR,62)
#define NVICIP63                                 NVIC_IP_REG(NVIC_BASE_PTR,63)
#define NVICIP64                                 NVIC_IP_REG(NVIC_BASE_PTR,64)
#define NVICIP65                                 NVIC_IP_REG(NVIC_BASE_PTR,65)
#define NVICIP66                                 NVIC_IP_REG(NVIC_BASE_PTR,66)
#define NVICIP67                                 NVIC_IP_REG(NVIC_BASE_PTR,67)
#define NVICIP68                                 NVIC_IP_REG(NVIC_BASE_PTR,68)
#define NVICIP69                                 NVIC_IP_REG(NVIC_BASE_PTR,69)
#define NVICIP70                                 NVIC_IP_REG(NVIC_BASE_PTR,70)
#define NVICIP71                                 NVIC_IP_REG(NVIC_BASE_PTR,71)
#define NVICIP72                                 NVIC_IP_REG(NVIC_BASE_PTR,72)
#define NVICIP73                                 NVIC_IP_REG(NVIC_BASE_PTR,73)
#define NVICIP74                                 NVIC_IP_REG(NVIC_BASE_PTR,74)
#define NVICIP75                                 NVIC_IP_REG(NVIC_BASE_PTR,75)
#define NVICIP76                                 NVIC_IP_REG(NVIC_BASE_PTR,76)
#define NVICIP77                                 NVIC_IP_REG(NVIC_BASE_PTR,77)
#define NVICIP78                                 NVIC_IP_REG(NVIC_BASE_PTR,78)
#define NVICIP79                                 NVIC_IP_REG(NVIC_BASE_PTR,79)
#define NVICIP80                                 NVIC_IP_REG(NVIC_BASE_PTR,80)
#define NVICIP81                                 NVIC_IP_REG(NVIC_BASE_PTR,81)
#define NVICIP82                                 NVIC_IP_REG(NVIC_BASE_PTR,82)
#define NVICIP83                                 NVIC_IP_REG(NVIC_BASE_PTR,83)
#define NVICIP84                                 NVIC_IP_REG(NVIC_BASE_PTR,84)
#define NVICIP85                                 NVIC_IP_REG(NVIC_BASE_PTR,85)
#define NVICIP86                                 NVIC_IP_REG(NVIC_BASE_PTR,86)
#define NVICIP87                                 NVIC_IP_REG(NVIC_BASE_PTR,87)
#define NVICIP88                                 NVIC_IP_REG(NVIC_BASE_PTR,88)
#define NVICIP89                                 NVIC_IP_REG(NVIC_BASE_PTR,89)
#define NVICIP90                                 NVIC_IP_REG(NVIC_BASE_PTR,90)
#define NVICIP91                                 NVIC_IP_REG(NVIC_BASE_PTR,91)
#define NVICIP92                                 NVIC_IP_REG(NVIC_BASE_PTR,92)
#define NVICIP93                                 NVIC_IP_REG(NVIC_BASE_PTR,93)
#define NVICIP94                                 NVIC_IP_REG(NVIC_BASE_PTR,94)
#define NVICIP95                                 NVIC_IP_REG(NVIC_BASE_PTR,95)
#define NVICIP96                                 NVIC_IP_REG(NVIC_BASE_PTR,96)
#define NVICIP97                                 NVIC_IP_REG(NVIC_BASE_PTR,97)
#define NVICIP98                                 NVIC_IP_REG(NVIC_BASE_PTR,98)
#define NVICIP99                                 NVIC_IP_REG(NVIC_BASE_PTR,99)
#define NVICIP100                                NVIC_IP_REG(NVIC_BASE_PTR,100)
#define NVICIP101                                NVIC_IP_REG(NVIC_BASE_PTR,101)
#define NVICIP102                                NVIC_IP_REG(NVIC_BASE_PTR,102)
#define NVICIP103                                NVIC_IP_REG(NVIC_BASE_PTR,103)
#define NVICSTIR                                 NVIC_STIR_REG(NVIC_BASE_PTR,0)

/* NVIC - Register array accessors */
#define NVIC_ISER(index)                         NVIC_ISER_REG(NVIC_BASE_PTR,index)
#define NVIC_ICER(index)                         NVIC_ICER_REG(NVIC_BASE_PTR,index)
#define NVIC_ISPR(index)                         NVIC_ISPR_REG(NVIC_BASE_PTR,index)
#define NVIC_ICPR(index)                         NVIC_ICPR_REG(NVIC_BASE_PTR,index)
#define NVIC_IABR(index)                         NVIC_IABR_REG(NVIC_BASE_PTR,index)
#define NVIC_IP(index)                           NVIC_IP_REG(NVIC_BASE_PTR,index)
#define NVIC_STIR(index)                         NVIC_STIR_REG(NVIC_BASE_PTR,index)

/**
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group NVIC_Peripheral */


/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register accessors */
#define OSC_CR_REG(base)                         ((base)->CR)

/**
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC0 base pointer */
#define OSC0_BASE_PTR                            ((OSC_MemMapPtr)0x40065000u)
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register instance definitions */
/* OSC0 */
#define OSC0_CR                                  OSC_CR_REG(OSC0_BASE_PTR)

/**
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group OSC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PIT
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PIT_Peripheral PIT
 * @{
 */

/** PIT - Peripheral register structure */
typedef struct PIT_MemMap {
  uint32_t MCR;                                    /**< PIT Module Control Register, offset: 0x0 */
  uint8_t RESERVED_0[220];
  uint32_t LTMR64H;                                /**< PIT Upper Lifetime Timer Register, offset: 0xE0 */
  uint32_t LTMR64L;                                /**< PIT Lower Lifetime Timer Register, offset: 0xE4 */
  uint8_t RESERVED_1[24];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t LDVAL;                                  /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    uint32_t CVAL;                                   /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    uint32_t TCTRL;                                  /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    uint32_t TFLG;                                   /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} volatile *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */
#define PIT_MCR_REG(base)                        ((base)->MCR)
#define PIT_LTMR64H_REG(base)                    ((base)->LTMR64H)
#define PIT_LTMR64L_REG(base)                    ((base)->LTMR64L)
#define PIT_LDVAL_REG(base,index)                ((base)->CHANNEL[index].LDVAL)
#define PIT_CVAL_REG(base,index)                 ((base)->CHANNEL[index].CVAL)
#define PIT_TCTRL_REG(base,index)                ((base)->CHANNEL[index].TCTRL)
#define PIT_TFLG_REG(base,index)                 ((base)->CHANNEL[index].TFLG)

/**
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */

/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base pointer */
#define PIT_BASE_PTR                             ((PIT_MemMapPtr)0x40037000u)
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register instance definitions */
/* PIT */
#define PIT_MCR                                  PIT_MCR_REG(PIT_BASE_PTR)
#define PIT_LTMR64H                              PIT_LTMR64H_REG(PIT_BASE_PTR)
#define PIT_LTMR64L                              PIT_LTMR64L_REG(PIT_BASE_PTR)
#define PIT_LDVAL0                               PIT_LDVAL_REG(PIT_BASE_PTR,0)
#define PIT_CVAL0                                PIT_CVAL_REG(PIT_BASE_PTR,0)
#define PIT_TCTRL0                               PIT_TCTRL_REG(PIT_BASE_PTR,0)
#define PIT_TFLG0                                PIT_TFLG_REG(PIT_BASE_PTR,0)
#define PIT_LDVAL1                               PIT_LDVAL_REG(PIT_BASE_PTR,1)
#define PIT_CVAL1                                PIT_CVAL_REG(PIT_BASE_PTR,1)
#define PIT_TCTRL1                               PIT_TCTRL_REG(PIT_BASE_PTR,1)
#define PIT_TFLG1                                PIT_TFLG_REG(PIT_BASE_PTR,1)

/* PIT - Register array accessors */
#define PIT_LDVAL(index)                         PIT_LDVAL_REG(PIT_BASE_PTR,index)
#define PIT_CVAL(index)                          PIT_CVAL_REG(PIT_BASE_PTR,index)
#define PIT_TCTRL(index)                         PIT_TCTRL_REG(PIT_BASE_PTR,index)
#define PIT_TFLG(index)                          PIT_TFLG_REG(PIT_BASE_PTR,index)

/**
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group PIT_Peripheral */


/* ----------------------------------------------------------------------------
   -- PMC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PMC_Peripheral PMC
 * @{
 */

/** PMC - Peripheral register structure */
typedef struct PMC_MemMap {
  uint8_t LVDSC1;                                  /**< Low Voltage Detect Status And Control 1 register, offset: 0x0 */
  uint8_t LVDSC2;                                  /**< Low Voltage Detect Status And Control 2 register, offset: 0x1 */
  uint8_t REGSC;                                   /**< Regulator Status And Control register, offset: 0x2 */
} volatile *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register accessors */
#define PMC_LVDSC1_REG(base)                     ((base)->LVDSC1)
#define PMC_LVDSC2_REG(base)                     ((base)->LVDSC2)
#define PMC_REGSC_REG(base)                      ((base)->REGSC)

/**
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */

/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base pointer */
#define PMC_BASE_PTR                             ((PMC_MemMapPtr)0x4007D000u)
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register instance definitions */
/* PMC */
#define PMC_LVDSC1                               PMC_LVDSC1_REG(PMC_BASE_PTR)
#define PMC_LVDSC2                               PMC_LVDSC2_REG(PMC_BASE_PTR)
#define PMC_REGSC                                PMC_REGSC_REG(PMC_BASE_PTR)

/**
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group PMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PORT
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PORT_Peripheral PORT
 * @{
 */

/** PORT - Peripheral register structure */
typedef struct PORT_MemMap {
  uint32_t PCR[32];                                /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  uint32_t GPCLR;                                  /**< Global Pin Control Low Register, offset: 0x80 */
  uint32_t GPCHR;                                  /**< Global Pin Control High Register, offset: 0x84 */
  uint8_t RESERVED_0[24];
  uint32_t ISFR;                                   /**< Interrupt Status Flag Register, offset: 0xA0 */
} volatile *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */
#define PORT_PCR_REG(base,index)                 ((base)->PCR[index])
#define PORT_GPCLR_REG(base)                     ((base)->GPCLR)
#define PORT_GPCHR_REG(base)                     ((base)->GPCHR)
#define PORT_ISFR_REG(base)                      ((base)->ISFR)

/**
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */

/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base pointer */
#define PORTA_BASE_PTR                           ((PORT_MemMapPtr)0x40049000u)
/** Peripheral PORTB base pointer */
#define PORTB_BASE_PTR                           ((PORT_MemMapPtr)0x4004A000u)
/** Peripheral PORTC base pointer */
#define PORTC_BASE_PTR                           ((PORT_MemMapPtr)0x4004B000u)
/** Peripheral PORTD base pointer */
#define PORTD_BASE_PTR                           ((PORT_MemMapPtr)0x4004C000u)
/** Peripheral PORTE base pointer */
#define PORTE_BASE_PTR                           ((PORT_MemMapPtr)0x4004D000u)
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register instance definitions */
/* PORTA */
#define PORTA_PCR0                               PORT_PCR_REG(PORTA_BASE_PTR,0)
#define PORTA_PCR1                               PORT_PCR_REG(PORTA_BASE_PTR,1)
#define PORTA_PCR2                               PORT_PCR_REG(PORTA_BASE_PTR,2)
#define PORTA_PCR3                               PORT_PCR_REG(PORTA_BASE_PTR,3)
#define PORTA_PCR4                               PORT_PCR_REG(PORTA_BASE_PTR,4)
#define PORTA_PCR5                               PORT_PCR_REG(PORTA_BASE_PTR,5)
#define PORTA_PCR6                               PORT_PCR_REG(PORTA_BASE_PTR,6)
#define PORTA_PCR7                               PORT_PCR_REG(PORTA_BASE_PTR,7)
#define PORTA_PCR8                               PORT_PCR_REG(PORTA_BASE_PTR,8)
#define PORTA_PCR9                               PORT_PCR_REG(PORTA_BASE_PTR,9)
#define PORTA_PCR10                              PORT_PCR_REG(PORTA_BASE_PTR,10)
#define PORTA_PCR11                              PORT_PCR_REG(PORTA_BASE_PTR,11)
#define PORTA_PCR12                              PORT_PCR_REG(PORTA_BASE_PTR,12)
#define PORTA_PCR13                              PORT_PCR_REG(PORTA_BASE_PTR,13)
#define PORTA_PCR14                              PORT_PCR_REG(PORTA_BASE_PTR,14)
#define PORTA_PCR15                              PORT_PCR_REG(PORTA_BASE_PTR,15)
#define PORTA_PCR16                              PORT_PCR_REG(PORTA_BASE_PTR,16)
#define PORTA_PCR17                              PORT_PCR_REG(PORTA_BASE_PTR,17)
#define PORTA_PCR18                              PORT_PCR_REG(PORTA_BASE_PTR,18)
#define PORTA_PCR19                              PORT_PCR_REG(PORTA_BASE_PTR,19)
#define PORTA_PCR20                              PORT_PCR_REG(PORTA_BASE_PTR,20)
#define PORTA_PCR21                              PORT_PCR_REG(PORTA_BASE_PTR,21)
#define PORTA_PCR22                              PORT_PCR_REG(PORTA_BASE_PTR,22)
#define PORTA_PCR23                              PORT_PCR_REG(PORTA_BASE_PTR,23)
#define PORTA_PCR24                              PORT_PCR_REG(PORTA_BASE_PTR,24)
#define PORTA_PCR25                              PORT_PCR_REG(PORTA_BASE_PTR,25)
#define PORTA_PCR26                              PORT_PCR_REG(PORTA_BASE_PTR,26)
#define PORTA_PCR27                              PORT_PCR_REG(PORTA_BASE_PTR,27)
#define PORTA_PCR28                              PORT_PCR_REG(PORTA_BASE_PTR,28)
#define PORTA_PCR29                              PORT_PCR_REG(PORTA_BASE_PTR,29)
#define PORTA_PCR30                              PORT_PCR_REG(PORTA_BASE_PTR,30)
#define PORTA_PCR31                              PORT_PCR_REG(PORTA_BASE_PTR,31)
#define PORTA_GPCLR                              PORT_GPCLR_REG(PORTA_BASE_PTR)
#define PORTA_GPCHR                              PORT_GPCHR_REG(PORTA_BASE_PTR)
#define PORTA_ISFR                               PORT_ISFR_REG(PORTA_BASE_PTR)
/* PORTB */
#define PORTB_PCR0                               PORT_PCR_REG(PORTB_BASE_PTR,0)
#define PORTB_PCR1                               PORT_PCR_REG(PORTB_BASE_PTR,1)
#define PORTB_PCR2                               PORT_PCR_REG(PORTB_BASE_PTR,2)
#define PORTB_PCR3                               PORT_PCR_REG(PORTB_BASE_PTR,3)
#define PORTB_PCR4                               PORT_PCR_REG(PORTB_BASE_PTR,4)
#define PORTB_PCR5                               PORT_PCR_REG(PORTB_BASE_PTR,5)
#define PORTB_PCR6                               PORT_PCR_REG(PORTB_BASE_PTR,6)
#define PORTB_PCR7                               PORT_PCR_REG(PORTB_BASE_PTR,7)
#define PORTB_PCR8                               PORT_PCR_REG(PORTB_BASE_PTR,8)
#define PORTB_PCR9                               PORT_PCR_REG(PORTB_BASE_PTR,9)
#define PORTB_PCR10                              PORT_PCR_REG(PORTB_BASE_PTR,10)
#define PORTB_PCR11                              PORT_PCR_REG(PORTB_BASE_PTR,11)
#define PORTB_PCR12                              PORT_PCR_REG(PORTB_BASE_PTR,12)
#define PORTB_PCR13                              PORT_PCR_REG(PORTB_BASE_PTR,13)
#define PORTB_PCR14                              PORT_PCR_REG(PORTB_BASE_PTR,14)
#define PORTB_PCR15                              PORT_PCR_REG(PORTB_BASE_PTR,15)
#define PORTB_PCR16                              PORT_PCR_REG(PORTB_BASE_PTR,16)
#define PORTB_PCR17                              PORT_PCR_REG(PORTB_BASE_PTR,17)
#define PORTB_PCR18                              PORT_PCR_REG(PORTB_BASE_PTR,18)
#define PORTB_PCR19                              PORT_PCR_REG(PORTB_BASE_PTR,19)
#define PORTB_PCR20                              PORT_PCR_REG(PORTB_BASE_PTR,20)
#define PORTB_PCR21                              PORT_PCR_REG(PORTB_BASE_PTR,21)
#define PORTB_PCR22                              PORT_PCR_REG(PORTB_BASE_PTR,22)
#define PORTB_PCR23                              PORT_PCR_REG(PORTB_BASE_PTR,23)
#define PORTB_PCR24                              PORT_PCR_REG(PORTB_BASE_PTR,24)
#define PORTB_PCR25                              PORT_PCR_REG(PORTB_BASE_PTR,25)
#define PORTB_PCR26                              PORT_PCR_REG(PORTB_BASE_PTR,26)
#define PORTB_PCR27                              PORT_PCR_REG(PORTB_BASE_PTR,27)
#define PORTB_PCR28                              PORT_PCR_REG(PORTB_BASE_PTR,28)
#define PORTB_PCR29                              PORT_PCR_REG(PORTB_BASE_PTR,29)
#define PORTB_PCR30                              PORT_PCR_REG(PORTB_BASE_PTR,30)
#define PORTB_PCR31                              PORT_PCR_REG(PORTB_BASE_PTR,31)
#define PORTB_GPCLR                              PORT_GPCLR_REG(PORTB_BASE_PTR)
#define PORTB_GPCHR                              PORT_GPCHR_REG(PORTB_BASE_PTR)
#define PORTB_ISFR                               PORT_ISFR_REG(PORTB_BASE_PTR)
/* PORTC */
#define PORTC_PCR0                               PORT_PCR_REG(PORTC_BASE_PTR,0)
#define PORTC_PCR1                               PORT_PCR_REG(PORTC_BASE_PTR,1)
#define PORTC_PCR2                               PORT_PCR_REG(PORTC_BASE_PTR,2)
#define PORTC_PCR3                               PORT_PCR_REG(PORTC_BASE_PTR,3)
#define PORTC_PCR4                               PORT_PCR_REG(PORTC_BASE_PTR,4)
#define PORTC_PCR5                               PORT_PCR_REG(PORTC_BASE_PTR,5)
#define PORTC_PCR6                               PORT_PCR_REG(PORTC_BASE_PTR,6)
#define PORTC_PCR7                               PORT_PCR_REG(PORTC_BASE_PTR,7)
#define PORTC_PCR8                               PORT_PCR_REG(PORTC_BASE_PTR,8)
#define PORTC_PCR9                               PORT_PCR_REG(PORTC_BASE_PTR,9)
#define PORTC_PCR10                              PORT_PCR_REG(PORTC_BASE_PTR,10)
#define PORTC_PCR11                              PORT_PCR_REG(PORTC_BASE_PTR,11)
#define PORTC_PCR12                              PORT_PCR_REG(PORTC_BASE_PTR,12)
#define PORTC_PCR13                              PORT_PCR_REG(PORTC_BASE_PTR,13)
#define PORTC_PCR14                              PORT_PCR_REG(PORTC_BASE_PTR,14)
#define PORTC_PCR15                              PORT_PCR_REG(PORTC_BASE_PTR,15)
#define PORTC_PCR16                              PORT_PCR_REG(PORTC_BASE_PTR,16)
#define PORTC_PCR17                              PORT_PCR_REG(PORTC_BASE_PTR,17)
#define PORTC_PCR18                              PORT_PCR_REG(PORTC_BASE_PTR,18)
#define PORTC_PCR19                              PORT_PCR_REG(PORTC_BASE_PTR,19)
#define PORTC_PCR20                              PORT_PCR_REG(PORTC_BASE_PTR,20)
#define PORTC_PCR21                              PORT_PCR_REG(PORTC_BASE_PTR,21)
#define PORTC_PCR22                              PORT_PCR_REG(PORTC_BASE_PTR,22)
#define PORTC_PCR23                              PORT_PCR_REG(PORTC_BASE_PTR,23)
#define PORTC_PCR24                              PORT_PCR_REG(PORTC_BASE_PTR,24)
#define PORTC_PCR25                              PORT_PCR_REG(PORTC_BASE_PTR,25)
#define PORTC_PCR26                              PORT_PCR_REG(PORTC_BASE_PTR,26)
#define PORTC_PCR27                              PORT_PCR_REG(PORTC_BASE_PTR,27)
#define PORTC_PCR28                              PORT_PCR_REG(PORTC_BASE_PTR,28)
#define PORTC_PCR29                              PORT_PCR_REG(PORTC_BASE_PTR,29)
#define PORTC_PCR30                              PORT_PCR_REG(PORTC_BASE_PTR,30)
#define PORTC_PCR31                              PORT_PCR_REG(PORTC_BASE_PTR,31)
#define PORTC_GPCLR                              PORT_GPCLR_REG(PORTC_BASE_PTR)
#define PORTC_GPCHR                              PORT_GPCHR_REG(PORTC_BASE_PTR)
#define PORTC_ISFR                               PORT_ISFR_REG(PORTC_BASE_PTR)
/* PORTD */
#define PORTD_PCR0                               PORT_PCR_REG(PORTD_BASE_PTR,0)
#define PORTD_PCR1                               PORT_PCR_REG(PORTD_BASE_PTR,1)
#define PORTD_PCR2                               PORT_PCR_REG(PORTD_BASE_PTR,2)
#define PORTD_PCR3                               PORT_PCR_REG(PORTD_BASE_PTR,3)
#define PORTD_PCR4                               PORT_PCR_REG(PORTD_BASE_PTR,4)
#define PORTD_PCR5                               PORT_PCR_REG(PORTD_BASE_PTR,5)
#define PORTD_PCR6                               PORT_PCR_REG(PORTD_BASE_PTR,6)
#define PORTD_PCR7                               PORT_PCR_REG(PORTD_BASE_PTR,7)
#define PORTD_PCR8                               PORT_PCR_REG(PORTD_BASE_PTR,8)
#define PORTD_PCR9                               PORT_PCR_REG(PORTD_BASE_PTR,9)
#define PORTD_PCR10                              PORT_PCR_REG(PORTD_BASE_PTR,10)
#define PORTD_PCR11                              PORT_PCR_REG(PORTD_BASE_PTR,11)
#define PORTD_PCR12                              PORT_PCR_REG(PORTD_BASE_PTR,12)
#define PORTD_PCR13                              PORT_PCR_REG(PORTD_BASE_PTR,13)
#define PORTD_PCR14                              PORT_PCR_REG(PORTD_BASE_PTR,14)
#define PORTD_PCR15                              PORT_PCR_REG(PORTD_BASE_PTR,15)
#define PORTD_PCR16                              PORT_PCR_REG(PORTD_BASE_PTR,16)
#define PORTD_PCR17                              PORT_PCR_REG(PORTD_BASE_PTR,17)
#define PORTD_PCR18                              PORT_PCR_REG(PORTD_BASE_PTR,18)
#define PORTD_PCR19                              PORT_PCR_REG(PORTD_BASE_PTR,19)
#define PORTD_PCR20                              PORT_PCR_REG(PORTD_BASE_PTR,20)
#define PORTD_PCR21                              PORT_PCR_REG(PORTD_BASE_PTR,21)
#define PORTD_PCR22                              PORT_PCR_REG(PORTD_BASE_PTR,22)
#define PORTD_PCR23                              PORT_PCR_REG(PORTD_BASE_PTR,23)
#define PORTD_PCR24                              PORT_PCR_REG(PORTD_BASE_PTR,24)
#define PORTD_PCR25                              PORT_PCR_REG(PORTD_BASE_PTR,25)
#define PORTD_PCR26                              PORT_PCR_REG(PORTD_BASE_PTR,26)
#define PORTD_PCR27                              PORT_PCR_REG(PORTD_BASE_PTR,27)
#define PORTD_PCR28                              PORT_PCR_REG(PORTD_BASE_PTR,28)
#define PORTD_PCR29                              PORT_PCR_REG(PORTD_BASE_PTR,29)
#define PORTD_PCR30                              PORT_PCR_REG(PORTD_BASE_PTR,30)
#define PORTD_PCR31                              PORT_PCR_REG(PORTD_BASE_PTR,31)
#define PORTD_GPCLR                              PORT_GPCLR_REG(PORTD_BASE_PTR)
#define PORTD_GPCHR                              PORT_GPCHR_REG(PORTD_BASE_PTR)
#define PORTD_ISFR                               PORT_ISFR_REG(PORTD_BASE_PTR)
/* PORTE */
#define PORTE_PCR0                               PORT_PCR_REG(PORTE_BASE_PTR,0)
#define PORTE_PCR1                               PORT_PCR_REG(PORTE_BASE_PTR,1)
#define PORTE_PCR2                               PORT_PCR_REG(PORTE_BASE_PTR,2)
#define PORTE_PCR3                               PORT_PCR_REG(PORTE_BASE_PTR,3)
#define PORTE_PCR4                               PORT_PCR_REG(PORTE_BASE_PTR,4)
#define PORTE_PCR5                               PORT_PCR_REG(PORTE_BASE_PTR,5)
#define PORTE_PCR6                               PORT_PCR_REG(PORTE_BASE_PTR,6)
#define PORTE_PCR7                               PORT_PCR_REG(PORTE_BASE_PTR,7)
#define PORTE_PCR8                               PORT_PCR_REG(PORTE_BASE_PTR,8)
#define PORTE_PCR9                               PORT_PCR_REG(PORTE_BASE_PTR,9)
#define PORTE_PCR10                              PORT_PCR_REG(PORTE_BASE_PTR,10)
#define PORTE_PCR11                              PORT_PCR_REG(PORTE_BASE_PTR,11)
#define PORTE_PCR12                              PORT_PCR_REG(PORTE_BASE_PTR,12)
#define PORTE_PCR13                              PORT_PCR_REG(PORTE_BASE_PTR,13)
#define PORTE_PCR14                              PORT_PCR_REG(PORTE_BASE_PTR,14)
#define PORTE_PCR15                              PORT_PCR_REG(PORTE_BASE_PTR,15)
#define PORTE_PCR16                              PORT_PCR_REG(PORTE_BASE_PTR,16)
#define PORTE_PCR17                              PORT_PCR_REG(PORTE_BASE_PTR,17)
#define PORTE_PCR18                              PORT_PCR_REG(PORTE_BASE_PTR,18)
#define PORTE_PCR19                              PORT_PCR_REG(PORTE_BASE_PTR,19)
#define PORTE_PCR20                              PORT_PCR_REG(PORTE_BASE_PTR,20)
#define PORTE_PCR21                              PORT_PCR_REG(PORTE_BASE_PTR,21)
#define PORTE_PCR22                              PORT_PCR_REG(PORTE_BASE_PTR,22)
#define PORTE_PCR23                              PORT_PCR_REG(PORTE_BASE_PTR,23)
#define PORTE_PCR24                              PORT_PCR_REG(PORTE_BASE_PTR,24)
#define PORTE_PCR25                              PORT_PCR_REG(PORTE_BASE_PTR,25)
#define PORTE_PCR26                              PORT_PCR_REG(PORTE_BASE_PTR,26)
#define PORTE_PCR27                              PORT_PCR_REG(PORTE_BASE_PTR,27)
#define PORTE_PCR28                              PORT_PCR_REG(PORTE_BASE_PTR,28)
#define PORTE_PCR29                              PORT_PCR_REG(PORTE_BASE_PTR,29)
#define PORTE_PCR30                              PORT_PCR_REG(PORTE_BASE_PTR,30)
#define PORTE_PCR31                              PORT_PCR_REG(PORTE_BASE_PTR,31)
#define PORTE_GPCLR                              PORT_GPCLR_REG(PORTE_BASE_PTR)
#define PORTE_GPCHR                              PORT_GPCHR_REG(PORTE_BASE_PTR)
#define PORTE_ISFR                               PORT_ISFR_REG(PORTE_BASE_PTR)

/* PORT - Register array accessors */
#define PORTA_PCR(index)                         PORT_PCR_REG(PORTA_BASE_PTR,index)
#define PORTB_PCR(index)                         PORT_PCR_REG(PORTB_BASE_PTR,index)
#define PORTC_PCR(index)                         PORT_PCR_REG(PORTC_BASE_PTR,index)
#define PORTD_PCR(index)                         PORT_PCR_REG(PORTD_BASE_PTR,index)
#define PORTE_PCR(index)                         PORT_PCR_REG(PORTE_BASE_PTR,index)

/**
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group PORT_Peripheral */


/* ----------------------------------------------------------------------------
   -- RCM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup RCM_Peripheral RCM
 * @{
 */

/** RCM - Peripheral register structure */
typedef struct RCM_MemMap {
  uint8_t SRS0;                                    /**< System Reset Status Register 0, offset: 0x0 */
  uint8_t SRS1;                                    /**< System Reset Status Register 1, offset: 0x1 */
  uint8_t RESERVED_0[2];
  uint8_t RPFC;                                    /**< Reset Pin Filter Control register, offset: 0x4 */
  uint8_t RPFW;                                    /**< Reset Pin Filter Width register, offset: 0x5 */
} volatile *RCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup RCM_Register_Accessor_Macros RCM - Register accessor macros
 * @{
 */


/* RCM - Register accessors */
#define RCM_SRS0_REG(base)                       ((base)->SRS0)
#define RCM_SRS1_REG(base)                       ((base)->SRS1)
#define RCM_RPFC_REG(base)                       ((base)->RPFC)
#define RCM_RPFW_REG(base)                       ((base)->RPFW)

/**
 * @}
 */ /* end of group RCM_Register_Accessor_Macros */


/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base pointer */
#define RCM_BASE_PTR                             ((RCM_MemMapPtr)0x4007F000u)
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS                            { RCM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- RCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup RCM_Register_Accessor_Macros RCM - Register accessor macros
 * @{
 */


/* RCM - Register instance definitions */
/* RCM */
#define RCM_SRS0                                 RCM_SRS0_REG(RCM_BASE_PTR)
#define RCM_SRS1                                 RCM_SRS1_REG(RCM_BASE_PTR)
#define RCM_RPFC                                 RCM_RPFC_REG(RCM_BASE_PTR)
#define RCM_RPFW                                 RCM_RPFW_REG(RCM_BASE_PTR)

/**
 * @}
 */ /* end of group RCM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group RCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- ROM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ROM_Peripheral ROM
 * @{
 */

/** ROM - Peripheral register structure */
typedef struct ROM_MemMap {
  uint32_t ENTRY[3];                               /**< Entry, array offset: 0x0, array step: 0x4 */
  uint32_t TABLEMARK;                              /**< End of Table Marker Register, offset: 0xC */
  uint8_t RESERVED_0[4028];
  uint32_t SYSACCESS;                              /**< System Access Register, offset: 0xFCC */
  uint32_t PERIPHID4;                              /**< Peripheral ID Register, offset: 0xFD0 */
  uint32_t PERIPHID5;                              /**< Peripheral ID Register, offset: 0xFD4 */
  uint32_t PERIPHID6;                              /**< Peripheral ID Register, offset: 0xFD8 */
  uint32_t PERIPHID7;                              /**< Peripheral ID Register, offset: 0xFDC */
  uint32_t PERIPHID0;                              /**< Peripheral ID Register, offset: 0xFE0 */
  uint32_t PERIPHID1;                              /**< Peripheral ID Register, offset: 0xFE4 */
  uint32_t PERIPHID2;                              /**< Peripheral ID Register, offset: 0xFE8 */
  uint32_t PERIPHID3;                              /**< Peripheral ID Register, offset: 0xFEC */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *ROM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register accessors */
#define ROM_ENTRY_REG(base,index)                ((base)->ENTRY[index])
#define ROM_TABLEMARK_REG(base)                  ((base)->TABLEMARK)
#define ROM_SYSACCESS_REG(base)                  ((base)->SYSACCESS)
#define ROM_PERIPHID4_REG(base)                  ((base)->PERIPHID4)
#define ROM_PERIPHID5_REG(base)                  ((base)->PERIPHID5)
#define ROM_PERIPHID6_REG(base)                  ((base)->PERIPHID6)
#define ROM_PERIPHID7_REG(base)                  ((base)->PERIPHID7)
#define ROM_PERIPHID0_REG(base)                  ((base)->PERIPHID0)
#define ROM_PERIPHID1_REG(base)                  ((base)->PERIPHID1)
#define ROM_PERIPHID2_REG(base)                  ((base)->PERIPHID2)
#define ROM_PERIPHID3_REG(base)                  ((base)->PERIPHID3)
#define ROM_COMPID_REG(base,index)               ((base)->COMPID[index])

/**
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */

/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base pointer */
#define ROM_BASE_PTR                             ((ROM_MemMapPtr)0xF0002000u)
/** Array initializer of ROM peripheral base pointers */
#define ROM_BASE_PTRS                            { ROM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register instance definitions */
/* ROM */
#define ROM_ENTRY0                               ROM_ENTRY_REG(ROM_BASE_PTR,0)
#define ROM_ENTRY1                               ROM_ENTRY_REG(ROM_BASE_PTR,1)
#define ROM_ENTRY2                               ROM_ENTRY_REG(ROM_BASE_PTR,2)
#define ROM_TABLEMARK                            ROM_TABLEMARK_REG(ROM_BASE_PTR)
#define ROM_SYSACCESS                            ROM_SYSACCESS_REG(ROM_BASE_PTR)
#define ROM_PERIPHID4                            ROM_PERIPHID4_REG(ROM_BASE_PTR)
#define ROM_PERIPHID5                            ROM_PERIPHID5_REG(ROM_BASE_PTR)
#define ROM_PERIPHID6                            ROM_PERIPHID6_REG(ROM_BASE_PTR)
#define ROM_PERIPHID7                            ROM_PERIPHID7_REG(ROM_BASE_PTR)
#define ROM_PERIPHID0                            ROM_PERIPHID0_REG(ROM_BASE_PTR)
#define ROM_PERIPHID1                            ROM_PERIPHID1_REG(ROM_BASE_PTR)
#define ROM_PERIPHID2                            ROM_PERIPHID2_REG(ROM_BASE_PTR)
#define ROM_PERIPHID3                            ROM_PERIPHID3_REG(ROM_BASE_PTR)
#define ROM_COMPID0                              ROM_COMPID_REG(ROM_BASE_PTR,0)
#define ROM_COMPID1                              ROM_COMPID_REG(ROM_BASE_PTR,1)
#define ROM_COMPID2                              ROM_COMPID_REG(ROM_BASE_PTR,2)
#define ROM_COMPID3                              ROM_COMPID_REG(ROM_BASE_PTR,3)

/* ROM - Register array accessors */
#define ROM_ENTRY(index)                         ROM_ENTRY_REG(ROM_BASE_PTR,index)
#define ROM_COMPID(index)                        ROM_COMPID_REG(ROM_BASE_PTR,index)

/**
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group ROM_Peripheral */


/* ----------------------------------------------------------------------------
   -- RTC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup RTC_Peripheral RTC
 * @{
 */

/** RTC - Peripheral register structure */
typedef struct RTC_MemMap {
  uint32_t TSR;                                    /**< RTC Time Seconds Register, offset: 0x0 */
  uint32_t TPR;                                    /**< RTC Time Prescaler Register, offset: 0x4 */
  uint32_t TAR;                                    /**< RTC Time Alarm Register, offset: 0x8 */
  uint32_t TCR;                                    /**< RTC Time Compensation Register, offset: 0xC */
  uint32_t CR;                                     /**< RTC Control Register, offset: 0x10 */
  uint32_t SR;                                     /**< RTC Status Register, offset: 0x14 */
  uint32_t LR;                                     /**< RTC Lock Register, offset: 0x18 */
  uint32_t IER;                                    /**< RTC Interrupt Enable Register, offset: 0x1C */
} volatile *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#define RTC_TSR_REG(base)                        ((base)->TSR)
#define RTC_TPR_REG(base)                        ((base)->TPR)
#define RTC_TAR_REG(base)                        ((base)->TAR)
#define RTC_TCR_REG(base)                        ((base)->TCR)
#define RTC_CR_REG(base)                         ((base)->CR)
#define RTC_SR_REG(base)                         ((base)->SR)
#define RTC_LR_REG(base)                         ((base)->LR)
#define RTC_IER_REG(base)                        ((base)->IER)

/**
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */

/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base pointer */
#define RTC_BASE_PTR                             ((RTC_MemMapPtr)0x4003D000u)
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register instance definitions */
/* RTC */
#define RTC_TSR                                  RTC_TSR_REG(RTC_BASE_PTR)
#define RTC_TPR                                  RTC_TPR_REG(RTC_BASE_PTR)
#define RTC_TAR                                  RTC_TAR_REG(RTC_BASE_PTR)
#define RTC_TCR                                  RTC_TCR_REG(RTC_BASE_PTR)
#define RTC_CR                                   RTC_CR_REG(RTC_BASE_PTR)
#define RTC_SR                                   RTC_SR_REG(RTC_BASE_PTR)
#define RTC_LR                                   RTC_LR_REG(RTC_BASE_PTR)
#define RTC_IER                                  RTC_IER_REG(RTC_BASE_PTR)

/**
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group RTC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SCB
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SCB_Peripheral SCB
 * @{
 */

/** SCB - Peripheral register structure */
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                  /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                  /**< CPUID Base Register, offset: 0xD00 */
  uint32_t ICSR;                                   /**< Interrupt Control and State Register, offset: 0xD04 */
  uint32_t VTOR;                                   /**< Vector Table Offset Register, offset: 0xD08 */
  uint32_t AIRCR;                                  /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  uint32_t SCR;                                    /**< System Control Register, offset: 0xD10 */
  uint32_t CCR;                                    /**< Configuration and Control Register, offset: 0xD14 */
  uint8_t RESERVED_2[4];
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint8_t RESERVED_3[8];
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register accessors */
#define SCB_ACTLR_REG(base)                      ((base)->ACTLR)
#define SCB_CPUID_REG(base)                      ((base)->CPUID)
#define SCB_ICSR_REG(base)                       ((base)->ICSR)
#define SCB_VTOR_REG(base)                       ((base)->VTOR)
#define SCB_AIRCR_REG(base)                      ((base)->AIRCR)
#define SCB_SCR_REG(base)                        ((base)->SCR)
#define SCB_CCR_REG(base)                        ((base)->CCR)
#define SCB_SHPR2_REG(base)                      ((base)->SHPR2)
#define SCB_SHPR3_REG(base)                      ((base)->SHPR3)
#define SCB_SHCSR_REG(base)                      ((base)->SHCSR)
#define SCB_DFSR_REG(base)                       ((base)->DFSR)

/**
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/* SCB - Peripheral instance base addresses */
/** Peripheral SystemControl base pointer */
#define SystemControl_BASE_PTR                   ((SCB_MemMapPtr)0xE000E000u)
/** Array initializer of SCB peripheral base pointers */
#define SCB_BASE_PTRS                            { SystemControl_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register instance definitions */
/* SystemControl */
#define SCB_ACTLR                                SCB_ACTLR_REG(SystemControl_BASE_PTR)
#define SCB_CPUID                                SCB_CPUID_REG(SystemControl_BASE_PTR)
#define SCB_ICSR                                 SCB_ICSR_REG(SystemControl_BASE_PTR)
#define SCB_VTOR                                 SCB_VTOR_REG(SystemControl_BASE_PTR)
#define SCB_AIRCR                                SCB_AIRCR_REG(SystemControl_BASE_PTR)
#define SCB_SCR                                  SCB_SCR_REG(SystemControl_BASE_PTR)
#define SCB_CCR                                  SCB_CCR_REG(SystemControl_BASE_PTR)
#define SCB_SHPR2                                SCB_SHPR2_REG(SystemControl_BASE_PTR)
#define SCB_SHPR3                                SCB_SHPR3_REG(SystemControl_BASE_PTR)
#define SCB_SHCSR                                SCB_SHCSR_REG(SystemControl_BASE_PTR)
#define SCB_DFSR                                 SCB_DFSR_REG(SystemControl_BASE_PTR)

/**
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group SCB_Peripheral */


/* ----------------------------------------------------------------------------
   -- SIM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SIM_Peripheral SIM
 * @{
 */

/** SIM - Peripheral register structure */
typedef struct SIM_MemMap {
  uint32_t SOPT1;                                  /**< System Options Register 1, offset: 0x0 */
  uint8_t RESERVED_0[4096];
  uint32_t SOPT2;                                  /**< System Options Register 2, offset: 0x1004 */
  uint8_t RESERVED_1[4];
  uint32_t SOPT4;                                  /**< System Options Register 4, offset: 0x100C */
  uint32_t SOPT5;                                  /**< System Options Register 5, offset: 0x1010 */
  uint32_t SOPT6;                                  /**< System Options Register 6, offset: 0x1014 */
  uint32_t SOPT7;                                  /**< System Options Register 7, offset: 0x1018 */
  uint8_t RESERVED_2[8];
  uint32_t SDID;                                   /**< System Device Identification Register, offset: 0x1024 */
  uint32_t SCGC1;                                  /**< System Clock Gating Control Register 1, offset: 0x1028 */
  uint32_t SCGC2;                                  /**< System Clock Gating Control Register 2, offset: 0x102C */
  uint32_t SCGC3;                                  /**< System Clock Gating Control Register 3, offset: 0x1030 */
  uint32_t SCGC4;                                  /**< System Clock Gating Control Register 4, offset: 0x1034 */
  uint32_t SCGC5;                                  /**< System Clock Gating Control Register 5, offset: 0x1038 */
  uint32_t SCGC6;                                  /**< System Clock Gating Control Register 6, offset: 0x103C */
  uint32_t SCGC7;                                  /**< System Clock Gating Control Register 7, offset: 0x1040 */
  uint32_t CLKDIV1;                                /**< System Clock Divider Register 1, offset: 0x1044 */
  uint32_t CLKDIV2;                                /**< System Clock Divider Register 2, offset: 0x1048 */
  uint32_t FCFG1;                                  /**< Flash Configuration Register 1, offset: 0x104C */
  uint32_t FCFG2;                                  /**< Flash Configuration Register 2, offset: 0x1050 */
  uint32_t UIDH;                                   /**< Unique Identification Register High, offset: 0x1054 */
  uint32_t UIDMH;                                  /**< Unique Identification Register Mid-High, offset: 0x1058 */
  uint32_t UIDML;                                  /**< Unique Identification Register Mid Low, offset: 0x105C */
  uint32_t UIDL;                                   /**< Unique Identification Register Low, offset: 0x1060 */
} volatile *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#define SIM_SOPT1_REG(base)                      ((base)->SOPT1)
#define SIM_SOPT2_REG(base)                      ((base)->SOPT2)
#define SIM_SOPT4_REG(base)                      ((base)->SOPT4)
#define SIM_SOPT5_REG(base)                      ((base)->SOPT5)
#define SIM_SOPT6_REG(base)                      ((base)->SOPT6)
#define SIM_SOPT7_REG(base)                      ((base)->SOPT7)
#define SIM_SDID_REG(base)                       ((base)->SDID)
#define SIM_SCGC1_REG(base)                      ((base)->SCGC1)
#define SIM_SCGC2_REG(base)                      ((base)->SCGC2)
#define SIM_SCGC3_REG(base)                      ((base)->SCGC3)
#define SIM_SCGC4_REG(base)                      ((base)->SCGC4)
#define SIM_SCGC5_REG(base)                      ((base)->SCGC5)
#define SIM_SCGC6_REG(base)                      ((base)->SCGC6)
#define SIM_SCGC7_REG(base)                      ((base)->SCGC7)
#define SIM_CLKDIV1_REG(base)                    ((base)->CLKDIV1)
#define SIM_CLKDIV2_REG(base)                    ((base)->CLKDIV2)
#define SIM_FCFG1_REG(base)                      ((base)->FCFG1)
#define SIM_FCFG2_REG(base)                      ((base)->FCFG2)
#define SIM_UIDH_REG(base)                       ((base)->UIDH)
#define SIM_UIDMH_REG(base)                      ((base)->UIDMH)
#define SIM_UIDML_REG(base)                      ((base)->UIDML)
#define SIM_UIDL_REG(base)                       ((base)->UIDL)

/**
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base pointer */
#define SIM_BASE_PTR                             ((SIM_MemMapPtr)0x40047000u)
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register instance definitions */
/* SIM */
#define SIM_SOPT1                                SIM_SOPT1_REG(SIM_BASE_PTR)
#define SIM_SOPT2                                SIM_SOPT2_REG(SIM_BASE_PTR)
#define SIM_SOPT4                                SIM_SOPT4_REG(SIM_BASE_PTR)
#define SIM_SOPT5                                SIM_SOPT5_REG(SIM_BASE_PTR)
#define SIM_SOPT6                                SIM_SOPT6_REG(SIM_BASE_PTR)
#define SIM_SOPT7                                SIM_SOPT7_REG(SIM_BASE_PTR)
#define SIM_SDID                                 SIM_SDID_REG(SIM_BASE_PTR)
#define SIM_SCGC1                                SIM_SCGC1_REG(SIM_BASE_PTR)
#define SIM_SCGC2                                SIM_SCGC2_REG(SIM_BASE_PTR)
#define SIM_SCGC3                                SIM_SCGC3_REG(SIM_BASE_PTR)
#define SIM_SCGC4                                SIM_SCGC4_REG(SIM_BASE_PTR)
#define SIM_SCGC5                                SIM_SCGC5_REG(SIM_BASE_PTR)
#define SIM_SCGC6                                SIM_SCGC6_REG(SIM_BASE_PTR)
#define SIM_SCGC7                                SIM_SCGC7_REG(SIM_BASE_PTR)
#define SIM_CLKDIV1                              SIM_CLKDIV1_REG(SIM_BASE_PTR)
#define SIM_CLKDIV2                              SIM_CLKDIV2_REG(SIM_BASE_PTR)
#define SIM_FCFG1                                SIM_FCFG1_REG(SIM_BASE_PTR)
#define SIM_FCFG2                                SIM_FCFG2_REG(SIM_BASE_PTR)
#define SIM_UIDH                                 SIM_UIDH_REG(SIM_BASE_PTR)
#define SIM_UIDMH                                SIM_UIDMH_REG(SIM_BASE_PTR)
#define SIM_UIDML                                SIM_UIDML_REG(SIM_BASE_PTR)
#define SIM_UIDL                                 SIM_UIDL_REG(SIM_BASE_PTR)

/**
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group SIM_Peripheral */


/* ----------------------------------------------------------------------------
   -- SMC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SMC_Peripheral SMC
 * @{
 */

/** SMC - Peripheral register structure */
typedef struct SMC_MemMap {
  uint8_t PMPROT;                                  /**< Power Mode Protection register, offset: 0x0 */
  uint8_t PMCTRL;                                  /**< Power Mode Control register, offset: 0x1 */
  uint8_t STOPCTRL;                                /**< Stop Control Register, offset: 0x2 */
  uint8_t PMSTAT;                                  /**< Power Mode Status register, offset: 0x3 */
} volatile *SMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SMC_Register_Accessor_Macros SMC - Register accessor macros
 * @{
 */


/* SMC - Register accessors */
#define SMC_PMPROT_REG(base)                     ((base)->PMPROT)
#define SMC_PMCTRL_REG(base)                     ((base)->PMCTRL)
#define SMC_STOPCTRL_REG(base)                   ((base)->STOPCTRL)
#define SMC_PMSTAT_REG(base)                     ((base)->PMSTAT)

/**
 * @}
 */ /* end of group SMC_Register_Accessor_Macros */

/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base pointer */
#define SMC_BASE_PTR                             ((SMC_MemMapPtr)0x4007E000u)
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS                            { SMC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SMC_Register_Accessor_Macros SMC - Register accessor macros
 * @{
 */


/* SMC - Register instance definitions */
/* SMC */
#define SMC_PMPROT                               SMC_PMPROT_REG(SMC_BASE_PTR)
#define SMC_PMCTRL                               SMC_PMCTRL_REG(SMC_BASE_PTR)
#define SMC_STOPCTRL                             SMC_STOPCTRL_REG(SMC_BASE_PTR)
#define SMC_PMSTAT                               SMC_PMSTAT_REG(SMC_BASE_PTR)

/**
 * @}
 */ /* end of group SMC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group SMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SPI
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SPI_Peripheral SPI
 * @{
 */

/** SPI - Peripheral register structure */
typedef struct SPI_MemMap {
  uint8_t C1;                                      /**< SPI control register 1, offset: 0x0 */
  uint8_t C2;                                      /**< SPI control register 2, offset: 0x1 */
  uint8_t BR;                                      /**< SPI baud rate register, offset: 0x2 */
  uint8_t S;                                       /**< SPI status register, offset: 0x3 */
  uint8_t RESERVED_0[1];
  uint8_t D;                                       /**< SPI data register, offset: 0x5 */
  uint8_t RESERVED_1[1];
  uint8_t M;                                       /**< SPI match register, offset: 0x7 */
} volatile *SPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register accessors */
#define SPI_C1_REG(base)                         ((base)->C1)
#define SPI_C2_REG(base)                         ((base)->C2)
#define SPI_BR_REG(base)                         ((base)->BR)
#define SPI_S_REG(base)                          ((base)->S)
#define SPI_D_REG(base)                          ((base)->D)
#define SPI_M_REG(base)                          ((base)->M)

/**
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base pointer */
#define SPI0_BASE_PTR                            ((SPI_MemMapPtr)0x40076000u)
/** Peripheral SPI1 base pointer */
#define SPI1_BASE_PTR                            ((SPI_MemMapPtr)0x40077000u)
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0_BASE_PTR, SPI1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register instance definitions */
/* SPI0 */
#define SPI0_C1                                  SPI_C1_REG(SPI0_BASE_PTR)
#define SPI0_C2                                  SPI_C2_REG(SPI0_BASE_PTR)
#define SPI0_BR                                  SPI_BR_REG(SPI0_BASE_PTR)
#define SPI0_S                                   SPI_S_REG(SPI0_BASE_PTR)
#define SPI0_D                                   SPI_D_REG(SPI0_BASE_PTR)
#define SPI0_M                                   SPI_M_REG(SPI0_BASE_PTR)
/* SPI1 */
#define SPI1_C1                                  SPI_C1_REG(SPI1_BASE_PTR)
#define SPI1_C2                                  SPI_C2_REG(SPI1_BASE_PTR)
#define SPI1_BR                                  SPI_BR_REG(SPI1_BASE_PTR)
#define SPI1_S                                   SPI_S_REG(SPI1_BASE_PTR)
#define SPI1_D                                   SPI_D_REG(SPI1_BASE_PTR)
#define SPI1_M                                   SPI_M_REG(SPI1_BASE_PTR)

/**
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group SPI_Peripheral */


/* ----------------------------------------------------------------------------
   -- SysTick
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SysTick_Peripheral SysTick
 * @{
 */

/** SysTick - Peripheral register structure */
typedef struct SysTick_MemMap {
  uint32_t CSR;                                    /**< SysTick Control and Status Register, offset: 0x0 */
  uint32_t RVR;                                    /**< SysTick Reload Value Register, offset: 0x4 */
  uint32_t CVR;                                    /**< SysTick Current Value Register, offset: 0x8 */
  uint32_t CALIB;                                  /**< SysTick Calibration Value Register, offset: 0xC */
} volatile *SysTick_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SysTick Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SysTick_Register_Masks SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#define SysTick_CSR_ENABLE_MASK                  0x1u
#define SysTick_CSR_ENABLE_SHIFT                 0
#define SysTick_CSR_TICKINT_MASK                 0x2u
#define SysTick_CSR_TICKINT_SHIFT                1
#define SysTick_CSR_CLKSOURCE_MASK               0x4u
#define SysTick_CSR_CLKSOURCE_SHIFT              2
#define SysTick_CSR_COUNTFLAG_MASK               0x10000u
#define SysTick_CSR_COUNTFLAG_SHIFT              16
/* RVR Bit Fields */
#define SysTick_RVR_RELOAD_MASK                  0xFFFFFFu
#define SysTick_RVR_RELOAD_SHIFT                 0
#define SysTick_RVR_RELOAD(x)                    (((uint32_t)(((uint32_t)(x))<<SysTick_RVR_RELOAD_SHIFT))&SysTick_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define SysTick_CVR_CURRENT_MASK                 0xFFFFFFu
#define SysTick_CVR_CURRENT_SHIFT                0
#define SysTick_CVR_CURRENT(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CVR_CURRENT_SHIFT))&SysTick_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define SysTick_CALIB_TENMS_MASK                 0xFFFFFFu
#define SysTick_CALIB_TENMS_SHIFT                0
#define SysTick_CALIB_TENMS(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CALIB_TENMS_SHIFT))&SysTick_CALIB_TENMS_MASK)
#define SysTick_CALIB_SKEW_MASK                  0x40000000u
#define SysTick_CALIB_SKEW_SHIFT                 30
#define SysTick_CALIB_NOREF_MASK                 0x80000000u
#define SysTick_CALIB_NOREF_SHIFT                31

/**
 * @}
 */ /* end of group SysTick_Register_Masks */
 
/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */


/**
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register accessors */
#define SysTick_CSR_REG(base)                    ((base)->CSR)
#define SysTick_RVR_REG(base)                    ((base)->RVR)
#define SysTick_CVR_REG(base)                    ((base)->CVR)
#define SysTick_CALIB_REG(base)                  ((base)->CALIB)

/**
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */

/* SysTick - Peripheral instance base addresses */
/** Peripheral SysTick base pointer */
#define SysTick_BASE_PTR                         ((SysTick_MemMapPtr)0xE000E010u)
/** Array initializer of SysTick peripheral base pointers */
#define SysTick_BASE_PTRS                        { SysTick_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register instance definitions */
/* SysTick */
#define SYST_CSR                                 SysTick_CSR_REG(SysTick_BASE_PTR)
#define SYST_RVR                                 SysTick_RVR_REG(SysTick_BASE_PTR)
#define SYST_CVR                                 SysTick_CVR_REG(SysTick_BASE_PTR)
#define SYST_CALIB                               SysTick_CALIB_REG(SysTick_BASE_PTR)

/**
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group SysTick_Peripheral */


/* ----------------------------------------------------------------------------
   -- TPM
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup TPM_Peripheral TPM
 * @{
 */

/** TPM - Peripheral register structure */
typedef struct TPM_MemMap {
  uint32_t SC;                                     /**< Status and Control, offset: 0x0 */
  uint32_t CNT;                                    /**< Counter, offset: 0x4 */
  uint32_t MOD;                                    /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    uint32_t CnSC;                                   /**< Channel (n) Status and Control, array offset: 0xC, array step: 0x8 */
    uint32_t CnV;                                    /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[6];
  uint8_t RESERVED_0[20];
  uint32_t STATUS;                                 /**< Capture and Compare Status, offset: 0x50 */
  uint8_t RESERVED_1[48];
  uint32_t CONF;                                   /**< Configuration, offset: 0x84 */
} volatile *TPM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TPM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup TPM_Register_Accessor_Macros TPM - Register accessor macros
 * @{
 */


/* TPM - Register accessors */
#define TPM_SC_REG(base)                         ((base)->SC)
#define TPM_CNT_REG(base)                        ((base)->CNT)
#define TPM_MOD_REG(base)                        ((base)->MOD)
#define TPM_CnSC_REG(base,index)                 ((base)->CONTROLS[index].CnSC)
#define TPM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
#define TPM_STATUS_REG(base)                     ((base)->STATUS)
#define TPM_CONF_REG(base)                       ((base)->CONF)

/**
 * @}
 */ /* end of group TPM_Register_Accessor_Macros */


/* TPM - Peripheral instance base addresses */
/** Peripheral TPM0 base pointer */
#define TPM0_BASE_PTR                            ((TPM_MemMapPtr)0x40038000u)
/** Peripheral TPM1 base pointer */
#define TPM1_BASE_PTR                            ((TPM_MemMapPtr)0x40039000u)
/** Peripheral TPM2 base pointer */
#define TPM2_BASE_PTR                            ((TPM_MemMapPtr)0x4003A000u)
/** Array initializer of TPM peripheral base pointers */
#define TPM_BASE_PTRS                            { TPM0_BASE_PTR, TPM1_BASE_PTR, TPM2_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- TPM - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup TPM_Register_Accessor_Macros TPM - Register accessor macros
 * @{
 */


/* TPM - Register instance definitions */
/* TPM0 */
#define TPM0_SC                                  TPM_SC_REG(TPM0_BASE_PTR)
#define TPM0_CNT                                 TPM_CNT_REG(TPM0_BASE_PTR)
#define TPM0_MOD                                 TPM_MOD_REG(TPM0_BASE_PTR)
#define TPM0_C0SC                                TPM_CnSC_REG(TPM0_BASE_PTR,0)
#define TPM0_C0V                                 TPM_CnV_REG(TPM0_BASE_PTR,0)
#define TPM0_C1SC                                TPM_CnSC_REG(TPM0_BASE_PTR,1)
#define TPM0_C1V                                 TPM_CnV_REG(TPM0_BASE_PTR,1)
#define TPM0_C2SC                                TPM_CnSC_REG(TPM0_BASE_PTR,2)
#define TPM0_C2V                                 TPM_CnV_REG(TPM0_BASE_PTR,2)
#define TPM0_C3SC                                TPM_CnSC_REG(TPM0_BASE_PTR,3)
#define TPM0_C3V                                 TPM_CnV_REG(TPM0_BASE_PTR,3)
#define TPM0_C4SC                                TPM_CnSC_REG(TPM0_BASE_PTR,4)
#define TPM0_C4V                                 TPM_CnV_REG(TPM0_BASE_PTR,4)
#define TPM0_C5SC                                TPM_CnSC_REG(TPM0_BASE_PTR,5)
#define TPM0_C5V                                 TPM_CnV_REG(TPM0_BASE_PTR,5)
#define TPM0_STATUS                              TPM_STATUS_REG(TPM0_BASE_PTR)
#define TPM0_CONF                                TPM_CONF_REG(TPM0_BASE_PTR)
/* TPM1 */
#define TPM1_SC                                  TPM_SC_REG(TPM1_BASE_PTR)
#define TPM1_CNT                                 TPM_CNT_REG(TPM1_BASE_PTR)
#define TPM1_MOD                                 TPM_MOD_REG(TPM1_BASE_PTR)
#define TPM1_C0SC                                TPM_CnSC_REG(TPM1_BASE_PTR,0)
#define TPM1_C0V                                 TPM_CnV_REG(TPM1_BASE_PTR,0)
#define TPM1_C1SC                                TPM_CnSC_REG(TPM1_BASE_PTR,1)
#define TPM1_C1V                                 TPM_CnV_REG(TPM1_BASE_PTR,1)
#define TPM1_STATUS                              TPM_STATUS_REG(TPM1_BASE_PTR)
#define TPM1_CONF                                TPM_CONF_REG(TPM1_BASE_PTR)
/* TPM2 */
#define TPM2_SC                                  TPM_SC_REG(TPM2_BASE_PTR)
#define TPM2_CNT                                 TPM_CNT_REG(TPM2_BASE_PTR)
#define TPM2_MOD                                 TPM_MOD_REG(TPM2_BASE_PTR)
#define TPM2_C0SC                                TPM_CnSC_REG(TPM2_BASE_PTR,0)
#define TPM2_C0V                                 TPM_CnV_REG(TPM2_BASE_PTR,0)
#define TPM2_C1SC                                TPM_CnSC_REG(TPM2_BASE_PTR,1)
#define TPM2_C1V                                 TPM_CnV_REG(TPM2_BASE_PTR,1)
#define TPM2_STATUS                              TPM_STATUS_REG(TPM2_BASE_PTR)
#define TPM2_CONF                                TPM_CONF_REG(TPM2_BASE_PTR)

/* TPM - Register array accessors */
#define TPM0_CnSC(index)                         TPM_CnSC_REG(TPM0_BASE_PTR,index)
#define TPM1_CnSC(index)                         TPM_CnSC_REG(TPM1_BASE_PTR,index)
#define TPM2_CnSC(index)                         TPM_CnSC_REG(TPM2_BASE_PTR,index)
#define TPM0_CnV(index)                          TPM_CnV_REG(TPM0_BASE_PTR,index)
#define TPM1_CnV(index)                          TPM_CnV_REG(TPM1_BASE_PTR,index)
#define TPM2_CnV(index)                          TPM_CnV_REG(TPM2_BASE_PTR,index)

/**
 * @}
 */ /* end of group TPM_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group TPM_Peripheral */


/* ----------------------------------------------------------------------------
   -- TSI
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup TSI_Peripheral TSI
 * @{
 */

/** TSI - Peripheral register structure */
typedef struct TSI_MemMap {
  uint32_t GENCS;                                  /**< TSI General Control and Status Register, offset: 0x0 */
  uint32_t DATA;                                   /**< TSI DATA Register, offset: 0x4 */
  uint32_t TSHD;                                   /**< TSI Threshold Register, offset: 0x8 */
} volatile *TSI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TSI - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup TSI_Register_Accessor_Macros TSI - Register accessor macros
 * @{
 */


/* TSI - Register accessors */
#define TSI_GENCS_REG(base)                      ((base)->GENCS)
#define TSI_DATA_REG(base)                       ((base)->DATA)
#define TSI_TSHD_REG(base)                       ((base)->TSHD)

/**
 * @}
 */ /* end of group TSI_Register_Accessor_Macros */


/* TSI - Peripheral instance base addresses */
/** Peripheral TSI0 base pointer */
#define TSI0_BASE_PTR                            ((TSI_MemMapPtr)0x40045000u)
/** Array initializer of TSI peripheral base pointers */
#define TSI_BASE_PTRS                            { TSI0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- TSI - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup TSI_Register_Accessor_Macros TSI - Register accessor macros
 * @{
 */


/* TSI - Register instance definitions */
/* TSI0 */
#define TSI0_GENCS                               TSI_GENCS_REG(TSI0_BASE_PTR)
#define TSI0_DATA                                TSI_DATA_REG(TSI0_BASE_PTR)
#define TSI0_TSHD                                TSI_TSHD_REG(TSI0_BASE_PTR)

/**
 * @}
 */ /* end of group TSI_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group TSI_Peripheral */


/* ----------------------------------------------------------------------------
   -- UART
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup UART_Peripheral UART
 * @{
 */

/** UART - Peripheral register structure */
typedef struct UART_MemMap {
  uint8_t BDH;                                     /**< UART Baud Rate Registers:High, offset: 0x0 */
  uint8_t BDL;                                     /**< UART Baud Rate Registers: Low, offset: 0x1 */
  uint8_t C1;                                      /**< UART Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< UART Control Register 2, offset: 0x3 */
  uint8_t S1;                                      /**< UART Status Register 1, offset: 0x4 */
  uint8_t S2;                                      /**< UART Status Register 2, offset: 0x5 */
  uint8_t C3;                                      /**< UART Control Register 3, offset: 0x6 */
  uint8_t D;                                       /**< UART Data Register, offset: 0x7 */
  uint8_t MA1;                                     /**< UART Match Address Registers 1, offset: 0x8 */
  uint8_t MA2;                                     /**< UART Match Address Registers 2, offset: 0x9 */
  uint8_t C4;                                      /**< UART Control Register 4, offset: 0xA */
  uint8_t C5;                                      /**< UART Control Register 5, offset: 0xB */
  uint8_t ED;                                      /**< UART Extended Data Register, offset: 0xC */
  uint8_t MODEM;                                   /**< UART Modem Register, offset: 0xD */
  uint8_t IR;                                      /**< UART Infrared Register, offset: 0xE */
  uint8_t RESERVED_0[1];
  uint8_t PFIFO;                                   /**< UART FIFO Parameters, offset: 0x10 */
  uint8_t CFIFO;                                   /**< UART FIFO Control Register, offset: 0x11 */
  uint8_t SFIFO;                                   /**< UART FIFO Status Register, offset: 0x12 */
  uint8_t TWFIFO;                                  /**< UART FIFO Transmit Watermark, offset: 0x13 */
  uint8_t TCFIFO;                                  /**< UART FIFO Transmit Count, offset: 0x14 */
  uint8_t RWFIFO;                                  /**< UART FIFO Receive Watermark, offset: 0x15 */
  uint8_t RCFIFO;                                  /**< UART FIFO Receive Count, offset: 0x16 */
  uint8_t RESERVED_1[1];
  uint8_t C7816;                                   /**< UART 7816 Control Register, offset: 0x18 */
  uint8_t IE7816;                                  /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  uint8_t IS7816;                                  /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  union {                                          /* offset: 0x1B */
    uint8_t WP7816_T_TYPE0;                          /**< UART 7816 Wait Parameter Register, offset: 0x1B */
    uint8_t WP7816_T_TYPE1;                          /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  };
  uint8_t WN7816;                                  /**< UART 7816 Wait N Register, offset: 0x1C */
  uint8_t WF7816;                                  /**< UART 7816 Wait FD Register, offset: 0x1D */
  uint8_t ET7816;                                  /**< UART 7816 Error Threshold Register, offset: 0x1E */
  uint8_t TL7816;                                  /**< UART 7816 Transmit Length Register, offset: 0x1F */
} volatile *UART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register accessors */
#define UART_BDH_REG(base)                       ((base)->BDH)
#define UART_BDL_REG(base)                       ((base)->BDL)
#define UART_C1_REG(base)                        ((base)->C1)
#define UART_C2_REG(base)                        ((base)->C2)
#define UART_S1_REG(base)                        ((base)->S1)
#define UART_S2_REG(base)                        ((base)->S2)
#define UART_C3_REG(base)                        ((base)->C3)
#define UART_D_REG(base)                         ((base)->D)
#define UART_MA1_REG(base)                       ((base)->MA1)
#define UART_MA2_REG(base)                       ((base)->MA2)
#define UART_C4_REG(base)                        ((base)->C4)
#define UART_C5_REG(base)                        ((base)->C5)
#define UART_ED_REG(base)                        ((base)->ED)
#define UART_MODEM_REG(base)                     ((base)->MODEM)
#define UART_IR_REG(base)                        ((base)->IR)
#define UART_PFIFO_REG(base)                     ((base)->PFIFO)
#define UART_CFIFO_REG(base)                     ((base)->CFIFO)
#define UART_SFIFO_REG(base)                     ((base)->SFIFO)
#define UART_TWFIFO_REG(base)                    ((base)->TWFIFO)
#define UART_TCFIFO_REG(base)                    ((base)->TCFIFO)
#define UART_RWFIFO_REG(base)                    ((base)->RWFIFO)
#define UART_RCFIFO_REG(base)                    ((base)->RCFIFO)
#define UART_C7816_REG(base)                     ((base)->C7816)
#define UART_IE7816_REG(base)                    ((base)->IE7816)
#define UART_IS7816_REG(base)                    ((base)->IS7816)
#define UART_WP7816_T_TYPE0_REG(base)            ((base)->WP7816_T_TYPE0)
#define UART_WP7816_T_TYPE1_REG(base)            ((base)->WP7816_T_TYPE1)
#define UART_WN7816_REG(base)                    ((base)->WN7816)
#define UART_WF7816_REG(base)                    ((base)->WF7816)
#define UART_ET7816_REG(base)                    ((base)->ET7816)
#define UART_TL7816_REG(base)                    ((base)->TL7816)

/**
 * @}
 */ /* end of group UART_Register_Accessor_Macros */



/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base pointer */
#define UART0_BASE_PTR                           ((UART_MemMapPtr)0x4006A000u)
/** Peripheral UART1 base pointer */
#define UART1_BASE_PTR                           ((UART_MemMapPtr)0x4006B000u)
/** Peripheral UART2 base pointer */
#define UART2_BASE_PTR                           ((UART_MemMapPtr)0x4006C000u)
/** Peripheral UART3 base pointer */
#define UART3_BASE_PTR                           ((UART_MemMapPtr)0x4006D000u)
/** Peripheral UART4 base pointer */
#define UART4_BASE_PTR                           ((UART_MemMapPtr)0x400EA000u)
/** Peripheral UART5 base pointer */
#define UART5_BASE_PTR                           ((UART_MemMapPtr)0x400EB000u)

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register instance definitions */
/* UART0 */
#define UART0_BDH                                UART_BDH_REG(UART0_BASE_PTR)
#define UART0_BDL                                UART_BDL_REG(UART0_BASE_PTR)
#define UART0_C1                                 UART_C1_REG(UART0_BASE_PTR)
#define UART0_C2                                 UART_C2_REG(UART0_BASE_PTR)
#define UART0_S1                                 UART_S1_REG(UART0_BASE_PTR)
#define UART0_S2                                 UART_S2_REG(UART0_BASE_PTR)
#define UART0_C3                                 UART_C3_REG(UART0_BASE_PTR)
#define UART0_D                                  UART_D_REG(UART0_BASE_PTR)
#define UART0_MA1                                UART_MA1_REG(UART0_BASE_PTR)
#define UART0_MA2                                UART_MA2_REG(UART0_BASE_PTR)
#define UART0_C4                                 UART_C4_REG(UART0_BASE_PTR)
#define UART0_C5                                 UART_C5_REG(UART0_BASE_PTR)
#define UART0_ED                                 UART_ED_REG(UART0_BASE_PTR)
#define UART0_MODEM                              UART_MODEM_REG(UART0_BASE_PTR)
#define UART0_IR                                 UART_IR_REG(UART0_BASE_PTR)
#define UART0_PFIFO                              UART_PFIFO_REG(UART0_BASE_PTR)
#define UART0_CFIFO                              UART_CFIFO_REG(UART0_BASE_PTR)
#define UART0_SFIFO                              UART_SFIFO_REG(UART0_BASE_PTR)
#define UART0_TWFIFO                             UART_TWFIFO_REG(UART0_BASE_PTR)
#define UART0_TCFIFO                             UART_TCFIFO_REG(UART0_BASE_PTR)
#define UART0_RWFIFO                             UART_RWFIFO_REG(UART0_BASE_PTR)
#define UART0_RCFIFO                             UART_RCFIFO_REG(UART0_BASE_PTR)
#define UART0_C7816                              UART_C7816_REG(UART0_BASE_PTR)
#define UART0_IE7816                             UART_IE7816_REG(UART0_BASE_PTR)
#define UART0_IS7816                             UART_IS7816_REG(UART0_BASE_PTR)
#define UART0_WP7816T0                           UART_WP7816_T_TYPE0_REG(UART0_BASE_PTR)
#define UART0_WP7816T1                           UART_WP7816_T_TYPE1_REG(UART0_BASE_PTR)
#define UART0_WN7816                             UART_WN7816_REG(UART0_BASE_PTR)
#define UART0_WF7816                             UART_WF7816_REG(UART0_BASE_PTR)
#define UART0_ET7816                             UART_ET7816_REG(UART0_BASE_PTR)
#define UART0_TL7816                             UART_TL7816_REG(UART0_BASE_PTR)
/* UART1 */
#define UART1_BDH                                UART_BDH_REG(UART1_BASE_PTR)
#define UART1_BDL                                UART_BDL_REG(UART1_BASE_PTR)
#define UART1_C1                                 UART_C1_REG(UART1_BASE_PTR)
#define UART1_C2                                 UART_C2_REG(UART1_BASE_PTR)
#define UART1_S1                                 UART_S1_REG(UART1_BASE_PTR)
#define UART1_S2                                 UART_S2_REG(UART1_BASE_PTR)
#define UART1_C3                                 UART_C3_REG(UART1_BASE_PTR)
#define UART1_D                                  UART_D_REG(UART1_BASE_PTR)
#define UART1_MA1                                UART_MA1_REG(UART1_BASE_PTR)
#define UART1_MA2                                UART_MA2_REG(UART1_BASE_PTR)
#define UART1_C4                                 UART_C4_REG(UART1_BASE_PTR)
#define UART1_C5                                 UART_C5_REG(UART1_BASE_PTR)
#define UART1_ED                                 UART_ED_REG(UART1_BASE_PTR)
#define UART1_MODEM                              UART_MODEM_REG(UART1_BASE_PTR)
#define UART1_IR                                 UART_IR_REG(UART1_BASE_PTR)
#define UART1_PFIFO                              UART_PFIFO_REG(UART1_BASE_PTR)
#define UART1_CFIFO                              UART_CFIFO_REG(UART1_BASE_PTR)
#define UART1_SFIFO                              UART_SFIFO_REG(UART1_BASE_PTR)
#define UART1_TWFIFO                             UART_TWFIFO_REG(UART1_BASE_PTR)
#define UART1_TCFIFO                             UART_TCFIFO_REG(UART1_BASE_PTR)
#define UART1_RWFIFO                             UART_RWFIFO_REG(UART1_BASE_PTR)
#define UART1_RCFIFO                             UART_RCFIFO_REG(UART1_BASE_PTR)
/* UART2 */
#define UART2_BDH                                UART_BDH_REG(UART2_BASE_PTR)
#define UART2_BDL                                UART_BDL_REG(UART2_BASE_PTR)
#define UART2_C1                                 UART_C1_REG(UART2_BASE_PTR)
#define UART2_C2                                 UART_C2_REG(UART2_BASE_PTR)
#define UART2_S1                                 UART_S1_REG(UART2_BASE_PTR)
#define UART2_S2                                 UART_S2_REG(UART2_BASE_PTR)
#define UART2_C3                                 UART_C3_REG(UART2_BASE_PTR)
#define UART2_D                                  UART_D_REG(UART2_BASE_PTR)
#define UART2_MA1                                UART_MA1_REG(UART2_BASE_PTR)
#define UART2_MA2                                UART_MA2_REG(UART2_BASE_PTR)
#define UART2_C4                                 UART_C4_REG(UART2_BASE_PTR)
#define UART2_C5                                 UART_C5_REG(UART2_BASE_PTR)
#define UART2_ED                                 UART_ED_REG(UART2_BASE_PTR)
#define UART2_MODEM                              UART_MODEM_REG(UART2_BASE_PTR)
#define UART2_IR                                 UART_IR_REG(UART2_BASE_PTR)
#define UART2_PFIFO                              UART_PFIFO_REG(UART2_BASE_PTR)
#define UART2_CFIFO                              UART_CFIFO_REG(UART2_BASE_PTR)
#define UART2_SFIFO                              UART_SFIFO_REG(UART2_BASE_PTR)
#define UART2_TWFIFO                             UART_TWFIFO_REG(UART2_BASE_PTR)
#define UART2_TCFIFO                             UART_TCFIFO_REG(UART2_BASE_PTR)
#define UART2_RWFIFO                             UART_RWFIFO_REG(UART2_BASE_PTR)
#define UART2_RCFIFO                             UART_RCFIFO_REG(UART2_BASE_PTR)
/* UART3 */
#define UART3_BDH                                UART_BDH_REG(UART3_BASE_PTR)
#define UART3_BDL                                UART_BDL_REG(UART3_BASE_PTR)
#define UART3_C1                                 UART_C1_REG(UART3_BASE_PTR)
#define UART3_C2                                 UART_C2_REG(UART3_BASE_PTR)
#define UART3_S1                                 UART_S1_REG(UART3_BASE_PTR)
#define UART3_S2                                 UART_S2_REG(UART3_BASE_PTR)
#define UART3_C3                                 UART_C3_REG(UART3_BASE_PTR)
#define UART3_D                                  UART_D_REG(UART3_BASE_PTR)
#define UART3_MA1                                UART_MA1_REG(UART3_BASE_PTR)
#define UART3_MA2                                UART_MA2_REG(UART3_BASE_PTR)
#define UART3_C4                                 UART_C4_REG(UART3_BASE_PTR)
#define UART3_C5                                 UART_C5_REG(UART3_BASE_PTR)
#define UART3_ED                                 UART_ED_REG(UART3_BASE_PTR)
#define UART3_MODEM                              UART_MODEM_REG(UART3_BASE_PTR)
#define UART3_IR                                 UART_IR_REG(UART3_BASE_PTR)
#define UART3_PFIFO                              UART_PFIFO_REG(UART3_BASE_PTR)
#define UART3_CFIFO                              UART_CFIFO_REG(UART3_BASE_PTR)
#define UART3_SFIFO                              UART_SFIFO_REG(UART3_BASE_PTR)
#define UART3_TWFIFO                             UART_TWFIFO_REG(UART3_BASE_PTR)
#define UART3_TCFIFO                             UART_TCFIFO_REG(UART3_BASE_PTR)
#define UART3_RWFIFO                             UART_RWFIFO_REG(UART3_BASE_PTR)
#define UART3_RCFIFO                             UART_RCFIFO_REG(UART3_BASE_PTR)
/* UART4 */
#define UART4_BDH                                UART_BDH_REG(UART4_BASE_PTR)
#define UART4_BDL                                UART_BDL_REG(UART4_BASE_PTR)
#define UART4_C1                                 UART_C1_REG(UART4_BASE_PTR)
#define UART4_C2                                 UART_C2_REG(UART4_BASE_PTR)
#define UART4_S1                                 UART_S1_REG(UART4_BASE_PTR)
#define UART4_S2                                 UART_S2_REG(UART4_BASE_PTR)
#define UART4_C3                                 UART_C3_REG(UART4_BASE_PTR)
#define UART4_D                                  UART_D_REG(UART4_BASE_PTR)
#define UART4_MA1                                UART_MA1_REG(UART4_BASE_PTR)
#define UART4_MA2                                UART_MA2_REG(UART4_BASE_PTR)
#define UART4_C4                                 UART_C4_REG(UART4_BASE_PTR)
#define UART4_C5                                 UART_C5_REG(UART4_BASE_PTR)
#define UART4_ED                                 UART_ED_REG(UART4_BASE_PTR)
#define UART4_MODEM                              UART_MODEM_REG(UART4_BASE_PTR)
#define UART4_IR                                 UART_IR_REG(UART4_BASE_PTR)
#define UART4_PFIFO                              UART_PFIFO_REG(UART4_BASE_PTR)
#define UART4_CFIFO                              UART_CFIFO_REG(UART4_BASE_PTR)
#define UART4_SFIFO                              UART_SFIFO_REG(UART4_BASE_PTR)
#define UART4_TWFIFO                             UART_TWFIFO_REG(UART4_BASE_PTR)
#define UART4_TCFIFO                             UART_TCFIFO_REG(UART4_BASE_PTR)
#define UART4_RWFIFO                             UART_RWFIFO_REG(UART4_BASE_PTR)
#define UART4_RCFIFO                             UART_RCFIFO_REG(UART4_BASE_PTR)
/* UART5 */
#define UART5_BDH                                UART_BDH_REG(UART5_BASE_PTR)
#define UART5_BDL                                UART_BDL_REG(UART5_BASE_PTR)
#define UART5_C1                                 UART_C1_REG(UART5_BASE_PTR)
#define UART5_C2                                 UART_C2_REG(UART5_BASE_PTR)
#define UART5_S1                                 UART_S1_REG(UART5_BASE_PTR)
#define UART5_S2                                 UART_S2_REG(UART5_BASE_PTR)
#define UART5_C3                                 UART_C3_REG(UART5_BASE_PTR)
#define UART5_D                                  UART_D_REG(UART5_BASE_PTR)
#define UART5_MA1                                UART_MA1_REG(UART5_BASE_PTR)
#define UART5_MA2                                UART_MA2_REG(UART5_BASE_PTR)
#define UART5_C4                                 UART_C4_REG(UART5_BASE_PTR)
#define UART5_C5                                 UART_C5_REG(UART5_BASE_PTR)
#define UART5_ED                                 UART_ED_REG(UART5_BASE_PTR)
#define UART5_MODEM                              UART_MODEM_REG(UART5_BASE_PTR)
#define UART5_IR                                 UART_IR_REG(UART5_BASE_PTR)
#define UART5_PFIFO                              UART_PFIFO_REG(UART5_BASE_PTR)
#define UART5_CFIFO                              UART_CFIFO_REG(UART5_BASE_PTR)
#define UART5_SFIFO                              UART_SFIFO_REG(UART5_BASE_PTR)
#define UART5_TWFIFO                             UART_TWFIFO_REG(UART5_BASE_PTR)
#define UART5_TCFIFO                             UART_TCFIFO_REG(UART5_BASE_PTR)
#define UART5_RWFIFO                             UART_RWFIFO_REG(UART5_BASE_PTR)
#define UART5_RCFIFO                             UART_RCFIFO_REG(UART5_BASE_PTR)

/**
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group UART_Peripheral */



/* ----------------------------------------------------------------------------
   -- USB
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup USB_Peripheral USB
 * @{
 */

/** USB - Peripheral register structure */
typedef struct USB_MemMap {
  uint8_t PERID;                                   /**< Peripheral ID register, offset: 0x0 */
  uint8_t RESERVED_0[3];
  uint8_t IDCOMP;                                  /**< Peripheral ID Complement register, offset: 0x4 */
  uint8_t RESERVED_1[3];
  uint8_t REV;                                     /**< Peripheral Revision register, offset: 0x8 */
  uint8_t RESERVED_2[3];
  uint8_t ADDINFO;                                 /**< Peripheral Additional Info register, offset: 0xC */
  uint8_t RESERVED_3[3];
  uint8_t OTGISTAT;                                /**< OTG Interrupt Status register, offset: 0x10 */
  uint8_t RESERVED_4[3];
  uint8_t OTGICR;                                  /**< OTG Interrupt Control Register, offset: 0x14 */
  uint8_t RESERVED_5[3];
  uint8_t OTGSTAT;                                 /**< OTG Status register, offset: 0x18 */
  uint8_t RESERVED_6[3];
  uint8_t OTGCTL;                                  /**< OTG Control register, offset: 0x1C */
  uint8_t RESERVED_7[99];
  uint8_t ISTAT;                                   /**< Interrupt Status register, offset: 0x80 */
  uint8_t RESERVED_8[3];
  uint8_t INTEN;                                   /**< Interrupt Enable register, offset: 0x84 */
  uint8_t RESERVED_9[3];
  uint8_t ERRSTAT;                                 /**< Error Interrupt Status register, offset: 0x88 */
  uint8_t RESERVED_10[3];
  uint8_t ERREN;                                   /**< Error Interrupt Enable register, offset: 0x8C */
  uint8_t RESERVED_11[3];
  uint8_t STAT;                                    /**< Status register, offset: 0x90 */
  uint8_t RESERVED_12[3];
  uint8_t CTL;                                     /**< Control register, offset: 0x94 */
  uint8_t RESERVED_13[3];
  uint8_t ADDR;                                    /**< Address register, offset: 0x98 */
  uint8_t RESERVED_14[3];
  uint8_t BDTPAGE1;                                /**< BDT Page Register 1, offset: 0x9C */
  uint8_t RESERVED_15[3];
  uint8_t FRMNUML;                                 /**< Frame Number Register Low, offset: 0xA0 */
  uint8_t RESERVED_16[3];
  uint8_t FRMNUMH;                                 /**< Frame Number Register High, offset: 0xA4 */
  uint8_t RESERVED_17[3];
  uint8_t TOKEN;                                   /**< Token register, offset: 0xA8 */
  uint8_t RESERVED_18[3];
  uint8_t SOFTHLD;                                 /**< SOF Threshold Register, offset: 0xAC */
  uint8_t RESERVED_19[3];
  uint8_t BDTPAGE2;                                /**< BDT Page Register 2, offset: 0xB0 */
  uint8_t RESERVED_20[3];
  uint8_t BDTPAGE3;                                /**< BDT Page Register 3, offset: 0xB4 */
  uint8_t RESERVED_21[11];
  struct {                                         /* offset: 0xC0, array step: 0x4 */
    uint8_t ENDPT;                                   /**< Endpoint Control register, array offset: 0xC0, array step: 0x4 */
    uint8_t RESERVED_0[3];
  } ENDPOINT[16];
  uint8_t USBCTRL;                                 /**< USB Control register, offset: 0x100 */
  uint8_t RESERVED_22[3];
  uint8_t OBSERVE;                                 /**< USB OTG Observe register, offset: 0x104 */
  uint8_t RESERVED_23[3];
  uint8_t CONTROL;                                 /**< USB OTG Control register, offset: 0x108 */
  uint8_t RESERVED_24[3];
  uint8_t USBTRC0;                                 /**< USB Transceiver Control Register 0, offset: 0x10C */
} volatile *USB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- USB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup USB_Register_Accessor_Macros USB - Register accessor macros
 * @{
 */


/* USB - Register accessors */
#define USB_PERID_REG(base)                      ((base)->PERID)
#define USB_IDCOMP_REG(base)                     ((base)->IDCOMP)
#define USB_REV_REG(base)                        ((base)->REV)
#define USB_ADDINFO_REG(base)                    ((base)->ADDINFO)
#define USB_OTGISTAT_REG(base)                   ((base)->OTGISTAT)
#define USB_OTGICR_REG(base)                     ((base)->OTGICR)
#define USB_OTGSTAT_REG(base)                    ((base)->OTGSTAT)
#define USB_OTGCTL_REG(base)                     ((base)->OTGCTL)
#define USB_ISTAT_REG(base)                      ((base)->ISTAT)
#define USB_INTEN_REG(base)                      ((base)->INTEN)
#define USB_ERRSTAT_REG(base)                    ((base)->ERRSTAT)
#define USB_ERREN_REG(base)                      ((base)->ERREN)
#define USB_STAT_REG(base)                       ((base)->STAT)
#define USB_CTL_REG(base)                        ((base)->CTL)
#define USB_ADDR_REG(base)                       ((base)->ADDR)
#define USB_BDTPAGE1_REG(base)                   ((base)->BDTPAGE1)
#define USB_FRMNUML_REG(base)                    ((base)->FRMNUML)
#define USB_FRMNUMH_REG(base)                    ((base)->FRMNUMH)
#define USB_TOKEN_REG(base)                      ((base)->TOKEN)
#define USB_SOFTHLD_REG(base)                    ((base)->SOFTHLD)
#define USB_BDTPAGE2_REG(base)                   ((base)->BDTPAGE2)
#define USB_BDTPAGE3_REG(base)                   ((base)->BDTPAGE3)
#define USB_ENDPT_REG(base,index)                ((base)->ENDPOINT[index].ENDPT)
#define USB_USBCTRL_REG(base)                    ((base)->USBCTRL)
#define USB_OBSERVE_REG(base)                    ((base)->OBSERVE)
#define USB_CONTROL_REG(base)                    ((base)->CONTROL)
#define USB_USBTRC0_REG(base)                    ((base)->USBTRC0)

/**
 * @}
 */ /* end of group USB_Register_Accessor_Macros */


/* USB - Peripheral instance base addresses */
/** Peripheral USB0 base pointer */
#define USB0_BASE_PTR                            ((USB_MemMapPtr)0x40072000u)
/** Array initializer of USB peripheral base pointers */
#define USB_BASE_PTRS                            { USB0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- USB - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup USB_Register_Accessor_Macros USB - Register accessor macros
 * @{
 */


/* USB - Register instance definitions */
/* USB0 */
#define USB0_PERID                               USB_PERID_REG(USB0_BASE_PTR)
#define USB0_IDCOMP                              USB_IDCOMP_REG(USB0_BASE_PTR)
#define USB0_REV                                 USB_REV_REG(USB0_BASE_PTR)
#define USB0_ADDINFO                             USB_ADDINFO_REG(USB0_BASE_PTR)
#define USB0_OTGISTAT                            USB_OTGISTAT_REG(USB0_BASE_PTR)
#define USB0_OTGICR                              USB_OTGICR_REG(USB0_BASE_PTR)
#define USB0_OTGSTAT                             USB_OTGSTAT_REG(USB0_BASE_PTR)
#define USB0_OTGCTL                              USB_OTGCTL_REG(USB0_BASE_PTR)
#define USB0_ISTAT                               USB_ISTAT_REG(USB0_BASE_PTR)
#define USB0_INTEN                               USB_INTEN_REG(USB0_BASE_PTR)
#define USB0_ERRSTAT                             USB_ERRSTAT_REG(USB0_BASE_PTR)
#define USB0_ERREN                               USB_ERREN_REG(USB0_BASE_PTR)
#define USB0_STAT                                USB_STAT_REG(USB0_BASE_PTR)
#define USB0_CTL                                 USB_CTL_REG(USB0_BASE_PTR)
#define USB0_ADDR                                USB_ADDR_REG(USB0_BASE_PTR)
#define USB0_BDTPAGE1                            USB_BDTPAGE1_REG(USB0_BASE_PTR)
#define USB0_FRMNUML                             USB_FRMNUML_REG(USB0_BASE_PTR)
#define USB0_FRMNUMH                             USB_FRMNUMH_REG(USB0_BASE_PTR)
#define USB0_TOKEN                               USB_TOKEN_REG(USB0_BASE_PTR)
#define USB0_SOFTHLD                             USB_SOFTHLD_REG(USB0_BASE_PTR)
#define USB0_BDTPAGE2                            USB_BDTPAGE2_REG(USB0_BASE_PTR)
#define USB0_BDTPAGE3                            USB_BDTPAGE3_REG(USB0_BASE_PTR)
#define USB0_ENDPT0                              USB_ENDPT_REG(USB0_BASE_PTR,0)
#define USB0_ENDPT1                              USB_ENDPT_REG(USB0_BASE_PTR,1)
#define USB0_ENDPT2                              USB_ENDPT_REG(USB0_BASE_PTR,2)
#define USB0_ENDPT3                              USB_ENDPT_REG(USB0_BASE_PTR,3)
#define USB0_ENDPT4                              USB_ENDPT_REG(USB0_BASE_PTR,4)
#define USB0_ENDPT5                              USB_ENDPT_REG(USB0_BASE_PTR,5)
#define USB0_ENDPT6                              USB_ENDPT_REG(USB0_BASE_PTR,6)
#define USB0_ENDPT7                              USB_ENDPT_REG(USB0_BASE_PTR,7)
#define USB0_ENDPT8                              USB_ENDPT_REG(USB0_BASE_PTR,8)
#define USB0_ENDPT9                              USB_ENDPT_REG(USB0_BASE_PTR,9)
#define USB0_ENDPT10                             USB_ENDPT_REG(USB0_BASE_PTR,10)
#define USB0_ENDPT11                             USB_ENDPT_REG(USB0_BASE_PTR,11)
#define USB0_ENDPT12                             USB_ENDPT_REG(USB0_BASE_PTR,12)
#define USB0_ENDPT13                             USB_ENDPT_REG(USB0_BASE_PTR,13)
#define USB0_ENDPT14                             USB_ENDPT_REG(USB0_BASE_PTR,14)
#define USB0_ENDPT15                             USB_ENDPT_REG(USB0_BASE_PTR,15)
#define USB0_USBCTRL                             USB_USBCTRL_REG(USB0_BASE_PTR)
#define USB0_OBSERVE                             USB_OBSERVE_REG(USB0_BASE_PTR)
#define USB0_CONTROL                             USB_CONTROL_REG(USB0_BASE_PTR)
#define USB0_USBTRC0                             USB_USBTRC0_REG(USB0_BASE_PTR)

/* USB - Register array accessors */
#define USB0_ENDPT(index)                        USB_ENDPT_REG(USB0_BASE_PTR,index)

/**
 * @}
 */ /* end of group USB_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group USB_Peripheral */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/**
 * @}
 */ /* end of group Peripheral_defines */


/* ----------------------------------------------------------------------------
   -- Backward Compatibility
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup Backward_Compatibility_Symbols Backward Compatibility
 * @{
 */

/* No backward compatibility issues. */

/**
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#else /* #if !defined(MCU_MKL25Z4) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0100u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0100u) */
#endif  /* #if !defined(MCU_MKL25Z4) */

/* MKL25Z4.h, eof. */
