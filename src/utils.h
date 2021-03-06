#ifndef FB_UTILS_H
#define FB_UTILS_H

#include <linux/fb.h>
#include <string>

using namespace std;

void getVInfo(int fd, fb_var_screeninfo* v_info_ptr);
void setVInfo(int fd, fb_var_screeninfo* v_info_ptr);
void getFInfo(int fd, fb_fix_screeninfo* f_info_ptr);

#endif //FB_UTILS_H
