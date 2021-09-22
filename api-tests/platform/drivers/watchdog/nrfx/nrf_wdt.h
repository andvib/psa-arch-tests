#ifndef NRF_WDT_H__
#define NRF_WDT_H__

#include "pal_common.h"


int nrf_wdt_init(addr_t base_addr, uint32_t time_us);
int nrf_wdt_enable(addr_t base_addr);
int nrf_wdt_disable(addr_t base_addr);
int nrf_wdt_is_enabled(addr_t base_addr);

#endif // NRF_WDT_H__
