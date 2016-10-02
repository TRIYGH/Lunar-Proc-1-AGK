// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

//constants for the screen resolution
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PAD = 1;
const int SHIP= 2;

float x, y, LandingValue;

// Begin app, called once at the start
void app::Begin( void )
{
	//set the virtual resolution
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	agk::CreateSprite(PAD,"landing%20pad.png");
	agk::CreateSprite(SHIP,"lunar%20lander.png");

	agk::SetClearColor(255,255,255);


	x = SCREEN_WIDTH / 2 - ( agk::GetSpriteWidth(PAD) / 2 );
	y = SCREEN_HEIGHT - ( agk::GetSpriteHeight(PAD) );
	agk::SetSpritePosition(PAD,x,y);
	LandingValue = y;  //save this for later when you land

	x = SCREEN_WIDTH / 2 - ( agk::GetSpriteWidth(SHIP) / 2 );
	y = y - ( agk::GetSpriteHeight(SHIP) - 16);
	agk::SetSpritePosition(SHIP,x,y);

	agk::SetSyncRate(10,1);
}

// Main loop, called every frame
void app::Loop ( void )
{
	//378 = y LV = 438

	if(agk::GetRawKeyState(AGK_KEY_SPACE))
		y=y-3;
	else
		y=y+1;

	if (y > (LandingValue-78) )
		y = LandingValue-78;

	agk::SetSpritePosition(SHIP,x,y);

	agk::Sync();

}

// Called when the app ends
void app::End ( void )
{
}
