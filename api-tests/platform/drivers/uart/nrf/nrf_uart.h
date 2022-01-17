#ifndef NRF_UART_H__
#define NRF_UART_H__

#include "pal_common.h"

/**
 * Function Prototypes
 */
void pal_uart_nrf_init(uint32_t uart_base_addr);
void pal_uart_nrf_print(const char *str, int32_t data);
void pal_uart_nrf_generate_irq(void);
void pal_uart_nrf_disable_irq(void);
void pal_uart_nrf_enable_interrupt(void);
void pal_uart_nrf_disable_interrupt(void);

/**
 * nRF UARTE Register Definitions
 */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/**
  * @brief UARTE_PSEL [PSEL] (Unspecified)
  */
typedef struct {
  __IOM uint32_t  RTS;                          /*!< (@ 0x00000000) Pin select for RTS signal                                  */
  __IOM uint32_t  TXD;                          /*!< (@ 0x00000004) Pin select for TXD signal                                  */
  __IOM uint32_t  CTS;                          /*!< (@ 0x00000008) Pin select for CTS signal                                  */
  __IOM uint32_t  RXD;                          /*!< (@ 0x0000000C) Pin select for RXD signal                                  */
} UARTE_PSEL_Type;                              /*!< Size = 16 (0x10)                                                          */

/**
  * @brief UARTE_RXD [RXD] (RXD EasyDMA channel)
  */
typedef struct {
  __IOM uint32_t  PTR;                          /*!< (@ 0x00000000) Data pointer                                               */
  __IOM uint32_t  MAXCNT;                       /*!< (@ 0x00000004) Maximum number of bytes in receive buffer                  */
  __IM  uint32_t  AMOUNT;                       /*!< (@ 0x00000008) Number of bytes transferred in the last transaction        */
} UARTE_RXD_Type;                               /*!< Size = 12 (0xc)                                                           */


/**
  * @brief UARTE_TXD [TXD] (TXD EasyDMA channel)
  */
typedef struct {
  __IOM uint32_t  PTR;                          /*!< (@ 0x00000000) Data pointer                                               */
  __IOM uint32_t  MAXCNT;                       /*!< (@ 0x00000004) Maximum number of bytes in transmit buffer                 */
  __IM  uint32_t  AMOUNT;                       /*!< (@ 0x00000008) Number of bytes transferred in the last transaction        */
} UARTE_TXD_Type;                               /*!< Size = 12 (0xc)                                                           */

/**
  * @brief UART with EasyDMA
  */
struct NRF_UARTE_Type {                         /*!< (@ 0x40008000) UARTE0_NS Structure                                        */
  __OM  uint32_t  TASKS_STARTRX;                /*!< (@ 0x00000000) Start UART receiver                                        */
  __OM  uint32_t  TASKS_STOPRX;                 /*!< (@ 0x00000004) Stop UART receiver                                         */
  __OM  uint32_t  TASKS_STARTTX;                /*!< (@ 0x00000008) Start UART transmitter                                     */
  __OM  uint32_t  TASKS_STOPTX;                 /*!< (@ 0x0000000C) Stop UART transmitter                                      */
  __IM  uint32_t  RESERVED[7];
  __OM  uint32_t  TASKS_FLUSHRX;                /*!< (@ 0x0000002C) Flush RX FIFO into RX buffer                               */
  __IM  uint32_t  RESERVED1[20];
  __IOM uint32_t  SUBSCRIBE_STARTRX;            /*!< (@ 0x00000080) Subscribe configuration for task STARTRX                   */
  __IOM uint32_t  SUBSCRIBE_STOPRX;             /*!< (@ 0x00000084) Subscribe configuration for task STOPRX                    */
  __IOM uint32_t  SUBSCRIBE_STARTTX;            /*!< (@ 0x00000088) Subscribe configuration for task STARTTX                   */
  __IOM uint32_t  SUBSCRIBE_STOPTX;             /*!< (@ 0x0000008C) Subscribe configuration for task STOPTX                    */
  __IM  uint32_t  RESERVED2[7];
  __IOM uint32_t  SUBSCRIBE_FLUSHRX;            /*!< (@ 0x000000AC) Subscribe configuration for task FLUSHRX                   */
  __IM  uint32_t  RESERVED3[20];
  __IOM uint32_t  EVENTS_CTS;                   /*!< (@ 0x00000100) CTS is activated (set low). Clear To Send.                 */
  __IOM uint32_t  EVENTS_NCTS;                  /*!< (@ 0x00000104) CTS is deactivated (set high). Not Clear To Send.          */
  __IOM uint32_t  EVENTS_RXDRDY;                /*!< (@ 0x00000108) Data received in RXD (but potentially not yet
                                                                    transferred to Data RAM)                                   */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  EVENTS_ENDRX;                 /*!< (@ 0x00000110) Receive buffer is filled up                                */
  __IM  uint32_t  RESERVED5[2];
  __IOM uint32_t  EVENTS_TXDRDY;                /*!< (@ 0x0000011C) Data sent from TXD                                         */
  __IOM uint32_t  EVENTS_ENDTX;                 /*!< (@ 0x00000120) Last TX byte transmitted                                   */
  __IOM uint32_t  EVENTS_ERROR;                 /*!< (@ 0x00000124) Error detected                                             */
  __IM  uint32_t  RESERVED6[7];
  __IOM uint32_t  EVENTS_RXTO;                  /*!< (@ 0x00000144) Receiver timeout                                           */
  __IM  uint32_t  RESERVED7;
  __IOM uint32_t  EVENTS_RXSTARTED;             /*!< (@ 0x0000014C) UART receiver has started                                  */
  __IOM uint32_t  EVENTS_TXSTARTED;             /*!< (@ 0x00000150) UART transmitter has started                               */
  __IM  uint32_t  RESERVED8;
  __IOM uint32_t  EVENTS_TXSTOPPED;             /*!< (@ 0x00000158) Transmitter stopped                                        */
  __IM  uint32_t  RESERVED9[9];
  __IOM uint32_t  PUBLISH_CTS;                  /*!< (@ 0x00000180) Publish configuration for event CTS                        */
  __IOM uint32_t  PUBLISH_NCTS;                 /*!< (@ 0x00000184) Publish configuration for event NCTS                       */
  __IOM uint32_t  PUBLISH_RXDRDY;               /*!< (@ 0x00000188) Publish configuration for event RXDRDY                     */
  __IM  uint32_t  RESERVED10;
  __IOM uint32_t  PUBLISH_ENDRX;                /*!< (@ 0x00000190) Publish configuration for event ENDRX                      */
  __IM  uint32_t  RESERVED11[2];
  __IOM uint32_t  PUBLISH_TXDRDY;               /*!< (@ 0x0000019C) Publish configuration for event TXDRDY                     */
  __IOM uint32_t  PUBLISH_ENDTX;                /*!< (@ 0x000001A0) Publish configuration for event ENDTX                      */
  __IOM uint32_t  PUBLISH_ERROR;                /*!< (@ 0x000001A4) Publish configuration for event ERROR                      */
  __IM  uint32_t  RESERVED12[7];
  __IOM uint32_t  PUBLISH_RXTO;                 /*!< (@ 0x000001C4) Publish configuration for event RXTO                       */
  __IM  uint32_t  RESERVED13;
  __IOM uint32_t  PUBLISH_RXSTARTED;            /*!< (@ 0x000001CC) Publish configuration for event RXSTARTED                  */
  __IOM uint32_t  PUBLISH_TXSTARTED;            /*!< (@ 0x000001D0) Publish configuration for event TXSTARTED                  */
  __IM  uint32_t  RESERVED14;
  __IOM uint32_t  PUBLISH_TXSTOPPED;            /*!< (@ 0x000001D8) Publish configuration for event TXSTOPPED                  */
  __IM  uint32_t  RESERVED15[9];
  __IOM uint32_t  SHORTS;                       /*!< (@ 0x00000200) Shortcuts between local events and tasks                   */
  __IM  uint32_t  RESERVED16[63];
  __IOM uint32_t  INTEN;                        /*!< (@ 0x00000300) Enable or disable interrupt                                */
  __IOM uint32_t  INTENSET;                     /*!< (@ 0x00000304) Enable interrupt                                           */
  __IOM uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Disable interrupt                                          */
  __IM  uint32_t  RESERVED17[93];
  __IOM uint32_t  ERRORSRC;                     /*!< (@ 0x00000480) Error source                                               */
  __IM  uint32_t  RESERVED18[31];
  __IOM uint32_t  ENABLE;                       /*!< (@ 0x00000500) Enable UART                                                */
  __IM  uint32_t  RESERVED19;
  __IOM UARTE_PSEL_Type PSEL;                   /*!< (@ 0x00000508) Unspecified                                                */
  __IM  uint32_t  RESERVED20[3];
  __IOM uint32_t  BAUDRATE;                     /*!< (@ 0x00000524) Baud rate. Accuracy depends on the HFCLK source
                                                                    selected.                                                  */
  __IM  uint32_t  RESERVED21[3];
  __IOM UARTE_RXD_Type RXD;                     /*!< (@ 0x00000534) RXD EasyDMA channel                                        */
  __IM  uint32_t  RESERVED22;
  __IOM UARTE_TXD_Type TXD;                     /*!< (@ 0x00000544) TXD EasyDMA channel                                        */
  __IM  uint32_t  RESERVED23[7];
  __IOM uint32_t  CONFIG;                       /*!< (@ 0x0000056C) Configuration of parity and hardware flow control          */
};                                              /*!< Size = 1392 (0x570)                                                       */

/* Register: UARTE_PSEL_TXD */
/* Description: Pin select for TXD signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_TXD_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_TXD_CONNECT_Msk (0x1UL << UARTE_PSEL_TXD_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_TXD_CONNECT_Connected (0UL) /*!< Connect */
#define UARTE_PSEL_TXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bit 5 : Port number */
#define UARTE_PSEL_TXD_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UARTE_PSEL_TXD_PORT_Msk (0x1UL << UARTE_PSEL_TXD_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_TXD_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_TXD_PIN_Msk (0x1FUL << UARTE_PSEL_TXD_PIN_Pos) /*!< Bit mask of PIN field. */

/**
  * @brief GPIO Port 0 (P0_NS)
  */
struct NRF_GPIO_Type {                          /*!< (@ 0x40842500) P0_NS Structure                                            */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  OUT;                          /*!< (@ 0x00000004) Write GPIO port                                            */
  __IOM uint32_t  OUTSET;                       /*!< (@ 0x00000008) Set individual bits in GPIO port                           */
  __IOM uint32_t  OUTCLR;                       /*!< (@ 0x0000000C) Clear individual bits in GPIO port                         */
  __IM  uint32_t  IN;                           /*!< (@ 0x00000010) Read GPIO port                                             */
  __IOM uint32_t  DIR;                          /*!< (@ 0x00000014) Direction of GPIO pins                                     */
  __IOM uint32_t  DIRSET;                       /*!< (@ 0x00000018) DIR set register                                           */
  __IOM uint32_t  DIRCLR;                       /*!< (@ 0x0000001C) DIR clear register                                         */
  __IOM uint32_t  LATCH;                        /*!< (@ 0x00000020) Latch register indicating what GPIO pins that
                                                                    have met the criteria set in the PIN_CNF[n].SENSE
                                                                    registers                                                  */
  __IOM uint32_t  DETECTMODE;                   /*!< (@ 0x00000024) Select between default DETECT signal behavior
                                                                    and LDETECT mode (For non-secure pin only)                 */
  __IOM uint32_t  DETECTMODE_SEC;               /*!< (@ 0x00000028) Select between default DETECT signal behavior
                                                                    and LDETECT mode (For secure pin only)                     */
  __IM  uint32_t  RESERVED1[117];
  __IOM uint32_t  PIN_CNF[32];                  /*!< (@ 0x00000200) Description collection: Configuration of GPIO
                                                                    pins                                                       */
};                                              /*!< Size = 640 (0x280)                                                        */

/* Register: GPIO_PIN_CNF */
/* Description: Description collection: Configuration of GPIO pins */

/* Bits 30..28 : Select which MCU/Subsystem controls this pin Note: this field is only accessible from secure code. */
#define GPIO_PIN_CNF_MCUSEL_Pos (28UL) /*!< Position of MCUSEL field. */
#define GPIO_PIN_CNF_MCUSEL_Msk (0x7UL << GPIO_PIN_CNF_MCUSEL_Pos) /*!< Bit mask of MCUSEL field. */
#define GPIO_PIN_CNF_MCUSEL_AppMCU (0x0UL) /*!< Application MCU */
#define GPIO_PIN_CNF_MCUSEL_NetworkMCU (0x1UL) /*!< Network MCU */
#define GPIO_PIN_CNF_MCUSEL_Peripheral (0x3UL) /*!< Peripheral with dedicated pins */
#define GPIO_PIN_CNF_MCUSEL_TND (0x7UL) /*!< Trace and Debug Subsystem */

/* Bits 17..16 : Pin sensing mechanism */
#define GPIO_PIN_CNF_SENSE_Pos (16UL) /*!< Position of SENSE field. */
#define GPIO_PIN_CNF_SENSE_Msk (0x3UL << GPIO_PIN_CNF_SENSE_Pos) /*!< Bit mask of SENSE field. */
#define GPIO_PIN_CNF_SENSE_Disabled (0UL) /*!< Disabled */
#define GPIO_PIN_CNF_SENSE_High (2UL) /*!< Sense for high level */
#define GPIO_PIN_CNF_SENSE_Low (3UL) /*!< Sense for low level */

/* Bits 11..8 : Drive configuration */
#define GPIO_PIN_CNF_DRIVE_Pos (8UL) /*!< Position of DRIVE field. */
#define GPIO_PIN_CNF_DRIVE_Msk (0xFUL << GPIO_PIN_CNF_DRIVE_Pos) /*!< Bit mask of DRIVE field. */
#define GPIO_PIN_CNF_DRIVE_S0S1 (0UL) /*!< Standard '0', standard '1' */
#define GPIO_PIN_CNF_DRIVE_H0S1 (1UL) /*!< High drive '0', standard '1' */
#define GPIO_PIN_CNF_DRIVE_S0H1 (2UL) /*!< Standard '0', high drive '1' */
#define GPIO_PIN_CNF_DRIVE_H0H1 (3UL) /*!< High drive '0', high 'drive '1'' */
#define GPIO_PIN_CNF_DRIVE_D0S1 (4UL) /*!< Disconnect '0', standard '1' (normally used for wired-or connections) */
#define GPIO_PIN_CNF_DRIVE_D0H1 (5UL) /*!< Disconnect '0', high drive '1' (normally used for wired-or connections) */
#define GPIO_PIN_CNF_DRIVE_S0D1 (6UL) /*!< Standard '0', disconnect '1' (normally used for wired-and connections) */
#define GPIO_PIN_CNF_DRIVE_H0D1 (7UL) /*!< High drive '0', disconnect '1' (normally used for wired-and connections) */
#define GPIO_PIN_CNF_DRIVE_E0E1 (11UL) /*!< Extra high drive '0', extra high drive '1' */

/* Bits 3..2 : Pull configuration */
#define GPIO_PIN_CNF_PULL_Pos (2UL) /*!< Position of PULL field. */
#define GPIO_PIN_CNF_PULL_Msk (0x3UL << GPIO_PIN_CNF_PULL_Pos) /*!< Bit mask of PULL field. */
#define GPIO_PIN_CNF_PULL_Disabled (0UL) /*!< No pull */
#define GPIO_PIN_CNF_PULL_Pulldown (1UL) /*!< Pull down on pin */
#define GPIO_PIN_CNF_PULL_Pullup (3UL) /*!< Pull up on pin */

/* Bit 1 : Connect or disconnect input buffer */
#define GPIO_PIN_CNF_INPUT_Pos (1UL) /*!< Position of INPUT field. */
#define GPIO_PIN_CNF_INPUT_Msk (0x1UL << GPIO_PIN_CNF_INPUT_Pos) /*!< Bit mask of INPUT field. */
#define GPIO_PIN_CNF_INPUT_Connect (0UL) /*!< Connect input buffer */
#define GPIO_PIN_CNF_INPUT_Disconnect (1UL) /*!< Disconnect input buffer */

/* Bit 0 : Pin direction. Same physical register as DIR register */
#define GPIO_PIN_CNF_DIR_Pos (0UL) /*!< Position of DIR field. */
#define GPIO_PIN_CNF_DIR_Msk (0x1UL << GPIO_PIN_CNF_DIR_Pos) /*!< Bit mask of DIR field. */
#define GPIO_PIN_CNF_DIR_Input (0UL) /*!< Configure pin as an input pin */
#define GPIO_PIN_CNF_DIR_Output (1UL) /*!< Configure pin as an output pin */

#endif // NRF_UART_H__
