#define yield                       __asm __volatile__ ("yield" : : : ); while (1) {}

#define read_coords(xxx) 		        __asm __volatile__ ("mov.v4 %0, v254" : "=v"(xxx) : : )
#define read_reg(var, reg)  		    __asm __volatile__ ("mov.v4 %0, "reg : "=d"(var) : : )

#define pixout(dxdy,rgba, flag)     __asm __volatile__ ("pixout %0, %1, %2" : : "v"(dxdy),"v"(rgba), "I"(flag) : /* No clobbered registers */ )
#define pixout_y(dxdy,rgba, flag)   __asm __volatile__ ("pixout_y %0, %1, %2" : : "v"(dxdy),"v"(rgba), "I"(flag) : /* No clobbered registers */ )
#define clampColor(val)             (val) < 0 ? 0 : (val) > 255 ? 255 : (val)

#define PIXOUT_FLAG                 (0x1 << 2) | 0x1

typedef unsigned ui_vec4 __attribute__((ext_vector_type(4)));

