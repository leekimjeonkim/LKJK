#numpy, aubio 임포트 후 환경설정 해주어야함.
#가상환경 맞춰줄 것.
from aubio import source, tempo
from numpy import median, diff

def get_file_bpm(path, params = None):
    
       # path: 실행환경, vm에선 assets에 넣어놓을 것.
        #param: 파라미터 실행범위
    
    if params is None:
        params = {}
    try:
        win_s = params['win_s']
        samplerate = params['samplerate']
        hop_s = params['hop_s']
    except KeyError:
        """
        # super fast , 비트레이트 부분으로
        samplerate, win_s, hop_s = 4000, 128, 64 
        # fast
        samplerate, win_s, hop_s = 8000, 512, 128
        """
        # default, mp3파일 bitrate에 맞춰서, 변경 시 overflow 뿜음.
        samplerate, win_s, hop_s = 44100, 1024, 512

    s = source(path, samplerate, hop_s)
    samplerate = s.samplerate
    o = tempo("specdiff", win_s, hop_s, samplerate) #specdiff옵션으로 검출
    # 비트 범위 선정
    beats = []
    # 프레임 설정 부
    total_frames = 0

    while True:
        samples, read = s()
        is_beat = o(samples)
        if is_beat:
            this_beat = o.get_last_s()
            beats.append(this_beat)
            #if o.get_confidence() > .2 and len(beats) > 2.:
            #    break
            #프레임이 너무 많아져서 4분이상의 경우엔 짤라줘야함
        total_frames += read
        if read < hop_s:
            break

    # 박자 변환 부
    if len(beats) > 1:
        if len(beats) < 4:
            print("길이가 너무 짧다.{:s}".format(path))
        bpms = 60./diff(beats)
        b = median(bpms)
    else:
        b = 0
        print("길이가 너무 부족하다.{:s}".format(path))
    return b

if __name__ == '__main__':
    import sys
    for f in sys.argv[1:]:
        bpm = get_file_bpm(f)
        print("{:6s} {:s}".format("{:2f}".format(bpm), f))