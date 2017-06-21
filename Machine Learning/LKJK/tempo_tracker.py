import sys
from aubio import tempo, source

win_s = 512                 # fft size
hop_s = win_s // 2          # hop size

if len(sys.argv) < 2:
    print("템포테스트, %s <filename> [samplerate]" % sys.argv[0])
    sys.exit(1)

filename = sys.argv[1]

samplerate = 0
if len( sys.argv ) > 2: samplerate = int(sys.argv[2])

s = source(filename, samplerate, hop_s)
samplerate = s.samplerate
o = tempo("default", win_s, hop_s, samplerate) #bpm에서 설정한 default값 이용.

# 샘플링값 따라 조정
# dafault값은 4, 블록 조정 단위라 바꿀 필요 x
delay = 4. * hop_s

# bpm과 같음
beats = []

# 프레임 리딩.
total_frames = 0
while True:
    samples, read = s()
    is_beat = o(samples)
    if is_beat:
        this_beat = int(total_frames - delay + is_beat[0] * hop_s) #5월 19일 수정.
        print("%f" % (this_beat / float(samplerate)))
        beats.append(this_beat)
    total_frames += read
    if read < hop_s: break
#print len(beats)