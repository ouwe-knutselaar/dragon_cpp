#include "DragonAudio.h"

#include <alsa/asoundlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sndfile.h>


using namespace std;

//snd_pcm_t *pcm_handle;
//SF_INFO sfinfo;
//snd_pcm_hw_params_t *hwparams;
//snd_pcm_uframes_t frames;

DragonAudio::DragonAudio() {

	cout<<"DragonAudio: start the constructor "<<endl;


}


DragonAudio::~DragonAudio() {
	// TODO Auto-generated destructor stub
	snd_pcm_drain(pcm_handle);
	snd_pcm_close(pcm_handle);
}


void DragonAudio::initialize()
{

	cout<<"DragonAudio: ALSA lib version "<<SND_LIB_VERSION_STR<<endl;
		// See: http://alsamodular.sourceforge.net/alsa_programming_howto.html
	unsigned int pcm = 0;
	unsigned int rate = 44100;
	unsigned int channels = 1;

	/* Open PCM device for playback. */
	int rc = snd_pcm_open(&pcm_handle, "default",SND_PCM_STREAM_PLAYBACK, 0);
	if (rc < 0) {
	    cerr<<"DragonAudio: unable to open pcm device: "<<snd_strerror(rc)<<endl;
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
	    fprintf(stderr,
	            "unable to set hw parameters: %s\n",
	            snd_strerror(pcm));
	    exit(1);
	}

	snd_pcm_hw_params_get_period_size(hwparams, &frames, 0);

	cout<<"DragonAudio: HW Frames is "<<(int)frames<<endl;
	cout<<"DragonAudio: PCM handle name = "<<snd_pcm_name(pcm_handle)<<endl;
	cout<<"DragonAudio: PCM state = "<<snd_pcm_state_name(snd_pcm_state(pcm_handle))<<endl;
	cout<<"DragonAudio: initialization finished"<<endl;

}




void DragonAudio::playWaveFile(char* waveFile)
{
	int readcount=0;
	short* buf;			// 16 bits sample
	int pcmrc;

	cout<<"DragonAudio: Play wave file "<<waveFile<<endl;
	SNDFILE *infile = sf_open(waveFile, SFM_READ, &sfinfo);
		if(infile == NULL){
			  cerr<<"Error reading file"<<endl;
			  return;
		}

	cout<<"Sample rate: "<<sfinfo.samplerate<<endl;
	cout<<"Channels amount: "<<sfinfo.channels <<endl;
	cout<<"Format is: "<<(sfinfo.format & SF_FORMAT_SUBMASK) <<endl;
	cout<<"Frames is: "<<sfinfo.frames<<endl;
	int bufsize = frames * sfinfo.channels * 2;		// 16 mcp dus 2 bytes
	buf = (short*)malloc(bufsize);
	cout<<" Buffer size is "<<bufsize<<endl;

	int tel=0;
	while ((readcount = sf_readf_short(infile, buf, frames))>0) {
		//cout<<tel;
		//tel=tel+readcount;
		pcmrc = snd_pcm_writei(pcm_handle, buf, readcount);

		if (pcmrc == -EPIPE) {
		    fprintf(stderr, "Underrun!\n");
		    snd_pcm_prepare(pcm_handle);
		}
		else if (pcmrc < 0) {
		    fprintf(stderr, "Error writing to PCM device: %s\n", snd_strerror(pcmrc));
		}
		else if (pcmrc != readcount) {
		    fprintf(stderr,"PCM write difffers from PCM read.\n");
		}
		//cout<<" "<<tel<<"  pcrm "<<pcmrc<<endl;

	}
	cout<<"finished" <<endl;
	free(buf);

}
