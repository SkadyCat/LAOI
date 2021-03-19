
#include "Aoi.h"
#include "AoiEntity.h"
#include "AoiTrigger.h"
#include "AoiContext.h"
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

AoiContext* g_context;

void renderScene(void) {
	g_context->Draw();
}

void idleFunc(void) {

}

void TimerFunc(int id) {
	g_context->Update(0.33);
}

int main() {
	int width = 1024;
	int height = 500;

	AoiContext* context = new AoiContext(width, height, 10);
	g_context = context;
	/*for (int i = 0; i < 1000; i++) {
		context->CreateEntity();
	}*/

	for (int i = 0; i < 20; i++) {
		context->CreateTriggerMarker(i);;
	}


	while (true)
	{

		cout << "hello world" << endl;
		_sleep(100);
		
	}
	return 0;
}

