/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made
 *to this file will be overwritten if the respective MCUXpresso Config Tools is
 *used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define BOARD_INITPINS_IOMUXC_GPR_GPR41_GPIO_MUX2_GPIO_SEL_HIGH_MASK           \
  0x8000U /*!< GPIO2 and CM7_GPIO2 share same IO MUX function, GPIO_MUX2       \
             selects one GPIO function: affected bits mask */

/* GPIO_AD_25 (coord M15), LPUART1_RXD/J32[2] */
/* Routed pin properties */
#define BOARD_INITPINS_LPUART1_RXD_PERIPHERAL LPUART1 /*!< Peripheral name */
#define BOARD_INITPINS_LPUART1_RXD_SIGNAL RXD         /*!< Signal name */

/* GPIO_AD_24 (coord L13), LPUART1_TXD/J31[2] */
/* Routed pin properties */
#define BOARD_INITPINS_LPUART1_TXD_PERIPHERAL LPUART1 /*!< Peripheral name */
#define BOARD_INITPINS_LPUART1_TXD_SIGNAL TXD         /*!< Signal name */

/* GPIO_AD_30 (coord K17), LPSPI1_SDO/U27[5]/J10[8]/Backlight_CTL/J48[34]/U46[4]
 */
/* Routed pin properties */
#define BOARD_INITPINS_LPSPI1_SDO_PERIPHERAL GPIO9 /*!< Peripheral name */
#define BOARD_INITPINS_LPSPI1_SDO_SIGNAL gpio_io   /*!< Signal name */
#define BOARD_INITPINS_LPSPI1_SDO_CHANNEL 29U      /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LPSPI1_SDO_GPIO                                         \
  GPIO9 /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_LPSPI1_SDO_GPIO_PIN 29U /*!< GPIO pin number */
#define BOARD_INITPINS_LPSPI1_SDO_GPIO_PIN_MASK                                \
  (1U << 29U) /*!< GPIO pin mask */

/* GPIO_AD_02 (coord R13),
 * SIM1_RST/J57[5]/J44[C2]/LCD_RST_B/J48[21]/J25[11]/J10[6] */
/* Routed pin properties */
#define BOARD_INITPINS_SIM1_RST_PERIPHERAL GPIO9 /*!< Peripheral name */
#define BOARD_INITPINS_SIM1_RST_SIGNAL gpio_io   /*!< Signal name */
#define BOARD_INITPINS_SIM1_RST_CHANNEL 1U       /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SIM1_RST_GPIO                                           \
  GPIO9                                     /*!< GPIO peripheral base pointer  \
                                             */
#define BOARD_INITPINS_SIM1_RST_GPIO_PIN 1U /*!< GPIO pin number */
#define BOARD_INITPINS_SIM1_RST_GPIO_PIN_MASK (1U << 1U) /*!< GPIO pin mask */

/* GPIO_AD_01 (coord R14),
 * SIM1_CLK/J44[C3]/J57[7]/CTP_RST_B/J48[28]/J10[4]/J25[13] */
/* Routed pin properties */
#define BOARD_INITPINS_SIM1_CLK_PERIPHERAL GPIO9 /*!< Peripheral name */
#define BOARD_INITPINS_SIM1_CLK_SIGNAL gpio_io   /*!< Signal name */
#define BOARD_INITPINS_SIM1_CLK_CHANNEL 0U       /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SIM1_CLK_GPIO                                           \
  GPIO9                                     /*!< GPIO peripheral base pointer  \
                                             */
#define BOARD_INITPINS_SIM1_CLK_GPIO_PIN 0U /*!< GPIO pin number */
#define BOARD_INITPINS_SIM1_CLK_GPIO_PIN_MASK (1U << 0U) /*!< GPIO pin mask */

/* GPIO_LPSR_04 (coord N7), I2C5_SDA/J48[26]/U32[18]/U34[6]/J10[18] */
/* Routed pin properties */
#define BOARD_INITPINS_I2C5_SDA_PERIPHERAL LPI2C5 /*!< Peripheral name */
#define BOARD_INITPINS_I2C5_SDA_SIGNAL SDA        /*!< Signal name */

/* GPIO_LPSR_05 (coord N8), I2C5_SCL/J48[27]/U32[17]/U34[4]/J10[20] */
/* Routed pin properties */
#define BOARD_INITPINS_I2C5_SCL_PERIPHERAL LPI2C5 /*!< Peripheral name */
#define BOARD_INITPINS_I2C5_SCL_SIGNAL SCL        /*!< Signal name */

/* GPIO_AD_00 (coord N12),
 * SIM1_TRXD/J44[C7]/J57[9]/CTP_INT/J48[29]/J25[15]/J9[14] */
/* Routed pin properties */
#define BOARD_INITPINS_SIM1_TRXD_PERIPHERAL GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_SIM1_TRXD_SIGNAL gpio_mux_io /*!< Signal name */
#define BOARD_INITPINS_SIM1_TRXD_CHANNEL 31U        /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SIM1_TRXD_GPIO                                          \
  GPIO2 /*!< GPIO peripheral base pointer                                      \
         */
#define BOARD_INITPINS_SIM1_TRXD_GPIO_PIN 31U /*!< GPIO pin number */
#define BOARD_INITPINS_SIM1_TRXD_GPIO_PIN_MASK                                 \
  (1U << 31U) /*!< GPIO pin mask                                               \
               */

/* GPIO_AD_04 (coord M13), SIM1_PD/J44[C8]/USER_LED_CTL1/J9[8]/J25[7] */
/* Routed pin properties */
#define BOARD_INITPINS_SIM1_PD_PERIPHERAL GPIO9 /*!< Peripheral name */
#define BOARD_INITPINS_SIM1_PD_SIGNAL gpio_io   /*!< Signal name */
#define BOARD_INITPINS_SIM1_PD_CHANNEL 3U       /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SIM1_PD_GPIO GPIO9  /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_SIM1_PD_GPIO_PIN 3U /*!< GPIO pin number */
#define BOARD_INITPINS_SIM1_PD_GPIO_PIN_MASK (1U << 3U) /*!< GPIO pin mask */

/* WAKEUP (coord T8), USER_BUTTON/SW7 */
/* Routed pin properties */
#define BOARD_INITPINS_USER_BUTTON_PERIPHERAL GPIO13 /*!< Peripheral name */
#define BOARD_INITPINS_USER_BUTTON_SIGNAL gpio_io    /*!< Signal name */
#define BOARD_INITPINS_USER_BUTTON_CHANNEL 0U        /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_USER_BUTTON_GPIO                                        \
  GPIO13 /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_USER_BUTTON_GPIO_PIN 0U /*!< GPIO pin number */
#define BOARD_INITPINS_USER_BUTTON_GPIO_PIN_MASK                               \
  (1U << 0U) /*!< GPIO pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M7F */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
