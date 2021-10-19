#ifndef QRX_H
#define QRX_H
#include <iostream>
#include "qrencode.h"
#include <vector>

namespace qR
{

    int qrx(const char* p, std::vector<bool> &qrr)
    {

        const int zoom = 10;

        QRcode *Code = QRcode_encodeString(p, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
        int Qwidth = Code->width * zoom;
        unsigned char* Qdata = Code->data;
        qrr.resize(static_cast<std::size_t>(Qwidth*Qwidth)*2);

        for (int y = 0; y < Qwidth; y+=zoom) {
            int y_index = y * Qwidth;
            for (int x = 0; x < Qwidth; x+=zoom) {
                std::uint8_t v = (*Qdata & 1) ? 1 : 0;
                  for (int iy = 0; iy < zoom; ++iy)  {
                      int iy_index = (y_index+iy*Qwidth);
                      for (int ix = 0; ix < zoom; ++ix) {
                          qrr[iy_index+(x+ix)] = v;
                      }
                  }

                Qdata+=1;
            }
        }


        QRcode_free(Code);
        return Qwidth;
    }

}

#endif // QRX_H
