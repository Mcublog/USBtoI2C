
#ifndef RETARGET_H
#define RETARGET_H

#ifdef __cplusplus
extern "C" {
#endif

int rt_get_char(void *handle, char* c, int len);
int rt_put_char(void *handle, char* c, int len);

#ifdef __cplusplus
}
#endif

#endif // RETARGET_H