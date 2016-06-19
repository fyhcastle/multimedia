#ifdef __cplusplus
extern "C"
{
#endif
	#include <libavcodec/avcodec.h> 
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
	#include <libavutil/opt.h>
	#include <libavutil/mathematics.h>
	#include <libavutil/samplefmt.h>
#ifdef __cplusplus
}
#endif

int getStream(AVFormatContext **fmt_ctx, AVCodecContext **dec_ctx, char* file_name) {
	int video_stream_index = -1;
	int ret;
	bool decoder_init = false;

	//打开视频文件
	if ((ret = avformat_open_input(fmt_ctx, file_name, NULL, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "fail to open input file.\n");
		return ret;
	}

	//获取流信息
	if ((ret = avformat_find_stream_info(*fmt_ctx, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "fail to find stream information.\n");
		avformat_close_input(fmt_ctx);
		return ret;
	}
	
	//从多个流中寻找视频流
	for (int i = 0; i < (*fmt_ctx)->nb_streams; i++) {
		if ((*fmt_ctx)->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			video_stream_index = i;

			//进行解码器的初始化
			if (!decoder_init) {
				*dec_ctx = (*fmt_ctx)->streams[i]->codec;

				AVCodec *cod = avcodec_find_decoder((*dec_ctx)->codec_id);

				if (!cod) {
					av_log(NULL, AV_LOG_ERROR, "fail to find decoder.\n");
					avformat_close_input(fmt_ctx);
					return 1;
				}
				if (avcodec_open2(*dec_ctx, cod, NULL) != 0) {
					av_log(NULL, AV_LOG_ERROR, "fail to open codecer.\n");
					avformat_close_input(fmt_ctx);
					return 2;
				}
				decoder_init = true;
				
			}
		}
		return 0;
	}
	
	return video_stream_index;
}