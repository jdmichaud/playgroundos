/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8 and 70, as configured by default */

#include "remap_pic.h"

#define PIC1            0x20           /* IO base address for master PIC */
#define PIC2            0xA0           /* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)
#define PIC_EOI         0x20            /* End - of - interrupt command code */

#define ICW1_ICW4       0x01            /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02            /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04            /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08            /* Level triggered (edge) mode */
#define ICW1_INIT       0x10            /* Initialization - required! */

#define ICW4_8086       0x01            /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02            /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08            /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C            /* Buffered mode/master */
#define ICW4_SFNM       0x10            /* Special fully nested (not) */

/*
  arguments:
    offset1 - vector offset for master PIC
      vectors on the master become offset1..offset1+7
    offset2 - same for slave PIC: offset2..offset2+7
 */
void remap_pics(int offset1, int offset2)
{
  UCHAR   a1, a2;

  a1 = inb(PIC1_DATA);   // save masks
  a2 = inb(PIC2_DATA);
  
  outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4); // starts the initialization sequence
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA, offset1);       // define the PIC vectors
  io_wait();
  outb(PIC2_DATA, offset2);
  io_wait();
  outb(PIC1_DATA, 4);             // continue initialization sequence
  io_wait();
  outb(PIC2_DATA, 2);
  io_wait();
  
  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();
  
  outb(PIC1_DATA, a1);   // restore saved masks.
  outb(PIC2_DATA, a2);
}

