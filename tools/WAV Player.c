#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#pragma comment(lib,"Dsound.lib")
#pragma comment(lib,"winmm.lib") 
#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME|DSBCAPS_GLOBALFOCUS)
#endif 

//VS
//Global var//////////////////////////////////////////////////
LPDIRECTSOUNDBUFFER g_lpdbsBuffer = NULL;
DSBUFFERDESC g_dsbd;
WAVEFORMATEX g_wfmx;
char* g_sndBuffer = NULL;
HWND g_hWnd =NULL;
LPDIRECTSOUND g_lpds = NULL;
////////////////////////////////////////////////////////////
BOOL LoadWav(TCHAR *FileName,UINT Flag)
{
HMMIO handle ;
MMCKINFO mmckriff,mmckIn;
PCMWAVEFORMAT pwfm;
memset(&mmckriff,0,sizeof(MMCKINFO));
if((handle= mmioOpen(FileName,NULL,MMIO_READ|MMIO_ALLOCBUF))==NULL)
return FALSE; 
if(0 !=mmioDescend(handle,&mmckriff,NULL,0))
{
mmioClose(handle,0);
return FALSE;
} 
if(mmckriff.ckid !=FOURCC_RIFF||mmckriff.fccType !=mmioFOURCC('W','A','V','E'))
{
mmioClose(handle,0);
return FAL****ckIn.ckid = mmioFOURCC('f','m','t',' ');
if(0 !=mmioDescend(handle,&mmckIn,&mmckriff,MMIO_FINDCHUNK))
{
mmioClose(handle,0);
return FALSE;
} 
if(mmioRead(handle,(HPSTR)&pwfm,sizeof(PCMWAVEFORMAT))!=sizeof(PCMWAVEFORMAT))
{
mmioClose(handle,0);
return FALSE;
} if(pwfm.wf.wFormatTag != WAVE_FORMAT_PCM)
{
mmioClose(handle,0);
return FALSE;
} 
memcpy(&g_wfmx,&pwfm,sizeof(pwfm));
g_wfmx.cbSize =0; if(0 != mmioAscend(handle,&mmckIn,0))
{
mmioClose(handle,0);
return FAL****ckIn.ckid = mmioFOURCC('d','a','t','a'); 
if(0 !=mmioDescend(handle,&mmckIn,&mmckriff,MMIO_FINDCHUNK))
{
mmioClose(handle,0);
return FALSE;
} g_sndBuffer = new char[mmckIn.cksize]; 
mmioRead(handle,(HPSTR)g_sndBuffer,mmckIn.cksize); mmioClose(handle,0); 
g_dsbd.dwSize = sizeof(DSBUFFERDESC);
g_dsbd.dwBufferBytes =mmckIn.cksize;
g_dsbd.dwFlags = DSBCAPS_CTRLDEFAULT;
g_dsbd.lpwfxFormat =&g_wfmx; 
if(FAILED(g_lpds ->CreateSoundBuffer(&g_dsbd,&g_lpdbsBuffer,NULL)))
{
delete [] g_sndBuffer;
return FALSE;
}
VOID* pDSLockedBuffer =NULL;
DWORD dwDSLockedBufferSize =0; 
if(g_lpdbsBuffer ->Lock(0,mmckIn.cksize,&pDSLockedBuffer,&dwDSLockedBufferSize,NULL,NULL,0L))
return FALSE;
memcpy(pDSLockedBuffer,g_sndBuffer,mmckIn.cksize); if(FAILED(g_lpdbsBuffer ->Unlock(pDSLockedBuffer,dwDSLockedBufferSize,NULL,0)))
{
delete [] g_sndBuffer;
return FALSE;
} return TRUE;
}
int main()
{ 
printf("----------------------------------------------\n");
printf("------------------WAV Player------------------\n");
printf("----------By Eisenberg Andrew Roland----------\n");
printf("----------------------------------------------\n");

char WAVFilePath[MAX_PATH];
printf("\n Input the WavFile Path:");
scanf("%s",WAVFilePath);
g_hWnd=GetConsoleWindow();
if(DirectSoundCreate(NULL,&g_lpds,NULL) == DS_OK)
if(g_lpds ->SetCooperativeLevel(g_hWnd,DSSCL_NORMAL)==DS_OK)
{
if(LoadWav(WAVFilePath,DSBCAPS_CTRLDEFAULT))
{
g_lpdbsBuffer->Play(0,0,0);
printf("\nWav Playing......");
}
else
{
return 0;
}
}

getchar();getchar();
return 0;
}
