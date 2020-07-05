#include "DragonAudio.h"

#include <alsa/asoundlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sndfile.h>




//snd_pcm_t *pcm_handle;
//SF_INFO sfinfo;
//snd_pcm_hw_params_t *hwparams;
//snd_pcm_uframes_t frames;

DragonAudio::DragonAudio() {

	std::cerr<<"DragonAudio: start the constructor \n";
}


DragonAudio::~DragonAudio() {
	// TODO Auto-generated destructor stub
	snd_pcm_drain(pcm_handle);
	snd_pcm_close(pcm_handle);
}


void DragonAudio::initialize()
{

	std::cerr<<"DragonAudio: ALSA lib version "<<SND_LIB_VERSION_STR<<"\n";
		// See: http://alsamodular.sourceforge.net/alsa_programming_howto.html
	unsigned int pcm = 0;
	unsigned int rate = 44100;
	unsigned int channels = 1;

	/* Open PCM device for playback. */
	int rc = snd_pcm_open(&pcm_handle, "default",SND_PCM_STREAM_PLAYBACK, 0);
	if (rc < 0) {
	    std::cerr<<"\x1B[31mDragonAudio: unable to open pcm device: "<<snd_strerror(rc)<<"\033[0m\n";
	    exit(1);
	}

	snd_pcm_hw_params_alloca(&hwparams);
	snd_pcm_hw_params_any(pcm_handle, hwparams);
	snd_pcm_hw_params_set_access(pcm_handle, hwparams,SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(pcm_handle, hwparams,SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(pcm_handle, hwparams, channels);
	snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &rate, 0);


	/* Write the parameters to the driver */
	pcm = snd_pcm_hw_params(pcm_handle, hwparams);
	if (pcm < 0) {
		std::cerr<<"\x1B[31mDragonAudio: unable to set hw parameters: "<<snd_strerror(pcm)<<"\033[0m\n";
	    exit(1);
	}

	snd_pcm_hw_params_get_period_size(hwparams, &frames, 0);

	std::cout<<"DragonAudio: HW Frames is "<<(int)frames<<"\n";
	std::cout<<"DragonAudio: PCM handle name = "<<snd_pcm_name(pcm_handle)<<"\n";
	std::cout<<"DragonAudio: PCM state = "<<snd_pcm_state_name(snd_pcm_state(pcm_handle))<<"\n";
	std::cout<<"DragonAudio: initialization finished\n";

}




void DragonAudio::playWaveFile(char* waveFile)
{
	int readcount=0;
	short* buf;			// 16 bits sample
	int pcmrc;

	sfinfo.format=0;											// Dit moet van de documentatie
	std::cerr<<"DragonAudio: Play wave file "<<waveFile<<"\n";
	SNDFILE *infile = sf_open(waveFile, SFM_READ, &sfinfo);
	if(infile == NULL){
		  std::cerr<<"\x1B[31mDragonAudio: Error reading file\n";
		  std::cerr<<sf_strerror(infile)<<"\033[0m\n";
		  return;
	}

	std::cerr<<"DragonAudio: Fie loaded\n";
	std::cerr<<"DragonAudio: Sample rate: "<<sfinfo.samplerate<<"\n";
	std::cerr<<"DragonAudio: Channels amount: "<<sfinfo.channels <<"\n";
	std::cerr<<"DragonAudio: Format is: "<<(sfinfo.format & SF_FORMAT_SUBMASK) <<"\n";
	std::cerr<<"DragonAudio: Frames is: "<<sfinfo.frames<<"\n";
	int bufsize = frames * sfinfo.channels * 2;		// 16 mcp dus 2 bytes
	buf = (short*)malloc(bufsize);
	std::cerr<<"DragonAudio: Buffer size is "<<bufsize<<"\n";

	int tel=0;
	while ((readcount = sf_readf_short(infile, buf, frames))>0) {
		//std::cout<<tel;
		//tel=tel+readcount;
		pcmrc = snd_pcm_writei(pcm_handle, buf, readcount);

		if (pcmrc == -EPIPE) {
		    fprintf(stderr, "DragonAudio: Underrun!\n");
		    snd_pcm_prepare(pcm_handle);
		}
		else if (pcmrc < 0) {
		    fprintf(stderr, "DragonAudio: Error writing to PCM device: %s\n", snd_strerror(pcmrc));
		}
		else if (pcmrc != readcount) {
		    fprintf(stderr,"DragonAudio: PCM write difffers from PCM read.\n");
		}
		//std::cout<<" "<<tel<<"  pcrm "<<pcmrc<<endl;

	}
	std::cerr<<"DragonAudio: finished\n";
	free(buf);

}
