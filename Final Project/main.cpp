#include "mbed.h"
#include "RGBmatrixPanel.h" // Hardware-specific library

PinName ub1=PTB9;
PinName ug1=PTA1;
PinName ur1=PTB23;
PinName lb2=PTA2;
PinName lg2=PTC2;
PinName lr2=PTC3;
RGBmatrixPanel matrix(ur1,ug1,ub1,lr2,lg2,lb2,PTB2,PTB3,PTB10,PTC12,PTB11,PTC4,false);
//RGBmatrixPanel(r1, g1, b1, r2, g2, b2, a, b, c, sclk, latch, oe, enable double_buffer);

void delay(int x){
    //Written with the help of Michael Xiao
    int i=0;
    while(i<x){
        wait_us(10);
        matrix.updateDisplay();
        i++;
    }
}

//int main(){
//          int y = 0;
//     while(1){
//
//         while (y<5){
//             matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
//             delay(1000);
//             matrix.drawCircle(20, 7, 7, matrix.Color333(0, 0, 0));
//             y++;
//         } 
//         while (y>0){
//             matrix.drawCircle(20, 7, 7, matrix.Color333(1, 1, 1));
//             delay(1000);
//             matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 0));
//             y--;
//         }
// 
//    }
// 
// 
//}