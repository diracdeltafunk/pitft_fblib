#include <fcntl.h> //O_RDWR, open 
#include <string> //strings
#include <cerrno> //errno
#include <iostream> //cout, cerr, endl
#include <linux/fb.h> //fb_*_screeninfo
#include <sys/mman.h> //mmap
#include <sys/ioctl.h> //ioctl
#include <stdint.h> //uint32_t, uint16_t
#include <cmath> //floor
#include <cstdlib> //exit

#include "utils.h" //(get|set)(V|F)Info

using namespace std;

int main(int argc, char** argv)
{

  if (argc != 2) {
    cerr << "Usage : " << argv[0] << " framebuffer" << endl;
    return 1;
  }

  struct fb_var_screeninfo v_info;
  struct fb_fix_screeninfo f_info;

  // Open the framebuffer device file for reading and writing
  cout << "Using framebuffer " << argv[1] << endl;
  int fbfd = open(argv[1], O_RDWR);
  if (!fbfd) {
    cerr << "Error #" << errno << ": cannot open framebuffer device." << endl;
    return 1;
  }

  getVInfo(fbfd, &v_info);
  getFInfo(fbfd, &f_info);

  // Output framebuffer info
  uint32_t bpp = v_info.bits_per_pixel;
  cout << "Framebuffer info:" << endl;
  cout << "  Resolution:  " << v_info.xres << "x" << v_info.yres << endl;
  cout << "  Color Depth: " << bpp << "bpp" << endl;

  if ((int) bpp != 16) {
    cout << "Setting color depth to 16bpp" << endl;
    // Set bpp
    v_info.bits_per_pixel = 16;
    setVInfo(fbfd, &v_info);
    // Check bpp
    getVInfo(fbfd, &v_info);
    bpp = v_info.bits_per_pixel;
    if ((int) bpp != 16) {
      cerr << "Error: Color depth not 16bpp. Can't draw.";
      return 1;
    }
  }

  // Map FB to RAM
  uint32_t screensize = f_info.smem_len;
  uint16_t* fb_map = (uint16_t*) mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
  if ((int) fb_map == -1) {
    cerr << "Error #" << errno << ": cannot map framebuffer to memory." << endl;
    return 1;
  }

  // Make it pretty!
  for (uint32_t offset = 0; offset < screensize; offset += 2) {
    *(fb_map + offset) = 0xffff;
  }

  cout << sizeof(*fb_map) << endl;

  // Cleanup
  munmap(fb_map, screensize);
  close(fbfd);
  return 0;
}
