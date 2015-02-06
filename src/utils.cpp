#include <cstdlib>
#include <cerrno>
#include <iostream>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include "utils.h"

using namespace std;

void getVInfo (int fd, struct fb_var_screeninfo* v_info_ptr) {
  // Get variable screen information
  if (ioctl(fd, FBIOGET_VSCREENINFO, v_info_ptr)) {
    cerr << "Error #" << errno << ": cannot read variable screen info." << endl;
    exit(1);
  }
}

void setVInfo (int fd, struct fb_var_screeninfo* v_info_ptr) {
  // Change variable screen information
  if (ioctl(fd, FBIOPUT_VSCREENINFO, v_info_ptr)) {
    cerr << "Error: cannot set variable screen info." << endl;
    exit(1);
  }
}

void getFInfo (int fd, struct fb_fix_screeninfo* f_info_ptr) {
  // Get fixed screen information
  if (ioctl(fd, FBIOGET_FSCREENINFO, f_info_ptr)) {
    cerr << "Error #" << errno << ": cannot read fixed screen info." << endl;
    exit(1);
  }
}
