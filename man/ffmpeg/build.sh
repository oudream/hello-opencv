#!/usr/bin/env bash

# https://github.com/FFmpeg/FFmpeg
# https://trac.ffmpeg.org/wiki/CompilationGuide
# https://trac.ffmpeg.org/wiki/CompilationGuide/macOS
# https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
# https://ffmpeg.org/ffmpeg.html
# https://ffmpeg.org/ffplay.html
# https://ffmpeg.org/ffprobe.html


### ffmpeg v4.2.2(192d1d3)
## 注意注意注意：默认编译出来的是静态库，在MacOs上测试的结果。所以要带上： --enable-shared
# https://trac.ffmpeg.org/wiki/CompilationGuide/macOS
# https://www.jianshu.com/p/99f870e8531d
# https://trac.ffmpeg.org/ticket/2659
git clone https://git.ffmpeg.org/ffmpeg.git ffmpeg
cd ffmpeg
git reset --hard 192d1d3
#./configure  --prefix=/usr/local --enable-gpl --enable-nonfree --enable-libass \
#--enable-libfdk-aac --enable-libfreetype --enable-libmp3lame \
#--enable-libtheora --enable-libvorbis --enable-libvpx --enable-libx264 --enable-libx265 --enable-libopus --enable-libxvid \
#--samples=fate-suite/
./configure --cc="clang" --enable-shared
make
#sudo make install
make install


# doc example ffpreset
/usr/local/share/ffmpeg
# lib
rm /usr/local/lib/libavutil.a
rm /usr/local/lib/libswscale.a
rm /usr/local/lib/libswresample.a
rm /usr/local/lib/libavcodec.a
rm /usr/local/lib/libavformat.a
rm /usr/local/lib/libavfilter.a
rm /usr/local/lib/libavdevice.a
# include
/usr/local/include/libavutil/
/usr/local/include/libswscale/
/usr/local/include/libswresample/
/usr/local/include/libavcodec/
/usr/local/include/libavformat/
/usr/local/include/libavfilter/
/usr/local/include/libavdevice/
# bin
/usr/local/bin/ffmpeg
/usr/local/bin/ffplay
/usr/local/bin/ffprobe
# /usr/local/lib/pkgconfig
/usr/local/lib/pkgconfig/libavutil.pc
/usr/local/lib/pkgconfig/libswscale.pc
/usr/local/lib/pkgconfig/libswresample.pc
/usr/local/lib/pkgconfig/libavcodec.pc
/usr/local/lib/pkgconfig/libavformat.pc
/usr/local/lib/pkgconfig/libavfilter.pc
/usr/local/lib/pkgconfig/libavdevice.pc