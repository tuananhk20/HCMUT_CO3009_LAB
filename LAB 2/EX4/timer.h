#ifndef INC_TIMER_H_

#define INC_TIMER_H_

extern int timer1_flag;

extern int timer2_flag;

void setTimer1(int duration);

void setTimer2(int duration);

void clearTimer1();

void timerRun();


#endif /* INC_TIMER_H_ */
