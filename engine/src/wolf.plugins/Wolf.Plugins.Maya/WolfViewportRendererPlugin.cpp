/*
	Project			 : Wolf Engine. Copyright (c) Pooya Eimandar All rights reserved. https://github.com/PooyaEimandar/Wolf-Engine
	File Name        : main.cpp
	File Description : The main of Maya Plugin
	Generated by     : Pooya Eimandar on Oct 6, 2014
	Last modified by : Pooya Eimandar on Oct 6, 2014
	Comment          :
*/

#if _MSC_VER >= 1700
#pragma warning( disable: 4005 )
#endif

#include "pch.h"
#include <WolfViewportRenderer.h>
#include "Commands\WLoadSceneCmd.h"

static MFnPlugin* plugin = 0;
static WolfViewportRenderer* renderer = 0;
static __declspec(align(16)) char g_d3dRendererStorage[sizeof(WolfViewportRenderer)];
static MCallbackId	 D3DfileNewCallbackId = 0;
static MCallbackId	 D3DmayaExitCallbackId = 0;

static bool ReleaseRenderer()
{
	if (renderer)
	{
		auto status = renderer->deregisterRenderer();
		if (status != MStatus::kSuccess)
		{
			status.perror("Failed to UnRegister wolf engine renderer properly.");
			return false;
		}
		renderer->~WolfViewportRenderer();
		renderer = 0;

		Log("Renderer UnRegistered");
	}

	return true;
}

static void D3DfileNewCallback(void* clientData)
{
	Log("New Call back");
	//if (renderer)
	//{
	//	g_d3dRenderer->clearResources(false, false); /* keep shaders */
	//}
}

static void D3DmayaExitCallback(void* clientData)
{
	Log("Exit Call back");
	if (renderer)
	{
		renderer->~WolfViewportRenderer();
		renderer = 0;
	}
}

MStatus initializePlugin(MObject obj)
{
	Log("Initializing Wolf plugin");

	MStatus status = MStatus::kFailure;
	plugin = new MFnPlugin(obj, "Pooya.Eimandar", "1.0.0", "Any");

	// Register the renderer
	if (!ReleaseRenderer())
	{
		status.perror("Failed to release last renderer.");
		return status;
	}

	//Create renderer
	renderer = new (g_d3dRendererStorage) WolfViewportRenderer();
	if (renderer)
	{
		status = renderer->registerRenderer();
		if (status != MStatus::kSuccess)
		{
			status.perror("Failed to register wolf engine renderer properly.");
		}

		// Must add in these callbacks as on exit Maya never calls uninitializePlugin() !!
		if (D3DfileNewCallbackId == 0)
		{
			D3DfileNewCallbackId = MSceneMessage::addCallback(MSceneMessage::kBeforeNew, D3DfileNewCallback);
		}
		if (D3DmayaExitCallbackId == 0)
		{
			D3DmayaExitCallbackId = MSceneMessage::addCallback(MSceneMessage::kMayaExiting, D3DmayaExitCallback);
		}

		Log("Wolf plugin initialized");
	}

	//Register commands
	Wolf::Commands = Wolf::WCommnads::NOP;
	status = plugin->registerCommand("WLoadScene", WLoadSceneCmd::Command);
	CHECK_MSTATUS_AND_RETURN_IT(status);

#pragma region Open and compile main wolf python commands

	int pythonFileStatus = -1;
	auto pythonSource = Wolf::System::IO::ReadTextFile(L"Scripts\\WolfCmds.py", pythonFileStatus);

	if (pythonFileStatus != 1)
	{
		if (pythonFileStatus == -1)
		{
			LogError("Could not find the file \"WolfCmds.py\"");
		}
		else if (pythonFileStatus == -2)
		{
			LogError("The file \"WolfCmds.py\" might be corrupted");
		}
		else if (pythonFileStatus == -3)
		{
			LogError("The file \"WolfCmds.py\" is empty");
		}
		else if (pythonFileStatus == -4)
		{
			LogError("Could not open the file \"WolfCmds.py\"");
		}
		status = MStatus::kFailure;
		CHECK_MSTATUS_AND_RETURN_IT(status);

		return status;
	}

	MGlobal::executePythonCommandStringResult(pythonSource);

#pragma endregion
	
	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	Log("Unloading Wolf plugin");

	MStatus status = MStatus::kSuccess;

	// Remove callbacks when plugin is unloaded.
	if (D3DfileNewCallbackId)
	{
		MMessage::removeCallback(D3DfileNewCallbackId);
		D3DfileNewCallbackId = 0;
	}
	if (D3DmayaExitCallbackId)
	{
		MMessage::removeCallback(D3DmayaExitCallbackId);
		D3DmayaExitCallbackId = 0;
	}

	// De-register the renderer
	if (!ReleaseRenderer())
	{
		Log("Problem on releasing renderer");
	}

	//De-register the commands
	plugin->deregisterCommand("WLoadScene");

	plugin = 0;

	Log("Wolf plugin Unloaded");

	return status;
}

