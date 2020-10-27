#ifndef AUDIO_STREAM_FLAC_H
#define AUDIO_STREAM_FLAC_H

#include "scene/resources/texture.h"
#include "core/io/resource_loader.h"
#include "servers/audio/audio_stream.h"
#include "thirdparty/dr_flac/dr_flac.h"

class AudioStreamFLAC;

class AudioStreamPlaybackFLAC : public AudioStreamPlaybackResampled {

	GDCLASS(AudioStreamPlaybackFLAC, AudioStreamPlaybackResampled);

	drflac *pFlac;
	uint32_t frames_mixed;

	bool active;
	int loops;

	friend class AudioStreamFLAC;

	Ref<AudioStreamFLAC> flac_stream;

	//void populate_first_frame(int, mp3dec_frame_info_t *);

protected:
	virtual void _mix_internal(AudioFrame *p_buffer, int p_frames) override;
	virtual float get_stream_sampling_rate() override;

public:
	virtual void start(float p_from_pos = 0.0) override;
	virtual void stop() override;
	virtual bool is_playing() const override;

	virtual int get_loop_count() const override; //times it looped

	virtual float get_playback_position() const override;
	virtual void seek(float p_time) override;

	AudioStreamPlaybackFLAC() {}
	~AudioStreamPlaybackFLAC();
};

class AudioStreamFLAC : public AudioStream {

	GDCLASS(AudioStreamFLAC, AudioStream);
	OBJ_SAVE_TYPE(AudioStream) //children are all saved as AudioStream, so they can be exchanged
	RES_BASE_EXTENSION("flacstr");

	friend class AudioStreamPlaybackFLAC;

	void *data;
	uint32_t data_len;

	float sample_rate;
	int channels;
	float length;
	bool loop;
	float loop_offset;
	void clear_data();

protected:
	static void _bind_methods();

public:
	void set_loop(bool p_enable);
	bool has_loop() const;

	void set_loop_offset(float p_seconds);
	float get_loop_offset() const;

	virtual Ref<AudioStreamPlayback> instance_playback() override;
	virtual String get_stream_name() const override;

	void set_data(const PoolVector<uint8_t> &p_data);
	PoolVector<uint8_t> get_data() const;

	virtual float get_length() const override; //if supported, otherwise return 0

	AudioStreamFLAC();
	virtual ~AudioStreamFLAC();
};

#endif
