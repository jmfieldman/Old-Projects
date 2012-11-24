#include "GoGL.h"
#include "sound.h"

IDirectMusicLoader8*      g_pLoader			= NULL;
IDirectMusicPerformance8* g_pPerformance	= NULL;
IDirectMusicSegment8*     g_pSegmentPlace	= NULL;
IDirectMusicSegment8*     g_pSegmentCapture	= NULL;
IDirectMusicSegment8*     g_pSegmentEndGame	= NULL;
 
bool	g_bSound1 = false;
bool	g_bSound2 = false;
bool	g_bSound3 = false;

void initSound()
{
	CoInitialize(NULL);
    
    CoCreateInstance(CLSID_DirectMusicLoader, NULL, 
                     CLSCTX_INPROC, IID_IDirectMusicLoader8,
                     (void**)&g_pLoader);

    CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
                     CLSCTX_INPROC, IID_IDirectMusicPerformance8,
                     (void**)&g_pPerformance );

	g_pPerformance->InitAudio( 
        NULL,                  // IDirectMusic interface not needed.
        NULL,                  // IDirectSound interface not needed.
        NULL,                  // Window handle.
        DMUS_APATH_SHARED_STEREOPLUSREVERB,  // Default audiopath type.
        64,                    // Number of performance channels.
        DMUS_AUDIOF_ALL,       // Features on synthesizer.
        NULL                   // Audio parameters; use defaults.
    );

	
    WCHAR wstrSearchPath[MAX_PATH];
    MultiByteToWideChar( CP_ACP, 0, ".", -1, 
                         wstrSearchPath, MAX_PATH );
 
	// set the search directory for where to find our sound effects
	g_pLoader->SetSearchDirectory( 
        GUID_DirectMusicAllTypes,   // Types of files sought.
        wstrSearchPath,             // Where to look.
        FALSE                       // Don't clear object data.
    );

	// load the sound file for piece placement as segment
    WCHAR wstrFileName1[MAX_PATH] = L"place.wav";
 
	if (FAILED(g_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // Class identifier.
        IID_IDirectMusicSegment8,   // ID of desired interface.
        wstrFileName1,              // Filename.
        (LPVOID*) &g_pSegmentPlace  // Pointer that receives interface.
    )))
    {
        MessageBox( NULL, "Sound effect missing: \"place.wav\"", 
                          "GoGL", MB_OK );
		closeSound();
		exit(0);
    } else g_bSound1 = true;

	// load the sound file for piece capture as segment
    WCHAR wstrFileName2[MAX_PATH] = L"cap.wav";
 
	if (FAILED(g_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // Class identifier.
        IID_IDirectMusicSegment8,   // ID of desired interface.
        wstrFileName2,              // Filename.
        (LPVOID*) &g_pSegmentCapture  // Pointer that receives interface.
    )))
    {
        MessageBox( NULL, "Sound effect missing: \"cap.wav\"", 
                          "GoGL", MB_OK );
		closeSound();
		exit(0);
    } else g_bSound2 = true;

	// load the sound file for game end as segment
    WCHAR wstrFileName3[MAX_PATH] = L"endgame.wav";
 
    	if (FAILED(g_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // Class identifier.
        IID_IDirectMusicSegment8,   // ID of desired interface.
        wstrFileName3,              // Filename.
        (LPVOID*) &g_pSegmentEndGame  // Pointer that receives interface.
    )))
    {
        MessageBox( NULL, "Sound effect missing: \"endgame.wav\"", 
                          "GoGL", MB_OK );
        closeSound();
		exit(0);
	} else g_bSound3 = true;
}

void sound_placement()
{
	if ( g_bSound1 )
	{
		// downloads the band to the performance   
		g_pSegmentPlace->Download( g_pPerformance );
    
		g_pPerformance->PlaySegmentEx(
	        g_pSegmentPlace,  // Segment to play.
		    NULL,        // Used for songs; not implemented.
			NULL,        // For transitions. 
			0,           // Flags.
			0,           // Start time; 0 is immediate.
			NULL,        // Pointer that receives segment state.
			NULL,        // Object to stop.
			NULL         // Audiopath, if not default.
		);      

		g_pSegmentPlace->Unload( g_pPerformance );
	}
}

void sound_capture()
{
	if ( g_bSound2 )
	{
		// downloads the band to the performance   
		g_pSegmentCapture->Download( g_pPerformance );
    
		g_pPerformance->PlaySegmentEx(
			g_pSegmentCapture,  // Segment to play.
			NULL,        // Used for songs; not implemented.
			NULL,        // For transitions. 
			0,           // Flags.
			0,           // Start time; 0 is immediate.
			NULL,        // Pointer that receives segment state.
	        NULL,        // Object to stop.
		    NULL         // Audiopath, if not default.
		);      

		g_pSegmentCapture->Unload( g_pPerformance );
	}
}

void sound_endgame()
{
	if ( g_bSound3 )
	{
		// downloads the band to the performance   
		g_pSegmentEndGame->Download( g_pPerformance );
    
		g_pPerformance->PlaySegmentEx(
		    g_pSegmentEndGame,  // Segment to play.
			NULL,        // Used for songs; not implemented.
			NULL,        // For transitions. 
			0,           // Flags.
			0,           // Start time; 0 is immediate.
			NULL,        // Pointer that receives segment state.
			NULL,        // Object to stop.
			NULL         // Audiopath, if not default.
		);      

		g_pSegmentEndGame->Unload( g_pPerformance );
	}
}

void closeSound()
{
    g_pPerformance->Stop(
        NULL,   // Stop all segments.
        NULL,   // Stop all segment states.
        0,      // Do it immediately.
        0       // Flags.
    );
 
    g_pPerformance->CloseDown();
 
    g_pLoader->Release(); 
    g_pPerformance->Release();
    if( g_bSound1 ) g_pSegmentPlace->Release();
	if( g_bSound2 ) g_pSegmentCapture->Release();
	if( g_bSound3 ) g_pSegmentEndGame->Release();

    CoUninitialize();
}