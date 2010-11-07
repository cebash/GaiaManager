
#include "sound.h"

extern "C" {
#include "at3plus.h"
}
#include <cell/sysmodule.h>

using namespace std;

int Sound::fm = -1;
sys_ppu_thread_t Sound::soundThread = 0;
Sound * Sound::currentSound = 0;

void playSampleThread( std::uint64_t __attribute__ ((unused)))
{
    Sound::playCurrent();
}


int Sound::init(void)
{
	return cellSysmoduleLoadModule(CELL_SYSMODULE_ATRAC3PLUS);

}


void Sound::free(void)
{
	cellSysmoduleUnloadModule(CELL_SYSMODULE_ATRAC3PLUS);

}


Sound::Sound(const string & i_sPath)
{
    _sPath = i_sPath;
}

void Sound::playCurrent()
{
    currentSound->playSample();
}

void Sound::play()
{
    currentSound = this;
	sys_ppu_thread_create(&soundThread, playSampleThread, NULL, 100, 0x8000, 0, (char *) "sound thread");
}


void Sound::playSample( )
{
	int32_t status;
	BGMArg bgmArg;

//      stop_atrac3();

//      delete_atrac3plus(&bgmArg);

	cellFsClose(fm);
//      status = cellFsOpen("/dev_hdd0/game/OMAN46756/USRDIR/BOOT.AT3", CELL_FS_O_RDONLY, &fm, NULL, 0);
	status = cellFsOpen( _sPath.c_str(), CELL_FS_O_RDONLY, &fm, NULL, 0);
	bgmArg.fd = fm;
	status = init_atrac3plus(&bgmArg);
	play_atrac3plus((uintptr_t) & bgmArg);
	cellFsClose(fm);
	sys_ppu_thread_exit(0);
}

/* vim: set ts=4 sw=4 sts=4 tw=120 */
