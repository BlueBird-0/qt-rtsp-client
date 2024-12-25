## Preview
Video Streaming Client Example
이 프로그램은 VMMV 구조를 따르는 Qt Client 예시 프로그램 입니다.
![simplescreenrecorder-2024-12-25_03(1)](https://github.com/user-attachments/assets/ff05e43f-a83b-4012-84a6-560e92813e83)

내부적으로 RTSP를 사용합니다. 따라서 영상을 전송하는 RTSP server가 필요합니다. [RTSPserver on Linux](https://github.com/rtspMediaStream/raspberrypi5-rtsp-server)

### Login Dialog & Viewer
<div style="display: flex; justify-content: space-between; align-items: flex-start;">
    <img src="https://github.com/user-attachments/assets/1f2cc203-dd36-4529-9a11-62baa657876a" alt="login1" style="height: 300px; width: auto; object-fit: contain;">
    <img src="https://github.com/user-attachments/assets/43ca6966-c8fb-4bf9-b57d-e090ea90d878" alt="rtspView" style="height: 300px; width: auto; object-fit: contain;">
</div>

## VMMV struct Class Diagram
![PrivateTech drawio](https://github.com/user-attachments/assets/8a2a63cf-d102-4ad6-bbbe-f28f3b2d9257)



## QMake Install
```bash
clone (https://github.com/BlueBird-0/qt-rtsp-client)
cd qt-rtsp-client
qmake
make
./qt-rtsp-client
```
## License
이 프로젝트는 MIT License를 따릅니다. 수정/배포 를 환영합니다.
