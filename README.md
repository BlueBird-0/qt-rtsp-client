## Preview
![simplescreenrecorder-2024-12-25_03(1)](https://github.com/user-attachments/assets/ff05e43f-a83b-4012-84a6-560e92813e83)

Video Streaming Client Example
VMMV 구조를 따르는 Qt Client 예시 프로그램 입니다.
내부적으로 RTSP를 사용합니다. 따라서 영상을 전송하는 RTSP server가 필요합니다.

[RTSPserver on Linux](https://github.com/rtspMediaStream/raspberrypi5-rtsp-server)

## License
이 프로젝트는 MIT License를 따릅니다. 수정/배포 를 환영합니다.

## QMake Install
```bash
clone (https://github.com/BlueBird-0/qt-rtsp-client)
cd qt-rtsp-client
qmake
make
./qt-rtsp-client
```
