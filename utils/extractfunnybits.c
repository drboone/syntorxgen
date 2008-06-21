/* extractfunnybits.c, Boone, 12/24/06
   Extract "spare" DPL bits from a code plug */

/* Modifications:
   12/24/06 Boone      Initial coding
   End Modifications */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAXSTR 256

unsigned char dpltable[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };

int main(int argc, char *argv[])
{
   char buf[MAXSTR+1];
   unsigned char i[16];
   int txdpl, txinv, txbits, tfbits;
   int rxdpl, rxinv, rxbits, rfbits;
   int bitscratch;
   int j = 1;

   FILE *fp;

   if((fp = fopen(argv[1],"r")) == NULL) {
      printf("Can't open %s - %s\n",argv[1],strerror(errno));
      exit(1);
   }

   for( ; ; )
   {
      if(fread(i,16,1,fp) != 1) {
         if(ferror(fp)) {
            printf("fread failed - %s\n",strerror(errno));
         }
         break;
      }
      printf("mode %d\n", j);
      txdpl = txinv = txbits = tfbits = 0;
      rxdpl = rxinv = rxbits = rfbits = 0;
#if 0
      sscanf(buf, "%02x %02x %02x %02x %02x %02x %02x %02x %02x "
         "%02x %02x %02x %02x %02x %02x %02x",
         &i[0], &i[1], &i[2], &i[3], &i[4], &i[5], &i[6], &i[7],
         &i[8], &i[9], &i[10], &i[11], &i[12], &i[13], &i[14], &i[15]);
#endif
      if (i[5] & 0x40 && i[5] & 0x20)
      {
         /* tx dpl */
         txdpl = 1;

         /* inverted bit */
         if (i[4] & 0x80)
            txinv = 1;

         /* dpl bits - a */
         bitscratch = (i[4] & 0x01) << 2;
         bitscratch |= (i[5] & 0x18) >> 3;
         txbits = (dpltable[bitscratch] << 6);

         /* dpl bits - b */
         bitscratch = (i[4] & 0x0e) >> 1;
         txbits |= (dpltable[bitscratch] << 3);

         /* dpl bits - c */
         bitscratch = (i[4] & 0x70) >> 4;
         txbits |= dpltable[bitscratch];

         /* but they're inverted */
         txbits = ~txbits;
         txbits &= 0x1ff;

         /* "funny bits" */
         tfbits = i[5] & 0x07;
      }
      if (i[7] & 0x40 && i[7] & 0x20)
      {
         /* rx dpl */
         rxdpl = 1;

         /* inverted bit */
         if (i[6] & 0x80)
            rxinv = 1;

         /* dpl bits - a */
         bitscratch = (i[6] & 0x01) << 2;
         bitscratch |= (i[7] & 0x18) >> 3;
         rxbits = (dpltable[bitscratch] << 6);

         /* dpl bits - b */
         bitscratch = (i[6] & 0x0e) >> 1;
         rxbits |= (dpltable[bitscratch] << 3);

         /* dpl bits - c */
         bitscratch = (i[6] & 0x70) >> 4;
         rxbits |= dpltable[bitscratch];

         /* but they're inverted */
         rxbits = ~rxbits;
         rxbits &= 0x1ff;

         /* "funny bits" */
         rfbits = i[7] & 0x07;
      }
      if (txdpl)
         if (txinv)
            printf("\ttx inverted dpl %03o funny %1o\n", txbits, tfbits);
         else
            printf("\ttx dpl %03o funny %1o\n", txbits, tfbits);
      if (rxdpl)
         if (rxinv)
            printf("\trx inverted dpl %03o funny %1o\n", rxbits, rfbits);
         else
            printf("\trx dpl %03o funny %1o\n", rxbits, rfbits);
      j++;
   }
}
