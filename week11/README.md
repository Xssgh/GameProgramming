
# Unreal Engine 5 Beginner Guide Summary (EP1~EP5)
**Source:** Unreal Engine 5 Beginner Tutorial Guide :contentReference[oaicite:0]{index=0}  

---

## EP1. 언리얼 엔진 설치 및 실행
### 1. 설치 과정
- Epic Games Launcher 다운로드 및 로그인
- Launcher → Unreal Engine 메뉴 → Library에서 엔진 버전 선택 후 Install
- 설치 옵션에서 필요한 구성 요소 선택 가능

### 2. 런처 기능
- Library 탭에서 설치된 UE 버전 확인
- My Projects 영역에서 기존 프로젝트 확인(기본 저장 경로 외의 위치는 자동 인식 안 됨)

### 3. 엔진 실행 & 새 프로젝트 생성
- Launch 버튼 클릭 → Project Browser 실행
- GAMES 카테고리 선택 후 템플릿 선택(1인칭/3인칭/탑다운 등)
- 프로젝트 이름 및 설정 후 생성

---

## EP2. 프로젝트 생성과 기본 화면 구성
### 1. 템플릿 생성
- Third Person 템플릿 예시
- UE4/UE5 레이아웃 선택 가능

### 2. 언리얼 기본 UI 구성
- **Viewport:** 월드 배치 및 카메라 시점 확인
- **Toolbar/Menu:** 프로젝트 실행, 세팅
- **Outliner:** 씬의 액터 계층 구조
- **Details:** 액터 상세 속성
- **Content Browser:** 리소스 관리
- **Actor Placement:** 기본 오브젝트 배치

### 3. 기본 조작
- WASD + 마우스 우클릭: 카메라 이동
- Q/W/E/R: 선택, 이동, 회전, 스케일
- 스냅, 카메라 속도 조절 가능

### 4. 레벨 생성 & 환경 조성
- Content Browser → 폴더 생성 → Level 생성
- 환경 라이트 믹서 또는 Actor 배치로 Sky, Light, Fog 구성

---

## EP3. 블루프린트 기초
### 1. 블루프린트 종류
- **레벨 블루프린트:** 특정 레벨에 종속
- **일반 블루프린트(Actor):** 재사용 가능한 스크립트/오브젝트

### 2. 블루프린트 UI 구성
- State Panel(함수/변수)
- Event Graph(로직 구성)
- Details Panel(속성 조정)

### 3. Enhanced Input 기반 키 입력 처리
- Input Action 생성 → IMC(Default)에 슬롯 추가
- Event Graph에서 Print String 등으로 반응 구현

### 4. Third Person 템플릿 동작 분석
- 이동: 축 값 기반 Add Movement Input
- 카메라: 마우스 입력을 카메라 회전에 연결
- 점프: IA_Jump 입력 기반

### 5. 플레이어 설정
- Pawn 블루프린트 생성 시:
  - Auto Possess Player = Player 0
  - AI Controller 비활성화

---

## EP4. C++ 개발 기초
### 1. Visual Studio 환경 구축
- Visual Studio Installer → "C++을 사용한 게임 개발" 워크로드 설치
- UE5 → Tools → Visual Studio 열기

### 2. C++ 기본 Actor 분석
- **Header 구조**
  - CoreMinimal.h
  - Actor.h
  - ClassName.generated.h (항상 마지막)
- **주요 함수**
  - BeginPlay()
  - Tick()

### 3. Actor 클래스에 Print 기능 구현 예시
- GEngine → AddOnScreenDebugMessage 사용
- C++ 클래스 기반 블루프린트 생성 후 월드에 배치

### 4. Visual Studio 연동 오류 해결
- 빌드 크래시 발생 시 프로젝트 C++ Save 파일 제거 후 UE/VS 재시작

---

## EP5. 샘플 & 애셋 사용법
### 1. 샘플 프로젝트 가져오기
- Launcher → 샘플 → 콘텐츠 예제 선택 → 라이브러리 추가 → 프로젝트 생성

### 2. Fab(구 Marketplace) 애셋 사용
- Fab → 모든 애셋 → 무료 필터
- 애셋 다운로드 후 특정 프로젝트에 추가
- Content Browser에서 폴더 형태로 생성됨

### 3. 연습: 애셋으로 레벨 꾸미기
- 가져온 모델/머티리얼을 배치하여 환경 구성 가능

---

## SUMMARY
EP1~EP5는 초보자가 언리얼 엔진을 설치하고, 프로젝트를 만들고, 블루프린트·C++ 기본 구성요소를 이해하며, 외부 애셋을 활용해 레벨 제작까지 진행할 수 있도록 구성된 입문 가이드이다. 설치–UI–스크립트–C++–애셋 pipeline 전체를 빠르게 익히는 데 최적화된 흐름을 제공한다.

