#ifndef DRAGONAUDIO_H_
#define DRAGONAUDIO_H_

#include <string>
#include <alsa/asoundlib.h>
#include <sndfile.h>




class DragonAudio {
public:
	DragonAudio();
	virtual ~DragonAudio();
	void initialize();

	void playWaveFile(char*);
	void stopWaveFile();

private:
	snd_pcm_t *pcm_handle;
	SF_INFO sfinfo;
	snd_pcm_hw_params_t *hwparams;
	snd_pcm_uframes_t frames;
};


#endif /* DRAGONAUDIO_H_ */
