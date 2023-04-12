#ifndef AUDIO_STREAM_FLAC_H
#define AUDIO_STREAM_FLAC_H

#include "scene/resources/texture.h"
#include "core/io/resource_loader.h"
#include "servers/audio/audio_stream.h"
#include "thirdparty/dr_flac/dr_flac.h"

class AudioStreamFLAC;

class AudioStreamPlaybackFLAC : public AudioStreamPlaybackResampled {
	GDCLASS(AudioStreamPlaybackFLAC, AudioStreamPlaybackResampled);

	enum {
		FADE_SIZE = 256
	};
	AudioFrame loop_fade[FADE_SIZE];
	int loop_fade_remaining = FADE_SIZE;

	drflac *pFlac = nullptr;
	uint32_t frames_mixed = 0;
	bool active = false;
	int loops = 0;

	friend class AudioStreamFLAC;

	Ref<AudioStreamFLAC> flac_stream;

	//void populate_first_frame(int, mp3dec_frame_info_t *);

protected:
	virtual int _mix_internal(AudioFrame *p_buffer, int p_frames) override;
	virtual float get_stream_sampling_rate() override;

public:
	virtual void start(double p_from_pos = 0.0) override;
	virtual void stop() override;
	virtual bool is_playing() const override;

	virtual int get_loop_count() const override; //times it looped

	virtual double get_playback_position() const override;
	virtual void seek(double p_time) override;

	virtual void tag_used_streams() override;

	AudioStreamPlaybackFLAC() {}
	~AudioStreamPlaybackFLAC();
};

class AudioStreamFLAC : public AudioStream {

	GDCLASS(AudioStreamFLAC, AudioStream);
	OBJ_SAVE_TYPE(AudioStream) //children are all saved as AudioStream, so they can be exchanged
	RES_BASE_EXTENSION("flacstr");

	friend class AudioStreamPlaybackFLAC;

	PackedByteArray data;
	uint32_t data_len = 0;

	float sample_rate = 1.0;
	int channels = 1;
	float length = 0.0;
	bool loop = false;
	float loop_offset = 0.0;
	void clear_data();

	double bpm = 0;
	int beat_count = 0;
	int bar_beats = 4;

protected:
	static void _bind_methods();

public:
	void set_loop(bool p_enable);
	virtual bool has_loop() const override;

	void set_loop_offset(double p_seconds);
	double get_loop_offset() const;

	void set_bpm(double p_bpm);
	virtual double get_bpm() const override;

	void set_beat_count(int p_beat_count);
	virtual int get_beat_count() const override;

	void set_bar_beats(int p_bar_beats);
	virtual int get_bar_beats() const override;

	virtual Ref<AudioStreamPlayback> instantiate_playback() override;
	virtual String get_stream_name() const override;

	void set_data(const Vector<uint8_t> &p_data);
	Vector<uint8_t> get_data() const;

	virtual double get_length() const override; //if supported, otherwise return 0

	virtual bool is_monophonic() const override;

	AudioStreamFLAC();
	virtual ~AudioStreamFLAC();
};

#endif
