# multimedia
基于给定的视频序列（如：xvid编码、AVI容器），借助FFmpeg库进行关键帧提取。采用FFmpeg/libavformat进行读取和解复用；采用FFmpeg/libavcodec进行视频数据的解码；并将解码后的关键帧数据转化为位图格式（BMP）保存；
