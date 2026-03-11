#ifndef _PROFILING_H_
#define _PROFILING_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t TEUtils_cycle_init(void);
extern uint32_t TEUtils_cycle_read(void);
extern uint32_t TEUtils_cycle_diff(uint32_t, uint32_t);


#endif /* _PROFILING_H_ */
#ifdef __cplusplus
}
#endif
