
#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>
#include <sys/ppu_thread.h>

class Sound
{
protected:
    std::string _sPath;
    
    static Sound * currentSound;    
    
    static int fm;
    static sys_ppu_thread_t soundThread;

    void playSample();


public:
    Sound( const std::string & i_sPath);
    void play();

    static void playCurrent();
};

#endif


/* vim: set ts=4 sw=4 sts=4 tw=120 */
