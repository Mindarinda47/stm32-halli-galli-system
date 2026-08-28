# Preserved Modules

현재 보존된 두 C 파일을 프로젝트의 대표 부분 코드로 포함합니다.
두 파일은 각각 독립 `main()`을 가진 실험 코드이며 최종 통합본은 아닙니다.

## 포함 코드

- [`ultrasonic_sensor_original.c`](ultrasonic_sensor_original.c): HC-SR04 Trigger/Echo와
  TIM2 counter를 사용한 거리 측정 실험
- [`touch_sensor_original.c`](touch_sensor_original.c): 터치 입력에 따른 GPIO 출력 실험

원본 제어 흐름은 수정하지 않았고 개인정보·공개 검토를 위해 원본 주석만 제거했습니다.
파일 상단에도 이 사실을 표시했습니다.

## 공개 범위

- 두 파일은 서로 독립된 센서 실험이며 대표 부분 코드로만 제시합니다.
- STM32 library, startup code와 IDE 설정은 vendor 배포물 복제를 피하기 위해 포함하지 않습니다.
- 원본 제어 흐름과 확인된 기술 항목은 [`../../docs/PROBLEM_SOLVING.md`](../../docs/PROBLEM_SOLVING.md)에 기록합니다.
