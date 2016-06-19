#include <stdio.h>
#include "decoder.h"

int main()
{
	//初始化并分配帧
	AVFormatContext *fmt_ctx = NULL;
	AVCodecContext *dec_ctx = NULL;	
	AVFrame *pf=av_frame_alloc();
	AVFrame *pfc = av_frame_alloc();
	int video_stream_index;
	int width, height;
	av_register_all();

	//读取视频，解复用
	video_stream_index=getStream(&fmt_ctx, &dec_ctx, "test.mp4");
	
	//解码并保存关键帧数据为bmp图片输出
	decoder(&fmt_ctx, &dec_ctx, video_stream_index,pf, pfc, &width,&height);
	
}

