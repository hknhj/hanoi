#include <bangtal.h>
#include <stdio.h>


SceneID background;
ObjectID startbutton, hanoiblock[7], bar[3], floor;
TimerID moving;
int n, heightA=7, heightB=0, heightC=0,from,to,by;
bool once = true;

const int animationTime = 5.f;

void move_tower(int n, int from, int to) {
	if (from == 314) {
		heightA--;
		if (to == 607) {
			heightB++;
			locateObject(hanoiblock[n], background, 607, 150 + 20 * heightB);
		}
		else if (to == 900) {
			heightC++;
			locateObject(hanoiblock[n], background, 900, 150 + 20 * heightC);
		}
	}
	else if (from == 607) {
		heightB--;
		if (to == 314) {
			heightA++;
			locateObject(hanoiblock[n], background, 314, 150 + 20 * heightA);
		}
		else if (to == 900) {
			heightC++;
			locateObject(hanoiblock[n], background, 900, 150 + 20 * heightC);
		}
	}
	else if (from == 900) {
		heightC--;
		if (to == 314) {
			heightA++;
			locateObject(hanoiblock[n], background, 314, 150 + 20 * heightA);
		}
		else if (to == 607) {
			heightB++;
			locateObject(hanoiblock[n], background, 607, 150 + 20 * heightB);
		}
	}
}

void hanoi(int n, int from, int by, int to){
	if (n == 1) {
		move_tower(hanoiblock[0], from,to);
	}
	else {
		hanoi(n - 1, from, to, by);
		move_tower(n, from, to);
		hanoi(n - 1, by, from, to);
	}
}



void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startbutton) {
		hideObject(startbutton);
		if (once == true) {
			hanoi(7, 314, 607, 900);
			once = false;
		}
		setTimer(moving, animationTime);
		startTimer(moving);
	}
}

void timerCallback(TimerID timer) {

	if (timer == moving) {
		move_tower(n, from, to);
		setTimer(moving, animationTime);
		startTimer(moving);
	}
}



int main() {

	background = createScene("하노이탑", "흰색배경.png");

	bar[0] = createObject("1번바.png");
	locateObject(bar[0], background, 396, 150);
	showObject(bar[0]);

	bar[1] = createObject("2번바.png");
	locateObject(bar[1], background, 689, 150);
	showObject(bar[1]);

	bar[2] = createObject("3번바.png");
	locateObject(bar[2], background, 982, 150);
	showObject(bar[2]);

	floor = createObject("바닥3.png");
	locateObject(floor, background, 0, 0);
	showObject(floor);


	char image[20];
	for (int i = 0; i < 7; i++) {
		sprintf_s(image, "블럭%d.png", i + 1);
		hanoiblock[i] = createObject(image);
		locateObject(hanoiblock[i], background, 314, 150+30*(6-i));
		showObject(hanoiblock[i]);
	}


	startbutton = createObject("시작버튼.png");
	locateObject(startbutton, background, 550, 600);
	showObject(startbutton);
	
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	startGame(background);
	
}