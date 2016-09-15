/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"
#include "Ball.h"

 // Scene root node
CNode* g_SceneRoot = NULL;

Ball* ball = NULL;

// Main entry point for the application
int main()
{
	//Initialise graphics system(s)
	Iw2DInit();

	// Create root node
	g_SceneRoot = new CNode();

	// Add 2D scene graph nodes to the root node here

	s3eAccelerometerStart();
	CIwFVec2 centre = CIwFVec2(Iw2DGetSurfaceWidth() / 2, Iw2DGetSurfaceHeight() / 2);
	ball = new Ball(centre, CIwFVec2(0, 0), CIwFVec2(Iw2DGetSurfaceWidth(), Iw2DGetSurfaceHeight()));


	// Loop forever, until the user or the OS performs some action to quit the app
	int i = 0;
	uint64 totalTime = 0;
	while (!s3eDeviceCheckQuitRequest())
	{
		//Update the input systems
		s3eKeyboardUpdate();
		s3ePointerUpdate();

		//Update the scene. The SDK's example framework has a fixed
		//framerate of 20fps, so we pass that duration to the update function.
		g_SceneRoot->Update(1000 / 20);

		Iw2DSurfaceClear(0xff00ff00);

		uint32 newTime = s3eTimerGetMs();
		totalTime += ball->updateLocation(s3eTimerGetMs(), CIwFVec2(s3eAccelerometerGetX(), -s3eAccelerometerGetY()));

		// Your rendering/app code goes here.

		Iw2DSetColour(0xff0000ff);
		Iw2DFillRect(CIwFVec2(0, 0), CIwFVec2(Iw2DGetSurfaceWidth(), Iw2DGetSurfaceHeight()));

		ball->paint();

		g_SceneRoot->Render();

		//Draws Surface to screen
		Iw2DSurfaceShow();
		// Sleep for 0ms to allow the OS to process events etc.
		s3eDeviceYield(0);
	}

	s3eAccelerometerStop();
	//Terminate modules being used
	delete ball;
	delete g_SceneRoot;

	Iw2DTerminate();

	// Return
	return 0;
}

