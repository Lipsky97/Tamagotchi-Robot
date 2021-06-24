/*
 * File:   main.c
 * Author: olipi
 *
 * Created on 11 lutego 2019, 05:48
 */


#include "xc.h"
#include "allcode_api.h"

int happiness = 50;
int food = 50;
int energy = 50;
int age = 0;

void say_sth(int a) {
    switch (a) {
        case 0://happy
            FA_PlayNote(2000, 100);
            FA_DelayMillis(100);
            FA_PlayNote(2000, 100);
            FA_PlayNote(2500, 200);
            break;
        case 1://sad
            FA_PlayNote(2000, 150);
            FA_PlayNote(1500, 50);
            FA_PlayNote(1250, 50);
            FA_PlayNote(1000, 50);
            FA_PlayNote(750, 100);
            break;
        case 2://roger that
            FA_PlayNote(2000, 100);
            FA_DelayMillis(100);
            FA_PlayNote(2000, 100);
            break;
        case 3://sleep
            FA_PlayNote(2000, 100);
            FA_PlayNote(1000, 100);
            break;
    }
}

void stats_subtract(int a) {
    if (a == 0 && happiness > 0) {
        happiness = happiness - 2;
    } else if (a == 1 && food > 0) {
        food--;
    } else if (a == 2 && energy > 0) {
        energy = energy - 1;
    }
}

void stats_add(int a) {
    if (a == 0 && happiness <= 96) {
        happiness = happiness + 4;
    } else if (a == 0 && happiness > 96 && happiness < 100) {
        int h = 100 - happiness;
        happiness = happiness + h;
    } else if (a == 1 && food <= 80) {
        food = food + 20;
    } else if (a == 1 && food > 80) {
        int f = 100 - food;
        food = food + f;
    } else if (a == 2 && energy < 100) {
        energy = energy + 1;
    }
}

void normal_eyes() {
    FA_LCDRectangle(35, 25, 55, 5, 0, 1);
    FA_LCDRectangle(72, 25, 92, 5, 0, 1);
}

void closed_eyes() {
    FA_LCDRectangle(35, 16, 55, 13, 0, 1);
    FA_LCDRectangle(72, 16, 92, 13, 0, 1);
}

void happy_eyes() {
    FA_LCDLine(35, 25, 45, 5);
    FA_LCDLine(45, 5, 55, 25);
    FA_LCDLine(72, 25, 82, 5);
    FA_LCDLine(82, 5, 92, 25);
}

void sad_eyes() {
    closed_eyes();
    FA_LCDLine(50, 16, 50, 20);
    FA_LCDLine(90, 16, 90, 25);
}

void heart_eyes() {
    FA_LCDRectangle(55, 14, 61, 9, 0, 1);
    FA_LCDRectangle(65, 14, 71, 9, 0, 1);
    FA_LCDRectangle(60, 19, 66, 15, 0, 1);
    FA_LCDRectangle(62, 14, 64, 12, 0, 1);
    FA_LCDRectangle(57, 16, 59, 15, 0, 1);
    FA_LCDRectangle(62, 21, 64, 20, 0, 1);
    FA_LCDRectangle(67, 16, 69, 15, 0, 1);
    FA_LCDLine(54, 13, 54, 10);
    FA_LCDLine(56, 8, 60, 8);
    FA_LCDLine(66, 8, 70, 8);
    FA_LCDLine(72, 10, 72, 13);
    FA_LCDPlot(62, 11);
    FA_LCDPlot(64, 11);
    FA_LCDPlot(56, 15);
    FA_LCDPlot(70, 15);
    FA_LCDPlot(58, 17);
    FA_LCDPlot(59, 17);
    FA_LCDPlot(59, 18);
    FA_LCDPlot(67, 17);
    FA_LCDPlot(67, 18);
    FA_LCDPlot(68, 17);
    FA_LCDPlot(61, 20);
    FA_LCDPlot(65, 20);
    FA_LCDPlot(63, 22);
}

void follow_hand() {
    int k = 0;
    FA_LCDClear();
    normal_eyes();
    while (k == 0) {
        if (FA_ReadIR(IR_FRONT) > 2500) {
            k = 1;
        }
        if (FA_ReadIR(IR_FRONT) > 100 && FA_ReadIR(IR_FRONT) < 4000) {
            FA_SetMotors(30, 30);
        }
        if (FA_ReadIR(IR_FRONT_RIGHT) > 600) {
            FA_Right(30);
        }
        if (FA_ReadIR(IR_RIGHT) > 600) {
            FA_Right(90);
        }
        if (FA_ReadIR(IR_REAR_RIGHT) > 600) {
            FA_Right(115);
        }
        if (FA_ReadIR(IR_FRONT_LEFT) > 600) {
            FA_Left(30);
        }
        if (FA_ReadIR(IR_LEFT) > 600) {
            FA_Left(90);
        }
        if (FA_ReadIR(IR_REAR_LEFT) > 600) {
            FA_Left(115);
        }
        if (FA_ReadIR(IR_REAR) > 600) {
            FA_Right(180);
        }
        if ((FA_ClockMS() % 4000) == 0) {
            stats_add(0);
            stats_subtract(1);
            stats_subtract(2);
        }
        if (energy < 0) {
            break;
        }
        FA_SetMotors(0, 0);
    }
}

void dead_eyes() {
    FA_LCDLine(35, 25, 55, 5);
    FA_LCDLine(35, 5, 55, 25);
    FA_LCDLine(72, 25, 92, 5);
    FA_LCDLine(72, 5, 92, 25);
}

void belly_rubs() {
    int a = 0;
    FA_Left(20);
    FA_Right(20);
    FA_Left(20);
    FA_Right(20);
    while (a < 10) {
        if (FA_ReadLine(0) > 100) {
            while (FA_ReadLine(0) > 100) {
                //empty loop
            }
            a++;
            FA_DelayMillis(100);
        }
    }
    happiness = happiness + 10;
}

void display_info() {
    FA_LCDString("Happiness: ", 11, 0, 0, 0, 1);
    FA_LCDNumber(happiness, 59, 0, 0, 1);
    FA_LCDString("Energy: ", 8, 0, 9, 0, 1);
    FA_LCDNumber(energy, 41, 9, 0, 1);
    FA_LCDString("Food: ", 6, 0, 18, 0, 1);
    FA_LCDNumber(food, 35, 18, 0, 1);
    FA_LCDNumber(FA_BTConnected(), 120, 0, 0, 1);
}

void deep_sleep() {
    FA_BTSendString("I'm sleepy\n", 12);
    say_sth(3);
    closed_eyes();
    FA_LCDBacklight(0);
    while (1) {
        if ((FA_ClockMS() % 2000) == 0) {
            stats_add(2);
            stats_subtract(1);
        }
        if (FA_ReadSwitch(1) == 1) {
            int i;
            for (i = 0; i < 5; i++) {
                FA_LCDClear();
                display_info();
                FA_DelaySecs(1);
                FA_LCDClear();
                closed_eyes();
            }
        }
        if ((energy <= 100 && energy >= 96) || food < 5) {
            break;
        }
    }
}

int main(void) {
    FA_RobotInit();
    int a = 0;
    int b = 0;
    while (1) {
        FA_LCDBacklight(50);
        FA_LCDClear();
        int bt = FA_BTGetByte();
        if (bt == 5) {
            stats_add(1);
            FA_BTSendString("yum yum\n", 9);
            FA_Right(370);
            say_sth(1);
        }
        if (energy <= 0 || FA_ReadLight() < 100 || bt == 1) {
            deep_sleep();
        }
        if (food <= 0) {
            FA_BTSendString("Imma dead :(\n", 14);
            break;
        }
        if (a % 50 == 0) {
            stats_subtract(0);
            stats_subtract(1);
            stats_subtract(2);
        }
        if (happiness >= 80) {
            happy_eyes();
            if (b == 1) {
                say_sth(0);
                FA_BTSendString("Best fun EVER\n", 15);
                b = 0;
            }
        } else if (happiness < 80 && happiness >= 20) {
            normal_eyes();
        } else if (happiness < 20) {
            sad_eyes();
            if (b == 0) {
                say_sth(1);
                FA_BTSendString("Play with me :(\n", 17);
                b = 1;
            }
        }
        if (FA_ReadSwitch(0) == 1 || bt == 2) {
            say_sth(2);
            follow_hand();
        }
        if (FA_ReadSwitch(1) == 1) {
            int i;
            for (i = 0; i < 5; i++) {
                FA_LCDClear();
                display_info();
                FA_DelaySecs(1);
            }
        }
        if ((FA_ReadLine(0) >= 0 && FA_ReadLine(0) < 50) || (FA_ReadLine(1) >= 0
                && FA_ReadLine(1) < 50)) {
            belly_rubs();
            FA_LCDClear();
            heart_eyes();
            FA_BTSendString("I love you, master\n", 20);
            say_sth(0);
            FA_LCDBacklight(0);
            FA_DelayMillis(250);
            FA_LCDBacklight(50);
            FA_DelayMillis(250);
            FA_LCDBacklight(0);
            FA_DelayMillis(250);
            FA_LCDBacklight(50);
            FA_DelaySecs(2);
        }
        a++;
        FA_DelayMillis(200);
    }
    FA_LCDClear();
    dead_eyes();
    FA_DelaySecs(5);
    return 0;
}
