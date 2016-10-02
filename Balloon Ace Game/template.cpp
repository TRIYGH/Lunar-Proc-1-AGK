// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

// Constants for the screen resolution
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
int GameState;
const int INTRO = 1;
const int PLAYGAME = 2;
const int END = 3;
const int PAUSE = 4;

const int TITLE_SCREEN_IMAGE = 1;
const int TITLE_SCREEN_SPRITE = 1;
const int GAMEOVER = 1;
const int INTROTEXT = 2;

const int POP_SOUND = 1;
const int INTRO_MUSIC = 1;

//const int GAME_PIECES = 2
const int planeImage = 2;
const int YBimage = 3;
const int GBimage = 4;

int Score = 0;

int BalloonY, BalloonX, PlaneY, GBalloonX, GBalloonY;
float MaxY_Postion;


// Function prototypes
void displayTitleScreen();
void hideTitleScreen();
void PlayGame();
void EndGame();
void hidegame();
void justPause();


// Begin app, called once at the start
void app::Begin( void )
{
// Set the virtual screen resolution.
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Set the window title.
	agk::SetWindowTitle("BALLOON ACE");

	// Load the images.
	agk::LoadImage(TITLE_SCREEN_IMAGE, "BalloonAce.png");
	//agk::LoadImage(YBimage, "YellowBalloon.png");
	//agk::LoadImage(GBimage, "GreenBalloon.png");
	//agk::LoadImage(planeImage, "Plane.png");
	//agk::LoadImage(INTRO_SCREEN_IMAGE, "intro.png");

	// Create the sprites.
	agk::CreateSprite(TITLE_SCREEN_SPRITE, "BALLOON ACE INTRO.png");
	agk::CreateSprite(planeImage, "Plane.png");
	agk::CreateSprite(YBimage, "YellowBalloon.png");
	agk::CreateSprite(GBimage, "GreenBalloon.png");

	// Hide the sprites.
	for ( int q = 1; q < 5; q++ )
		agk::SetSpriteVisible(q,0);
	
	// Load the sounds.
	agk::LoadSound(POP_SOUND, "pop.wav");
	

	// Load the music.
	agk::LoadMusic(INTRO_MUSIC, "vultureTrouble.mp3");
	

	// Set up the animation sequence.
	//agk::SetSpriteAnimation(VULTURE_SPRITE, FRAME_WIDTH, FRAME_HEIGHT, FRAME_COUNT);

	// Create the text.
	agk::CreateText(GAMEOVER, "GAME OVER");
	//agk::CreateText(INTROTEXT, "Intro screen goes here - with a instructions");
	
	
	// Set the text size.
	agk::SetTextSize(GAMEOVER, 72);
	//agk::SetTextSize(INTROTEXT, 24);

	agk::SetTextVisible(GAMEOVER,0);
	
	GameState = INTRO;

	MaxY_Postion = ( 480 - agk::GetSpriteHeight(YBimage) );
	BalloonY = agk::Random(0,MaxY_Postion);
	BalloonX = 639;
	PlaneY = 220;
	GBalloonY = agk::Random(0,MaxY_Postion);
	GBalloonX = 339;

	agk::SetSyncRate(150,1);



	//agk::Sync();
}

// Main loop, called every frame
void app::Loop ( void )
{
	//agk::Print(GameState);

	int enterPressed;

	// This switch statement determines the game state.
	switch(GameState)
	{
		// The game has just started.
		case INTRO:

			// Display the title screen.
			displayTitleScreen();

			// If the user presses the enter key,
			// hide the title screen and change
			// the game state to intro started.

			if(agk::GetRawKeyState(AGK_KEY_ENTER))
				hideTitleScreen();
			break;

		// The intro has just started.
		case PLAYGAME:

			PlayGame();

			break;

		case END:
						
			hidegame();

			break;

		case PAUSE:

			if (agk::Timer() >= 3)
				justPause();

			break;
	}
}

// Called when the app ends
void app::End ( void )
{
}

void displayTitleScreen()
{
	if(!agk::GetSpriteVisible(TITLE_SCREEN_SPRITE))
		agk::SetSpriteVisible(TITLE_SCREEN_SPRITE,1);
	agk::Sync();
}

void hideTitleScreen()
{
	agk::SetSpriteVisible(TITLE_SCREEN_SPRITE,0);
	agk::PlaySound(POP_SOUND);
	agk::Sync();
	GameState = PLAYGAME;
	agk::SetSpriteVisible(2,1);
	agk::SetSpriteVisible(3,1);
	agk::SetSpriteVisible(4,1);
}

void PlayGame()
{

	agk::SetSpritePosition(YBimage,BalloonX,BalloonY);
	
	agk::SetSpritePosition(planeImage,0,PlaneY);

	if( agk::GetRawKeyState(AGK_KEY_UP) )
		PlaneY--;

	if( agk::GetRawKeyState(AGK_KEY_DOWN) )
		PlaneY++;
	
	BalloonX--;

	agk::Sync();

		if ( BalloonX < -150 )
		{
			BalloonX = 639;
			BalloonY = agk::Random(0,MaxY_Postion);
		}

		
	if(agk::GetSpriteCollision(2,3))
	{
		agk::PlaySound(POP_SOUND);
		Score++;
		BalloonX = 639;
		BalloonY = agk::Random(0,MaxY_Postion);
	}

//----------------------
	
	agk::SetSpritePosition(GBimage,GBalloonX,GBalloonY);

	agk::SetSpritePosition(planeImage,0,PlaneY);

	if( agk::GetRawKeyState(AGK_KEY_UP) )
		PlaneY--;

	if( agk::GetRawKeyState(AGK_KEY_DOWN) )
		PlaneY++;
	
	GBalloonX--;

	agk::Sync();

	if ( GBalloonX < -150 )
	{
		GBalloonX = 639;
		GBalloonY = agk::Random(0,MaxY_Postion);
	}


		if(agk::GetSpriteCollision(2,4))
	{
		agk::PlaySound(POP_SOUND);
		Score++;
		GBalloonX = 639;
		GBalloonY = agk::Random(0,MaxY_Postion);
	}
		agk::PrintC("SCORE: ");
		agk::Print(Score);

		if(Score == 2)
			GameState = END;

}

void hidegame()
{
	for ( int q = 1; q < 5; q++ )
		agk::SetSpriteVisible(q,0);

	agk::Sync();
	agk::ResetTimer();

	agk::SetTextSize(GAMEOVER, 72);
	agk::SetTextVisible(GAMEOVER,1);
	agk::SetTextPosition(GAMEOVER,20,200);

	agk::Sync();

	int HighScore;
	agk::ResetTimer();

	agk::PrintC("Congrats - ");
	agk::PrintC(Score);
	agk::PrintC(" is a CRAZY HIGH score: .....");
	agk::Print("and it is being checked to see if it is a high score!");

	agk::Sync();
	if(agk::Timer()<4)
		int p = 0;

	if(agk::GetFileExists("BalloonAceHighScores.dat"))
	{
		agk::OpenToRead(1,"BalloonAceHighScores.dat");
		HighScore = agk::ReadInteger(1);
		if ( HighScore < Score )
		{
			HighScore = Score;
			agk::Print("YEP - You hold the new High Score Record");
		}
	}
	else
	{
		agk::OpenToWrite(1,"BalloonAceHighScores.dat");
		HighScore = Score;
		agk::Print("You hold the new High Score Record");
	}
	
	agk::WriteInteger(1,HighScore);

	agk::Print("XXXXXXXXXXXXXX Written XXXXXXXXXXX");
	agk::Sync();
	agk::ResetTimer();
	if (agk::Timer() <= 3)
		int p = 0;

	agk::Print("XXXXXXXXXXXXXX timer done XXXXXXXXXXX");
	agk::Sync();
	GameState = PAUSE;
}

void justPause()
{
	int p = 0 ;
	agk::Print(p);
}