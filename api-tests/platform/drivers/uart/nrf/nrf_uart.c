#include "nrf_uart.h"

#define NRF_DATA_FORMAT_MAX_BYTES (16)
#define NRF_PRINT_BUF_SIZE (256)

struct NRF_UARTE_Type *g_nrf_uarte;

#if defined(NRF5340_XXAA_APPLICATION)
const uint32_t gpio_periph_address = 0x40842500;
#ifdef PSA_API_TEST_IPC
const uint32_t output_port = 0;
const uint32_t output_pin = 25;
#else
const uint32_t output_port = 0;
const uint32_t output_pin = 20;
#endif

#elif defined(NRF9160_XXAA)
const uint32_t gpio_periph_address = 0x40842500;
#ifdef PSA_API_TEST_IPC
const uint32_t output_port = 0;
const uint32_t output_pin = 1;
#else
const uint32_t output_port = 0;
const uint32_t output_pin = 29;
#endif

#else
#error "Unknown device for nrf_uart driver!"
#endif


void pal_uart_nrf_init(uint32_t uart_base_addr)
{
    struct NRF_GPIO_Type *nrf_gpio = (struct NRF_GPIO_Type *)gpio_periph_address;

    nrf_gpio->OUTSET = 1UL << output_pin;

    uint32_t cnf = nrf_gpio->PIN_CNF[output_pin] & GPIO_PIN_CNF_MCUSEL_Msk;
    cnf |= ((uint32_t)GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
           ((uint32_t)GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) |
           ((uint32_t)GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
           ((uint32_t)GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
           ((uint32_t)GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
    nrf_gpio->PIN_CNF[output_pin] = cnf;

    g_nrf_uarte = (struct NRF_UARTE_Type *)uart_base_addr;

    // Set baudrate
    g_nrf_uarte->BAUDRATE = 0x01D60000; // Baudrate 115200

    g_nrf_uarte->PSEL.RTS = 0xFFFFFFFF; // Disabled
    g_nrf_uarte->PSEL.CTS = 0xFFFFFFFF; // Disabled
    g_nrf_uarte->PSEL.TXD =
        ((uint32_t)UARTE_PSEL_TXD_CONNECT_Connected << UARTE_PSEL_TXD_CONNECT_Pos) |
        (output_port << UARTE_PSEL_TXD_PORT_Pos) | (output_pin << UARTE_PSEL_TXD_PIN_Pos);

    g_nrf_uarte->CONFIG = 0x0; // HWFC | PARITY | STOP | PARITYTYPE

    g_nrf_uarte->ENABLE = 0x8;
}

void pal_uart_nrf_enable_interrupt(void)
{
    g_nrf_uarte->INTENSET = 0x100; // Enable ENDTX interrupt
}

void pal_uart_nrf_disable_interrupt(void)
{
    g_nrf_uarte->INTENCLR = 0x100; // Disable ENDTX interrupt
}

int format_string(char format_identifier, int32_t data, char *buffer)
{
    uint8_t char_count = 0;
    int8_t is_neg = 0;
    uint8_t work_buf[NRF_DATA_FORMAT_MAX_BYTES];
    if(format_identifier == 'd')
    {
        if(data < 0)
        {
            data = -(data);
            is_neg = 1;
        }

        uint8_t j = 0;
        while(data != 0)
        {
            j       = data % 10;
            data    = data / 10;
            work_buf[char_count++] = j + 48;
        }

        if(is_neg)
        {
            work_buf[char_count++] = '-';
        }
    }
    else if(format_identifier == 'x' || format_identifier == 'X')
    {
        uint8_t j = 0;
        int8_t l = 2 * sizeof(data);
        while(l--)
        {
            j = data & 0xf;
            data >>= 4;
            work_buf[char_count++] = j + ((j > 9) ? 55 : 48);
        }
    }

    int string_len = 0;
    while (char_count > 0)
    {
        buffer[string_len++] = work_buf[--char_count];
    }
    return string_len;
}

void pal_uart_nrf_print(const char *str, int32_t data)
{
    static char print_buf[NRF_PRINT_BUF_SIZE];

    uint32_t write_idx = 0;
    const char* read_ptr = str;
    for(; *read_ptr != '\0'; ++read_ptr)
    {
        if (*read_ptr == '%')
        {
            char buffer[NRF_DATA_FORMAT_MAX_BYTES];
            size_t buf_size = format_string(*(++read_ptr), data, buffer);
            for(uint8_t i = 0; i < buf_size; i++)
            {
                if(write_idx >= NRF_PRINT_BUF_SIZE)
                {
                    /* Buffer size exceeded - print what is in buffer and dump the rest */
                    goto print;
                }
                print_buf[write_idx++] = buffer[i];
            }
        }else if (*read_ptr == '\n') {
            if(write_idx >= NRF_PRINT_BUF_SIZE - 2)
            {
                /* Buffer size exceeded - print what is in buffer and dump the rest */
                goto print;
            }
            print_buf[write_idx++] = *read_ptr;
            print_buf[write_idx++] = '\r';
        }else{
            if(write_idx >= NRF_PRINT_BUF_SIZE)
            {
                /* Buffer size exceeded - print what is in buffer and dump the rest */
                goto print;
            }
            print_buf[write_idx++] = *read_ptr;
        }
    }

print:
    /* Point UARTE peripheral to string location */
    g_nrf_uarte->TXD.PTR = (uint32_t)print_buf;
    g_nrf_uarte->TXD.MAXCNT = write_idx;

    /* Clear event and trigger transmission task */
    g_nrf_uarte->EVENTS_ENDTX = 0x0UL;
    g_nrf_uarte->TASKS_STARTTX = 0x01UL;

    int endtx = 0;
    do
    {
        endtx = g_nrf_uarte->EVENTS_ENDTX;
    }while (!endtx);
}
