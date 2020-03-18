#!/usr/bin/env bash

# 1) 播放 test.mp4 ，播放完成后自动退出
ffplay -autoexit test.mp4
# 2) 以 320 x 240 的大小播放 test.mp4
ffplay -x 320 -y 240 test.mp4
# 3) 将窗口标题设置为 "myplayer"，循环播放 2 次
ffplay -window_title myplayer -loop 2 test.mp4
# 4) 以s16le格式播放 双通道 32K 的 PCM 音频数据
ffplay -f s16le -ar 32000 -ac 2 test.pcm


# ffpeobe查看一个视频的文件
ffprobe ~/a.mp4
# 键入上述命令之后，可以看到第一部分的信息是Metadata信息:
#    Metadata:
#            major_brand: jsom
#            minor_version: 512
#            compatible_brands: isomiso2avc1mp41
#            encoder: Lavf55.12.100
# 这行信息表明了该文件的Metadata信息，比如encoder是Lavf55.12.100，其中Lavf代表的是FFmpeg输出的文件，
# 后面的编号代表了FFmpeg的版本代号，接下来的一行信息如下：
#    Duration: 00:04:34.560 start: 0.023220, bitrate: 577kb/s
# 上面的一行的内容表示Duration是4分34秒560毫秒，开始播放的时间是从23ms开始播放的，整个文件的比特率是577Kbit/s，
# 紧接着再来看下一行：
#    Stream#0:0 (un): Video:h264 (avc1/0x31637661), yuv420p, 480*480, 508kb/s, 24fps
# 这行信息表示第一个stream是视频流，编码方式是H264的格式（封装格式是AVC1），每一帧的数据表示是YUV420P的格式，
# 分辨率是480*480，这路流的比特率是508Kbit/s，帧率是每秒钟24帧，紧接着再来看下一行：
#    Stream#0:1 (und):Audio: aac(LC)(mp4a/0x6134706D), 44100Hz, stereo, fltp, 63kb/s
# 这行信息表示第二个stream是音频流，编码方式是AAC（封装格式是MP4A），并且采用的Profile是LC规格，采样率是44100Hz，
# 声道数是立体声，数据表示格式是浮点型，这路音频流的比特率是63Kbit/s。
#    tbn= the time base in AVStream that has come from the container
#    tbc= the time base in AVCodecContext for the codec used for a particular stream
#    tbr= tbr is guessed from the video stream and is the value users want to see when they look for the video frame rate
#    25  tbr代表帧率；
#    12800 tbn代表文件层（st）的时间精度，即1S=12800，和duration相关；
#    50   tbc代表视频层（st->codec）的时间精度，即1S=50，和strem->duration和时间戳相关。


# download ffmpeg-20190826-0821bc4-win64-static.zip
# https://ffmpeg.zeranoe.com/builds/win64/static/
# rtsp ws
node ./jsmpeg/websocket-relay.js supersecret 8081 8082
# rtsp convert to mp2
# rtsp info : ffprobe.exe rtsp://admin:12345@10.31.16.210/h264/ch1/sub/av_stream
ffmpeg -i rtsp://admin:12345@10.31.16.210/h264/ch1/sub/av_stream -f mpegts -codec:v mpeg1video -s 352x288 -b:v 1000k -bf 0 http://localhost:8081/supersecret



# https://wklchris.github.io/FFmpeg.html
### 截图命令
# 截取一张352x240尺寸大小，格式为jpg的图片
ffmpeg -i input_file -y -f image2 -t 0.001 -s 352x240 output.jpg
# 把视频的前30帧转换成一个Animated Gif
ffmpeg -i input_file -vframes 30 -y -f gif output.gif
# 在视频的第8.01秒出截取230x240的缩略图
ffmpeg -i input_file -y -f mjpeg -ss 8 -t 0.001 -s 320x240 output.jpg
# 每隔一秒截一张图
ffmpeg -i out.mp4 -f image2 -vf fps=fps=1 out%d.png
# 每隔20秒截一张图
ffmpeg -i out.mp4 -f image2 -vf fps=fps=1/20 out%d.png
# 多张截图合并到一个文件里（2x3）每隔一千帧(秒数=1000/fps25)即40s截一张图
ffmpeg -i out.mp4 -frames 3 -vf "select=not(mod(n\,1000)),scale=320:240,tile=2x3" out.png
# 从视频中生成GIF图片
ffmpeg -i out.mp4 -t 10 -pix_fmt rgb24 out.gif
# 转换视频为图片（每帧一张图）
ffmpeg -i out.mp4 out%4d.png
# 图片转换为视频
ffmpeg -f image2 -i out%4d.png -r 25 video.mp4
# 切分视频并生成M3U8文件
ffmpeg -i input.mp4 -c:v libx264 -c:a aac -strict -2 -f hls -hls_time 20 -hls_list_size 0 -hls_wrap 0 output.m3u8



### 合并视频
# 方案-：将这几个视频放在一个新文件夹内，Shift 右键运行 cmd，输入（注意：如果要保存为批处理文件，
# 请循环变量的双写百分号。）：
(for %i in (*.flv) do @echo file '%i') > mylist.txt
ffmpeg -f concat -i mylist.txt -c copy output.flv
# 方案二：先将这几个视频无损地转为 mpegts 文件，再通过 concat 协议合并。以常见的 H.264 视频与 aac 音频为例：
ffmpeg -i "1.flv" -c copy -bsf:v h264_mp4toannexb -f mpegts 1.ts
ffmpeg -i "2.flv" -c copy -bsf:v h264_mp4toannexb -f mpegts 2.ts
ffmpeg -i "concat:1.ts|2.ts" -c copy -bsf:a aac_adtstoasc "All.mp4"

### 分割视频
#指定视频的起始与持续时长就可以分割视频了。下例截取了视频的前 5 秒（00:05:00），
# 注意-t后接“截取视频段长度”而不是“截取终点时刻”：
ffmpeg -i "input.mp4" -ss 00:00:00 -t 5 -c copy "output.mp4"

### 批量格式转换
# 比如，对于数据流用 mpeg 编码的一个 flv 文件，可以这样转为 mp4 文件：
ffmpeg -i "input.flv" -c copy "output.mp4"
# 因此一个批量转换也很容易通过 for 语句实现（%~n 表示保留不含扩展名的文件名）：
for %i in (*.mp4) do ffmpeg -i "%i" -c copy "%~ni.flv"

### 截图
# 静态图水印
# 下例添加 png 或其他静态格式的水印，放置在距左侧 20 像素,距顶端 40 像素的地方。水印与视频的基准点都是左上角点。
ffmpeg -i input.mp4 -i wm.png -filter_complex "overlay=20:40" output.mp4
# 如果要放在右下角使用overlay= main_w-overlay_w:main_h-overlay_h，参数的含义应该较好理解。
# 如果要指定水印的大小，比如 384x216：
ffmpeg -i input.mp4 -i wm.png -filter_complex "[1:v]scale=384:216[wm];[0:v][wm]overlay=0:0" output.mp4
# 参数 0:v 表示第1个输入的视频流（本例即input.mp4的视频流），1:v 表示第2个输入的视频流（本例即wm.gif）。
# 分号前的[wm]用于引用。
#GIF 水印
# 添加 gif 水印与静态图水印有一些不同之处：
# 需要将 ignore_loop 参数指明为 0，表示 gif 无限循环。
# 需要用到复合过滤器 filter_complex。
# 需要过滤器的 shortest=1 选项，表示至少在一个视频流循环一次后，再终止输出。如果不加该选项，输出将无法自行停止。
# 一个指定 50x50 大小 GIF 水印在左上角的例子：
ffmpeg -y -i input.mp4 -ignore_loop 0 -i wm.gif -filter_complex "[1:v]scale=50:50[wm];[0:v][wm]overlay=0:0:shortest=1" output.mp4

### 外挂字幕
# 将字幕作为单独的数据流（而不是混入视频流中），封装到容器内。一般对此特性有良好支持的容器是 mkv。在封装时，一般需要转为 ass 格式。
ffmpeg -i input.mp4 -i input.srt -c:v copy -c:a copy -c:s ass output.mkv
# 一些注意点：
# 字幕文件请用 UTF-8 编码。
# Windows 系统缺少一个字体接口，因此需要自己配置 fonts.conf 文件，放在 %FONTCONFIG_PATH% 这个环境用户变量里（往往需要你自己新建）。
# 该变量应该指向C:\Users\用户名\。
# 网上流传了一份 fonts.conf 文件内容（见附录），请复制后粘贴到你对应文件夹的 fonts.conf 文件中。

### 内嵌字幕
# 在播放器不支持独立字幕流的场合，需要将字幕混入视频流中（因此需要重编码）。
ffmpeg -i input.mp4 -vf subtitles=input.srt output.mp4
# 如果字幕以字幕流的形式位于一个视频文件中，可以直接调用：
ffmpeg -i input.mkv -vf subtitles=input.mkv output.mp4
# 同样，Windows 用户需要配置 fonts.conf 文件。



ffmpeg [options] [[infile options] -i infile]... {[outfile options] outfile}...

    # Getting help:
    #    -h      -- print basic options
    #    -h long -- print more options
    #    -h full -- print all options (including all format and codec specific options, very long)
    #    -h type=name -- print all options for the named decoder/encoder/demuxer/muxer/filter/bsf
    #    See man ffmpeg for detailed description of the options.
    #
    # Print help / information / capabilities:
    -L                  # show license
    -h topic            # show help
    -? topic            # show help
    -help topic         # show help
    --help topic        # show help
    -version            # show version
    -buildconf          # show build configuration
    -formats            # show available formats
    -muxers             # show available muxers
    -demuxers           # show available demuxers
    -devices            # show available devices
    -codecs             # show available codecs
    -decoders           # show available decoders
    -encoders           # show available encoders
    -bsfs               # show available bit stream filters
    -protocols          # show available protocols
    -filters            # show available filters
    -pix_fmts           # show available pixel formats
    -layouts            # show standard channel layouts
    -sample_fmts        # show available audio sample formats
    -colors             # show available color names
    -sources device     # list sources of the input device
    -sinks device       # list sinks of the output device
    -hwaccels           # show available HW acceleration methods
    
## Global options (affect whole program instead of just one file:
    -loglevel loglevel  # set logging level
    -v loglevel         # set logging level
    -report             # generate a report
    -max_alloc bytes    # set maximum size of a single allocated block
    -y                  # overwrite output files
    -n                  # never overwrite output files
    -ignore_unknown     # Ignore unknown stream types
    -filter_threads     # number of non-complex filter threads
    -filter_complex_threads  # number of threads for -filter_complex
    -stats              # print progress report during encoding
    -max_error_rate # maximum error rate  ratio of errors (0.0: no errors, 1.0: 100% errors) above which ffmpeg returns an error instead of success.
    -bits_per_raw_sample # number  set the number of bits per raw sample
    -vol volume         # change audio volume (256=normal)
    
## Per-file main options:
    -f fmt              # force format
    -c codec            # codec name
    -codec codec        # codec name
    -pre preset         # preset name
    -map_metadata outfile[,metadata]:infile[,metadata]  # set metadata information of outfile from infile
    -t duration         # record or transcode "duration" seconds of audio/video
    -to time_stop       # record or transcode stop time
    -fs limit_size      # set the limit file size in bytes
    -ss time_off        # set the start time offset
    -sseof time_off     # set the start time offset relative to EOF
    -seek_timestamp     # enable/disable seeking by timestamp with -ss
    -timestamp time     # set the recording timestamp ('now' to set the current time)
    -metadata string=string  # add metadata
    -program title=string:st=number...  # add program with specified streams
    -target type        # specify target file type ("vcd", "svcd", "dvd", "dv" or "dv50" with optional prefixes "pal-", "ntsc-" or "film-")
    -apad               # audio pad
    -frames number      # set the number of frames to output
    -filter filter_graph  # set stream filtergraph
    -filter_script filename  # read stream filtergraph description from a file
    -reinit_filter      # reinit filtergraph on input parameter changes
    -discard            # discard
    -disposition        # disposition
    
## Video options:
    -vframes number     # set the number of video frames to output
    -r rate             # set frame rate (Hz value, fraction or abbreviation)
    -s size             # set frame size (WxH or abbreviation)
    -aspect aspect      # set aspect ratio (4:3, 16:9 or 1.3333, 1.7777)
    -bits_per_raw_sample number  # set the number of bits per raw sample
    -vn                 # disable video
    -vcodec codec       # force video codec ('copy' to copy stream)
    -timecode hh:mm:ss[:;.]ff  # set initial TimeCode value.
    -pass n             # select the pass number (1 to 3)
    -vf filter_graph    # set video filters
    -ab bitrate         # audio bitrate (please use -b:a)
    -b bitrate          # video bitrate (please use -b:v)
    -dn                 # disable data
    
## Audio options:
    -aframes number     # set the number of audio frames to output
    -aq quality         # set audio quality (codec-specific)
    -ar rate            # set audio sampling rate (in Hz)
    -ac channels        # set number of audio channels
    -an                 # disable audio
    -acodec codec       # force audio codec ('copy' to copy stream)
    -vol volume         # change audio volume (256=normal)
    -af filter_graph    # set audio filters
    
## Subtitle options:
    -s size             # set frame size (WxH or abbreviation)
    -sn                 # disable subtitle
    -scodec codec       # force subtitle codec ('copy' to copy stream)
    -stag fourcc/tag    # force subtitle tag/fourcc
    -fix_sub_duration   # fix subtitles duration
    -canvas_size size   # set canvas size (WxH or abbreviation)
    -spre preset        # set the subtitle options to the indicated preset
